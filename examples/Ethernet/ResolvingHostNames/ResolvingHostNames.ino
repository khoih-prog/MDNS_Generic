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
 *****************************************************************************************************************************/

//  Illustrates how to resolve host names via MDNS (Multicast DNS)

#include "defines.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <MDNS_Generic.h>

EthernetUDP udp;
MDNS mdns(udp);

void nameFound(const char* name, IPAddress ip);

uint16_t macIndex;

void initEthernet()
{
#if USE_ETHERNET_PORTENTA_H7
  MDNS_LOGWARN(F("======== USE_PORTENTA_H7_ETHERNET ========"));
#elif USE_NATIVE_ETHERNET
  MDNS_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
#elif USE_ETHERNET_GENERIC
  MDNS_LOGWARN(F("=========== USE_ETHERNET_GENERIC ==========="));  
#elif USE_ETHERNET_ESP8266
  MDNS_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
#elif USE_ETHERNET_ENC
  MDNS_LOGWARN(F("=========== USE_ETHERNET_ENC ==========="));  
#else
  MDNS_LOGWARN(F("========================="));
#endif

#if !(USE_NATIVE_ETHERNET || USE_ETHERNET_PORTENTA_H7)

#if (USING_SPI2)
  #if defined(CUR_PIN_MISO)
    MDNS_LOGWARN(F("Default SPI pinout:"));
    MDNS_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
    MDNS_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
    MDNS_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
    MDNS_LOGWARN1(F("SS:"),   CUR_PIN_SS);
    MDNS_LOGWARN(F("========================="));
  #endif
#else
  MDNS_LOGWARN(F("Default SPI pinout:"));
  MDNS_LOGWARN1(F("MOSI:"), MOSI);
  MDNS_LOGWARN1(F("MISO:"), MISO);
  MDNS_LOGWARN1(F("SCK:"),  SCK);
  MDNS_LOGWARN1(F("SS:"),   SS);
  MDNS_LOGWARN(F("========================="));
#endif

#if defined(ESP8266)
  // For ESP8266, change for other boards if necessary
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   D2    // For ESP8266
  #endif

  MDNS_LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);

  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // For ESP8266
    // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
    // EthernetGeneric    X                 X            X            X            X        0
    // Ethernet_ESP8266   0                 0            0            0            0        0
    // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
    // Must use library patch for Ethernet, EthernetLarge libraries
    Ethernet.init (USE_THIS_SS_PIN);

  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN);
  
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#elif defined(ESP32)

  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   5   //22    // For ESP32
  #endif

  MDNS_LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
    // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN); 
  
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#elif ETHERNET_USE_RPIPICO

  pinMode(USE_THIS_SS_PIN, OUTPUT);
  digitalWrite(USE_THIS_SS_PIN, HIGH);
  
  // ETHERNET_USE_RPIPICO, use default SS = 5 or 17
  #ifndef USE_THIS_SS_PIN
    #if defined(ARDUINO_ARCH_MBED)
      #define USE_THIS_SS_PIN   5     // For Arduino Mbed core
    #else  
      #define USE_THIS_SS_PIN   17    // For E.Philhower core
    #endif
  #endif

  MDNS_LOGWARN1(F("RPIPICO setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // For RPI Pico using Arduino Mbed RP2040 core
    // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
    // For RPI Pico using E. Philhower RP2040 core
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
    // Default pin 5/17 to SS/CS
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);
     
  #endif    //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#else   //defined(ESP8266)
  // unknown board, do nothing, use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif

  #if defined(BOARD_NAME)
    MDNS_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);
  #else
    MDNS_LOGWARN1(F("Unknown board setCsPin:"), USE_THIS_SS_PIN);
  #endif

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
  
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN);
    
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#endif    // defined(ESP8266)

#endif    // #if !(USE_NATIVE_ETHERNET)

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  //uint16_t macIndex = millis() % NUMBER_OF_MAC;
  macIndex = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[macIndex], ip);
  Ethernet.begin(mac[macIndex]);

#if !(USE_NATIVE_ETHERNET || USE_ETHERNET_PORTENTA_H7)
  MDNS_LOGWARN(F("========================="));
  
  #if defined( ESP32 )
    // Just info to know how to connect correctly
    // To change for other SPI
    MDNS_LOGWARN(F("Currently Used SPI pinout:"));
    MDNS_LOGWARN1(F("MOSI:"), PIN_MOSI);
    MDNS_LOGWARN1(F("MISO:"), PIN_MISO);
    MDNS_LOGWARN1(F("SCK:"),  PIN_SCK);
    MDNS_LOGWARN1(F("SS:"),   PIN_SS);
  #else
    #if defined(CUR_PIN_MISO)
      MDNS_LOGWARN(F("Currently Used SPI pinout:"));
      MDNS_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
      MDNS_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
      MDNS_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
      MDNS_LOGWARN1(F("SS:"),   CUR_PIN_SS);
    #else
      MDNS_LOGWARN(F("Currently Used SPI pinout:"));
      MDNS_LOGWARN1(F("MOSI:"), MOSI);
      MDNS_LOGWARN1(F("MISO:"), MISO);
      MDNS_LOGWARN1(F("SCK:"),  SCK);
      MDNS_LOGWARN1(F("SS:"),   SS);
    #endif
  #endif
  
  MDNS_LOGWARN(F("========================="));

#elif (USE_ETHERNET_PORTENTA_H7)
  if (Ethernet.hardwareStatus() == EthernetNoHardware) 
  {
    Serial.println("No Ethernet found. Stay here forever");
    
    while (true) 
    {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  
  if (Ethernet.linkStatus() == LinkOFF) 
  {
    Serial.println("Not connected Ethernet cable");
  }
#endif

  Serial.print(F("Using mac index = "));
  Serial.println(macIndex);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());  
}

void setup()
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  Serial.print("\nStart ResolvingHostNames on "); Serial.print(BOARD_NAME);
  Serial.print(" using "); Serial.println(SHIELD_TYPE);
  Serial.println(MDNS_GENERIC_VERSION);

  initEthernet();

  // Initialize the mDNS library. You can now reach or ping this
  // Arduino via the host name "arduino.local", provided that your operating
  // system is mDNS/Bonjour-enabled (such as MacOS X).
  // Always call this before any other method!
  String hostname = String(BOARD_NAME) + "_" + String(macIndex);
  
  //hostname.toUpperCase();
  hostname.toLowerCase();
  hostname.replace(" ",  "-");
  hostname.replace(".",  "-");
  hostname.replace("_",  "-");
  
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
