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

  Version: 1.0.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      01/08/2020 Initial coding to support W5x00 using Ethernet, EthernetLarge libraries
                                  Supported boards: nRF52, STM32, SAMD21/SAMD51, SAM DUE, Mega
 *****************************************************************************************************************************/

#ifndef MDNS_Debug_H
#define MDNS_Debug_H

#include <stdio.h>

#ifdef MDNS_DEBUG_PORT
#define MDNS_DEBUG_OUTPUT MDNS_DEBUG_PORT
#else
#define MDNS_DEBUG_OUTPUT Serial
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


#define MDNS_LOGERROR(x)        if(_MDNS_LOGLEVEL_>0) { MDNS_DEBUG_OUTPUT.print("[MDNS] "); MDNS_DEBUG_OUTPUT.println(x); }
#define MDNS_LOGERROR1(x,y)     if(_MDNS_LOGLEVEL_>0) { MDNS_DEBUG_OUTPUT.print("[MDNS] "); MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(y); }
#define MDNS_LOGERROR2(x,y,z)   if(_MDNS_LOGLEVEL_>0) { MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(y); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(z); }
#define MDNS_LOGERROR3(x,y,z,w) if(_MDNS_LOGLEVEL_>0) { MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(y); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(z); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(w); }

#define MDNS_LOGWARN(x)         if(_MDNS_LOGLEVEL_>1) { MDNS_DEBUG_OUTPUT.print("[MDNS] "); MDNS_DEBUG_OUTPUT.println(x); }
#define MDNS_LOGWARN1(x,y)      if(_MDNS_LOGLEVEL_>1) { MDNS_DEBUG_OUTPUT.print("[MDNS] "); MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(y); }
#define MDNS_LOGWARN2(x,y,z)    if(_MDNS_LOGLEVEL_>1) { MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(y); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(z); }
#define MDNS_LOGWARN3(x,y,z,w)    if(_MDNS_LOGLEVEL_>1) { MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(y); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(z); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(w); }

#define MDNS_LOGINFO(x)         if(_MDNS_LOGLEVEL_>2) { MDNS_DEBUG_OUTPUT.print("[MDNS] "); MDNS_DEBUG_OUTPUT.println(x); }
#define MDNS_LOGINFO1(x,y)      if(_MDNS_LOGLEVEL_>2) { MDNS_DEBUG_OUTPUT.print("[MDNS] "); MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(y); }
#define MDNS_LOGINFO2(x,y,z)    if(_MDNS_LOGLEVEL_>2) { MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(y); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(z); }
#define MDNS_LOGINFO3(x,y,z,w)  if(_MDNS_LOGLEVEL_>2) { MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(y); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(z); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(w); }


#define MDNS_LOGDEBUG(x)        if(_MDNS_LOGLEVEL_>3) { MDNS_DEBUG_OUTPUT.println(x); }
#define MDNS_LOGDEBUG0(x)       if(_MDNS_LOGLEVEL_>3) { MDNS_DEBUG_OUTPUT.print(x); }
#define MDNS_LOGDEBUG1(x,y)     if(_MDNS_LOGLEVEL_>3) { MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(y); }
#define MDNS_LOGDEBUG2(x,y,z)   if(_MDNS_LOGLEVEL_>3) { MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(y); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(z); }
#define MDNS_LOGDEBUG3(x,y,z,w) if(_MDNS_LOGLEVEL_>3) { MDNS_DEBUG_OUTPUT.print(x); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(y); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.print(z); MDNS_DEBUG_OUTPUT.print(" "); MDNS_DEBUG_OUTPUT.println(w); }


#endif    // MDNS_Debug_H
