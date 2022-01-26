/****************************************************************************************************************************
  MDNS_Generic.h

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

  Version: 1.4.0
  
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
  1.3.1    K Hoang      10/10/2021 Update `platform.ini` and `library.json`
  1.4.0    K Hoang      26/01/2022 Fix `multiple-definitions` linker error
 *****************************************************************************************************************************/

#ifndef __MDNS_GENERIC_H__
#define __MDNS_GENERIC_H__

#include "MDNS_Generic.hpp"
#include "MDNS_Generic_Impl.h"

#endif // __MDNS_GENERIC_H__
