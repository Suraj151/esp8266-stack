/**************************** WiFi Interface ***********************************
This file is part of the pdi stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

Author          : Suraj I.
created Date    : 1st June 2019
******************************************************************************/

#include "WiFiInterface.h"
#include "LoggerInterface.h"
#include "DeviceControlInterface.h"

extern "C" void preinit() {
  __i_dvc_ctrl.eraseConfig();
	uint8_t sta_mac[6];
  esp_wifi_get_mac(WIFI_IF_STA, sta_mac);
  // esp_efuse_mac_get_default(sta_mac);
  // wifi_get_macaddr(STATION_IF, sta_mac);
  sta_mac[0] +=2;
  esp_wifi_set_mac(WIFI_IF_AP, sta_mac);
  // esp_iface_mac_addr_set(sta_mac, ESP_MAC_WIFI_SOFTAP);
	// wifi_set_macaddr(SOFTAP_IF, sta_mac);
}

/**
 * begin wifi interface
 */
wifi_status_t toWifiStatus(wl_status_t stat)
{
  wifi_status_t _wifi_status = CONN_STATUS_MAX;
  switch (stat)
  {
  case WL_CONNECTED:
    _wifi_status = CONN_STATUS_CONNECTED;
    break;    
  case WL_NO_SSID_AVAIL:
    _wifi_status = CONN_STATUS_NOT_AVAILABLE;
    break;
  case WL_CONNECT_FAILED:
    _wifi_status = CONN_STATUS_CONNECTION_FAILED;
    break;
  case WL_DISCONNECTED:
    _wifi_status = CONN_STATUS_DISCONNECTED;
    break;
  default:
    _wifi_status = CONN_STATUS_MAX;
    break;
  }

  return _wifi_status;
}

/**
 * WiFiInterface constructor.
 */
WiFiInterface::WiFiInterface() : m_wifi(&WiFi), m_wifi_led(0)
{
  this->m_wifi->onEvent((WiFiEventSysCb)&WiFiInterface::wifi_event_handler_cb);
  // wifi_set_event_handler_cb( (wifi_event_handler_cb_t)&WiFiInterface::wifi_event_handler_cb );
}

/**
 * WiFiInterface destructor.
 */
WiFiInterface::~WiFiInterface()
{
  this->m_wifi = nullptr;
}

/**
 * Init the wifi interface
 */
void WiFiInterface::init()
{
  // this->m_wifi->mode(WIFI_AP_STA);
  setSleepMode(WIFI_PS_NONE); 
  setOutputPower(WIFI_POWER_19_5dBm);  
  persistent(false);
}

/**
 * setOutputPower
 */
void WiFiInterface::setOutputPower(float _dBm)
{
  if (nullptr != this->m_wifi)
  {
    this->m_wifi->setTxPower((wifi_power_t)WIFI_POWER_21dBm);
  }
}

/**
 * set persistent
 */
void WiFiInterface::persistent(bool _persistent)
{
  if (nullptr != this->m_wifi)
  {
    this->m_wifi->persistent(_persistent);
  }
}

/**
 * setMode
 */
bool WiFiInterface::setMode(pdi_wifi_mode_t _mode)
{

  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->mode(static_cast<WiFiMode_t>(_mode));
  }
  return status;
}

/**
 * getMode
 */
pdi_wifi_mode_t WiFiInterface::getMode()
{

  pdi_wifi_mode_t mode = 0;
  if (nullptr != this->m_wifi)
  {
    mode = static_cast<pdi_wifi_mode_t>(this->m_wifi->getMode());
  }
  return mode;
}

/**
 * setSleepMode
 */
bool WiFiInterface::setSleepMode(sleep_mode_t type, uint8_t listenInterval)
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->setSleep(static_cast<wifi_ps_type_t>(type));
  }
  return status;
}

/**
 * getSleepMode
 */
