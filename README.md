## BlynkEthernet_STM32_Manager

[![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkEthernet_STM32_WM.svg?)](https://www.ardu-badge.com/BlynkEthernet_STM32_WM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/BlynkEthernet_STM32_WM.svg)](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/BlynkEthernet_STM32_WM.svg)](http://github.com/khoih-prog/BlynkEthernet_STM32_WM/issues)

---

### Releases v1.0.4

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROMe***.
3. Permit to input special chars such as ***%*** and ***#*** into data fields.
4. MultiBlynk Servers and Tokens with Auto(Re)Connect feature.

### New in Version v1.0.3
1. Reduce html and code size for faster Config Portal response. Enhance GUI.
2. Change default macAddress for boards to avoid macAddress conflict while simultaneously testing multiple boards.

### New in Version v1.0.2

1. Fix crashing bug when using dynamic EthernetServer
2. Enhance examples, fix indentation, update README.md

- This is the new library, adding to the current Blynk_WiFiManager. It's designed to help you eliminate `hardcoding` your Blynk credentials in `STM32` boards using with Ethernet (Built-in LAN8742A, W5100, W5200, W5500, ENC28J60, etc). It's currently ***not supporting SSL and can not saved config dada to non-volatile memory (EEPROM, battery-saved SRAM, SPIFFS, etc.)***. To be fixed in future releases.
- You can update Blynk Credentials any time you need to change via Configure Portal. Data to be saved in configurable locations in EEPROM.

This library currently supports
1. STM32 boards with built-in Ethernet LAN8742A such as :
  - ***Nucleo-144 (F429ZI, F767ZI)***
  - ***Discovery (STM32F746G-DISCOVERY)***
  - ***All STM32 Boards with Built-in Ethernet***, See [How To Use Built-in Ethernet](https://github.com/khoih-prog/EthernetWebServer_STM32/issues/1)
2. ***STM32 boards (with 64+K Flash) running ENC28J60 shields***
3. ***STM32 boards (with 64+K Flash) running W5x00 shields***

---
---

## Prerequisite

1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
2. [`Blynk library 0.6.1+`](https://www.arduino.cc/en/guide/libraries#toc3)
3. [`Arduino Core for STM32 1.9.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 (Use Arduino Board Manager)
3. Depending on which Ethernet card you're using:
   - [`STM32Ethernet library v1.2.0+`](https://github.com/stm32duino/STM32Ethernet) for built-in Ethernet LAN8742A on (Nucleo-144, Discovery). To be used with [`STM32duino_LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP). 
   - [`Ethernet library v2.0.0+`](https://www.arduino.cc/en/Reference/Ethernet) for W5100, W5200 and W5500.
   - [`Ethernet2 library v1.0.4+`](https://github.com/khoih-prog/Ethernet2) for W5500 (Deprecated, use Arduino Ethernet library).
   - [`Ethernet3 library v1.5.3+`](https://github.com/sstaub/Ethernet3) for W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.
   - [`EthernetLarge library v2.0.0+`](https://github.com/OPEnSLab-OSU/EthernetLarge) for W5100, W5200 and W5500. ***Ready*** from v1.0.1.
   - [`UIPEthernet library v2.0.9+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60.
4. [`EthernetWebServer_STM32 library v1.0.6+`](https://github.com/khoih-prog/EthernetWebServer_STM32). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_STM32.svg?)](https://www.ardu-badge.com/EthernetWebServer_STM32).

---

## Installation

#### Use Arduino Library Manager
The best way is to use `Arduino Library Manager`. Search for `BlynkEthernet_STM32_Manager`, then select / install the latest version. 
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkEthernet_STM32_WM.svg?)](https://www.ardu-badge.com/BlynkEthernet_STM32_WM) for more detailed instructions.

#### Manual Install

1. Navigate to [BlynkEthernet_STM32_Manager](https://github.com/khoih-prog/BlynkEthernet_STM32_WM) page.
2. Download the latest release `BlynkEthernet_STM32_WM-master.zip`.
3. Extract the zip file to `BlynkEthernet_STM32_WM-master` directory 
4. Copy whole 
  - `BlynkEthernet_STM32_WM-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **BlynkEthernet_STM32_Manager** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for BlynkEthernet_STM32_Manager in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---

### Libraries' Patches

1. If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

2. To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

3. To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)

4. To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

6. **To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library**, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- For [UIPEthernet v2.0.8](https://github.com/UIPEthernet/UIPEthernet)

  - [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
  - [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
  - [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
  - [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

- For [UIPEthernet v2.0.9](https://github.com/UIPEthernet/UIPEthernet)

  - [UIPEthernet.h](LibraryPatches/UIPEthernet-2.0.9/UIPEthernet.h)
  - [UIPEthernet.cpp](LibraryPatches/UIPEthernet-2.0.9/UIPEthernet.cpp)
  - [Enc28J60Network.h](LibraryPatches/UIPEthernet-2.0.9/utility/Enc28J60Network.h)
  - [Enc28J60Network.cpp](LibraryPatches/UIPEthernet-2.0.9/utility/Enc28J60Network.cpp)

---

### How to use

In your code, replace
1. `BlynkSimpleEthernet.h`      with `BlynkSTM32Ethernet_WM.h`        for board using W5100, W5200, W5500 `without SSL`
2. `BlynkSimpleUIPEthernet.h`   with `BlynkSTM32UIPEthernet_WM.h`     for board using ENC28J60 `without SSL`

3. For STM32 with built-in Ethernet, use 

 - `BlynkSTM32BIEthernet_WM.h` to use Blynk Manager feature (Config Portal, MultiBlynk, Dynamic Parameters, etc.)
 - `BlynkSimple_STM32BI_Ethernet.h` to just use Blynk feature


```
// Start location to store config data to avoid conflict with other functions
#define EEPROM_START   0

```

Then replace `Blynk.begin(...)` with :

`Blynk.begin()`

in your code. Keep `Blynk.run()` intact.

That's it.

---

### How to add dynamic parameters from sketch

- To add custom parameters, just modify from the example below

```
#define USE_DYNAMIC_PARAMETERS     true

/////////////// Start dynamic Credentials ///////////////

//Defined in <BlynkSimpleEsp8266_WM.h> and <BlynkSimpleEsp8266_SSL_WM.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "";

MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
  { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
  { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
  { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
  { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
#endif


/////// // End dynamic Credentials ///////////

```

- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS     false
```

---
---

### Examples

Also see examples: 
 1. [AM2315_W5100](examples/AM2315_W5100)
 2. [DHT11_W5100](examples/DHT11_W5100)
 3. [W5100_Blynk](examples/W5100_Blynk) 
 4. [W5100_WM_Config](examples/W5100_WM_Config)
 5. [W5100_Blynk_Email](examples/W5100_Blynk_Email)
 6. [ENC28J60_Blynk](examples/ENC28J60_Blynk) 
 7. [ENC28J60_WM_Config](examples/ENC28J60_WM_Config)
 8. [ENC28J60_Blynk_Email](examples/ENC28J60_Blynk_Email)
 9. [BI_Ethernet_Blynk](examples/BI_Ethernet_Blynk) 
10. [BI_Ethernet_WM_Config](examples/BI_Ethernet_WM_Config)
11. [BI_Ethernet_Blynk_Email](examples/BI_Ethernet_Blynk_Email)
12. [BlynkHTTPClient](examples/BlynkHTTPClient)

---

## So, how it works?

If no valid config data are stored in EEPROM, it will switch to `Configuration Mode`. Connect to access point at the IP address displayed on Terminal or Router's DHCP server as in the following terminal output:

```
Start BI_Ethernet_Blynk on STM32F7 board, running Built-in LAN8742A Ethernet
[1] EEPROMsz16384
[3] CCSum=0x0,RCSum=0x0
[5] CrCCsum=0,CrRCsum=0
[7] InitEEPROM,sz=16384,Datasz=380
[10] CrCCSum=3120
[12] MAC: FE-C9-A1-8E-D4-B7
[5629] Dynamic IP OK, connected
[6629] IP:192.168.2.88
[6629] bg:NoDat.Stay
F
Your stored Credentials :
MQTT Server = blank
Port = blank
MQTT UserName = blank
MQTT PWD = blank
Subs Topics = blank
Pubs Topics = blank
```

After you connected to, for example, `192.168.2.86`, the Browser will display the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/pics/Selection_2.png">
</p>

Enter your credentials (Blynk Server and Port). If you prefer static IP, input it (for example `192.168.2.79`) in the corresponding field. Otherwise, just leave it `blank` or `nothing` to use auto IP assigned by DHCP server.

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/pics/Selection_3.png">
</p>

Then click `Save`. After the  board auto-restarted, you will see if it's connected to your Blynk server successfully as in the following terminal output:

```
Start BI_Ethernet_Blynk on STM32F7 board, running Built-in LAN8742A Ethernet
[1] EEPROMsz16384
[3] CCSum=0x0,RCSum=0x0
[5] CrCCsum=0,CrRCsum=0
[7] InitEEPROM,sz=16384,Datasz=380
[10] CrCCSum=3120
[12] MAC: FE-C9-A1-8E-D4-B7
[5629] Dynamic IP OK, connected
[6629] IP:192.168.2.88
[6629] bg:NoDat.Stay
Your stored Credentials :
MQTT Server = blank
Port = blank
MQTT UserName = blank
MQTT PWD = blank
Subs Topics = blank
Pubs Topics = blank
FFFFFFFFFF FFFFFFFFFF
Save,CSum=0x2c22
[68929] Hdr=LAN8742A,BName=STM32F767ZIT6-Blynk-WM
[68930] Svr=account.duckdns.org,Tok=tokentoken1a1nKgun10heJSu2G6KQUlJRGIOrVD0QX
[68942] Prt=8080,SIP=192.168.2.88
[68945] CrCCSum=8662
[68947] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on Arduino

[68961] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[68982] Ready (ping: 7ms).
[69049] Connected to Blynk Server = account.duckdns.org, Token = token
[69052] r:E&B OK
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
```

This `Blynk.begin()` is not a blocking call, so you can use it for critical functions requiring in loop(). 
Anyway, this is better for projects using Blynk just for GUI (graphical user interface).

In operation, if Ethernet or Blynk connection is lost, `Blynk.run()` will try reconnecting automatically. Therefore, `Blynk.run()` must be called in the `loop()` function. Don't use:

```cpp
void loop()
{
  if (Blynk.connected())
     Blynk.run();
     
  ...
}
```

just

```cpp
void loop()
{
  Blynk.run();
  ...
}
```

---
---

## Example [BI_Ethernet_Blynk](examples/BI_Ethernet_Blynk) 

Please take a look at other examples, as well.

```
#if defined(ESP8266) || defined(ESP32) || defined(AVR) || (ARDUINO_SAM_DUE) || defined(CORE_TEENSY)
#error This code is designed to run on STM32 platform, not AVR, Teensy, SAM DUE, SAMD, ESP8266 nor ESP32! Please check your Tools->Board setting.
#endif

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define USE_BUILTIN_ETHERNET    true
//  If don't use USE_BUILTIN_ETHERNET, and USE_UIP_ETHERNET => use W5x00 with Ethernet library
#define USE_UIP_ETHERNET        false

#if (USE_BUILTIN_ETHERNET)
#define ETHERNET_NAME     "Built-in LAN8742A Ethernet"
#elif (USE_UIP_ETHERNET)
#define ETHERNET_NAME     "ENC28J60 Ethernet Shield"
#else
#define ETHERNET_NAME     "W5x00 Ethernet Shield"
#endif

#if defined(STM32F0)
#warning STM32F0 board selected
#define DEVICE_NAME  "STM32F0"
#elif defined(STM32F1)
#warning STM32F1 board selected
#define DEVICE_NAME  "STM32F1"
#elif defined(STM32F2)
#warning STM32F2 board selected
#define DEVICE_NAME  "STM32F2"
#elif defined(STM32F3)
#warning STM32F3 board selected
#define DEVICE_NAME  "STM32F3"
#elif defined(STM32F4)
#warning STM32F4 board selected
#define DEVICE_NAME  "STM32F4"
#elif defined(STM32F7)
#warning STM32F7 board selected
#define DEVICE_NAME  "STM32F7"
#else
#warning STM32 unknown board selected
#define DEVICE_NAME  "STM32 Unknown"
#endif

#define BLYNK_NO_YIELD

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

#define USE_DYNAMIC_PARAMETERS      true

// Start location in EEPROM to store config data. Default 0.
// Config data Size currently is 128 bytes w/o chksum, 132 with chksum)
#define EEPROM_START     0

#define USE_SSL     false

#if USE_BLYNK_WM

#if USE_SSL
// Need ArduinoECCX08 and ArduinoBearSSL libraries
// Currently, error not enough memory for many STM32 boards. Don't use
#error SSL not support
#else
#if USE_BUILTIN_ETHERNET
#include <BlynkSTM32BIEthernet_WM.h>
#elif USE_UIP_ETHERNET
#include <BlynkSTM32UIPEthernet_WM.h>
#else
#include <BlynkSTM32Ethernet_WM.h>
#endif
#endif

/////////////// Start dynamic Credentials ///////////////

//Defined in <BlynkEthernet_WM.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "";

MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
  { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
  { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
  { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
  { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
#endif


/////// // End dynamic Credentials ///////////

#else   //USE_BLYNK_WM

#if USE_BUILTIN_ETHERNET
#include <BlynkSimple_STM32BI_Ethernet.h>
#elif USE_UIP_ETHERNET
#include <BlynkSimpleUIPEthernet.h>
#else
#include <BlynkSimpleEthernet.h>
#endif

#define USE_LOCAL_SERVER      true

#if USE_LOCAL_SERVER
char auth[] = "******";
char server[] = "account.duckdns.org";
//char server[] = "192.168.2.112";

#else
char auth[] = "******";
char server[] = "blynk-cloud.com";
#endif

#define BLYNK_HARDWARE_PORT       8080

#endif    //USE_BLYNK_WM

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
#define W5100_CS  10
#define SDCARD_CS 4
#endif

void setup()
{
  // Debug console
  Serial.begin(115200);
  Serial.println("\nStart BI_Ethernet_Blynk on " + String(DEVICE_NAME) + " board, running " + String(ETHERNET_NAME));

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card
#endif

#if USE_BLYNK_WM
  Blynk.begin();
#else
#if USE_LOCAL_SERVER
  Blynk.begin(auth, server, BLYNK_HARDWARE_PORT);
#else
  Blynk.begin(auth);
  // You can also specify server:
  //Blynk.begin(auth, server, BLYNK_HARDWARE_PORT);
#endif
#endif

  if (Blynk.connected())
  {
#if USE_BLYNK_WM
    Serial.print(F("Conn2Blynk: server = "));
    Serial.print(Blynk.getServerName());
    Serial.print(F(", port = "));
    Serial.println(Blynk.getHWPort());
    Serial.print(F("Token = "));
    Serial.println(Blynk.getToken());
#endif
    Serial.print(F("IP = "));
    Serial.println(Ethernet.localIP());
  }
}

void heartBeatPrint(void)
{
  static int num = 1;

  if (Blynk.connected())
    Serial.print(F("B"));
  else
    Serial.print(F("F"));

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     60000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
void displayCredentials(void)
{
  Serial.println("\nYour stored Credentials :");

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}
#endif

void loop()
{
  Blynk.run();
  check_status();

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
#endif    
}
```

---

### Debug Termimal Output Samples

The following is the sample terminal output when running example [BI_Ethernet_Blynk](examples/BI_Ethernet_Blynk) on Nucleo-144 F767ZI with built-in Ethernet PHY.

```
Start BI_Ethernet_Blynk on STM32F7 board, running Built-in LAN8742A Ethernet
[1] EEPROMsz16384
[3] CCSum=0x0,RCSum=0x0
[5] CrCCsum=0,CrRCsum=0
[7] InitEEPROM,sz=16384,Datasz=380
[10] CrCCSum=3120
[12] MAC: FE-C9-A1-8E-D4-B7
[5629] Dynamic IP OK, connected
[6629] IP:192.168.2.88
[6629] bg:NoDat.Stay
Your stored Credentials :
MQTT Server = blank
Port = blank
MQTT UserName = blank
MQTT PWD = blank
Subs Topics = blank
Pubs Topics = blank
FFFFFFFFFF FFFFFFFFFF
Save,CSum=0x2c22
[68929] Hdr=LAN8742A,BName=STM32F767ZIT6-Blynk-WM
[68930] Svr=account.duckdns.org,Tok=tokentoken1a1nKgun10heJSu2G6KQUlJRGIOrVD0QX
[68942] Prt=8080,SIP=192.168.2.88
[68945] CrCCSum=8662
[68947] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on Arduino

[68961] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[68982] Ready (ping: 7ms).
[69049] Connected to Blynk Server = account.duckdns.org, Token = token
[69052] r:E&B OK
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
BBBBBBBBBB BBBBBBBBBB BBBB
```

---
---

### Releases v1.0.4

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROMe***.
3. Permit to input special chars such as ***%*** and ***#*** into data fields.
4. MultiBlynk Servers and Tokens with Auto(Re)Connect feature.

### New in Version v1.0.3
1. Reduce html and code size for faster Config Portal response.  Enhance GUI.
2. Change default macAddress for boards to avoid macAddress conflict while simultaneously testing multiple boards.

### New in Version v1.0.2

1. Fix crashing bug when using dynamic EthernetServer
2. Enhance examples, fix indentation, update README.md

### Releases v1.0.1

***New in this version***

1. Fix hanging bug in STM32 boards with built-in Ethernet LAN8742A.

### Releases v1.0.0

***New in this version***

1. Add support to STM32 boards with built-in Ethernet LAN8742A, ENC28J60 or W5x00 Ethernet shields 

---

### TO DO

 1. Same features for other boards with Ethernet shields.
 2. To write code and make SSL working. Currently, Ethernet SSL is not supported by Blynk code yet.
 3. Make simulated EEPROM work on all STM32 boards

### DONE

 1. Permit EEPROM size and location configurable to avoid conflict with others.
 2. More flexible to configure reconnection timeout.
 3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
 4. If the config data not entered completely (Server, HardwarePort and Blynk token), entering config portal
 5. Change Synch XMLHttpRequest to Async
 6. Reduce memory usage.
 7. Support W5x00, ENC28J60 Ethernet shield as well as built-in Ethernet LAN8742A
 8. Add checksum
 9. Support STM32 boards
10. Add MultiBlynk features with Auto(Re)Connect to the available Server.
11. Easy-to-use Dynamic Parameters without the necessity to write complicated ArduinoJSon functions
12. Permit to input special chars such as ***%*** and ***#*** into data fields. 

---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

## Copyright

Copyright 2020- Khoi Hoang
