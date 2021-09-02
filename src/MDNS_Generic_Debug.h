/****************************************************************************************************************************
  MDNS_Generic_Debug.h
   
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

#ifndef MDNS_Debug_H
#define MDNS_Debug_H

#include <stdio.h>

#ifdef MDNS_DEBUG_PORT
  #define MDNS_DBG_PORT MDNS_DEBUG_PORT
#else
  #define MDNS_DBG_PORT Serial
#endif

// Change _MDNS_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _MDNS_LOGLEVEL_
#define _MDNS_LOGLEVEL_       0
#endif

///////////////////////////////////////

const char MDNS_MARK[]  = "[MDNS] ";
const char MDNS_SP[]    = " ";

#define MDNS_PRINT          MDNS_DBG_PORT.print
#define MDNS_PRINTLN        MDNS_DBG_PORT.println
#define MDNS_FLUSH          MDNS_DBG_PORT.flush

#define MDNS_PRINT_MARK     MDNS_PRINT(MDNS_MARK)
#define MDNS_PRINT_SP       MDNS_PRINT(MDNS_SP)

///////////////////////////////////////

#define MDNS_LOGERROR(x)        if(_MDNS_LOGLEVEL_>0) { MDNS_PRINT_MARK; MDNS_PRINTLN(x); }
#define MDNS_LOGERROR0(x)       if(_MDNS_LOGLEVEL_>0) { MDNS_PRINT(x); }
#define MDNS_LOGERROR1(x,y)     if(_MDNS_LOGLEVEL_>0) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINTLN(y); }
#define MDNS_LOGERROR2(x,y,z)   if(_MDNS_LOGLEVEL_>0) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINT(y); MDNS_PRINT_SP; MDNS_PRINTLN(z); }
#define MDNS_LOGERROR3(x,y,z,w) if(_MDNS_LOGLEVEL_>0) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINT(y); MDNS_PRINT_SP; MDNS_PRINT(z); MDNS_PRINT_SP; MDNS_PRINTLN(w); }

///////////////////////////////////////

#define MDNS_LOGWARN(x)         if(_MDNS_LOGLEVEL_>1) { MDNS_PRINT_MARK; MDNS_PRINTLN(x); }
#define MDNS_LOGWARN0(x)        if(_MDNS_LOGLEVEL_>1) { MDNS_PRINT(x); }
#define MDNS_LOGWARN1(x,y)      if(_MDNS_LOGLEVEL_>1) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINTLN(y); }
#define MDNS_LOGWARN2(x,y,z)    if(_MDNS_LOGLEVEL_>1) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINT(y); MDNS_PRINT_SP; MDNS_PRINTLN(z); }
#define MDNS_LOGWARN3(x,y,z,w)    if(_MDNS_LOGLEVEL_>1) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINT(y); MDNS_PRINT_SP; MDNS_PRINT(z); MDNS_PRINT_SP; MDNS_PRINTLN(w); }

///////////////////////////////////////

#define MDNS_LOGINFO(x)         if(_MDNS_LOGLEVEL_>2) { MDNS_PRINT_MARK; MDNS_PRINTLN(x); }
#define MDNS_LOGINFO0(x)        if(_MDNS_LOGLEVEL_>2) { MDNS_PRINT(x); }
#define MDNS_LOGINFO1(x,y)      if(_MDNS_LOGLEVEL_>2) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINTLN(y); }
#define MDNS_LOGINFO2(x,y,z)    if(_MDNS_LOGLEVEL_>2) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINT(y); MDNS_PRINT_SP; MDNS_PRINTLN(z); }
#define MDNS_LOGINFO3(x,y,z,w)  if(_MDNS_LOGLEVEL_>2) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINT(y); MDNS_PRINT_SP; MDNS_PRINT(z); MDNS_PRINT_SP; MDNS_PRINTLN(w); }

///////////////////////////////////////

#define MDNS_LOGDEBUG(x)        if(_MDNS_LOGLEVEL_>3) { MDNS_PRINT_MARK; MDNS_PRINTLN(x); }
#define MDNS_LOGDEBUG0(x)       if(_MDNS_LOGLEVEL_>3) { MDNS_PRINT(x); }
#define MDNS_LOGDEBUG1(x,y)     if(_MDNS_LOGLEVEL_>3) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINTLN(y); }
#define MDNS_LOGDEBUG2(x,y,z)   if(_MDNS_LOGLEVEL_>3) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINT(y); MDNS_PRINT_SP; MDNS_PRINTLN(z); }
#define MDNS_LOGDEBUG3(x,y,z,w) if(_MDNS_LOGLEVEL_>3) { MDNS_PRINT_MARK; MDNS_PRINT(x); MDNS_PRINT_SP; MDNS_PRINT(y); MDNS_PRINT_SP; MDNS_PRINT(z); MDNS_PRINT_SP; MDNS_PRINTLN(w); }

///////////////////////////////////////

#endif    // MDNS_Debug_H
