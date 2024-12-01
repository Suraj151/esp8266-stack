/**************************** WiFi Interface ***********************************
This file is part of the pdi stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

Author          : Suraj I.
created Date    : 1st June 2019
******************************************************************************/

#ifndef _MOCKDEVICE_WIFI_INTERFACE_H_
#define _MOCKDEVICE_WIFI_INTERFACE_H_

#include "mockdevice.h"
#include <interface/pdi/modules/wifi/iWiFiInterface.h>
#include "LoggerInterface.h"
#include "DeviceControlInterface.h"

// declare device specific
// class IPAddress;

/**
 * WiFiInterface class
 */
class WiFiInterface : public iWiFiInterface
{

public:
  /**
   * WiFiInterface constructor.
   */
  WiFiInterface(){}
  /**
   * WiFiInterface destructor.
   */
  ~WiFiInterface(){}

  // generic api's
  void init() override{}
  void setOutputPower(float _dBm) override{}
  void persistent(bool _persistent) override{}
  bool setMode(wifi_mode_t _mode) override{return 0;}
  wifi_mode_t getMode() override{return 0;}
  bool setSleepMode(sleep_mode_t type, uint8_t listenInterval = 0) override{return 0;}
  sleep_mode_t getSleepMode() override{return 0;}
  bool enableSTA(bool _enable) override{return 0;}
  bool enableAP(bool _enable) override{return 0;}
  uint8_t channel() override{return 0;}
  int hostByName(const char *aHostname, ipaddress_t &aResult, uint32_t timeout_ms) override{return 0;}

  wifi_status_t begin(char *_ssid, char *_passphrase = nullptr, int32_t _channel = 0, const uint8_t *_bssid = nullptr, bool _connect = true) override{return CONN_STATUS_MAX;}
  bool config(ipaddress_t &_local_ip, ipaddress_t &_gateway, ipaddress_t &_subnet) override{return 0;}
  bool reconnect() override{return 0;}
  bool disconnect(bool _wifioff = false) override{return 0;}
  bool isConnected() override{return 0;}
  bool setAutoReconnect(bool _autoReconnect) override{return 0;}

  // STA network info
  ipaddress_t localIP() override{return 0;}
  std::string macAddress() override{return "";}
  ipaddress_t subnetMask() override{return 0;}
  ipaddress_t gatewayIP() override{return 0;}
  ipaddress_t dnsIP(uint8_t _dns_no = 0) override{return 0;}

  // STA WiFi info
  wifi_status_t status() override{return CONN_STATUS_MAX;}
  std::string SSID() const override{return "";}
  uint8_t *BSSID() override{return 0;}
  int32_t RSSI() override{return 0;}

  // Soft AP api's
  bool softAP(const char *_ssid, const char *_passphrase = nullptr, int _channel = 1, int _ssid_hidden = 0, int _max_connection = 4) override{return 0;}
  bool softAPConfig(ipaddress_t _local_ip, ipaddress_t _gateway, ipaddress_t _subnet) override{return 0;}
  bool softAPdisconnect(bool _wifioff = false) override{return 0;}
  ipaddress_t softAPIP() override{return 0;}

  // n/w scan api's
  int8_t scanNetworks(bool _async = false, bool _show_hidden = false, uint8_t _channel = 0, uint8_t *ssid = nullptr) override{return 0;}
  void scanNetworksAsync(std::function<void(int)> _onComplete, bool _show_hidden = false) override{}
  std::string SSID(uint8_t _networkItem) override{return "";}
  int32_t RSSI(uint8_t _networkItem) override{return 0;}
  uint8_t *BSSID(uint8_t _networkItem) override{return 0;}
  bool get_bssid_within_scanned_nw_ignoring_connected_stations(char *ssid, uint8_t *bssid, uint8_t *ignorebssid, int _scanCount) override{return 0;}
  bool getApsConnectedStations(std::vector<wifi_station_info_t> &stations) override{return 0;};

  void enableNetworkStatusIndication() override{}
  void enableNAPT() override{}
  // static void wifi_event_handler_cb( System_Event_t * _event ){}

  // misc api's
  static void preinitWiFiOff(){}

private:

  /**
   * @var	int16_t for network indication
   */
  int16_t   m_wifi_led;
};

#endif