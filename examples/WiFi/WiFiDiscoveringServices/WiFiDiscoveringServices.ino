/****************************************************************************************************************************
  WiFiDiscoveringServices.ino
  
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

//  Illustrates how to discover Bonjour services on your network.

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

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <MDNS_Generic.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP), length must be 8

int status = WL_IDLE_STATUS;     // the Wifi radio's status

MDNS mdns(udp);

void serviceFound(const char* type, MDNSServiceProtocol proto,
                  const char* name, IPAddress ip, unsigned short port,
                  const char* txtContent);

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

// This function is called when a name is resolved via mMDNS/Bonjour. We set
// this up in the setup() function above. The name you give to this callback
// function does not matter at all, but it must take exactly these arguments
// as below.
// If a service is discovered, name, ipAddr, port and (if available) txtContent
// will be set.
// If your specified discovery timeout is reached, the function will be called
// with name (and all successive arguments) being set to NULL.
void serviceFound(const char* type, MDNSServiceProtocol /*proto*/,
                  const char* name, IPAddress ip,
                  unsigned short port,
                  const char* txtContent)
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

    // Check out http://www.zeroconf.org/Rendezvous/txtrecords.html for a
    // primer on the structure of TXT records. Note that the Bonjour
    // library will always return the txt content as a zero-terminated
    // string, even if the specification does not require this.
    if (txtContent)
    {
      Serial.print("\ttxt record: ");

      char buf[256];
      char len = *txtContent++;
      int i = 0;

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

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart WiFiDiscoveringServices on "); Serial.println(BOARD_NAME);
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
  // discovers a service instance. In this case, we will call the function
  // named "serviceFound".
  mdns.setServiceFoundCallback(serviceFound);

  Serial.println("Enter a mDNS service name via the Arduino Serial Monitor");
  Serial.println(" to discover instances on the network.");
  Serial.println("Examples are \"_http\", \"_afpovertcp\" or \"_ssh\" (Note "
                 "the underscores).");
}

void loop()
{
  char serviceName[256];
  int length = 0;

  // read in a service name from the Arduino IDE's serial monitor.
  while (Serial.available())
  {
    serviceName[length] = Serial.read();
    length = (length + 1) % 256;
    delay(5);
  }

  serviceName[length] = '\0';

  // You can use the "isDiscoveringService()" function to find out whether the
  // mDNS library is currently discovering service instances.
  // If so, we skip this input, since we want our previous request to continue.
  if (!mdns.isDiscoveringService())
  {
    if (length > 0)
    {
      Serial.print("Discovering services of type '");
      Serial.print(serviceName);
      Serial.println("' via Multi-Cast DNS (Bonjour)...");

      // Now we tell the mDNS library to discover the service. Below, I have
      // hardcoded the TCP protocol, but you can also specify to discover UDP
      // services.
      // The last argument is a duration (in milliseconds) for which we will
      // search (specify 0 to run the discovery indefinitely).
      // Note that the library will resend the discovery message every 10
      // seconds, so if you search for longer than that, you will receive
      // duplicate instances.

      mdns.startDiscoveringService(serviceName, MDNSServiceTCP, 5000);
    }
  }

  // This actually runs the mDNS module. YOU HAVE TO CALL THIS PERIODICALLY,
  // OR NOTHING WILL WORK!
  // Preferably, call it once per loop().
  mdns.run();
}
