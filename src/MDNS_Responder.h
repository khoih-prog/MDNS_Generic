/****************************************************************************************************************************
  MDNS_Responder.h
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

  Version: 1.4.2
  
  Version  Modified By   Date      Comments
  -------  -----------  ---------- -----------
  1.0.0    K Hoang      01/08/2020 Initial coding to support W5x00 using Ethernet, EthernetLarge libraries
                                   Supported boards: nRF52, STM32, SAMD21/SAMD51, SAM DUE, Mega
  ...
  1.3.0    K Hoang      28/09/2021 Add support to Portenta_H7, using WiFi or Ethernet
  1.3.1    K Hoang      10/10/2021 Update `platform.ini` and `library.json`
  1.4.0    K Hoang      26/01/2022 Fix `multiple-definitions` linker error
  1.4.1    K Hoang      11/04/2022 Use Ethernet_Generic library as default. Support SPI1/SPI2 for RP2040/ESP32
  1.4.2    K Hoang      12/10/2022 Fix bugs in UDP length check and in WiFi example
 *****************************************************************************************************************************/
// Port of CC3000 MDNS Responder to WINC1500.
// Author: Tony DiCola
//
// This MDNSResponder class implements just enough MDNS functionality to respond
// to name requests, for example 'foo.local'.  This does not implement any other
// MDNS or Bonjour functionality like services, etc.
//
// Copyright (c) 2016 Adafruit Industries.  All right reserved.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef MDNS_RESPONDER_H
#define MDNS_RESPONDER_H

#include "MDNS_Responder.hpp"
#include "MDNS_Responder_Impl.h"

#endif
