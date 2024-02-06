/*******************************************************************************
This file is part of the Ewings Esp Stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

File            : MqttPubSubTable.h
Author          : Suraj I.
created Date    : 1st Jan 2024

Note            : THIS FILE IS AUTOGENERATED - DO NOT EDIT MANUALLY
*******************************************************************************/

#ifndef _MQTTPUBSUBTABLE_H_
#define _MQTTPUBSUBTABLE_H_

#include <database/core/DatabaseTable.h>

/**
 * @name    MqttPubSubTable
 *
 * @purpose Mqtt PubSub table handles publish & subscribe topic configs load/store operations
 *
 */
class MqttPubSubTable : public DatabaseTable<mqtt_pubsub_config_table>
{

  public:
    /**
     * @purpose Constructor
     */
    MqttPubSubTable()
    {
    }

    /**
     * @purpose Destructor
     */
    ~MqttPubSubTable()
    {
    }

    /**
     * @purpose register table to database.
     */
    void boot()
    {
        this->register_table(MQTT_PUBSUB_CONFIG_TABLE_ADDRESS);
    }

    /**
     * @purpose get/fetch table from database.
     */
    bool get(mqtt_pubsub_config_table *_table)
    {
        return this->get_table(MQTT_PUBSUB_CONFIG_TABLE_ADDRESS, _table);
    }

    /**
     * @purpose set table from database.
     */
    bool set(mqtt_pubsub_config_table *_table)
    {
        return this->set_table(MQTT_PUBSUB_CONFIG_TABLE_ADDRESS, _table);
    }

    /**
     * @purpose clear table in database.
     */
    void clear()
    {
        this->clear_table(MQTT_PUBSUB_CONFIG_TABLE_ADDRESS);
    }

  private:
  protected:
};

extern MqttPubSubTable __mqtt_pubsub_table;

#endif // _MQTTPUBSUBTABLE_H_
