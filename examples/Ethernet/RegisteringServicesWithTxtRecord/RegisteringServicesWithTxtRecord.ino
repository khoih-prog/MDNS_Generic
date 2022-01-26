/****************************************************************************************************************************
  RegisteringServicesWithTxtRecord.ino

  mDNS library to support mDNS (registering services) and DNS-SD (service discovery).

  Based on and modified from https://github.com/arduino-libraries/ArduinoMDNS
  Built by Khoi Hoang https://github.com/khoih-prog/MDNS_Generic
  Licensed under MIT license

  Original Author: Georg Kaindl (http://gkaindl.com)

  This file is part of Arduino EthernetBonjour.

  EthernetBonjour is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
  as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

  EthernetBonjour is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with EthernetBonjour.
  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************************************************************/
//  Illustrates how to register a service with a TXT record.

#include "defines.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <MDNS_Generic.h>

EthernetUDP udp;
MDNS mdns(udp);

#define HTTP_PORT      80

EthernetServer server(HTTP_PORT);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart RegisteringServicesWithTxtRecord on "); Serial.print(BOARD_NAME);
  Serial.print(" using "); Serial.println(SHIELD_TYPE);
  Serial.println(MDNS_GENERIC_VERSION);

  Serial.println(("========================="));
  Serial.println(("Default SPI pinout:"));
  Serial.print("MOSI:");
  Serial.println(MOSI);
  Serial.print("MISO:");
  Serial.println(MISO);
  Serial.print("SCK:");
  Serial.println(SCK);
  Serial.print("SS:");
  Serial.println(SS);
  Serial.println(("========================="));

  // unknown board, do nothing, use default SS = 10
#ifndef USE_THIS_SS_PIN
  #define USE_THIS_SS_PIN   10    // For other boards
#endif

  MDNS_LOGERROR3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
  
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_ETHERNET3
    // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
  
    Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (ETHERNET3_MAX_SOCK_NUM);

  #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )

  // start the ethernet connection and the server:
  // Use Static IP
  //Ethernet.begin(mac, ip);
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  Ethernet.begin(mac[index]);

  // Just info to know how to connect correctly
  Serial.println("=========================");
  Serial.println("Currently Used SPI pinout:");
  Serial.print("MOSI:");
  Serial.println(MOSI);
  Serial.print("MISO:");
  Serial.println(MISO);
  Serial.print("SCK:");
  Serial.println(SCK);
  Serial.print("SS:");
  Serial.println(SS);
  Serial.println("=========================");

  Serial.print("Using mac index = ");
  Serial.println(index);

  Serial.print("Connected! IP address: ");
  Serial.println(Ethernet.localIP());

  delay(1000);
  

  // Initialize the mDNS library. You can now reach or ping this Arduino via the host name "arduino.local", provided that your operating
  // system is mDNS/Bonjour-enabled (such as MacOS X). Always call this before any other method!
  String hostname = String(BOARD_NAME) + "_" + String(index);
  
  //hostname.toUpperCase();
  hostname.toLowerCase();
  hostname.replace(" ",  "-");
  hostname.replace("_",  "-");
  
  Serial.print("Registering mDNS hostname: "); Serial.println(hostname);
  Serial.print("To access, using "); Serial.print(hostname); Serial.println(".local");

  mdns.begin(Ethernet.localIP(), hostname.c_str());

  // Now let's register the service we're offering (a web service) via mDNS! To do so, we call the addServiceRecord() method. The first argument is the
  // name of our service instance and its type, separated by a dot. In this case, the service type is _http. There are many other service types, use
  // google to look up some common ones, but you can also invent your own service type, like _mycoolservice - As long as your clients know what to
  // look for, you're good to go.
  // The second argument is the port on which the service is running. This is port 80 here, the standard HTTP port.
  // The last argument is the protocol type of the service, either TCP or UDP. Of course, our service is a TCP service.
  // With the service registered, it will show up in a Bonjour-enabled webbrowser. As an example, if you are using Apple's Safari, you will now see
  // the service under Bookmarks -> Bonjour (Provided that you have enabled Bonjour in the "Bookmarks" preferences in Safari).

  String mDNS_Service = String(BOARD_NAME) + "_mDNS_Webserver._http";
  
  Serial.println("AddService : " + mDNS_Service);

  mdns.addServiceRecord(mDNS_Service.c_str(), HTTP_PORT, MDNSServiceTCP);

  // Now we'll register a second service record: This time, we specify a TXT content as well, in order to point to a specific page on our server.
  // This is just an example to show that the mDNS library supports TXT records as well, but I won't go into detail about how they work. Check
  // out http://www.zeroconf.org/Rendezvous/txtrecords.html for an excellent primer.
  // What this does is that your browser will now show a second mDNS entry, which will take you to another page on the Arduino web server.

  String mDNS_Service_Page2 = String(BOARD_NAME) + "_mDNS_Webserver_Page2._http";
  
  Serial.println("AddService : " + mDNS_Service_Page2);
  
  mdns.addServiceRecord(mDNS_Service_Page2.c_str(), HTTP_PORT, MDNSServiceTCP, "\x7path=/2");
}

void loop()
{
  // This actually runs the mDNS module. YOU HAVE TO CALL THIS PERIODICALLY, OR NOTHING WILL WORK! Preferably, call it once per loop().
  mdns.run();

  // The code below is just taken from the "WebServer" example in the Ethernet library. The only difference here is that this web server gets announced
  // over Bonjour, but this happens in setup(). This just displays something in the browser when you connect.
  EthernetClient client = server.available();

  char lastLetter = '\0';
  char isPage2 = 0;

  if (client)
  {
    // an http request ends with a blank line
    bool current_line_is_blank = true;

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();

        if ('/' == lastLetter && '2' == c)
          isPage2 = 1;
          
        lastLetter = c;

        // if we've gotten to the end of the line (received a newline character) and the line is blank, 
        // the http request has ended, so we can send a reply
        if (c == '\n' && current_line_is_blank) 
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();

          if (isPage2) 
          {
            client.println("This is the second page advertised via Bonjour!");
          } 
          else 
          {
            client.println("Hello from mDNS-enabled web-server running on ");
            client.println(BOARD_NAME);
          }

          break;
        }
        
        if (c == '\n') 
        {
          // we're starting a new line
          current_line_is_blank = true;
        } 
        else if (c != '\r') 
        {
          // we've gotten a character on the current line
          current_line_is_blank = false;
        }
      }
    }
    
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}
