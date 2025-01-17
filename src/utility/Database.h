/****************************** Database **************************************
This file is part of the pdi stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

Author          : Suraj I.
created Date    : 1st June 2019
******************************************************************************/

#ifndef _DATABASE_HANDLER_
#define _DATABASE_HANDLER_

#include <utility/Utility.h>

/**
 * define database tables max limit
 */
#ifdef MAX_DB_TABLES
#define MAX_TABLES MAX_DB_TABLES
#else
#define MAX_TABLES 20
#endif

class DatabaseTableAbstractLayer
{

public:
	friend class Database;

	/**
	 * DatabaseTableAbstractLayer constructor
	 */
	DatabaseTableAbstractLayer()
	{
		if (DatabaseTableAbstractLayer::m_total_instances < MAX_TABLES)
		{
			DatabaseTableAbstractLayer::m_instances[DatabaseTableAbstractLayer::m_total_instances] = this;
			DatabaseTableAbstractLayer::m_total_instances++;
		}
	}

	/**
	 * DatabaseTableAbstractLayer destructor
	 */
	~DatabaseTableAbstractLayer()
	{
	}

	/**
	 * override boot
	 */
	virtual void boot() = 0;
	/**
	 * override clear
	 */
	virtual void clear() = 0;

	/**
	 * @array	DatabaseTableAbstractLayer* m_instances
	 */
	static DatabaseTableAbstractLayer *m_instances[MAX_TABLES];
	/**
	 * @var	int m_total_instances
	 */
	static int m_total_instances;
};

/**
 * define table structure here
 */
struct struct_tables
{
	uint16_t m_table_address;
	uint16_t m_table_size;
	// void *m_default_table;
	DatabaseTableAbstractLayer *m_instance;
};

/**
 * Database class
 */
class Database
{

public:
	pdiutil::vector<struct_tables> m_database_tables;

	Database();
	~Database();

	void init_database(uint32_t _size);
	bool register_table(struct_tables &_table);
	struct_tables get_last_table(void);
	void clear_all(void);

	/**
	 * @var	uint db max size
	 */
	uint32_t m_max_db_size;
};

extern Database __database;
#endif
