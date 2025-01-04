# Portable Device Interface Stack

PDIStack Framework covers all essential things to build IoT applications easily.
Basically it is designed on the top of portable interface layers that any device can create their interface from. esp8266-arduino examples provided to make things easy to understand for developers.

**PDI Framework Structure**


<p align="center">
  <img width="500" src="https://github.com/Suraj151/esp8266-framework/blob/master/doc/ewings_stack.jpg">
</p>


Arduino has provided user-friendly libraries that use different devices SDK APIs at bottom. Since arduino has made its easy iot development environment impact over developers, it's easy for them to develop applications with Arduino ide.

PDI framework sits on the top of service layers which internally uses the portable interface. So the device which needs to run this framework should write the interface provided.

# Installation

**install from arduino ide**

Goto Tools->Manage Libraries... then in library manager window type pdi-framework in search bar then from results find pdi-framework by Suraj I., select latest version and click on install.

**install manually**

To install manually for esp8266 clone or download source, copy folder to esp8266 libraries path ( in windows 10 generally path is like ==> C:\Users\suraj\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.6.2\libraries...).

# Usage

Restart the arduino ide and navigate to File->Examples->pdi-framework->PdiStack example compile and upload.

**Note :** before compile make sure that you have selected correct board in arduino ide and in `devices/DeviceConfig.h` file as below
```
/**
 * enable/disable devices. enable/uncomment one from below list to get it compiled
 */
// #define MOCK_DEVICE_TEST
#define DEVICE_ESP8266
// #define DEVICE_ESP32
// #define DEVICE_ARDUINOUNO
```

for example we selected esp8266 device to compile and flash as above.

* after flash and initializing device completely, check in pc/mobile wifi list if **pdiStack** name appear.
* select it and enter default password **pdiStack@123**.
* finally after succesful connectinon to device open browser, type **192.168.0.1** in address bar and press enter
* you will directed to login screen, enter default username and password **( username: pdiStack, password: pdiStack@123 )**
* now you will able to see below menu options

<p align="center">
  <img src="https://github.com/Suraj151/esp8266-framework/blob/master/doc/portal_home_menu.jpg">
</p>


you can play with all settings. you can modify configs by making changes in files of src/config folder. Go to wifi settings and change the default station ssid, password to connect to your station. you can also change ssid and password for access point. device will reset once after you submit wifi settings, i.e. you have to reconnect device.

**Note** that by default session will active for 300 seconds once login, you can change its timeout in server config file.

**Note** not all devices having wifi/network feature to run web server on device as mentioned in above esp8266 example. e.g. arduino uno device wont have the web server enabled due to lack of network feature.

# Services

PDI framework provides some basic services that required to develop simple iot application. All services are available globally to each other. The services are

* **MQTT Service:**
This lightweight messaging protocol can be used to monitor or operate device itself or sensors that are connected to the device.
To configure and test MQTT go on device local server and select MQTT section under main menu.


* **OTA Service:**
Over The Air (OTA) feature has ability to update the device firmware remotely. By default OTA configurations are accessible with local server. OTA service is uses firmware version to decide whether start to update or not. OTA server can be set in OTA configuration which is accesible through local server.

    we need to set below route at server

    GET route format as ==> http://server.com/ota?mac_id=xx:xx:xx:xx:xx:xx&version=2019041100 --// this link is called by device on every x seconds provided in OTA configuration with its mac_id and current version ( available in global configuration ) as parameters. Response should be in json as ==> { latest : 2019041101 } which returns latest firmware version available on server

    by default update start only if device current firmware version is older than received firmware version from server.

    when device start the update process after knowing its current firmware version is older it looks for the downloadable file from the same server in format given below

    server address / bin / device mac address / latest firmware version .bin file
    e.g. http://server.com/bin/xx:xx:xx:xx:xx:xx/2019041101.bin


* **ESPNOW Service:**
This service is extended version of ESPNOW feature available in esp8266 with some easy to use api. with help of this feature we can build mesh networking, broadcasting etc n/w as per requirements. this service is not configurable from server for now. but you can manage it with easily available api of this service.

* **WiFi Service:**
This service provides simplified api's to dynamically interact with wifi devices on practical field. it has internet based connection ability over same network configs devices which are usefull in mesh scenarios. it also has ability to enable dynamic subnetting heiraechy where each individual device sits in different network and knows how far (in hop distance manner) he is from main hub centre.

* **GPIO Service:**
GPIOs are actually going to interact with sensors. We can read sensor or we can drive appliances with the help of this GPIO services. More on this GPIO service can work with MQTT/HTTP transports provided to monitor/control the GPIO's remotely

* **MAIL Service:**
MAIL service is uses SMTP transport to connect and send mail to any account. you should have a SMTP server account credentials that device uses to send mail. to set configuration goto local server and select Email section under main menu.
you can test it with tick option provided in email section before submit configuration form. the best demo way to test this section is create free mailtrap account where we get configurations.
this service should be enabled from common configuration file wherever this service act as dependency service. for example GPIO alert system has alert channel of email. GPIO alerts generated on user selected alert channel.

