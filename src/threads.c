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

#include "network.h"

#include <stdlib.h>
#include <string.h>

void *threadRun( void *arg )
{
	struct ThreadInData *inData = (struct ThreadInData *)arg;
	struct ThreadOutData *outData = (struct ThreadOutData *)malloc( sizeof( struct ThreadOutData ) );

	char portStatus = checkPortStatus( inData->hostInfo, inData->port );

	outData->isOpen = ( PortStatus_Open == portStatus );
	outData->port = inData->port;
	outData->serviceName = resolveServiceName( inData->port );
	
	pthread_exit( outData );

	return NULL;
}

