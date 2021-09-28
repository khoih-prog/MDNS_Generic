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

  Version: 1.3.0
  
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
 *****************************************************************************************************************************/

#ifndef __MDNS_GENERIC_H__
#define __MDNS_GENERIC_H__

#if ( SYSTEM_ENDIAN == _ENDIAN_LITTLE_ )
  #warning SYSTEM_ENDIAN == _ENDIAN_LITTLE_
#else
  #warning SYSTEM_ENDIAN == _ENDIAN_BIG_
#endif

#define MDNS_GENERIC_VERSION        "MDNS_Generic v1.3.0"

extern "C"
{
  #include <inttypes.h>
}

#include <Arduino.h>

#include "MDNS_Generic_Debug.h"


typedef uint8_t byte;

typedef enum _MDNSState_t
{
  MDNSStateIdle,
  MDNSStateQuerySent
} MDNSState_t;

typedef enum _MDNSError_t
{
  MDNSTryLater                = 3,
  MDNSNothingToDo             = 2,
  MDNSSuccess                 = 1,
  MDNSInvalidArgument         = -1,
  MDNSOutOfMemory             = -2,
  MDNSSocketError             = -3,
  MDNSAlreadyProcessingQuery  = -4,
  MDNSNotFound                = -5,
  MDNSServerError             = -6,
  MDNSTimedOut                = -7
} MDNSError_t;

typedef struct _MDNSDataInternal_t 
{
  uint32_t xid;
  uint32_t lastQueryFirstXid;
} MDNSDataInternal_t;

typedef enum _MDNSServiceProtocol_t 
{
  MDNSServiceTCP,
  MDNSServiceUDP
} MDNSServiceProtocol_t;

typedef MDNSServiceProtocol_t MDNSServiceProtocol;

typedef struct _MDNSServiceRecord_t 
{
  uint16_t                port;
  MDNSServiceProtocol_t   proto;
  uint8_t*                name;
  uint8_t*                servName;
  uint8_t*                textContent;
} MDNSServiceRecord_t;

typedef void (*MDNSNameFoundCallback)(const char*, IPAddress);
typedef void (*MDNSServiceFoundCallback)(const char*, MDNSServiceProtocol_t, const char*, IPAddress, unsigned short, const char*);

#define  NumMDNSServiceRecords   (8)

//class MDNS
class MDNS
{
  private:
    UDP*                      _udp;
    IPAddress                 _ipAddress;
    MDNSDataInternal_t        _mdnsData;
    MDNSState_t               _state;
    uint8_t*                  _name;
    MDNSServiceRecord_t*      _serviceRecords[NumMDNSServiceRecords];
    unsigned long             _lastAnnounceMillis;
  
    uint8_t*                  _resolveNames[2];
    unsigned long             _resolveLastSendMillis[2];
    unsigned long             _resolveTimeouts[2];

    MDNSServiceProtocol_t     _resolveServiceProto;

    MDNSNameFoundCallback     _nameFoundCallback;
    MDNSServiceFoundCallback  _serviceFoundCallback;

    MDNSError_t _processMDNSQuery();
    MDNSError_t _sendMDNSMessage(uint32_t peerAddress, uint32_t xid, int type, int serviceRecord);


    void _writeDNSName(const uint8_t* name, uint16_t* pPtr, uint8_t* buf, int bufSize, int zeroTerminate);
    void _writeMyIPAnswerRecord(uint16_t* pPtr, uint8_t* buf, int bufSize);
    void _writeServiceRecordName(int recordIndex, uint16_t* pPtr, uint8_t* buf, int bufSize, int tld);
    void _writeServiceRecordPTR(int recordIndex, uint16_t* pPtr, uint8_t* buf, int bufSize, uint32_t ttl);

    int _initQuery(uint8_t idx, const char* name, unsigned long timeout);
    void _cancelQuery(uint8_t idx);

    uint8_t* _findFirstDotFromRight(const uint8_t* str);

    void _removeServiceRecord(int idx);

    int _matchStringPart(const uint8_t** pCmpStr, int* pCmpLen, const uint8_t* buf, int dataLen);

    const uint8_t* _postfixForProtocol(MDNSServiceProtocol_t proto);

    void _finishedResolvingName(char* name, const byte ipAddr[4]);
    
  public:
    MDNS(UDP& udp);
    ~MDNS();

    int begin(const IPAddress& ip);
    int begin(const IPAddress& ip, const char* name);
    void run();

    int setName(const char* name);
    
    // KH, to convert to be ESP-compatible
    // Add service to MDNS-SD
    // MDNS.addService("http", "tcp", HTTP_PORT);

    int addServiceRecord(const char* name, uint16_t port, MDNSServiceProtocol_t proto);
    int addServiceRecord(const char* name, uint16_t port, MDNSServiceProtocol_t proto, const char* textContent);

    void removeServiceRecord(uint16_t port, MDNSServiceProtocol_t proto);
    void removeServiceRecord(const char* name, uint16_t port, MDNSServiceProtocol_t proto);

    void removeAllServiceRecords();

    void setNameResolvedCallback(MDNSNameFoundCallback newCallback);
    int resolveName(const char* name, unsigned long timeout);
    void cancelResolveName();
    int isResolvingName();

    void setServiceFoundCallback(MDNSServiceFoundCallback newCallback);
    int startDiscoveringService(const char* serviceName, MDNSServiceProtocol_t proto,
                                unsigned long timeout);
    void stopDiscoveringService();
    int isDiscoveringService();
};

#include "MDNS_Generic_Impl.h"

#endif // __MDNS_GENERIC_H__