sleep_mode_t WiFiInterface::getSleepMode()
{

  sleep_mode_t mode = 0;
  if (nullptr != this->m_wifi)
  {
    mode = this->m_wifi->getSleep();
  }
  return mode;
}

/**
 * enableSTA
 */
bool WiFiInterface::enableSTA(bool _enable)
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->enableSTA(_enable);
  }
  return status;
}

/**
 * enableAP
 */
bool WiFiInterface::enableAP(bool _enable)
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->enableAP(_enable);
  }
  return status;
}

/**
 * return the channel
 */
uint8_t WiFiInterface::channel()
{
  uint8_t channel = 0;
  if (nullptr != this->m_wifi)
  {
    channel = this->m_wifi->channel();
  }
  return channel;
}

/**
 * hostByName
 */
int WiFiInterface::hostByName(const char *aHostname, ipaddress_t &aResult, uint32_t timeout_ms)
{
  int status = 0;
  if (nullptr != this->m_wifi)
  {
    IPAddress ip = (uint32_t)aResult;
    status = this->m_wifi->hostByName(aHostname, ip);
    aResult = (uint32_t)ip;
  }
  return status;
}

/**
 * begin wifi interface
 */
wifi_status_t WiFiInterface::begin(char *_ssid, char *_passphrase, int32_t _channel, const uint8_t *_bssid, bool _connect)
{
  wifi_status_t _wifi_status = CONN_STATUS_MAX;
  if (nullptr != this->m_wifi)
  {
    wl_status_t stat = this->m_wifi->begin(_ssid, _passphrase, _channel, _bssid, _connect);
    _wifi_status = toWifiStatus(stat);
  }
  return _wifi_status;
}

/**
 * config
 */
bool WiFiInterface::config(ipaddress_t &_local_ip, ipaddress_t &_gateway, ipaddress_t &_subnet)
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->config((uint32_t)_local_ip, (uint32_t)_gateway, (uint32_t)_subnet);
  }
  return status;
}

/**
 * reconnect
 */
bool WiFiInterface::reconnect()
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->reconnect();
  }
  return status;
}

/**
 * disconnect
 */
bool WiFiInterface::disconnect(bool _wifioff)
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->disconnect(_wifioff);
  }
  return status;
}

/**
 * isConnected
 */
bool WiFiInterface::isConnected()
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->isConnected();
  }
  return status;
}

/**
 * setAutoReconnect
 */
bool WiFiInterface::setAutoReconnect(bool _autoReconnect)
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->setAutoReconnect(_autoReconnect);
  }
  return status;
}

/**
 * localIP
 */
ipaddress_t WiFiInterface::localIP()
{
  IPAddress ip((uint32_t)0);
  if (nullptr != this->m_wifi)
  {
    ip = this->m_wifi->localIP();
  }
  return (uint32_t)ip;
}

/**
 * macAddress
 */
pdiutil::string WiFiInterface::macAddress()
{
  pdiutil::string mac;
  if (nullptr != this->m_wifi)
  {
    mac = this->m_wifi->macAddress().c_str();
  }
  return mac;
}

/**
 * subnetMask
 */
ipaddress_t WiFiInterface::subnetMask()
{
  IPAddress ip((uint32_t)0);
  if (nullptr != this->m_wifi)
  {
    ip = this->m_wifi->subnetMask();
  }
  return (uint32_t)ip;
}

/**
 * gatewayIP
 */
ipaddress_t WiFiInterface::gatewayIP()
{
  IPAddress ip((uint32_t)0);
  if (nullptr != this->m_wifi)
  {
    ip = this->m_wifi->gatewayIP();
  }
  return (uint32_t)ip;
}

/**
 * dnsIP
 */
ipaddress_t WiFiInterface::dnsIP(uint8_t _dns_no)
{
  IPAddress ip((uint32_t)0);
  if (nullptr != this->m_wifi)
  {
    ip = this->m_wifi->dnsIP(_dns_no);
  }
  return (uint32_t)ip;
}

/**
 * status
 */
