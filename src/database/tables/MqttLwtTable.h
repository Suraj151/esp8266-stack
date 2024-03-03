/*******************************************************************************
This file is part of the Ewings Esp Stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

File            : MqttLwtTable.h
Author          : Suraj I.
created Date    : 1st Jan 2024

Note            : THIS FILE IS AUTOGENERATED - DO NOT EDIT MANUALLY
*******************************************************************************/

#ifndef _MQTTLWTTABLE_H_
#define _MQTTLWTTABLE_H_

#include <database/core/DatabaseTable.h>

/**
 * @name    MqttLwtTable
 *
 * @purpose Mqtt Lwt table handles LWT configs load/store operations
 *
 */
class MqttLwtTable : public DatabaseTable<mqtt_lwt_config_table>
{

  public:
    /**
     * @purpose Constructor
     */
    MqttLwtTable()
    {
    }

    /**
     * @purpose Destructor
     */
    ~MqttLwtTable()
    {
    }

    /**
     * @purpose register table to database.
     */
    void boot()
    {
        this->register_table(MQTT_LWT_CONFIG_TABLE_ADDRESS);
    }

    /**
     * @purpose get/fetch table from database.
     */
    bool get(mqtt_lwt_config_table *_table)
    {
        return this->get_table(MQTT_LWT_CONFIG_TABLE_ADDRESS, _table);
    }

    /**
     * @purpose set table from database.
     */
    bool set(mqtt_lwt_config_table *_table)
    {
        return this->set_table(MQTT_LWT_CONFIG_TABLE_ADDRESS, _table);
    }

    /**
     * @purpose clear table in database.
     */
    void clear()
    {
        this->clear_table(MQTT_LWT_CONFIG_TABLE_ADDRESS);
    }

  private:
  protected:
};

extern MqttLwtTable __mqtt_lwt_table;

#endif // _MQTTLWTTABLE_H_