/****************************************************************************************************************************
  ResolvingHostNames.ino

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

//  Illustrates how to resolve host names via MDNS (Multicast DNS)

#include "defines.h"

#include <MDNS_Generic.h>

EthernetUDP udp;
MDNS mdns(udp);

void nameFound(const char* name, IPAddress ip);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart ResolvingHostNames on "); Serial.print(BOARD_NAME);
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

  // Initialize the mDNS library. You can now reach or ping this
  // Arduino via the host name "arduino.local", provided that your operating
  // system is mDNS/Bonjour-enabled (such as MacOS X).
  // Always call this before any other method!
  String hostname = String(BOARD_NAME) + "_" + String(index);
  hostname.toUpperCase();
  hostname.replace(" ",  "-");
  
  Serial.print("Registering mDNS hostname: "); Serial.println(hostname);
  Serial.print("To access, using "); Serial.print(hostname); Serial.println(".local");

  mdns.begin(Ethernet.localIP(), hostname.c_str());

  // We specify the function that the mDNS library will call when it
  // resolves a host name. In this case, we will call the function named
  // "nameFound".
  mdns.setNameResolvedCallback(nameFound);

  Serial.println("Enter a mDNS host name via the Arduino Serial Monitor to have it resolved.");
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

// This function is called when a name is resolved via mDNS/Bonjour. We set
// this up in the setup() function above. The name you give to this callback
// function does not matter at all, but it must take exactly these arguments
// (a const char*, which is the hostName you wanted resolved, and a const
// byte[4], which contains the IP address of the host on success, or NULL if
// the name resolution timed out).
void nameFound(const char* name, IPAddress ip)
{
  if ( (ip[0] != 0) && (ip[1] != 0) && (ip[2] != 0) && (ip[3] != 0) )
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