wifi_status_t WiFiInterface::status()
{
  wifi_status_t _wifi_status = CONN_STATUS_MAX;
  if (nullptr != this->m_wifi)
  {
    wl_status_t stat = this->m_wifi->status();
    _wifi_status = toWifiStatus(stat);
  }
  return _wifi_status;
}

/**
 * SSID
 */
pdiutil::string WiFiInterface::SSID() const
{
  pdiutil::string ssid;
  if (nullptr != this->m_wifi)
  {
    ssid = this->m_wifi->SSID().c_str();
  }
  return ssid;
}

/**
 * BSSID
 */
uint8_t *WiFiInterface::BSSID()
{
  uint8_t *bssid = nullptr;
  if (nullptr != this->m_wifi)
  {
    bssid = this->m_wifi->BSSID();
  }
  return bssid;
}

/**
 * RSSI
 */
int32_t WiFiInterface::RSSI()
{
  int32_t rssi = 0;
  if (nullptr != this->m_wifi)
  {
    rssi = this->m_wifi->RSSI();
  }
  return rssi;
}

/**
 * softAP
 */
bool WiFiInterface::softAP(const char *_ssid, const char *_passphrase, int _channel, int _ssid_hidden, int _max_connection)
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->softAP(_ssid, _passphrase, _channel, _ssid_hidden, _max_connection);
  }
  return status;
}

/**
 * softAPConfig
 */
bool WiFiInterface::softAPConfig(ipaddress_t _local_ip, ipaddress_t _gateway, ipaddress_t _subnet)
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    // start lease from gateway onwards
    ipaddress_t lease_start(_gateway[0], _gateway[1], _gateway[2], _gateway[3]+1);
    // Set the DNS server for clients of the AP to the one we also use for the STA interface
    ipaddress_t dns((uint32_t)this->m_wifi->dnsIP());
    status = this->m_wifi->softAPConfig((uint32_t)_local_ip, (uint32_t)_gateway, (uint32_t)_subnet, (uint32_t)lease_start, (uint32_t)dns);
  }
  return status;
}

/**
 * softAPdisconnect
 */
bool WiFiInterface::softAPdisconnect(bool _wifioff)
{
  bool status = false;
  if (nullptr != this->m_wifi)
  {
    status = this->m_wifi->softAPdisconnect(_wifioff);
  }
  return status;
}

/**
 * softAPIP
 */
ipaddress_t WiFiInterface::softAPIP()
{
  IPAddress ip((uint32_t)0);
  if (nullptr != this->m_wifi)
  {
    ip = this->m_wifi->softAPIP();
  }
  return (uint32_t)ip;
}

/**
 * scanNetworks
 */
int8_t WiFiInterface::scanNetworks(bool _async, bool _show_hidden, uint8_t _channel, uint8_t *ssid)
{
  int8_t num = 0;
  if (nullptr != this->m_wifi)
  {
    num = this->m_wifi->scanNetworks(_async, _show_hidden, false, 300, _channel, (const char*)ssid);
  }
  return num;
}

/**
 * scanNetworksAsync
 */
void WiFiInterface::scanNetworksAsync(pdiutil::function<void(int)> _onComplete, bool _show_hidden)
{
  if (nullptr != this->m_wifi)
  {
    static int asyncScanTaskId = -1;

    // check whether scan task is already running and return
    if( asyncScanTaskId == -1 ){
      return;
    }else{  // start scanning for network with async true. 
      this->scanNetworks(true);
    }

    // scan every 500ms for scanning done
    asyncScanTaskId = __task_scheduler.updateInterval( asyncScanTaskId, [&]() {

      int16_t WiFiScanStatus = this->m_wifi->scanComplete();

      if (WiFiScanStatus < 0) {  // it is busy scanning or got an error

        if (WiFiScanStatus == WIFI_SCAN_FAILED) {

          LogE("WiFi Scan has failed. Starting again.\n");
          this->scanNetworks(true);
        }
        // other option is status WIFI_SCAN_RUNNING - just wait.
      } else {

        // callback on Found Zero or more Wireless Networks
        _onComplete(WiFiScanStatus);

        // clear scan task interval once scan complete
        __task_scheduler.clearInterval(asyncScanTaskId);
        asyncScanTaskId = -1;
      }
    }, 200);
  }
}

