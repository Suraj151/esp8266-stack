/*******************************************************************************
This file is part of the Ewings Esp Stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

File            : GlobalTable.h
Author          : Suraj I.
created Date    : 1st Jan 2024

Note            : THIS FILE IS AUTOGENERATED - DO NOT EDIT MANUALLY
*******************************************************************************/

#ifndef _GLOBALTABLE_H_
#define _GLOBALTABLE_H_

#include <database/core/DatabaseTable.h>

/**
 * @name    GlobalTable
 *
 * @purpose Global table handles global config load/store operations
 *
 */
class GlobalTable : public DatabaseTable<global_config_table>
{

  public:
    /**
     * @purpose Constructor
     */
    GlobalTable()
    {
    }

    /**
     * @purpose Destructor
     */
    ~GlobalTable()
    {
    }

    /**
     * @purpose register table to database.
     */
    void boot()
    {
        this->register_table(GLOBAL_CONFIG_TABLE_ADDRESS);
    }

    /**
     * @purpose get/fetch table from database.
     */
    bool get(global_config_table *_table)
    {
        return this->get_table(_table, GLOBAL_CONFIG_TABLE_ADDRESS);
    }

    /**
     * @purpose set table from database.
     */
    bool set(global_config_table *_table)
    {
        return this->set_table(_table, GLOBAL_CONFIG_TABLE_ADDRESS);
    }

    /**
     * @purpose clear table in database.
     */
    void clear()
    {
        this->clear_table(GLOBAL_CONFIG_TABLE_ADDRESS);
    }

  private:
  protected:
};

extern GlobalTable __global_table;

#endif // _GLOBALTABLE_H_
