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

