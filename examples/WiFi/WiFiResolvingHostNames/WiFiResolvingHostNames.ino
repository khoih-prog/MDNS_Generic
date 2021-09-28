/****************************************************************************************************************************
  WiFiResolvingHostNames.ino

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

  Version: 1.3.0
  
  Version  Modified By   Date      Comments
  -------  -----------  ---------- -----------
  1.0.0    K Hoang      01/08/2020 Initial coding to support W5x00 using Ethernet, EthernetLarge libraries
                                  Supported boards: nRF52, STM32, SAMD21/SAMD51, SAM DUE, Mega
  1.0.1    K Hoang      02/10/2020 Add support to W5x00 using Ethernet2, Ethernet3 libraries
  1.1.0    K Hoang      12/06/2021 Add support to RP2040-based boards
  1.2.0    K Hoang      01/09/2021 Add support to generic boards using WiFi or WiFiNINA
  1.2.1    K Hoang      02/09/2021 Remove support to ESP8266 to use native ESP8266mDNS library
  1.3.0-b1 K Hoang      13/09/2021 Add support to Portenta_H7, using WiFi or Ethernet
  1.3.0    K Hoang      28/09/2021 Add support to Portenta_H7, using WiFi or Ethernet
 *****************************************************************************************************************************/

//  Illustrates how to resolve host names via MDNS (Multicast DNS)

#include "defines.h"
#include "arduino_secrets.h"

#if defined(ESP32)

  String hostname = "ESP_" + String(ESP_getChipId(), HEX);

#else
  #if !defined(WIFI_NETWORK_TYPE)
    // Select one, but WIFI_NETWORK_ESP
    #warning You have to select a WiFi Network here, or default will be used => possibly creating error.
    
    #define WIFI_NETWORK_TYPE           NETWORK_WIFI_DEFAULT
    //#define WIFI_NETWORK_TYPE           WIFI_NETWORK_WIFININA
    //#define WIFI_NETWORK_TYPE           WIFI_NETWORK_WIFI101
    //#define WIFI_NETWORK_TYPE           WIFI_NETWORK_ESPAT
    //#define WIFI_NETWORK_TYPE           WIFI_NETWORK_ESP
    //#define WIFI_NETWORK_TYPE           WIFI_NETWORK_PORTENTA_H7
  #endif

  String hostname = BOARD_TYPE;

#endif

#if (WIFI_NETWORK_TYPE == WIFI_NETWORK_WIFININA)
  #include <SPI.h>
  #include <WiFiNINA_Generic.h>
  #include <WiFiUdp_Generic.h>
  #warning WIFI_NETWORK_TYPE == NETWORK_WIFININA
  WiFiUDP udp;
  WiFiServer server(80);

#elif (WIFI_NETWORK_TYPE == WIFI_NETWORK_WIFI101)
  #include <SPI.h>
  #include <WiFi101.h>
  #include <WiFiUdp.h>
  #warning WIFI_NETWORK_TYPE == NETWORK_WIFI101
  WiFiUDP udp;
  WiFiServer server(80);

#elif (WIFI_NETWORK_TYPE == WIFI_NETWORK_ESPAT)
  #include <WiFiEspAT.h>
  #include <WiFiUdp.h>
  #warning WIFI_NETWORK_TYPE == NETWORK_WIFI_ESPAT
  WiFiUDP udp;
  WiFiServer server(80);

#elif (WIFI_NETWORK_TYPE == WIFI_NETWORK_ESP)
  #include <WiFi.h>
  #include <WiFiUdp.h>
  
  #warning WIFI_NETWORK_TYPE == NETWORK_WIFI_ESP
  WiFiUDP udp;
  WiFiServer server(80);

#elif (WIFI_NETWORK_TYPE == WIFI_NETWORK_PORTENTA_H7)
  #include <WiFi.h>
  #include <WiFiUdp.h>
  
  #warning WIFI_NETWORK_TYPE == NETWORK_WIFI_PORTENTA_H7
  WiFiUDP udp;
  WiFiServer server(80);

#elif (WIFI_NETWORK_TYPE == NETWORK_WIFI_DEFAULT)
  //#error You must select a WiFi network type
  #include <WiFi.h>
  #include <WiFiUdp.h>
  
  #warning WIFI_NETWORK_TYPE == NETWORK_WIFI_DEFAULT
  WiFiUDP udp;
  WiFiServer server(80);