/**
 * SSID
 */
pdiutil::string WiFiInterface::SSID(uint8_t _networkItem)
{
  pdiutil::string ssid;
  if (nullptr != this->m_wifi)
  {
    ssid = this->m_wifi->SSID(_networkItem).c_str();
  }
  return ssid;
}

/**
 * RSSI
 */
int32_t WiFiInterface::RSSI(uint8_t _networkItem)
{
  int32_t rssi = 0;
  if (nullptr != this->m_wifi)
  {
    rssi = this->m_wifi->RSSI(_networkItem);
  }
  return rssi;
}

/**
 * BSSID
 */
uint8_t *WiFiInterface::BSSID(uint8_t _networkItem)
{
  uint8_t *bssid = nullptr;
  if (nullptr != this->m_wifi)
  {
    bssid = this->m_wifi->BSSID(_networkItem);
  }
  return bssid;
}

/**
 * scan ssid not in connected stations and return bssid and found result
 * 1. Get connected stations list
 * 2. Check whether scan result items are already in connected list
 * 3. If scanned ssid not in connected stations list then it can be connected
 * 4. Check its bssid marked as not ignored before make confimation on connection
 *
 * @param   char*     ssid
 * @param   uint8_t*  bssid
 * @return  bool
 */
bool WiFiInterface::get_bssid_within_scanned_nw_ignoring_connected_stations(char *ssid, uint8_t *bssid, uint8_t *ignorebssid, int _scanCount)
{

  if( nullptr == this->m_wifi || nullptr == ssid || nullptr == bssid || nullptr == ignorebssid ){
    return false;
  }

  LogI("Scanning stations\n");

  int n = _scanCount;
  // int indices[n];
  // for (int i = 0; i < n; i++) {
  //   indices[i] = i;
  // }
  // for (int i = 0; i < n; i++) {
  //   for (int j = i + 1; j < n; j++) {
  //     if (this->m_wifi->RSSI(indices[j]) > this->m_wifi->RSSI(indices[i])) {
  //       std::swap(indices[i], indices[j]);
  //     }
  //   }
  // }
  wifi_sta_list_t wifi_sta_list;
  memset(&wifi_sta_list, 0, sizeof(wifi_sta_list_t));
  esp_wifi_ap_get_sta_list(&wifi_sta_list);
  
  char* _ssid_buff = new char[WIFI_CONFIGS_BUF_SIZE];
  if( nullptr == _ssid_buff ){
    return false;
  }
  memset( _ssid_buff, 0, WIFI_CONFIGS_BUF_SIZE );

  for (int i = 0; i < n; ++i) {

    pdiutil::string _ssid = this->SSID(i);
    // _ssid.toCharArray( _ssid_buff, _ssid.length()+1 );
    strncpy(_ssid_buff, _ssid.c_str(), _ssid.size());

    if( __are_arrays_equal( ssid, _ssid_buff, _ssid.size() ) ){

      bool _found = false;

      for (int i = 0; i < wifi_sta_list.num; i++) {

		    wifi_sta_info_t sta_info = wifi_sta_list.sta[i];

        memcpy(bssid, sta_info.mac, 6);
        bssid[0] +=2;

        if( __are_arrays_equal( (char*)bssid, (char*)this->m_wifi->BSSID(i), 6 ) ){

          _found = true;
          break;
        }
		  }

      if( !_found ){

        if( !__are_arrays_equal( (char*)ignorebssid, (char*)this->BSSID(i), 6 ) ){
          memcpy(bssid, this->BSSID(i), 6);
          delete[] _ssid_buff;
          return true;
        }
      }
    }
  }

  delete[] _ssid_buff;
  return false;
}

