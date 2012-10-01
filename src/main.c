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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"
#include "network.h"
#include "colors.h"
#include "timer.h"
#include "app-config.h"
#include "threads.h"

void printPlusesMinuses( char isOpen, short port )
{
	printf( "%c%u\n", ( isOpen? '+': '-' ), port );
}

void printOpenClosed( char isOpen, short port )
{
	char *statusColor = Color_getString( 1, 37, ( isOpen? 42: 41 ) );
	struct servent *portInfo = getservbyport( htons( port ), NULL );

	printf( "Port %d (%s) is %s%s%s\n", 
		port,
		portInfo != NULL? portInfo->s_name: "-",
		statusColor,
		( isOpen? "OPEN": "CLOSED" ),
		COLOR_RESET_STRING
	);
	FREE_NULL( statusColor );
}

/**
 * Application entry point.
 */
int main( int argc, char **argv )
{
	pthread_t *threads = NULL;
	int numPorts = -1;
	struct ThreadOutData **outData = NULL;
	struct hostent *hostInfo = NULL;
	int counter = 0;
	int currentPort = -1;
	int i = 0;

	AppConfig appConfig;
	AppConfig_init( &appConfig );
	AppConfig_parseCommandLine( &appConfig, argc, argv );

	threads = (pthread_t *)calloc( appConfig.numThreads, sizeof( pthread_t ) );
	numPorts = appConfig.toPort - appConfig.fromPort;
	outData = malloc( sizeof( struct ThreadOutData ) * numPorts );

	Timer_start();

	hostInfo = resolveHostInfo( appConfig.hostName );

	if( hostInfo == NULL )
	{
		fprintf( stderr, "Unable to resolve host: %s\n", appConfig.hostName );
		return EXIT_FAILURE;
	}

	printf( "Host resolved to IP: %s\n", inet_ntoa( *((struct in_addr *)hostInfo->h_addr_list[0]) ) );

	currentPort = appConfig.fromPort;
	while( currentPort < appConfig.toPort )
	{
		int threadsCreated = 0;
		unsigned int i = 0;
		for( i = 0; i < appConfig.numThreads; i++ )
		{
			if( currentPort <= appConfig.toPort )
			{
				struct ThreadInData *inData = (struct ThreadInData*)malloc( sizeof( struct ThreadInData ) );
				memset( inData, 0, sizeof( struct ThreadInData ) );
				inData->hostInfo = hostInfo;
				inData->port = currentPort;
				inData->appConfig = &appConfig;
				pthread_create( &threads[ i ], NULL, threadRun, (void *)inData );
				currentPort++;
				threadsCreated++;
			}
		}

		for( i = 0; i < threadsCreated; i++ )
		{
			pthread_join( threads[ i ], (void **)&outData[ counter ] );
			counter++;
		}
	}

	for( i = 0; i < numPorts; i++ )
	{
		void ( *printFunction )( char, short ) = printOpenClosed;
		if( FORMAT_PLUSES_MINUSES == appConfig.printFormat )
		{
			printFunction = printPlusesMinuses;
		}
		if( outData[i]->isOpen || appConfig.showOnlyOpen == 0 )
		{
			printFunction( outData[i]->isOpen, outData[i]->port ); 
		}
	}

	Timer_stop();

	printf( "Elapsed time: %ld seconds\n", Timer_getElapsedTime() );

	FREE_NULL( threads );

	return EXIT_SUCCESS;
}

