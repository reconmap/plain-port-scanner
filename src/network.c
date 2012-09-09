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
#include "network.h"

struct hostent *resolveHostInfo( const char *hostName )
{
	struct hostent *hostInfo = gethostbyname( hostName );
	return hostInfo;
}

PortStatus checkPortStatus( struct hostent *hostInfo, unsigned short port )
{
	int socketHandle = socket( AF_INET, SOCK_STREAM, 0 );
	if( socketHandle < 0 )
	{
		return PortStatus_Closed;
	}

	struct sockaddr_in socketInfo;
	bzero( &socketInfo, sizeof( struct sockaddr_in ) );
	memcpy( (void *)&socketInfo.sin_addr, hostInfo->h_addr, hostInfo->h_length );
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons( port );

	if( connect( socketHandle, (struct sockaddr *)&socketInfo, sizeof( struct sockaddr_in ) ) < 0 )
	{
		close( socketHandle );
		return PortStatus_Closed;
	}

	close( socketHandle );

	return PortStatus_Open;
}

