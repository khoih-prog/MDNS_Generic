/****************************************************************************************************************************
  WiFiRegisteringServicesWithTxtRecord.ino

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

  Version: 1.2.1
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      01/08/2020 Initial coding to support W5x00 using Ethernet, EthernetLarge libraries
                                  Supported boards: nRF52, STM32, SAMD21/SAMD51, SAM DUE, Mega
  1.0.1   K Hoang      02/10/2020 Add support to W5x00 using Ethernet2, Ethernet3 libraries
  1.1.0   K Hoang      12/06/2021 Add support to RP2040-based boards
  1.2.0   K Hoang      01/09/2021 Add support to generic boards using WiFi or WiFiNINA
  1.2.1   K Hoang      02/09/2021 Remove support to ESP8266 to use native ESP8266mDNS library
 *****************************************************************************************************************************/

//  Illustrates how to register a service with a TXT record.

#include "defines.h"
#include "arduino_secrets.h"

#if defined(ESP32)

  #define WIFI_NETWORK_WIFININA   false
  #define WIFI_NETWORK_WIFI101    false
  #define WIFI_NETWORK_ESPAT      false
  #define WIFI_NETWORK_ESP        true

  String hostname = "ESP_" + String(ESP_getChipId(), HEX);

#else

  // Select one to be true, but WIFI_NETWORK_ESP
  #define WIFI_NETWORK_WIFININA   true
  #define WIFI_NETWORK_WIFI101    false
  #define WIFI_NETWORK_ESPAT      false
  #define WIFI_NETWORK_ESP        false

  String hostname = BOARD_TYPE;

#endif

#if WIFI_NETWORK_WIFININA
  #include <SPI.h>
  #include <WiFiNINA_Generic.h>
  #include <WiFiUdp_Generic.h>
  #warning WIFI_NETWORK_TYPE == NETWORK_WIFININA
  WiFiUDP udp;
  WiFiServer server(80);

#elif WIFI_NETWORK_WIFI101
  #include <SPI.h>
  #include <WiFi101.h>
  #include <WiFiUdp.h>
  #warning WIFI_NETWORK_TYPE == NETWORK_WIFI101
  WiFiUDP udp;
  WiFiServer server(80);

#elif WIFI_NETWORK_ESPAT
  #include <WiFiEspAT.h>
  #include <WiFiUdp.h>
  #warning WIFI_NETWORK_TYPE == NETWORK_WIFI_ESPAT
  WiFiUDP udp;
  WiFiServer server(80);

#elif WIFI_NETWORK_ESP
  #include <WiFi.h>
  #include <WiFiUdp.h>
  
  #warning WIFI_NETWORK_TYPE == NETWORK_WIFI_ESP
  WiFiUDP udp;
  WiFiServer server(80);
  
#else
  #error You must select a WiFi network type
#endif

#include <MDNS_Generic.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP), length must be 8

int status = WL_IDLE_STATUS;     // the Wifi radio's status

MDNS mdns(udp);

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("Local IP address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart WiFiRegisteringServicesWithTxtRecord on "); Serial.println(BOARD_NAME);
  Serial.println(MDNS_GENERIC_VERSION);

#if ( WIFI_NETWORK_WIFININA || WIFI_NETWORK_WIFI101 )
  Serial.println("Used/default SPI pinout:");
  Serial.print("MOSI:");
  Serial.println(MOSI);
  Serial.print("MISO:");
  Serial.println(MISO);
  Serial.print("SCK:");
  Serial.println(SCK);
  Serial.print("SS:");
  Serial.println(SS);

  // check for the WiFi module:
#if WIFI_NETWORK_WIFININA
  if (WiFi.status() == WL_NO_MODULE)
#else
  if (WiFi.status() == WL_NO_SHIELD)
#endif
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

#if WIFI_NETWORK_WIFININA
  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the firmware");
  }
#endif

#endif

  Serial.print("Attempting to connect to SSID: "); Serial.println(ssid);
  
  WiFi.begin(ssid, pass);
  
  delay(1000);
  
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {    
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.status();

    delay(1000);
  }

  printWifiStatus();

  server.begin();

  hostname.toUpperCase();
  hostname.replace(" ",  "-");

  Serial.print("Registering mDNS hostname: "); Serial.println(hostname);
  Serial.print("To access, using "); Serial.print(hostname); Serial.println(".local");

  // Initialize the mDNS library. You can now reach or ping this
  // Arduino via the host name "hostname.local", provided that your operating
  // system is mDNS/Bonjour-enabled (such as MacOS X).
  // Always call this before any other method!
  mdns.begin(WiFi.localIP(), hostname.c_str());

  // Now let's register the service we're offering (a web service) via Bonjour!
  // To do so, we call the addServiceRecord() method. The first argument is the
  // name of our service instance and its type, separated by a dot. In this
  // case, the service type is _http. There are many other service types, use
  // google to look up some common ones, but you can also invent your own
  // service type, like _mycoolservice - As long as your clients know what to
  // look for, you're good to go.
  // The second argument is the port on which the service is running. This is
  // port 80 here, the standard HTTP port.
  // The last argument is the protocol type of the service, either TCP or UDP.
  // Of course, our service is a TCP service.
  // With the service registered, it will show up in a mDNA/Bonjour-enabled web
  // browser. As an example, if you are using Apple's Safari, you will now see
  // the service under Bookmarks -> Bonjour (Provided that you have enabled
  // Bonjour in the "Bookmarks" preferences in Safari).
  mdns.addServiceRecord("Arduino mDNS Webserver Example._http", 80, MDNSServiceTCP);

  // Now we'll register a second service record: This time, we specify a TXT
  // content as well, in order to point to a specific page on our server.
  // This is just an example to show that the mDNS library supports TXT
  // records as well, but I won't go into detail about how they work. Check
  // out http://www.zeroconf.org/Rendezvous/txtrecords.html for an excellent
  // primer.
  // What this does is that your browser will now show a second mDNS entry,
  // which will take you to another page on the Arduino web server.
  mdns.addServiceRecord("Arduino mDNS Webserver Example, Page 2._http", 80, MDNSServiceTCP, "\x7path=/2");
}

void loop()
{
  // This actually runs the mDNS module. YOU HAVE TO CALL THIS PERIODICALLY,
  // OR NOTHING WILL WORK! Preferably, call it once per loop().
  mdns.run();

  // The code below is just taken from the "WebServer" example in the Ethernet
  // library. The only difference here is that this web server gets announced
  // over mDNS, but this happens in setup(). This just displays something
  // in the browser when you connect.
  WiFiClient client = server.available();
  
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

        // if we've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so we can send a reply
        if (c == '\n' && current_line_is_blank)
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();

          if (isPage2)
          {
            client.println("This is the second page advertised via mDNS!");
          }
          else
          {
            client.println("Hello from a mDNS-enabled web-server running ");
            client.println("on your Arduino board!");
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