/**
 * return the list of connected stations info to acess point
 */
bool WiFiInterface::getApsConnectedStations(pdiutil::vector<wifi_station_info_t> &stations)
{
  wifi_sta_list_t wifi_sta_list;
  memset(&wifi_sta_list, 0, sizeof(wifi_sta_list_t));
  esp_wifi_ap_get_sta_list(&wifi_sta_list);


  for (int i = 0; i < wifi_sta_list.num; i++) {

    wifi_sta_info_t sta_info = wifi_sta_list.sta[i];
    wifi_station_info_t _station(sta_info.mac, 0);

    stations.push_back(_station);
  }

  return true;
}

/**
 * n/w status indication
 */
void WiFiInterface::enableNetworkStatusIndication()
{
  m_wifi_led = 2;

  __i_dvc_ctrl.gpioMode(DIGITAL_WRITE, this->m_wifi_led);
  __i_dvc_ctrl.gpioWrite(DIGITAL_WRITE, this->m_wifi_led, HIGH );

  __task_scheduler.setInterval( [&]() { 

      LogI("Handling LED Status Indications\n");
      LogFmtI("RSSI : %d\n", this->m_wifi->RSSI());

      if( !this->m_wifi->localIP() != INADDR_NONE || !this->m_wifi->isConnected() || ( this->m_wifi->RSSI() < (int)WIFI_RSSI_THRESHOLD ) ){

        LogW("WiFi not connected.\n");
        __i_dvc_ctrl.gpioWrite(DIGITAL_WRITE, this->m_wifi_led, LOW );
      }else{

        __i_dvc_ctrl.gpioWrite(DIGITAL_WRITE, this->m_wifi_led, HIGH );
        __i_dvc_ctrl.wait(40);
        __i_dvc_ctrl.gpioWrite(DIGITAL_WRITE, this->m_wifi_led, LOW );
      }

    }, 2.5*MILLISECOND_DURATION_1000, __i_dvc_ctrl.millis_now() );
}

/**
 * enable napt feature
 */
void WiFiInterface::enableNAPT(bool enable)
{
  bool bStatus = this->m_wifi->AP.enableNAPT(enable);
  LogFmtS("NAPT enable status : %d\n", (int)bStatus);
}

/**
 * static wifi event handler
 *
 */
void WiFiInterface::wifi_event_handler_cb(arduino_event_t *_event)
{
  if( nullptr != _event ){

    LogFmtI("\nesp event : %d\n", (int)_event->event_id);
    event_name_t e = EVENT_NAME_MAX;

    if ( ARDUINO_EVENT_WIFI_STA_CONNECTED == _event->event_id ) {
      __task_scheduler.setTimeout( [&]() { __i_wifi.enableNAPT(true); }, NAPT_INIT_DURATION_AFTER_WIFI_CONNECT, __i_dvc_ctrl.millis_now() );
      e = EVENT_WIFI_STA_CONNECTED;
    }else if( ARDUINO_EVENT_WIFI_STA_DISCONNECTED == _event->event_id ){
      __task_scheduler.setTimeout( [&]() { __i_wifi.enableNAPT(false); }, MILLISECOND_DURATION_1000, __i_dvc_ctrl.millis_now() );
      e = EVENT_WIFI_STA_DISCONNECTED;
    }else if( ARDUINO_EVENT_WIFI_AP_STACONNECTED == _event->event_id ){
      e = EVENT_WIFI_AP_STACONNECTED;
    }else if( ARDUINO_EVENT_WIFI_AP_STADISCONNECTED == _event->event_id ){
      e = EVENT_WIFI_AP_STADISCONNECTED;
    }

    if( EVENT_NAME_MAX != e ){
      __utl_event.execute_event(e, _event);
    }
  }
}

/**
 * preinitWiFiOff
 */
void WiFiInterface::preinitWiFiOff()
{
  // WiFiClass::preinitWiFiOff();
}

WiFiInterface __i_wifi;