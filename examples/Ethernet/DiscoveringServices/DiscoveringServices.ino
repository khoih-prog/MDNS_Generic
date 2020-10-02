/****************************************************************************************************************************
  DiscoveringServices.ino
  
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
  
  Version: 1.0.1
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      01/08/2020 Initial coding to support W5x00 using Ethernet, EthernetLarge libraries
                                  Supported boards: nRF52, STM32, SAMD21/SAMD51, SAM DUE, Mega
  1.0.1   K Hoang      02/10/2020 Add support to W5x00 using Ethernet2, Ethernet3 libraries
 *****************************************************************************************************************************/
//

//  Illustrates how to discover Bonjour services on your network.

#include "defines.h"

#include <MDNS_Generic.h>

EthernetUDP udp;
MDNS mdns(udp);

void serviceFound(const char* type, MDNSServiceProtocol proto, const char* name, IPAddress ip, 
                  unsigned short port, const char* txtContent);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStarting DiscoveringServices on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));

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
  
  // Initialize the mDNS library. You can now reach or ping this
  // Arduino via the host name "arduino.local", provided that your operating
  // system is mDNS/Bonjour-enabled (such as MacOS X).
  // Always call this before any other method!
  String hostname = String(BOARD_NAME) + "_" + String(index);
  hostname.toLowerCase();
  hostname.replace(" ", "_");
  
  Serial.println("Register host name: " + hostname + ".local");

  mdns.begin(Ethernet.localIP(), hostname.c_str() /*"arduino"*/);

  // We specify the function that the mDNS library will call when it
  // discovers a service instance. In this case, we will call the function
  // named "serviceFound".
  mdns.setServiceFoundCallback(serviceFound);

  Serial.println("Enter a mDNS service name via Serial Monitor to discover instances on the network.");
  Serial.println("Examples are \"_http\", \"_afpovertcp\" or \"_ssh\" (Note the underscores).");
}

void loop()
{ 
  char serviceName[256];
  uint8_t length = 0;
  
  // read in a service name from the Arduino IDE's serial monitor.
  while (Serial.available()) 
  {
    serviceName[length] = Serial.read();
    length = (length+1) % 256;
    delay(5);
  }

  // Terminal adds "\r\n", need to remove
  if (length > 1)
    length = (length - 2) % 256;
    
  serviceName[length] = '\0';
  
  // You can use the "isDiscoveringService()" function to find out whether the Bonjour library is currently discovering service instances.
  // If so, we skip this input, since we want our previous request to continue.
  if (!mdns.isDiscoveringService()) 
  {
    if (length > 0) 
    {
      Serial.print("Discovering services of type '");
      Serial.print(serviceName);
      Serial.println("' via Multi-Cast DNS (Bonjour)...");

      // Now we tell the mDNS library to discover the service. Below, I have hardcoded the TCP protocol, but you can also specify to discover UDP services.
      // The last argument is a duration (in milliseconds) for which we will search (specify 0 to run the discovery indefinitely). Note that the library
      // will resend the discovery message every 10 seconds, so if you search for longer than that, you will receive duplicate instances.

      mdns.startDiscoveringService(serviceName, MDNSServiceTCP, 5000);
    }  
  }

  // This actually runs the Bonjour module. YOU HAVE TO CALL THIS PERIODICALLY,
  // OR NOTHING WILL WORK!
  // Preferably, call it once per loop().
  mdns.run();
}

// This function is called when a name is resolved via MDNS/Bonjour. We set this up in the setup() function above. The name you give to this callback
// function does not matter at all, but it must take exactly these arguments as below. If a service is discovered, name, ipAddr, port and (if available) 
// txtContent will be set. If your specified discovery timeout is reached, the function will be called with name (and all successive arguments) being set to NULL.
void serviceFound(const char* type, MDNSServiceProtocol /*proto*/, const char* name, IPAddress ip,
                  unsigned short port, const char* txtContent)
{
  if (NULL == name) 
  {
  	Serial.print("Finished discovering services of type ");
  	Serial.println(type);
  } 
  else 
  {
    Serial.print("Found: '");
    Serial.print(name);
    Serial.print("' at ");
    Serial.print(ip);
    Serial.print(", port ");
    Serial.print(port);
    Serial.println(" (TCP)");

    // Check out http://www.zeroconf.org/Rendezvous/txtrecords.html for a primer on the structure of TXT records. Note that the Bonjour
    // library will always return the txt content as a zero-terminated string, even if the specification does not require this.
    if (txtContent) 
    {
      Serial.print("\ttxt record: ");
      
      char buf[256];
      char len = *txtContent++;
      int i=0;
      
      while (len) 
      {
        i = 0;
        
        while (len--)
          buf[i++] = *txtContent++;
          
        buf[i] = '\0';
        
        Serial.print(buf);
        len = *txtContent++;
        
        if (len)
          Serial.print(", ");
        else
          Serial.println();
      }
    }
  }
}
