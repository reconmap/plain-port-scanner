/**
 * plain-port-scanner finds open ports in local and remote hosts.
 * Copyright (C) 2012 Santiago Lizardo
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "threads.h"
#include "colors.h"
#include "network.h"

void printPlusesMinuses( char isOpen, short port )
{
	printf( "%c%u\n", ( isOpen? '+': '-' ), port );
}

void printOpenClosed( char isOpen, short port )
{
	printf( "Port %d is %s%s%s\n", 
		port,
		Color_getString( 1, 37, ( isOpen? 42: 41 ) ),
		( isOpen? "OPEN": "CLOSED" ),
		COLOR_RESET_STRING
	);
}

void *threadRun( void *arg )
{
	struct ThreadArg *threadArg = (struct ThreadArg *)arg;
	char portStatus = checkPortStatus( threadArg->hostInfo, threadArg->port );
	void **( *printFunction )( char, short ) = printOpenClosed(char, short);
	if( FORMAT_PLUSES_MINUSES == threadArg->printFormat )
	{
		( printFunction ) = &printPlusesMinuses;
	}
	if( portStatus == PortStatus_Open || threadArg->appConfig->showOnlyOpen == 0 )
	{
		char isOpen = ( PortStatus_Open == portStatus );
		(*printFunction)( isOpen, threadArg->port ); 
	}
	return NULL;
}