* **GPIO Alerts:**
GPIO alerts are provided to get notified on specific condition met. from local web portal of device GPIO alert conditions can be set in GPIO alert section which is available under GPIO manage section.

* **Database:**
Database service can be used to get/set any config in device NVM memory.

* **Auth Service:**
Auth service can be used to check whether user is logged in or not which required for few auth dependent services.

* **Serial Service:**
Serial service is mostly related to the serial communication of device. Serial service handles the serial events received on devices.

* **CommandLine Service:**
CommandLine service provides few basic commands to use. this will be covered in another section

# Local Web Server

PDI framework has local web portal. In case if device supports the internet then web server can be enabled. As aexample Esp8266 has built in WiFi feature that work in both station as well as access point mode. Station mode is mode using which we can connect to other wifi network. Access point mode is mode using which Esp8266 create its own network. PDI stack comes with a local http server facility using access point mode of esp8266. By default this server has setting, monitor pages added.

Web Server Framework has following components

* **Controllers :**
Controllers used to handle request from client. collecting user inputs, processing, building response for requests etc. works can be carried out in this component.

* **Middlewares :**
Middlewares used to provide filter like component for all requests. by default only auth middlware checks every request for its session. middlware needs to be assigned to route while registering them in controller.

* **Session Handler :**
Session handler takes care of login sessions. By default, login session expire after 5 minutes.

* **Route Handler :**
This handles routing operations of the server. It registers a specific controllers method to URL with facility of authentication through middlware.

* **Database :**
Devices can have non volatile memories where DB can store its data. Database service is used to store PDI framework related config data. Web Server uses this database service to fetch and view settings and control panel of device. For example Esp8266 has software eeprom library that actually uses space in flash memory

* **View Helpers :**
These helpers help to dynamically creates html elements.

* **Views :**
These are static html pages that split into header, middle and footer sections. At the time of sending http response we gathers them to form a complete html page.

* **Web Resources :**
These are required resources to server framework components.

# Features

Devices might have many built in features that will be useful in network applications. Those features are added with PDI Framework structure.

* **NAT :**
Network address translation (NAT) is a method of remapping one IP address space into another by modifying network address information in the IP header of packets while they are in transit across a traffic routing device. With this feature we can extend station network ( network that has active internet ) range.

    from v2.6.^ arduino has provided initial support example of NAT with lwip v2 variant (IPv4 only).

    before that lwip 1.4 is used to enable napt ( network address & port transform ) feature but with some customizations in lwip1.4.

    **you can test lwip 1.4** just rename "...esp8266/tools/sdk/lwip" with "...esp8266/tools/sdk/lwip.org" and copy lwip folder ( in this repo ) there. do not forget to select lwip 1.4 compile from source variant in arduino tools option while building.

    By default this feature is active based on what lwip variant from ide tool option is selected.

* **MESH :**
This feature easily possible with esp device esponow feature. in devices with esp8266 provided basic espnow service to make this available in application where mesh network is required. The basic motive to bring this feature is connectivity.


# Utilities

This common section is made to support/help all other section in their operations. This section consists of some most vital libraries that enable services to run in background/periodically. This section is the base for all other section hence all other services are dependent on this section.

* **Queue :**
Queue is dynamic service which enables users to push any data in it and pop it later for use.

* **String Helpers :**
String Helpers helps the user in many string related operations like finding, replacing, JSON parsing, etc.

* **Scheduler :**
Scheduler enables the feature of scheduling many things that executes later once or every time on specific intervals/timeouts. Scheduler also accepts priority as parameter for task, where by default big number is kept as big priority.

* **Reset Factory :**
This helps to reset the whole device to its default settings in case of device malfunctioning badly. By pressing flash key on device for about 6-7 seconds this service resets all settings to its default one. also this service accept task which should be run while reset factory executing.

* **Data Type Converters :**
As name clears the purpose of this utility. It just used to convert the data types from one to another like integer to string and vice versa.

* **Event :**
This is to handle specific event tasks that should be executed on event arrival. just register the event listener as task to perticular event and fire it when event happens.

* **CommandBase :**
This is to handle user commands. It will help to parse command options and provide it to command line service to execute the command.

# Device Iot (beta)

Added example of device iot where internal services take care of publishing/sending payload provided by device to mqtt iot server.
currently MQTT server configs for device iot are configured from server with DEVICE_IOT_CONFIG_REQ_URL set in **config/DeviceIotConfig.h**.
to DEVICE_IOT_CONFIG_REQ_URL http server should response the config includes
* topic
* password
* keepalive
* data rate
* samples per data

other configs like
* clientid, username are kept as device mac by default
* host, port can be configured in **config/DeviceIotConfig.h** file

you can modify them as per requirements

**Note** that currently mqtt configs (in **config/MqttConfig.h**/web portal) are not used for device iot purpose.

by default this service is disabled. to enable, just uncomment ENABLE_DEVICE_IOT in **config/Common.h** file

# Detailed Documentation
Detailed documentation is ongoing..., please visit [wiki page](https://github.com/Suraj151/esp8266-framework/wiki)....
