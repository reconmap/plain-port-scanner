/**
 * plain-port-scanner finds open ports in local and remote hosts.
 * Copyright (C) Santiago Lizardo
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
#include "network.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

struct hostent *resolveHostInfo( const char *hostName )
{
	struct hostent *hostInfo = gethostbyname( hostName );
	return hostInfo;
}

char *resolveServiceName( unsigned short port )
{
	bool shouldFree = false;
	char *serviceName = NULL;
	struct servent *portInfo = NULL;
#if !(defined(__APPLE__) && defined(__MACH__))
	struct servent *portInfoPointer;
#endif
	char buffer[1024];	

	memset( buffer, 0, 1024 );

#if defined(__APPLE__) && defined(__MACH__)
	if( ( portInfo = getservbyport( htons( port ), NULL ) ) != NULL )
#else
	shouldFree = true;
	portInfo = (struct servent*)malloc( sizeof( struct servent ) );
	if( 0 == getservbyport_r( htons( port ), NULL, portInfo, buffer, 1024, &portInfoPointer ) && portInfoPointer != NULL )
#endif
	{
		serviceName = strdup( portInfo->s_name );
	}

	if( shouldFree && portInfo )
		free( portInfo );

	return serviceName;
}

PortStatus checkPortStatus( struct hostent *hostInfo, unsigned short port )
{
	char portStatus = PortStatus_Closed;

	int socketHandle = socket( AF_INET, SOCK_STREAM, 0 );
	struct sockaddr_in socketInfo;
	if( hostInfo == NULL )
	{
		return PortStatus_Unkown;
	}
	if( socketHandle < 0 )
	{
		return PortStatus_Unkown;
	}

	bzero( &socketInfo, sizeof( struct sockaddr_in ) );
	memcpy( (void *)&socketInfo.sin_addr, hostInfo->h_addr, hostInfo->h_length );
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons( port );

	if( connect( socketHandle, (struct sockaddr *)&socketInfo, sizeof( struct sockaddr_in ) ) == 0 )
	{
		portStatus = PortStatus_Open;
	}

	close( socketHandle );

	return portStatus;
}

