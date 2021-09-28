## MDNS_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/MDNS_Generic.svg?)](https://www.ardu-badge.com/MDNS_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/MDNS_Generic.svg)](https://github.com/khoih-prog/MDNS_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/MDNS_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/MDNS_Generic.svg)](http://github.com/khoih-prog/MDNS_Generic/issues)
[![star this repo](https://githubbadges.com/star.svg?user=khoih-prog&repo=MDNS_Generic)](https://github.com/khoih-prog/MDNS_Generic)

---
---

## Table of Contents

* [Important Notes about Portenta_H7](#important-notes-about-portenta_h7)
* [Why do we need this MDNS_Generic library](#why-do-we-need-this-mdns_generic-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For Portenta_H7 boards](#10-for-portenta_h7-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. For fixing ESP32 compile error](#7-for-fixing-esp32-compile-error)
* [Important Notes](#important-notes)
* [Basic Usage](#basic-usage)
  * [ 1. Using the mDNS services](#1-using-the-mdns-services)
  * [ 2. Specify callback function when resolving host name](#2-specify-callback-function-when-resolving-host-name)
  * [ 3. Specify callback function when discovering offered services](#3-specify-callback-function-when-discovering-offered-services)
  * [ 4. To resolve a host name](#4-to-resolve-a-host-name)
  * [ 5. To register a service via mDNS](#5-to-register-a-service-via-mdns)
  * [ 6. To discover services](#6-to-discover-services)
* [Examples](#examples)
  * [Ethernet](#ethernet)
    * [ 1. DiscoveringServices](examples/Ethernet/DiscoveringServices)
    * [ 2. RegisteringServices](examples/Ethernet/RegisteringServices)
    * [ 3. RegisteringServicesWithTxtRecord](examples/Ethernet/RegisteringServicesWithTxtRecord)
    * [ 4. ResolvingHostNames](examples/Ethernet/ResolvingHostNames)
  * [WiFi](#wifi)
    * [ 1. WiFiDiscoveringServices](examples/WiFi/WiFiDiscoveringServices)
    * [ 2. WiFiRegisteringServices](examples/WiFi/WiFiRegisteringServices)
    * [ 3. WiFiRegisteringServicesWithTxtRecord](examples/WiFi/WiFiRegisteringServicesWithTxtRecord)
    * [ 4. WiFiResolvingHostNames](examples/WiFi/WiFiResolvingHostNames)
* [Example ResolvingHostNames](#example-resolvinghostnames)
  * [1. File ResolvingHostNames.ino](#1-file-resolvinghostnamesino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. ResolvingHostNames on nRF52 Adafruit NRF52840_FEATHER EXPRESS with W5500 using Ethernet2 library](#1-resolvinghostnames-on-nrf52-adafruit-nrf52840_feather-express-with-w5500-using-ethernet2-library)
  * [ 2. DiscoveringServices on nRF52 Adafruit NRF52840_FEATHER EXPRESS with W5500 using EthernetLarge library](#2-discoveringservices-on-nrf52-adafruit-nrf52840_feather-express-with-w5500-using-ethernetlarge-library)
  * [ 3. ResolvingHostNames on SAMD21 Seeeduino SEEED_XIAO_M0 with W5500 using EthernetLarge library](#3-resolvinghostnames-on-samd21-seeeduino-seeed_xiao_m0-with-w5500-using-ethernetlarge-library)
  * [ 4. DiscoveringServices on NUCLEO_F767ZI with W5x00 using Ethernet2 Library](#4-discoveringservices-on-nucleo_f767zi-with-w5x00-using-ethernet2-library)
  * [ 5. ResolvingHostNames on NUCLEO_F767ZI with W5x00 using Ethernet2 Library](#5-resolvinghostnames-on-nucleo_f767zi-with-w5x00-using-ethernet2-library)
  * [ 6. ResolvingHostNames on RASPBERRY_PI_PICO with W5x00 using EthernetLarge Library](#6-resolvinghostnames-on-raspberry_pi_pico-with-w5x00-using-ethernetlarge-library)
  * [ 7. DiscoveringServices on MBED RASPBERRY_PI_PICO with W5x00 using EthernetLarge Library](#7-discoveringservices-on-mbed-raspberry_pi_pico-with-w5x00-using-ethernetlarge-library)
  * [ 8. WiFiRegisteringServices on MBED NANO_RP2040_CONNECT](#8-wifiregisteringservices-on-mbed-nano_rp2040_connect)
    * [ 8.1 PING Terminal](#81-ping-terminal)
  * [ 9. WiFiRegisteringServices on ESP32_DEV](#9-wifiregisteringservices-on-esp32_dev)
    * [ 9.1 PING Terminal](#91-ping-terminal)
  * [10. RegisteringServices on NRF52840_FEATHER with W5x00 using EthernetLarge Library](#10-registeringservices-on-nrf52840_feather-with-w5x00-using-ethernetlarge-library)
    * [10.1 PING Terminal](#101-ping-terminal)
  * [11. WiFiRegisteringServices on PORTENTA_H7_M7](#11-wifiregisteringservices-on-PORTENTA_H7_M7)
    * [11.1 PING Terminal](#111-ping-terminal)
  * [12. RegisteringServices on PORTENTA_H7_M7 using Ethernet using Portenta_Ethernet Library](#12-registeringservices-on-PORTENTA_H7_M7-using-Ethernet-using-Portenta_Ethernet-Library)
    * [12.1 PING Terminal](#121-ping-terminal)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Notes about Portenta_H7

**Already working in v1.3.0**. Check 

* 1.1 [**Portenta H7 UDP Multicast not working - mbed v2.4.1** #321](https://github.com/arduino/ArduinoCore-mbed/issues/321)
* 1.2 [**Portenta H7 MDNS Library compatibility** #4](https://github.com/khoih-prog/MDNS_Generic/issues/4)

Please use the [Packages' Patches for mbed_portenta](https://github.com/khoih-prog/MDNS_Generic/tree/master/Packages_Patches/arduino/hardware/mbed_portenta)

### Why do we need this [MDNS_Generic library](https://github.com/khoih-prog/MDNS_Generic)

#### Features

MDNS ([**Multicast DNS**](https://en.wikipedia.org/wiki/Multicast_DNS)) is a protocol to resolve **hostnames to IP addresses** within small networks that do not include a local name server. It is a zero-configuration service, using essentially the same programming interfaces, packet formats and operating semantics as the unicast Domain Name System (DNS).

The mDNS protocol, published as [RFC 6762](https://tools.ietf.org/html/rfc6762), uses IP multicast User Datagram Protocol (UDP) packets, and is implemented by the [Apple Bonjour](https://en.wikipedia.org/wiki/Bonjour_(software)) and open source [Avahi software packages](https://en.wikipedia.org/wiki/Avahi_(software)).

mDNS can work in conjunction with DNS Service Discovery (DNS-SD), a companion zero-configuration networking technique specified separately in [RFC 6763](https://tools.ietf.org/html/rfc6763).


This [**MDNS_Generic library**](https://github.com/khoih-prog/MDNS_Generic) is based on and modified from [**Dario Pennisi's ArduinoMDNS Library**](https://github.com/arduino-libraries/ArduinoMDNS) to provide support to many more boards, such as **ESP32, Portenta_H7, Arduino SAMD21, Adafruit SAMD21/SAMD51, Seeeduino SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1, Teensy, SAM DUE, AVR Mega, RP2040-based boards, etc.** and enable those boards to use MDNS services. The currently supported modules/shield is **W5x00 using Ethernet, EthernetLarge, Ethernet2 or Ethernet3 library**. 

- The **WiFiNINA modules/shields are currently supported from v1.2.0**, using [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)
- The **WiFi101 modules/shields are currently supported from v1.2.0**, using [WiFi101 Library](https://github.com/arduino-libraries/WiFi101)

- **Ethernet2 Library is also supported only after applying the fix to add Multicast feature**. See [**Libraries' Patches**](https://github.com/khoih-prog/EthernetWebServer#libraries-patches)
- ENC28J60 using EthernetENC or UIPEthernet library is not supported as UDP Multicast is not available by design.
- LAN8742A using STM32Ethernet / STM32 LwIP libraries is not supported as UDP Multicast is not enabled by design, unless you modify the code to add support.


---

#### Currently Supported Boards

  - **ESP32**
  - **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox etc.**.
  - **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)**.
  - **Adafruit SAM21 (Itsy-Bitsy M0, Metro M0, Feather M0, Gemma M0, etc.)**.
  - **Adafruit SAM51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
  - **Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)**
  - **STM32 (Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.)**.
  - **STM32F/L/H/G/WB/MP1 (Nucleo-64 L053R8,Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32Fx, STM32H7, STM32Lx, STM32Gx, STM32WB, STM32MP1, etc.) having 64K+ Flash program memory.**
  
  - RP2040-based boards, such as **Nano RP2040 Connect**, using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).

  - RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
  
  - **Portenta_H7**
  
  
#### Currently supported Ethernet shields/modules

  1. **W5x00's using Ethernet, EthernetLarge or Ethernet3 Library.**
  2. **Ethernet2 Library is also supported only after applying the fix to add Multicast feature**. See [Libraries' Patches](https://github.com/khoih-prog/EthernetWebServer#libraries-patches)
  3. ENC28J60 using EthernetENC and UIPEthernet library is not supported as UDP Multicast is not available by design.
  4. LAN8742A using STM32Ethernet / STM32 LwIP libraries is not supported as UDP Multicast is not enabled by design, unless you modify the code to add support.
  5. Portenta_H7 Ethernet using [`Portenta_Ethernet`](https://github.com/arduino/ArduinoCore-mbed/tree/master/libraries/Ethernet) library
  
#### Currently supported WiFi shields/modules

1. WiFiNINA using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
2. WiFi101 using [`WiFi101 library`](https://github.com/arduino-libraries/WiFi101)
3. U-Blox W101, W102 using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
4. ESP8266-AT command using [`WiFiEspAT library`](https://github.com/jandrassy/WiFiEspAT)
5. ESP32 using native WiFi
6. Portenta_H7 WiFi using [`Portenta_WiFi`](https://github.com/arduino/ArduinoCore-mbed/tree/master/libraries/WiFi) library
  
---
---

 
## Prerequisites

 1. [`Arduino IDE v1.8.16+`](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino AVR core 1.8.3+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) for AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 3. [`Teensy core v1.55+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 4. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 5. [`Arduino SAMD core 1.8.11+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 6. [`Adafruit SAMD core 1.7.5+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 7. [`Seeeduino SAMD core 1.8.1+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 8. [`Adafruit nRF52 v1.1.0`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest) 
 9. [`ArduinoCore-mbed mbed_rp2040, mbed_nano, mbed_portenta core 2.5.2+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) **Portenta_H7, RP2040-based boards, such as Nano_RP2040_Connect, RASPBERRY_PI_PICO**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
10. [`Earle Philhower's arduino-pico core v1.9.5+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest) 
11. [`Arduino Core for STM32 v2.0.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
12. [`ESP32 Core 2.0.0+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
 
13. Depending on which Ethernet module/shield you're using :
   - [`Ethernet library v2.0.0+`](https://github.com/arduino-libraries/Ethernet) for W5100, W5200 and W5500.  [![GitHub release](https://img.shields.io/github/release/arduino-libraries/Ethernet.svg)](https://github.com/arduino-libraries/Ethernet/releases/latest)
   - [`EthernetLarge library v2.0.0+`](https://github.com/OPEnSLab-OSU/EthernetLarge) for W5100, W5200 and W5500.
   - [`Ethernet2 library v1.0.4+`](https://github.com/khoih-prog/Ethernet2) for W5500. [![GitHub release](https://img.shields.io/github/release/adafruit/Ethernet2.svg)](https://github.com/adafruit/Ethernet2/releases/latest)
   - [`Ethernet3 library v1.5.5+`](https://github.com/sstaub/Ethernet3) for W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip. [![GitHub release](https://img.shields.io/github/release/sstaub/Ethernet3.svg)](https://github.com/sstaub/Ethernet3/releases/latest)
   
14. [`STM32Ethernet library v1.2.0+`](https://github.com/stm32duino/STM32Ethernet) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32Ethernet.svg)](https://github.com/stm32duino/STM32Ethernet/releases/latest). To be used with [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP). [![GitHub release](https://img.shields.io/github/release/stm32duino/LwIP.svg)](https://github.com/stm32duino/LwIP/releases/latest). **Not yet ready** in v1.3.0.
   
15. [`WiFiNINA_Generic library v1.8.13+`](https://github.com/khoih-prog/WiFiNINA_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic) if using WiFiNINA for boards such as Nano 33 IoT, nRF52, Teensy, etc.
16. [`WiFi101 library v0.16.1+`](https://github.com/arduino-libraries/WiFi101) if using WINC1500/WiFi101 shields (MKR1000, MKR1010, etc.). [![GitHub release](https://img.shields.io/github/release/arduino-libraries/WiFi101.svg)](https://github.com/arduino-libraries/WiFi101/releases/latest)
17. [`WiFiEspAT library v1.3.1+`](https://github.com/jandrassy/WiFiEspAT) if using ESP8288/ESP32-AT shields. [![GitHub release](https://img.shields.io/github/release/jandrassy/WiFiEspAT.svg)](https://github.com/jandrassy/WiFiEspAT/releases/latest)

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**MDNS_Generic**](https://github.com/khoih-prog/MDNS_Generic), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/MDNS_Generic.svg?)](https://www.ardu-badge.com/MDNS_Generic) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**MDNS_Generic**](https://github.com/khoih-prog/MDNS_Generic) page.
2. Download the latest release `MDNS_Generic-master.zip`.
3. Extract the zip file to `MDNS_Generic-master` directory 
4. Copy whole `MDNS_Generic-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**MDNS_Generic** library](https://platformio.org/lib/show/11238/MDNS_Generic) by using [Library Manager](https://platformio.org/lib/show/11238/MDNS_Generic/installation). Search for **MDNS_Generic** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 1.0.0](Packages_Patches/adafruit/hardware/nrf52/1.0.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.0.0). 

Supposing the Adafruit nRF52 version is 1.0.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.0.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.0.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.0.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.0.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.0.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.0.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.0.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.15/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.15. These files must be copied into the directory:

- `./arduino-1.8.15/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.15/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.15/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.15/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.11](Packages_Patches/arduino/hardware/samd/1.8.11) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.11).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.11. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.11/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.7.5) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.5). 

Supposing the Adafruit SAMD core version is 1.7.5. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.5/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.8.1) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1). 

Supposing the Seeeduino SAMD core version is 1.8.1. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/1.9.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/1.9.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/2.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/2.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/2.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 2.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`

#### 10. For Portenta_H7 boards

To fix `Portenta H7 MDNS Library compatibility`, please use the [Packages' Patches for mbed_portenta](https://github.com/khoih-prog/MDNS_Generic/tree/master/Packages_Patches/arduino/hardware/mbed_portenta)

For more info, check 

* 1.1 [**Portenta H7 UDP Multicast not working - mbed v2.4.1** #321](https://github.com/arduino/ArduinoCore-mbed/issues/321)
* 1.2 [**Portenta H7 MDNS Library compatibility** #4](https://github.com/khoih-prog/MDNS_Generic/issues/4)

---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.12/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

---
---

### Important Notes

1. For **Adafruit nRF52**, use the SPI's  pin as follows:

  - SS/CS     = 10
  - SPI_MOSI  = MO(SI)
  - SPI_MISO  = MI(SO)
  - SPI_SCK   = SCK

2. For **Adafruit SAMD21/SAMD51**, use the SPI's CS/SS pin as follows:

  - Itsy-Bitsy M0/M4, Feather M0 (Express), Hallowing M0 Express, Zero, Metro M0 => use CS = 16 = pin A2
  - Feather M4 (SAMD51)   => use SS/CS = 9
  - Grand Central M4      => use SS/CS = 53
  - Hallowing M4          => use SS/CS = 10
  - Metro M4 AirLift      => use SS/CS = 36

To know the default CS/SS pins of not listed boards, check the related `variant.h` files in 

`~/.arduino15/packages/adafruit/hardware/samd/x.y.zz/variants/board_name/variant.h`

3. For **Arduino SAM DUE**, use the SPI's  pin as follows:

  - SS/CS     = 10
  - SPI_MOSI  = 75 ( pin 4 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_MISO  = 74 ( pin 1 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_SCK   = 76 ( pin 3 @ [ICSP connector](pics/ICSP_connector.jpg) )
  
<p align="center">
    <img src="https://github.com/khoih-prog/MDNS_Generic/blob/master/pics/ICSP_connector.jpg">
</p>
  
  
---
---

## Basic Usage

### 1. Using the mDNS services

```c++
EthernetUDP udp;
MDNS mdns(udp);

mdns.begin(Ethernet.localIP(), hostname.c_str() /*"arduino"*/);

void loop()
{
  mdns.run();
}
```

### 2. Specify callback function when resolving host name

```c++
mdns.setNameResolvedCallback(nameFound);

void nameFound(const char* name, IPAddress ip)
{
  // To process the MDNS resolved name and IP from hostname
}
```

### 3. Specify callback function when discovering offered services

```c++
mdns.setServiceFoundCallback(serviceFound);

void serviceFound(const char* type, MDNSServiceProtocol /*proto*/, const char* name, IPAddress ip,
                  unsigned short port, const char* txtContent)
{
  // To process the MDNS resolved name, IP, port and txtContent (if available) 
}
```

### 4. To resolve a host name

```c++
mdns.resolveName(hostName, 5000);
```

### 5. To register a service via mDNS

```c++
mdns.addServiceRecord("You_Service._http", 80, MDNSServiceTCP);
```


### 6. To discover services

```c++
mdns.startDiscoveringService(serviceName, MDNSServiceTCP, 5000);
```

---
---

### Examples

#### Ethernet

1. [DiscoveringServices](examples/Ethernet/DiscoveringServices)
2. [RegisteringServices](examples/Ethernet/RegisteringServices)
3. [RegisteringServicesWithTxtRecord](examples/Ethernet/RegisteringServicesWithTxtRecord)
4. [ResolvingHostNames](examples/Ethernet/ResolvingHostNames)

#### WiFi

1. [WiFiDiscoveringServices](examples/WiFi/WiFiDiscoveringServices)
2. [WiFiRegisteringServices](examples/WiFi/WiFiRegisteringServices)
3. [WiFiRegisteringServicesWithTxtRecord](examples/WiFi/WiFiRegisteringServicesWithTxtRecord)
4. [WiFiResolvingHostNames](examples/WiFi/WiFiResolvingHostNames)


---

### Example [ResolvingHostNames](examples/Ethernet/ResolvingHostNames)


#### 1. File [ResolvingHostNames.ino](examples/Ethernet/ResolvingHostNames/ResolvingHostNames.ino)

```cpp
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
  
  //hostname.toUpperCase();
  hostname.toLowerCase();
  hostname.replace(" ",  "-");
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
```

#### 2. File [defines.h](examples/Ethernet/ResolvingHostNames/defines.h)

```cpp
#ifndef defines_h
#define defines_h

#define MDNS_DEBUG_PORT       Serial

// Debug Level from 0 to 4
#define _MDNS_LOGLEVEL_       1

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(ETHERNET_USE_SAMD)
    #undef ETHERNET_USE_SAMD
  #endif
  #define ETHERNET_USE_SAMD      true
  #endif

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #if defined(ETHERNET_USE_NRF528XX)
    #undef ETHERNET_USE_NRF528XX
  #endif
  #define ETHERNET_USE_NRF528XX      true
#endif

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ETHERNET_USE_SAM_DUE)
    #undef ETHERNET_USE_SAM_DUE
  #endif
  #define ETHERNET_USE_SAM_DUE      true
#endif

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
  #if defined(ETHERNET_USE_STM32)
    #undef ETHERNET_USE_STM32
  #endif
  #define ETHERNET_USE_STM32        true
#endif

#if ( defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || defined(ARDUINO_GENERIC_RP2040) )
  #if defined(ETHERNET_USE_RP2040)
    #undef ETHERNET_USE_RP2040
  #endif
  #define ETHERNET_USE_RP2040      true
#endif


#if ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )

  #if defined(BOARD_NAME)
    #undef BOARD_NAME
  #endif

  #if defined(CORE_CM7)
    #warning Using Portenta H7 M7 core
    #define BOARD_NAME              "PORTENTA_H7_M7"
  #else
    #warning Using Portenta H7 M4 core
    #define BOARD_NAME              "PORTENTA_H7_M4"
  #endif

#elif defined(ETHERNET_USE_SAMD)
  // For SAMD
  
  #if ( defined(ARDUINO_SAMD_ZERO) && !defined(SEEED_XIAO_M0) )
    #define BOARD_TYPE      "SAMD Zero"
  #elif defined(ARDUINO_SAMD_MKR1000)
    #define BOARD_TYPE      "SAMD MKR1000"
  #elif defined(ARDUINO_SAMD_MKRWIFI1010)
    #define BOARD_TYPE      "SAMD MKRWIFI1010"
  #elif defined(ARDUINO_SAMD_NANO_33_IOT)
    #define BOARD_TYPE      "SAMD NANO_33_IOT"
  #elif defined(ARDUINO_SAMD_MKRFox1200)
    #define BOARD_TYPE      "SAMD MKRFox1200"
  #elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
    #define BOARD_TYPE      "SAMD MKRWAN13X0"
  #elif defined(ARDUINO_SAMD_MKRGSM1400)
    #define BOARD_TYPE      "SAMD MKRGSM1400"
  #elif defined(ARDUINO_SAMD_MKRNB1500)
    #define BOARD_TYPE      "SAMD MKRNB1500"
  #elif defined(ARDUINO_SAMD_MKRVIDOR4000)
    #define BOARD_TYPE      "SAMD MKRVIDOR4000"
  #elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
    #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
  #elif defined(ADAFRUIT_FEATHER_M0_EXPRESS)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_FEATHER_M0_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M0_EXPRESS)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_METRO_M0_EXPRESS"
  #elif defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_CIRCUITPLAYGROUND_M0"
  #elif defined(ADAFRUIT_GEMMA_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_GEMMA_M0"
  #elif defined(ADAFRUIT_TRINKET_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_TRINKET_M0"
  #elif defined(ADAFRUIT_ITSYBITSY_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_ITSYBITSY_M0"
  #elif defined(ARDUINO_SAMD_HALLOWING_M0)
    #define BOARD_TYPE      "SAMD21 ARDUINO_SAMD_HALLOWING_M0"
  #elif defined(ADAFRUIT_METRO_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_EXPRESS"
  #elif defined(ADAFRUIT_GRAND_CENTRAL_M4)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_GRAND_CENTRAL_M4"
  #elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_FEATHER_M4_EXPRESS"
  #elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_ITSYBITSY_M4_EXPRESS"
  #elif defined(ADAFRUIT_TRELLIS_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_TRELLIS_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYPORTAL)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL"
  #elif defined(ADAFRUIT_PYPORTAL_M4_TITANO)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL_M4_TITANO"
  #elif defined(ADAFRUIT_PYBADGE_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_M4_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_AIRLIFT_LITE"
  #elif defined(ADAFRUIT_PYGAMER_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYBADGE_AIRLIFT_M4)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_AIRLIFT_M4"
  #elif defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_MONSTER_M4SK_EXPRESS"
  #elif defined(ADAFRUIT_HALLOWING_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_HALLOWING_M4_EXPRESS"
  #elif defined(SEEED_WIO_TERMINAL)
    #define BOARD_TYPE      "SAMD SEEED_WIO_TERMINAL"
  #elif defined(SEEED_FEMTO_M0)
    #define BOARD_TYPE      "SAMD SEEED_FEMTO_M0"
  #elif defined(SEEED_XIAO_M0)
    #define BOARD_TYPE      "SAMD SEEED_XIAO_M0"
    #define USE_THIS_SS_PIN       A1
    #warning define SEEED_XIAO_M0 USE_THIS_SS_PIN == A1
  #elif defined(Wio_Lite_MG126)
    #define BOARD_TYPE      "SAMD SEEED Wio_Lite_MG126"
  #elif defined(WIO_GPS_BOARD)
    #define BOARD_TYPE      "SAMD SEEED WIO_GPS_BOARD"
  #elif defined(SEEEDUINO_ZERO)
    #define BOARD_TYPE      "SAMD SEEEDUINO_ZERO"
  #elif defined(SEEEDUINO_LORAWAN)
    #define BOARD_TYPE      "SAMD SEEEDUINO_LORAWAN"
  #elif defined(SEEED_GROVE_UI_WIRELESS)
    #define BOARD_TYPE      "SAMD SEEED_GROVE_UI_WIRELESS"
  #elif defined(__SAMD21E18A__)
    #define BOARD_TYPE      "SAMD21E18A"
  #elif defined(__SAMD21G18A__)
    #define BOARD_TYPE      "SAMD21G18A"
  #elif defined(__SAMD51G19A__)
    #define BOARD_TYPE      "SAMD51G19A"
  #elif defined(__SAMD51J19A__)
    #define BOARD_TYPE      "SAMD51J19A"
  #elif defined(__SAMD51J20A__)
    #define BOARD_TYPE      "SAMD51J20A"
  #elif defined(__SAM3X8E__)
    #define BOARD_TYPE      "SAM3X8E"
  #elif defined(__CPU_ARC__)
    #define BOARD_TYPE      "CPU_ARC"
  #elif defined(__SAMD51__)
    #define BOARD_TYPE      "SAMD51"
  #else
    #define BOARD_TYPE      "SAMD Unknown"
  #endif

#elif (ETHERNET_USE_SAM_DUE)
  #define BOARD_TYPE      "SAM DUE"

#elif (ETHERNET_USE_NRF528XX)

  #if defined(NRF52840_FEATHER)
    #define BOARD_TYPE      "NRF52840_FEATHER"
  #elif defined(NRF52832_FEATHER)
    #define BOARD_TYPE      "NRF52832_FEATHER"
  #elif defined(NRF52840_FEATHER_SENSE)
    #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
  #elif defined(NRF52840_ITSYBITSY)
    #define BOARD_TYPE      "NRF52840_ITSYBITSY"
  #elif defined(NRF52840_CIRCUITPLAY)
    #define BOARD_TYPE      "NRF52840_CIRCUITPLAY"
  #elif defined(NRF52840_CLUE)
    #define BOARD_TYPE      "NRF52840_CLUE"
  #elif defined(NRF52840_METRO)
    #define BOARD_TYPE      "NRF52840_METRO"
  #elif defined(NRF52840_PCA10056)
    #define BOARD_TYPE      "NRF52840_PCA10056"
  #elif defined(NINA_B302_ublox)
    #define BOARD_TYPE      "NINA_B302_ublox"
  #elif defined(NINA_B112_ublox)
    #define BOARD_TYPE      "NINA_B112_ublox"
  #elif defined(PARTICLE_XENON)
    #define BOARD_TYPE      "PARTICLE_XENON"
  #elif defined(ARDUINO_NRF52_ADAFRUIT)
    #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
  #else
    #define BOARD_TYPE      "nRF52 Unknown"
  #endif

#elif ( defined(CORE_TEENSY) )
  #if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    #define BOARD_TYPE      "TEENSY 4.1/4.0"
  #elif defined(__MK66FX1M0__)
    #define BOARD_TYPE "Teensy 3.6"
  #elif defined(__MK64FX512__)
    #define BOARD_TYPE "Teensy 3.5"
  #elif defined(__MKL26Z64__)
    #define BOARD_TYPE "Teensy LC"
  #elif defined(__MK20DX256__)
    #define BOARD_TYPE "Teensy 3.2" // and Teensy 3.1 (obsolete)
  #elif defined(__MK20DX128__)
    #define BOARD_TYPE "Teensy 3.0"
  #elif defined(__AVR_AT90USB1286__)
    #error Teensy 2.0++ not supported yet
  #elif defined(__AVR_ATmega32U4__)
    #error Teensy 2.0 not supported yet
  #else
    // For Other Boards
    #define BOARD_TYPE      "Unknown Teensy Board"
  #endif

#elif (ETHERNET_USE_STM32)
  #if defined(STM32F0)
    #define BOARD_TYPE  "STM32F0"
  #elif defined(STM32F1)
    #define BOARD_TYPE  "STM32F1"
  #elif defined(STM32F2)
    #define BOARD_TYPE  "STM32F2"
  #elif defined(STM32F3)
    #define BOARD_TYPE  "STM32F3"
  #elif defined(STM32F4)
    #define BOARD_TYPE  "STM32F4"
  #elif defined(STM32F7)
    #define BOARD_TYPE  "STM32F7"
  #elif defined(STM32L0)
    #define BOARD_TYPE  "STM32L0"
  #elif defined(STM32L1)
    #define BOARD_TYPE  "STM32L1"
  #elif defined(STM32L4)
    #define BOARD_TYPE  "STM32L4"
  #elif defined(STM32H7)
    #define BOARD_TYPE  "STM32H7"
  #elif defined(STM32G0)
    #define BOARD_TYPE  "STM32G0"
  #elif defined(STM32G4)
    #define BOARD_TYPE  "STM32G4"
  #elif defined(STM32WB)
    #define BOARD_TYPE  "STM32WB"
  #elif defined(STM32MP1)
    #define BOARD_TYPE  "STM32MP1"
  #else
    #define BOARD_TYPE  "STM32 Unknown"
  #endif

#elif ETHERNET_USE_RP2040
  
  // Default pin 5 (in Mbed) or 17 to SS/CS
  #if defined(ARDUINO_ARCH_MBED)
    // For RPI Pico using Arduino Mbed RP2040 core
    // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
    
    #define USE_THIS_SS_PIN       5

    #if defined(BOARD_NAME)
      #undef BOARD_NAME
    #endif

    #if defined(ARDUINO_NANO_RP2040_CONNECT)
      #define BOARD_TYPE      "MBED NANO_RP2040_CONNECT"
    #elif defined(ARDUINO_RASPBERRY_PI_PICO) 
      #define BOARD_TYPE      "MBED RASPBERRY_PI_PICO"
    #elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
      #define BOARD_TYPE      "MBED ADAFRUIT_FEATHER_RP2040"
    #elif defined(ARDUINO_GENERIC_RP2040)
      #define BOARD_TYPE      "MBED GENERIC_RP2040"
    #else
      #define BOARD_TYPE      "MBED Unknown RP2040"
    #endif
    
  #else
    // For RPI Pico using E. Philhower RP2040 core
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
    #define USE_THIS_SS_PIN       17

  #endif
    
  #define SS_PIN_DEFAULT        USE_THIS_SS_PIN

  // For RPI Pico
  #warning Use RPI-Pico RP2040 architecture

#else
  // For Mega
  #define BOARD_TYPE      "AVR Mega"
#endif

#if defined(ARDUINO_BOARD)
  #define BOARD_NAME    ARDUINO_BOARD
#elif !defined(BOARD_NAME)
  #define BOARD_NAME    BOARD_TYPE
#endif

#include <SPI.h>

// UIPEthernet, Ethernet_Shield_W5200, EtherCard, EtherSia libraries are not supported

// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
// You can define here or customize for each board at same place with BOARD_TYPE
// Check @ defined(SEEED_XIAO_M0)
//#define USE_THIS_SS_PIN   22  //21  //5 //4 //2 //15

// Only one if the following to be true
#define USE_ETHERNET              false //true
#define USE_ETHERNET2             false //true
#define USE_ETHERNET3             false //true
#define USE_ETHERNET_LARGE        false
#define USE_ETHERNET_PORTENTA_H7  true

#if USE_ETHERNET_PORTENTA_H7
  //#include "PortentaEthernet.h"
  #include "Ethernet.h"
  #include "EthernetUdp.h"
  #warning Using Portenta_Ethernet lib for Portenta_H7.
  #define SHIELD_TYPE       "Ethernet using Portenta_Ethernet Library"

#elif USE_ETHERNET
  #include "Ethernet.h"
  #include "EthernetUdp.h"
  #warning Use Ethernet lib
  #define SHIELD_TYPE           "W5x00 using Ethernet Library" 
#elif USE_ETHERNET_LARGE
  #include "EthernetLarge.h"
  #include "EthernetUdp.h"
  #warning Use EthernetLarge lib
  #define SHIELD_TYPE           "W5x00 using EthernetLarge Library"
#elif USE_ETHERNET2
  #include "Ethernet2.h"
  #include "EthernetUdp2.h"
  #warning Use Ethernet2 lib
  #define SHIELD_TYPE           "W5x00 using Ethernet2 Library"
#elif USE_ETHERNET3
  #include "Ethernet3.h"
  #include "EthernetUdp3.h"
  #warning Use Ethernet3 lib   
  #define SHIELD_TYPE           "W5x00 using Ethernet3 Library" 
#else
  #define USE_ETHERNET          true
  #include "Ethernet.h"
  #warning Use Ethernet lib
  #define SHIELD_TYPE           "W5x00 using Ethernet Library"
#endif

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 222);

#endif    //defines_h
```

---
---

### Debug Terminal Output Samples

#### 1. ResolvingHostNames on nRF52 Adafruit NRF52840_FEATHER EXPRESS with W5500 using Ethernet2 library

This is terminal debug output when running [ResolvingHostNames](examples/Ethernet/ResolvingHostNames) on nRF52 **Adafruit NRF52840_FEATHER EXPRESS with W5500 Ethernet module using Ethernet2 library.**


```
Starting ResolvingHostNames on NRF52840_FEATHER with W5x00 using Ethernet2 Library
MDNS_Generic v1.3.0
=========================
Default SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
=========================
[MDNS] Board : NRF52840_FEATHER , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
=========================
Using mac index = 15
Connected! IP address: 192.168.2.158
Registering mDNS hostname: NRF52840_FEATHER_15
To access, using NRF52840_FEATHER_15.local
Enter a mDNS host name via the Arduino Serial Monitor to have it resolved.
Do not postfix the name with ".local"
Resolving 'raspberrypi-02' via Multicast DNS (Bonjour)...
The IP address for 'raspberrypi-02' is 192.168.2.122
Resolving 'raspberrypi-01' via Multicast DNS (Bonjour)...
The IP address for 'raspberrypi-01' is 192.168.2.120
```

---

#### 2. DiscoveringServices on nRF52 Adafruit NRF52840_FEATHER EXPRESS with W5500 using EthernetLarge library

This is terminal debug output when running [DiscoveringServices](examples/Ethernet/DiscoveringServices) on nRF52 **Adafruit NRF52840_FEATHER EXPRESS with W5500 Ethernet module using EthernetLarge library.**

```
Starting DiscoveringServices on NRF52840_FEATHER with W5x00 using EthernetLarge Library
MDNS_Generic v1.3.0
=========================
Default SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
=========================
[MDNS] Board : NRF52840_FEATHER , setCsPin: 10
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5500, SSIZE =8192
=========================
Currently Used SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
=========================
Using mac index = 16
Connected! IP address: 192.168.2.160
Registering mDNS hostname: NRF52840_FEATHER_16
To access, using NRF52840_FEATHER_16.local
Enter a mDNS service name via Serial Monitor to discover instances on the network.
Examples are "_http", "_afpovertcp" or "_ssh" (Note the underscores).
Discovering services of type '_http' via Multi-Cast DNS (Bonjour)...
Found: 'Arduino Bonjour Webserver Example' at 192.168.2.156, port 4 (TCP)
Found: 'Arduino mDNS Webserver Example, Page 2' at 192.168.2.156, port 4 (TCP)
Found: 'Linksys07265' at 192.168.2.12, port 80 (TCP)
Finished discovering services of type _http

```

---

#### 3. ResolvingHostNames on SAMD21 Seeeduino SEEED_XIAO_M0 with W5500 using EthernetLarge library

This is terminal debug output when running [ResolvingHostNames](examples/Ethernet/ResolvingHostNames) on SAMD21 **Seeeduino SEEED_XIAO_M0 with W5500 Ethernet module using EthernetLarge library.**

```
Starting ResolvingHostNames on SEEED_XIAO_M0 with W5x00 using EthernetLarge Library
MDNS_Generic v1.3.0
=========================
Default SPI pinout:
MOSI:10
MISO:9
SCK:8
SS:4
=========================
[MDNS] Board : SEEED_XIAO_M0 , setCsPin: 1
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 1
W5100::init: W5500, SSIZE =8192
=========================
Currently Used SPI pinout:
MOSI:10
MISO:9
SCK:8
SS:4
=========================
Using mac index = 0
Connected! IP address: 192.168.2.165
Registering mDNS hostname: SEEED_XIAO_M0_0
To access, using SEEED_XIAO_M0_0.local
Enter a mDNS host name via the Arduino Serial Monitor to have it resolved.
Do not postfix the name with ".local"
Resolving 'raspberrypi-01' via Multicast DNS (Bonjour)...
The IP address for 'raspberrypi-01' is 192.168.2.110
Resolving 'raspberrypi-02' via Multicast DNS (Bonjour)...
The IP address for 'raspberrypi-02' is 192.168.2.112
```

---

#### 4. DiscoveringServices on NUCLEO_F767ZI with W5x00 using Ethernet2 Library

This is terminal debug output when running [DiscoveringServices](examples/Ethernet/DiscoveringServices) on STM32 **Nucleo-144 NUCLEO_F767ZI with W5x00 using Ethernet2 Library.**

```
Starting DiscoveringServices on NUCLEO_F767ZI with W5x00 using Ethernet2 Library
MDNS_Generic v1.3.0
=========================
Default SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
=========================
[MDNS] Board : NUCLEO_F767ZI , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
=========================
Using mac index = 15
Connected! IP address: 192.168.2.98
Registering mDNS hostname: NUCLEO_F767ZI_15
To access, using NUCLEO_F767ZI_15.local
Enter a mDNS service name via Serial Monitor to discover instances on the network.
Examples are "_http", "_afpovertcp" or "_ssh" (Note the underscores).
Discovering services of type '_http' via Multi-Cast DNS (Bonjour)...
Found: 'Arduino mDNS Webserver Example' at 192.168.2.85, port 0 (TCP)
Found: 'Linksys07265' at 192.168.2.12, port 80 (TCP)
Finished discovering services of type _http
```

---

#### 5. ResolvingHostNames on NUCLEO_F767ZI with W5x00 using Ethernet2 Library

This is terminal debug output when running [ResolvingHostNames](examples/Ethernet/ResolvingHostNames) on STM32 **Nucleo-144 NUCLEO_F767ZI with W5x00 using Ethernet2 Library.**

```
Starting ResolvingHostNames on NUCLEO_F767ZI with W5x00 using Ethernet2 Library
MDNS_Generic v1.3.0
=========================
Default SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
=========================
[MDNS] Board : NUCLEO_F767ZI , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
=========================
Using mac index = 15
Connected! IP address: 192.168.2.98
Registering mDNS hostname: NUCLEO_F767ZI_15
To access, using NUCLEO_F767ZI_15.local
Enter a mDNS host name via the Arduino Serial Monitor to have it resolved.
Do not postfix the name with ".local"
Resolving 'raspberrypi-02' via Multicast DNS (Bonjour)...
The IP address for 'raspberrypi-02' is 192.168.2.112
Resolving 'raspberrypi-01' via Multicast DNS (Bonjour)...
The IP address for 'raspberrypi-01' is 192.168.2.110
```

---

#### 6. ResolvingHostNames on RASPBERRY_PI_PICO with W5x00 using EthernetLarge Library

This is terminal debug output when running [ResolvingHostNames](examples/Ethernet/ResolvingHostNames) on **RASPBERRY_PI_PICO with W5x00 using EthernetLarge Library.**

```
Starting ResolvingHostNames on RASPBERRY_PI_PICO with W5x00 using EthernetLarge Library
MDNS_Generic v1.3.0
=========================
Default SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
[MDNS] Board : RASPBERRY_PI_PICO , setCsPin: 17
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 17
W5100::init: W5500, SSIZE =8192
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
Using mac index = 6
Connected! IP address: 192.168.2.115
Registering mDNS hostname: MBED_RASPBERRY_PI_PICO_6
To access, using MBED_RASPBERRY_PI_PICO_6.local
Enter a mDNS host name via the Arduino Serial Monitor to have it resolved.
Do not postfix the name with ".local"
Resolving 'raspberrypi-01' via Multicast DNS (Bonjour)...
The IP address for 'raspberrypi-01' is 192.168.2.120
Resolving 'raspberrypi-02' via Multicast DNS (Bonjour)...
The IP address for 'raspberrypi-02' is 192.168.2.122
```

---

#### 7. DiscoveringServices on MBED RASPBERRY_PI_PICO with W5x00 using EthernetLarge Library

This is terminal debug output when running [DiscoveringServices](examples/Ethernet/DiscoveringServices) on **MBED RASPBERRY_PI_PICO using W5x00 using EthernetLarge Library.**

```
Start DiscoveringServices on MBED RASPBERRY_PI_PICO using W5x00 using EthernetLarge Library
MDNS_Generic v1.3.0
=========================
Default SPI pinout:
MOSI:3
MISO:4
SCK:2
SS:5
=========================
[MDNS] Board : MBED RASPBERRY_PI_PICO , setCsPin: 5
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 5, new ss_pin = 10, W5100Class::ss_pin = 5
W5100::init: W5500, SSIZE =8192
=========================
Currently Used SPI pinout:
MOSI:3
MISO:4
SCK:2
SS:5
=========================
Using mac index = 13
Connected! IP address: 192.168.2.93
Registering mDNS hostname: MBED_RASPBERRY_PI_PICO_13
To access, using MBED_RASPBERRY_PI_PICO_13.local
Enter a mDNS service name via Serial Monitor to discover instances on the network.
Examples are "_http", "_afpovertcp" or "_ssh" (Note the underscores).
Discovering services of type '_http' via Multi-Cast DNS (Bonjour)...
Found: 'Linksys08398' at 192.168.2.14, port 80 (TCP)
Found: 'Linksys07265' at 192.168.2.12, port 80 (TCP)
```

---

#### 8. WiFiRegisteringServices on MBED NANO_RP2040_CONNECT

This is terminal debug output when running [WiFiRegisteringServices](examples/WiFi/WiFiRegisteringServices) on **MBED NANO_RP2040_CONNECT using WiFiNINA_Generic Library.**

```
Start WiFiRegisteringServices on MBED NANO_RP2040_CONNECT
MDNS_Generic v1.3.0
Used/default SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
Attempting to connect to SSID: HueNet1
SSID: HueNet1
Local IP address: 192.168.2.111
Signal strength (RSSI):-21 dBm
Registering mDNS hostname: MBED-NANO_RP2040_CONNECT
To access, using MBED-NANO_RP2040_CONNECT.local
```

##### 8.1 PING Terminal

```
kh@kh-Inspiron-3593:~$ ping MBED-NANO_RP2040_CONNECT.local
PING arduino.local (192.168.2.111) 56(84) bytes of data.
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=1 ttl=255 time=65.1 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=2 ttl=255 time=48.6 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=3 ttl=255 time=70.8 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=4 ttl=255 time=93.0 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=5 ttl=255 time=116 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=6 ttl=255 time=35.8 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=7 ttl=255 time=37.2 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=8 ttl=255 time=8.45 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=9 ttl=255 time=36.5 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=10 ttl=255 time=59.5 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=11 ttl=255 time=29.0 ms
64 bytes from arduino-1f98 (192.168.2.111): icmp_seq=12 ttl=255 time=48.7 ms
...
```

---

#### 9. WiFiRegisteringServices on ESP32_DEV

This is terminal debug output when running [WiFiRegisteringServices](examples/WiFi/WiFiRegisteringServices) on **ESP32_DEV**

```
Start WiFiRegisteringServices on ESP32_DEV
MDNS_Generic v1.3.0
Attempting to connect to SSID: HueNet1
SSID: HueNet1
Local IP address: 192.168.2.80
Signal strength (RSSI):-25 dBm
Registering mDNS hostname: ESP_9ABF498
To access, using ESP_9ABF498.local
```

##### 9.1 PING Terminal

```
kh@kh-Inspiron-3593:~$ ping ESP_9ABF498.local
PING arduino.local (192.168.2.80) 56(84) bytes of data.
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=1 ttl=255 time=29.4 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=2 ttl=255 time=49.3 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=3 ttl=255 time=20.7 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=4 ttl=255 time=42.5 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=5 ttl=255 time=13.5 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=6 ttl=255 time=43.4 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=7 ttl=255 time=12.4 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=8 ttl=255 time=30.0 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=9 ttl=255 time=59.5 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=10 ttl=255 time=24.5 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=11 ttl=255 time=47.2 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=12 ttl=255 time=18.5 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=13 ttl=255 time=39.7 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=14 ttl=255 time=10.9 ms
64 bytes from esp32-090ADC (192.168.2.80): icmp_seq=15 ttl=255 time=33.5 ms
...
```

---

#### 10. RegisteringServices on NRF52840_FEATHER with W5x00 using EthernetLarge Library

This is terminal debug output when running [RegisteringServices](examples/WiFi/RegisteringServices) on **NRF52840_FEATHER with W5x00 using EthernetLarge Library**


```
Start RegisteringServices on NRF52840_FEATHER using W5x00 using EthernetLarge Library
MDNS_Generic v1.3.0
=========================
Default SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
=========================
[MDNS] Board : NRF52840_FEATHER , setCsPin: 10
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5500, SSIZE =8192
=========================
Currently Used SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
=========================
Using mac index = 11
Connected! IP address: 192.168.2.106
Registering mDNS hostname: NRF52840_FEATHER_11
To access, using NRF52840_FEATHER_11.local
AddService : NRF52840_FEATHER_mDNS_Webserver._http
```


##### 10.1 PING Terminal

```
kh@kh-Inspiron-3593:~$ ping NRF52840_FEATHER_11.local
PING NRF52840_FEATHER_11.local (192.168.2.106) 56(84) bytes of data.
64 bytes from WIZnetEFBE0C (192.168.2.106): icmp_seq=1 ttl=128 time=0.253 ms
64 bytes from WIZnetEFBE0C (192.168.2.106): icmp_seq=2 ttl=128 time=0.303 ms
64 bytes from WIZnetEFBE0C (192.168.2.106): icmp_seq=3 ttl=128 time=0.289 ms
64 bytes from WIZnetEFBE0C (192.168.2.106): icmp_seq=4 ttl=128 time=0.256 ms
...
```

---

---

#### 11. WiFiRegisteringServices on PORTENTA_H7_M7

This is terminal debug output when running [RegisteringServices](examples/WiFi/RegisteringServices) on **PORTENTA_H7_M7 Murata WiFi**


```
Start WiFiRegisteringServices on PORTENTA_H7_M7
MDNS_Generic v1.3.0
Attempting to connect to SSID: HueNet1
SSID: HueNet1
Local IP address: 192.168.2.94
Signal strength (RSSI):-35 dBm
Registering mDNS hostname: portenta-h7-m7
To access, using portenta-h7-m7.local
[MDNS] ::begin: UDP beginMulticast statusCode= OK
[MDNS] ::_sendMDNSMessage: xid= 0
[MDNS] ::_sendMDNSMessage: queryCount= 0
[MDNS] ::_sendMDNSMessage: answerCount= 1024
[MDNS] ::_sendMDNSMessage: authorityCount= 0
[MDNS] ::_sendMDNSMessage: additionalCount= 256
[MDNS] ::_sendMDNSMessage: statusCode = 1
```


##### 11.1 PING Terminal

```
kh@kh-Inspiron-3593:~$ ping portenta-h7-m7.local
PING portenta-h7-m7.local (192.168.2.94) 56(84) bytes of data.
64 bytes from 192.168.2.94 (192.168.2.94): icmp_seq=1 ttl=255 time=49.4 ms
64 bytes from 192.168.2.94 (192.168.2.94): icmp_seq=2 ttl=255 time=153 ms
64 bytes from 192.168.2.94 (192.168.2.94): icmp_seq=3 ttl=255 time=73.4 ms
64 bytes from 192.168.2.94 (192.168.2.94): icmp_seq=4 ttl=255 time=95.7 ms
64 bytes from 192.168.2.94 (192.168.2.94): icmp_seq=5 ttl=255 time=119 ms
64 bytes from 192.168.2.94 (192.168.2.94): icmp_seq=6 ttl=255 time=22.0 ms
64 bytes from 192.168.2.94 (192.168.2.94): icmp_seq=7 ttl=255 time=30.4 ms
64 bytes from 192.168.2.94 (192.168.2.94): icmp_seq=8 ttl=255 time=47.7 m
...
```

---

#### 12. RegisteringServices on PORTENTA_H7_M7 using Ethernet using Portenta_Ethernet Library

This is terminal debug output when running [RegisteringServices](examples/WiFi/RegisteringServices) on **PORTENTA_H7_M7 using Ethernet using Portenta_Ethernet Library**


```
Start RegisteringServices on PORTENTA_H7_M7 using Ethernet using Portenta_Ethernet Library
MDNS_Generic v1.3.0
=========================
Default SPI pinout:
MOSI:8
MISO:10
SCK:9
SS:7
=========================
[MDNS] Board : PORTENTA_H7_M7 , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:8
MISO:10
SCK:9
SS:7
=========================
Using mac index = 11
Connected! IP address: 192.168.2.87
Registering mDNS hostname: portenta-h7-m7-15
To access, using portenta-h7-m7-11.local
[MDNS] ::begin: UDP beginMulticast statusCode= OK
AddService : PORTENTA_H7_M7_mDNS_Webserver._http
[MDNS] ::_sendMDNSMessage: xid= 0
[MDNS] ::_sendMDNSMessage: queryCount= 0
[MDNS] ::_sendMDNSMessage: answerCount= 1024
[MDNS] ::_sendMDNSMessage: authorityCount= 0
[MDNS] ::_sendMDNSMessage: additionalCount= 256
[MDNS] ::_sendMDNSMessage: statusCode = 1
```


##### 12.1 PING Terminal

```
kh@kh-Inspiron-3593:~$ ping portenta-h7-m7-15.local
PING portenta-h7-m7-15.local (192.168.2.87) 56(84) bytes of data.
64 bytes from 192.168.2.87 (192.168.2.87): icmp_seq=1 ttl=255 time=0.964 ms
64 bytes from 192.168.2.87 (192.168.2.87): icmp_seq=2 ttl=255 time=0.216 ms
64 bytes from 192.168.2.87 (192.168.2.87): icmp_seq=3 ttl=255 time=1.07 ms
64 bytes from 192.168.2.87 (192.168.2.87): icmp_seq=4 ttl=255 time=4.40 ms
64 bytes from 192.168.2.87 (192.168.2.87): icmp_seq=5 ttl=255 time=0.314 ms
64 bytes from 192.168.2.87 (192.168.2.87): icmp_seq=6 ttl=255 time=0.635 ms
64 bytes from 192.168.2.87 (192.168.2.87): icmp_seq=7 ttl=255 time=0.996 ms
64 bytes from 192.168.2.87 (192.168.2.87): icmp_seq=8 ttl=255 time=4.47 ms
...
```
---
---

### Debug

Debug is enabled by default on Serial. To disable, add at the beginning of sketch

```cpp
/* Comment this out to disable prints and save space */
// Debug Level from 0 to 4
#define MDNS_DEBUG_PORT       Serial

// Debug Level from 0 to 4
#define _MDNS_LOGLEVEL_       1
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, dependent libraries or this library version.

Sometimes, the library will only work if you update the core to the newer or older version because some function compatibility.

---
---


### Issues

Submit issues to: [**MDNS_Generic issues**](https://github.com/khoih-prog/MDNS_Generic/issues)

---
---

### TO DO

 1. Support more boards.
 2. Support ENC28J60 Ethernet.
 3. Support LAN8742A Ethernet.
 4. Support more non-compatible Ethernet Libraries such as Ethernet_Shield_W5200, EtherCard, EtherSia
 5. Add more examples

---

### DONE

 1. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)**
 2. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**.
 3. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
 4. Add support to **Seeeduino SAMD21/SAMD51: LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, Wio Terminal, Grove UI Wireless, etc.**
 5. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**.
 6. Add support to SAM DUE.
 7. Add support to **STM32F/L/H/G/WB/MP1.**
 8. Add support to **Ethernet W5x00**, using either [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet) or [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge) library
 9. Add debugging feature.
10. Add support to **Ethernet W5x00**, using [`Ethernet2`](https://github.com/adafruit/Ethernet2) or [`Ethernet3`](https://github.com/sstaub/Ethernet3) library
11. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico core**](https://github.com/earlephilhower/arduino-pico).
12. Add support to RP2040-based boards, such as **NANO_RP2040_CONNECT, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
13. Add Version String and Table of Contents
14. Add support to RP2040-based boards, such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) using WiFi / [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)
15. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico) using WiFi / [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)
16. Add support to ESP32 boards using native ESP WiFi
17. Add support to Generic boards, such as **MKR WiFi1010**, using [WiFi101 Library](https://github.com/arduino-libraries/WiFi101)
18. Add support to **Portenta_H7 Vision-shield Ethernet** using [`Portenta_Ethernet`](https://github.com/arduino/ArduinoCore-mbed/tree/master/libraries/Ethernet) library
19. Add support to **Portenta_H7 Murata WiFi** using [`Portenta_WiFi`](https://github.com/arduino/ArduinoCore-mbed/tree/master/libraries/WiFi) library


---
---

### Contributions and Thanks

1. Based on and modified from [TrippyLighting's EthernetBonjour](https://github.com/TrippyLighting/EthernetBonjour) and [Dario Pennisi's ArduinoMDNS](https://github.com/arduino-libraries/ArduinoMDNS)
2. Thanks to [Zuroy](https://github.com/Zuroy) to report the issue in [Portenta H7 MDNS Library compatibility #4](https://github.com/khoih-prog/MDNS_Generic/issues/4) then post an issue on [`ArduinoCore-mbed`](https://github.com/arduino/ArduinoCore-mbed) leading to a fix in [SocketWrapper: UDP: send packet on endPacket(), not on write() #337](https://github.com/arduino/ArduinoCore-mbed/pull/337) leading to the new version v1.3.0 to provide support to **Portenta_H7** using either Murata WiFi or Vision-shield Ethernet.

<table>
  <tr>
    <td align="center"><a href="https://github.com/TrippyLighting"><img src="https://github.com/TrippyLighting.png" width="100px;" alt="TrippyLighting"/><br /><sub><b>⭐️ TrippyLighting</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/pnndra"><img src="https://github.com/pnndra.png" width="100px;" alt="pnndra"/><br /><sub><b>⭐️ Dario Pennisi</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/Zuroy"><img src="https://github.com/Zuroy.png" width="100px;" alt="Zuroy"/><br /><sub><b>Zuroy</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- Most of the credits go to original authors **Georg Kaindl**, [**TrippyLighting**](https://github.com/TrippyLighting) and [**Dario Pennisi**](https://github.com/pnndra).

- The library is licensed under [GPLv3](https://github.com/khoih-prog/MDNS_Generic/blob/master/LICENSE)

---

## Copyright

1. Copyright (C) 2010 Georg Kaindl
2. Copyright (c) 2017 Arduino LLC.  All right reserved.
3. Copyright (c) 2020- Khoi Hoang



