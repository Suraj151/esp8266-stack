/********************* ESP32 Portable Device Interface ************************
This file is part of the pdi stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

Author          : Suraj I.
created Date    : 1st Jan 2024
******************************************************************************/

#ifndef _ESP32_PORTABLE_DEVICE_INTERFACE_H_
#define _ESP32_PORTABLE_DEVICE_INTERFACE_H_

#include "LoggerInterface.h"
#include "DatabaseInterface.h"
#include "DeviceControlInterface.h"
#ifdef ENABLE_WIFI_SERVICE
#include "WiFiInterface.h"
#include "WiFiClientInterface.h"
#include "WiFiServerInterface.h"
#endif
#ifdef ENABLE_NETWORK_SERVICE
#include "NtpInterface.h"
#include "PingInterface.h"
#endif
#ifdef ENABLE_SERIAL_SERVICE
#include "SerialInterface.h"
#endif

#endif  // _ESP32_PORTABLE_DEVICE_INTERFACE_H_
