/******************************* Service Command *****************************
This file is part of the pdi stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

Author          : Suraj I.
created Date    : 1st June 2019
******************************************************************************/

#ifndef _SERVICE_COMMAND_H_
#define _SERVICE_COMMAND_H_

#include "CommandCommon.h"

/**
 * service command
 * 
 */
struct ServiceCommand : public CommandBase {

	/* Service options */
	enum ServiceCommandQuery{
		SERVICE_COMMAND_QUERY_MIN = 0,
		SERVICE_COMMAND_QUERY_CONFIG,
		SERVICE_COMMAND_QUERY_STATUS,
		SERVICE_COMMAND_QUERY_MAX
	};

	/* Constructor */
	ServiceCommand(){
		Clear();
		SetCommand(CMD_NAME_SERVICE);
		AddOption(CMD_OPTION_NAME_S);
		AddOption(CMD_OPTION_NAME_Q);
	}

#ifdef ENABLE_AUTH_SERVICE
	/* override the necesity of required permission */
	bool needauth() override { return true; }
#endif

	/* execute command with provided options */
	cmd_status_t execute(){

#ifdef ENABLE_AUTH_SERVICE
		// return in case authentication needed and not authorized yet
		if( needauth() && !__auth_service.getAuthorized()){
			return CMD_STATUS_NEED_AUTH;
		}
#endif

		cmd_status_t status = CMD_STATUS_OK;
		ServiceProvider *srvc = nullptr;
		ServiceCommandQuery srvcq = SERVICE_COMMAND_QUERY_MAX;
		CommandOption *cmdoptn = RetrieveOption(CMD_OPTION_NAME_S);
		
		if( nullptr != cmdoptn ){
			srvc = ServiceProvider::getService((service_t)StringToUint16(cmdoptn->optionval, cmdoptn->optionvalsize));
		}

		cmdoptn = RetrieveOption(CMD_OPTION_NAME_Q);
		if( nullptr != cmdoptn ){
			srvcq = (ServiceCommandQuery)StringToUint16(cmdoptn->optionval, cmdoptn->optionvalsize);
		}

		if( nullptr != srvc && srvcq > SERVICE_COMMAND_QUERY_MIN && srvcq < SERVICE_COMMAND_QUERY_MAX ){

			if( srvcq == SERVICE_COMMAND_QUERY_CONFIG ){

				srvc->printConfigToTerminal(m_terminal);
			}else if( srvcq == SERVICE_COMMAND_QUERY_STATUS ){

			}
		}

		return status;
	}
};


#endif
