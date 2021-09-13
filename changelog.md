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

* [Changelog](#changelog)
  * [Releases v1.3.0-beta1](#releases-v130-beta1)
  * [Releases v1.2.1](#releases-v121)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.1](#releases-v101)
  * [Releases v1.0.0](#releases-v100)

---
---

## Changelog

### Releases v1.3.0-beta1

1. Add support to Portenta_H7, using WiFi or Ethernet. **Still not working**, just for preliminary tests. Check 

* 1.1 [**Portenta H7 UDP Multicast not working - mbed v2.4.1** #321](https://github.com/arduino/ArduinoCore-mbed/issues/321)
* 1.2 [**Portenta H7 MDNS Library compatibility** #4](https://github.com/khoih-prog/MDNS_Generic/issues/4)

for latest situation.


### Releases v1.2.1

 1. Remove support to ESP8266 to use native [**ESP8266mDNS** library](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS)

### Releases v1.2.0

 1. Add support to RP2040-based boards, such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) using WiFi / [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)
 2. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico) using WiFi / [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)
 3. Add support to ESP32 and ESP8266 boards using native ESP WiFi
 4. Add support to Generic boards, such as **MKR WiFi1010**, using [WiFi101 Library](https://github.com/arduino-libraries/WiFi101)
 5. Add WiFi-related examples. 
 6. Modify hostname from easily-duplicated `arduino` to board-related hostname to fix issue caused by duplicated hostname, such as [mDNS stops working after two minutes #5](https://github.com/khoih-prog/MDNS_Generic/issues/5)
 7. Verify issue [**mDNS stops working after two minutes** #5](https://github.com/khoih-prog/MDNS_Generic/issues/5) is fixed, using Nano_RP2040_Connect, WiFiNINA FW 1.4.8 and [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)
 8. Change License from `MIT` to [GPLv3](https://github.com/khoih-prog/MDNS_Generic/blob/master/LICENSE)


### Releases v1.1.0

 1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
 2. Add support to RP2040-based boards, such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
 3. Update examples
 4. Update `Packages' Patches
 5. Add Version String and Table of Contents

### Releases v1.0.1

1. Add support to **W5x00 using Ethernet2 or Ethernet3 library**
2. Update Platform.ini to support PlatformIO 5.x owner-based dependency declaration.
3. Update Packages' Patches.
4. Update Libraries' Patches for **Ethernet2 library to add Multicast feature** necessary for this [**MDNS_Generic library**](https://github.com/khoih-prog/MDNS_Generic)
5. Enhance examples.


#### Releases v1.0.0

1. Add support to **nRF52** boards, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**.
2. Add support to **SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
3. Add support to **SAMD21 (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.)**.
4. Add support to **Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)**
5. Add support to all **STM32F/L/H/G/WB/MP1 (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.)**
6. Add support to **Teensy (4.1, 4.0, 3.x, Teensy++ 2.0, Teensy 2.0, etc.)**
7. Add sample Packages Patches for **STM32F/L/H/G/WB/MP1**
8. Add Library Patches for Ethernet.
9. Add Packages' Patches for Arduino SAMD21 to fix compiler error issue when using **STL** for Nano-33-IoT, ZERO, MKR, etc.


