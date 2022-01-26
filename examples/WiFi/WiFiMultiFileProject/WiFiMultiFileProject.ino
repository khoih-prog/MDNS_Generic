/****************************************************************************************************************************
  multiFileProject.ino
  
   mDNS library to support mDNS (registering services) and DNS-SD (service discovery).
  
  Based on and modified from https://github.com/arduino-libraries/ArduinoMDNS
  Built by Khoi Hoang https://github.com/khoih-prog/MDNS_Generic
  Licensed under MIT license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

// The .hpp contains only definitions, and can be included as many times as necessary, without `Multiple Definitions` Linker Error
// The .h contains implementations, and can be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error

#include "defines.h"
#include "arduino_secrets.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "MDNS_Generic.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "MDNS_Responder.h"

#include "multiFileProject.h"

void setup() 
{

}

void loop() 
{
  // put your main code here, to run repeatedly:
}
