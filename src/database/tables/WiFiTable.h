/*******************************************************************************
This file is part of the Ewings Esp Stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

File            : WiFiTable.h
Author          : Suraj I.
created Date    : 1st Jan 2024

Note            : THIS FILE IS AUTOGENERATED - DO NOT EDIT MANUALLY
*******************************************************************************/

#ifndef _WIFITABLE_H_
#define _WIFITABLE_H_

#include <database/core/DatabaseTable.h>

/**
 * @name    WiFiTable
 *
 * @purpose Wifi table handles wifi configs load/store operations
 *
 */
class WiFiTable : public DatabaseTable<wifi_config_table>
{

  public:
    /**
     * @purpose Constructor
     */
    WiFiTable()
    {
    }

    /**
     * @purpose Destructor
     */
    ~WiFiTable()
    {
    }

    /**
     * @purpose register table to database.
     */
    void boot()
    {
        this->register_table(WIFI_CONFIG_TABLE_ADDRESS);
    }

    /**
     * @purpose get/fetch table from database.
     */
    bool get(wifi_config_table *_table)
    {
        return this->get_table(WIFI_CONFIG_TABLE_ADDRESS, _table);
    }

    /**
     * @purpose set table from database.
     */
    bool set(wifi_config_table *_table)
    {
        return this->set_table(WIFI_CONFIG_TABLE_ADDRESS, _table);
    }

    /**
     * @purpose clear table in database.
     */
    void clear()
    {
        this->clear_table(WIFI_CONFIG_TABLE_ADDRESS);
    }

  private:
  protected:
};

extern WiFiTable __wifi_table;

#endif // _WIFITABLE_H_
