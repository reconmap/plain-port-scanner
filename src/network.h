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
#ifndef NETWORK_H
#define NETWORK_H

#include <netdb.h>
#include <string.h>
#include <strings.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef enum 
{
	PortStatus_Open,
	PortStatus_Closed
} PortStatus;

struct hostent *resolveHostInfo( const char *hostName );

PortStatus checkPortStatus( struct hostent *hostInfo, unsigned short port );

#endif

