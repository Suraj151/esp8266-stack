/******************************** type defs ***********************************
This file is part of the Ewings Esp Stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

Author          : Suraj I.
created Date    : 1st June 2019
******************************************************************************/

#ifndef _DATA_TYPE_DEFS_H_
#define _DATA_TYPE_DEFS_H_

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <string>
#include <cstdio>
#include <cstring>
#include <functional>

// option to define the attribute for read only data
// redefine this in derived interface
#define RODT_ATTR(x) x

typedef uint8_t gpio_id_t;
typedef int64_t gpio_val_t;

typedef uint8_t wifi_mode_t;
typedef uint8_t sleep_mode_t;
typedef uint16_t wifi_status_t;
typedef uint8_t follow_redirects_t;

typedef uint16_t http_method_t;

/**
 * Define required callback type
 */
typedef std::function<void(int)> CallBackIntArgFn;
typedef std::function<void(void)> CallBackVoidArgFn;
typedef std::function<void(void *)> CallBackVoidPointerArgFn;

/**
 * Define log types
 */
typedef enum
{
  INFO_LOG,
  ERROR_LOG,
  WARNING_LOG,
  SUCCESS_LOG
} logger_type_t;

/**
 * Define ip stuff
 */
typedef enum
{
  IP_ADDR_TYPE_V4 = 4,  /** IPv4 */
  IP_ADDR_TYPE_V6 = 6,  /** IPv6 */
  IP_ADDR_TYPE_ANY = 46 /** IPv4+IPv6 ("dual-stack") */
} ip_addr_type;

struct ipaddress_t
{
  uint8_t ip4[4];
  ip_addr_type type;

  ipaddress_t(uint32_t _ip4) : type(IP_ADDR_TYPE_V4)
  {
    ip4[0] = (uint8_t)_ip4;
    ip4[1] = (uint8_t)(_ip4 >> 8);
    ip4[2] = (uint8_t)(_ip4 >> 16);
    ip4[3] = (uint8_t)(_ip4 >> 24);
  }

  ipaddress_t(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet) : type(IP_ADDR_TYPE_V4)
  {
    ip4[0] = first_octet;
    ip4[1] = second_octet;
    ip4[2] = third_octet;
    ip4[3] = fourth_octet;
  }

  operator std::string()
  {
    return (std::to_string(ip4[0]) + "." + std::to_string(ip4[1]) + "." + std::to_string(ip4[2]) + "." + std::to_string(ip4[3]));
  }

  operator uint32_t()
  {
    return (((uint32_t)ip4[0]<<24) | ((uint32_t)ip4[1]<<16) | ((uint32_t)ip4[2]<<8) | ((uint32_t)ip4[3]));
  }

  uint8_t operator[](int index)
  {
    return index < 4 ? ip4[index] : 0;
  }
};

/* upgrade defs */
typedef enum {
    UPGRADE_STATUS_FAILED = -1,
    UPGRADE_STATUS_SUCCESS,
    UPGRADE_STATUS_IGNORE,  // no update available
    UPGRADE_STATUS_MAX
} upgrade_status_t;

#endif