#else

  #error You have to select an appropriate WiFi network type from the list
  
#endif

#include <MDNS_Generic.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP), length must be 8

int status = WL_IDLE_STATUS;     // the Wifi radio's status

MDNS mdns(udp);

void nameFound(const char* name, IPAddress ip);

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

// This function is called when a name is resolved via mDNS/Bonjour. We set
// this up in the setup() function above. The name you give to this callback
// function does not matter at all, but it must take exactly these arguments
// (a const char*, which is the hostName you wanted resolved, and a const
// byte[4], which contains the IP address of the host on success, or NULL if
// the name resolution timed out).
void nameFound(const char* name, IPAddress ip)
{
  //if ( (ip[0] != 0) && (ip[1] != 0) && (ip[2] != 0) && (ip[3] != 0) )
  if ( (ip[0] != 0) || (ip[1] != 0) || (ip[2] != 0) || (ip[3] != 0) )
  {
    Serial.print("The IP address for '");
    Serial.print(name);
    Serial.print("' is ");
    Serial.println(ip);

    for (int i = 0; i < 4; i++)
    {
      MDNS_LOGDEBUG3("IP[", i, "]=", ip[i]);
    }
  }
  else if (ip[0] == 0)
  {
    Serial.print("Resolving '");
    Serial.print(name);
    Serial.println("' error.");
  }
  else
  {
    Serial.print("Resolving '");
    Serial.print(name);
    Serial.println("' timed out.");
  }
}

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial);
  
  Serial.print("\nStart WiFiResolvingHostNames on "); Serial.println(BOARD_NAME);
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

  // Initialize the mDNS library. You can now reach or ping this
  // Arduino via the host name "arduino.local", provided that your operating
  // system is mDNS/Bonjour-enabled (such as MacOS X).
  // Always call this before any other method!
  //hostname.toUpperCase();
  hostname.toLowerCase();
  hostname.replace(" ",  "-");
  hostname.replace("_",  "-");

  Serial.print("Registering mDNS hostname: "); Serial.println(hostname);
  Serial.print("To access, using "); Serial.print(hostname); Serial.println(".local");

  // Initialize the mDNS library. You can now reach or ping this
  // Arduino via the host name "hostname.local", provided that your operating
  // system is mDNS/Bonjour-enabled (such as MacOS X).
  // Always call this before any other method!
  mdns.begin(WiFi.localIP(), hostname.c_str());

  // We specify the function that the mDNS library will call when it
  // resolves a host name. In this case, we will call the function named
  // "nameFound".
  mdns.setNameResolvedCallback(nameFound);

  Serial.println("Enter a mDNS host name via the Arduino Serial Monitor to "
                 "have it resolved.");
  Serial.println("Do not postfix the name with \".local\"");
}


void loop()
{
  static char hostName[256];
  //char hostName[512];

  uint8_t length = 0;

  // read in a host name from the Arduino IDE's serial monitor.
  while (Serial.available())
  {
    hostName[length] = Serial.read();
    length = (length + 1) % 256;
    delay(5);
  }

  // Terminal adds "\r\n", need to remove
  if (length > 1)
    length = (length - 2) % 256;

  hostName[length] = '\0';

  // You can use the "isResolvingName()" function to find out whether the
  // mDNS library is currently resolving a host name.
  // If so, we skip this input, since we want our previous request to continue.
  if (!mdns.isResolvingName())
  {
    if (length > 0)
    {
      MDNS_LOGDEBUG3("Receiving len = ", length, ", hostname", hostName);

      Serial.print("Resolving '");
      Serial.print(hostName);
      Serial.println("' via Multicast DNS (Bonjour)...");

      // Now we tell the mDNS library to resolve the host name. We give it a
      // timeout of 5 seconds (e.g. 5000 milliseconds) to find an answer. The
      // library will automatically resend the query every second until it
      // either receives an answer or your timeout is reached - In either case,
      // the callback function you specified in setup() will be called.

      mdns.resolveName(hostName, 5000);
    }
  }

  // This actually runs the mDNS module. YOU HAVE TO CALL THIS PERIODICALLY,
  // OR NOTHING WILL WORK! Preferably, call it once per loop().
  mdns.run();

  //delay(1000);
}
