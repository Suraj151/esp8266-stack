/********************************* PDI stack *********************************
This file is part of the pdi stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

Author          : Suraj I.
created Date    : 1st June 2019
******************************************************************************/

#ifndef _PDI_STACK_H_
#define _PDI_STACK_H_

#include <interface/pdi.h>

#ifdef ENABLE_HTTP_SERVER
#include <webserver/WebServer.h>
#endif

#include <service_provider/database/DatabaseServiceProvider.h>
#include <service_provider/device/FactoryResetServiceProvider.h>

#ifdef ENABLE_GPIO_SERVICE
#include <service_provider/device/GpioServiceProvider.h>
#endif

#ifdef ENABLE_WIFI_SERVICE
#include <service_provider/network/WiFiServiceProvider.h>
#endif

#ifdef ENABLE_OTA_SERVICE
#include <service_provider/device/OtaServiceProvider.h>
#endif

#ifdef ENABLE_MQTT_SERVICE
#include <service_provider/transport/MqttServiceProvider.h>
#endif

#ifdef ENABLE_EMAIL_SERVICE
#include <service_provider/email/EmailServiceProvider.h>
#endif

#ifdef ENABLE_DEVICE_IOT
#include <service_provider/iot/DeviceIotServiceProvider.h>
#endif

#ifdef ENABLE_SERIAL_SERVICE
#include <service_provider/transport/SerialServiceProvider.h>
#endif

#ifdef ENABLE_AUTH_SERVICE
#include <service_provider/auth/AuthServiceProvider.h>
#endif

#ifdef ENABLE_CMD_SERVICE
#include <service_provider/cmd/CommandLineServiceProvider.h>
#endif

/**
 * PDIStack class
 */
class PDIStack {

  public:

    /**
     * PDIStack constructor.
     */
    PDIStack();
    /**
     * PDIStack destructor.
     */
    ~PDIStack();

    void initialize( void );
    void serve( void );

  protected:
    static void handleLogPrints( void );

#ifdef ENABLE_WIFI_SERVICE
    /**
		 * @var	iClientInterface*  m_client
		 */
    iClientInterface  *m_client;

    /**
		 * @var	iServerInterface*  m_server
		 */
    iServerInterface  *m_server;
#endif
};

extern PDIStack PdiStack;

#endif
