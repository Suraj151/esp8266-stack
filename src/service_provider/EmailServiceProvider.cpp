/******************************* Email service *********************************
This file is part of the Ewings Esp8266 Stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

Author          : Suraj I.
created Date    : 1st June 2019
******************************************************************************/

#include <config/Config.h>

#if defined(ENABLE_EMAIL_SERVICE)

#include "EmailServiceProvider.h"


/**
 * begin email service with wifi and client
 *
 * @param ESP8266WiFiClass*	_wifi
 * @param WiFiClient*	      _wifi_client
 */
void EmailServiceProvider::begin( ESP8266WiFiClass* _wifi, WiFiClient* _wifi_client ){

  this->wifi = _wifi;
  this->wifi_client = _wifi_client;
  this->handleEmails();
}

/**
 * handle emails
 *
 */
void EmailServiceProvider::handleEmails(){

  email_config_table __email_config = __database_service.get_email_config_table();

  this->_mail_handler_cb_id = __task_scheduler.updateInterval(
    this->_mail_handler_cb_id,
    [&]() {

      email_config_table _email_config = __database_service.get_email_config_table();
      #ifdef EW_SERIAL_LOG
      Logln(F("Handling emails"));
      #endif
      if( strlen(_email_config.mail_host) > 0 && strlen(_email_config.sending_domain) > 0 &&
        strlen(_email_config.mail_from) > 0 && strlen(_email_config.mail_to) > 0 && _email_config.mail_frequency > 0
      ){

        String _payload = "";

        _payload += "MIME-Version: 1.0\n";
        _payload += "Content-Type: multipart/mixed; boundary=jncvdcsjnss\n";
        _payload += "--jncvdcsjnss\n";
        _payload += "Content-Type: text/plain; name=\"test.txt\"\n";
        _payload += "Content-Disposition:attachment; filename=\"test.txt\"\n";
        // _payload += "Content-Transfer-Encoding:base64\n";

        _payload += "this is test file.\n";

        _payload += "--jncvdcsjnss\n";
        // #ifdef ENABLE_GPIO_SERVICE
        //
        // for (uint8_t _pin = 0; _pin < MAX_NO_OF_GPIO_PINS; _pin++) {
        //
        //   if( !__gpio_service.is_exceptional_gpio_pin(_pin) ){
        //
        //     _payload += "D";
        //     _payload += _pin;
        //     _payload += " ( mode : ";
        //     _payload += __gpio_service.virtual_gpio_configs.gpio_mode[_pin];
        //     _payload += ", val : ";
        //     _payload += __gpio_service.virtual_gpio_configs.gpio_readings[_pin];
        //     _payload += ")\n";
        //   }
        // }
        // _payload += "A0 ( mode : ";
        // _payload += __gpio_service.virtual_gpio_configs.gpio_mode[MAX_NO_OF_GPIO_PINS];
        // _payload += ", val : ";
        // _payload += __gpio_service.virtual_gpio_configs.gpio_readings[MAX_NO_OF_GPIO_PINS];
        // _payload += ")\n\n";
        // #endif
        //
        // _payload += "Hello from Esp\n";
        // _payload += this->wifi->macAddress();

        int _size = _payload.length() + 1;
        char* _pload = new char[ _size ];
        memset( _pload, 0, _size );
        _payload.toCharArray( _pload, _size );

        this->sendMail( _pload );
        delete[] _pload;
      }
      _ClearObject(&_email_config);
    },
    __email_config.mail_frequency*1000, millis()
  );

  _ClearObject(&__email_config);
}

/**
 * send email and return the result of operation
 *
 * @return  bool
 */
bool EmailServiceProvider::sendMail( char* mail_body ){

  email_config_table _email_config = __database_service.get_email_config_table();

  bool ret = false;

  if( __status_wifi.wifi_connected ){

    ret = this->smtp.begin( this->wifi_client, _email_config.mail_host, _email_config.mail_port );
    if( ret ){
      ret = this->smtp.sendHello( _email_config.sending_domain );
    }
    if( ret ){
      ret = this->smtp.sendAuthLogin( _email_config.mail_username, _email_config.mail_password );
    }
    if( ret ){
      ret = this->smtp.sendFrom( _email_config.mail_from );
    }
    if( ret ){
      ret = this->smtp.sendTo( _email_config.mail_to );
    }
    if( ret ){
      ret = this->smtp.sendDataCommand();
    }
    if( ret ){
      this->smtp.sendDataHeader( _email_config.mail_from_name, _email_config.mail_to, _email_config.mail_subject );
      ret = this->smtp.sendDataBody( mail_body );
    }
    if( ret ){
      ret = this->smtp.sendQuit();
    }

    this->smtp.end();
  }

  _ClearObject(&_email_config);
  return ret;
}


#ifdef EW_SERIAL_LOG
/**
 * print email configs
 */
void EmailServiceProvider::printEmailConfigLogs(){

  email_config_table _email_config = __database_service.get_email_config_table();

  Logln(F("\nEmail Configs :"));
  // Logln(F("ssid\tpassword\tlocal\tgateway\tsubnet"));

  Log(_email_config.sending_domain); Log("\t");
  Log(_email_config.mail_host); Log("\t");
  Log(_email_config.mail_port); Log("\t");
  Log(_email_config.mail_username); Log("\t");
  Log(_email_config.mail_password); Log("\t\n");
  Log(_email_config.mail_from); Log("\t");
  Log(_email_config.mail_from_name); Log("\t");
  Log(_email_config.mail_to); Log("\t");
  Log(_email_config.mail_subject); Log("\t");
  Logln(_email_config.mail_frequency);
}
#endif

EmailServiceProvider __email_service;

#endif