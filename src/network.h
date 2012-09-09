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

