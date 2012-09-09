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

#include "network.h"
#include "colors.h"
#include "timer.h"
#include "app-config.h"
#include "threads.h"

/**
 * Application entry point.
 */
int main( int argc, char **argv )
{
	AppConfig appConfig;
	AppConfig_init( &appConfig );
	AppConfig_parseCommandLine( &appConfig, argc, argv );

	pthread_t *threads = (pthread_t*)calloc( appConfig.numThreads, sizeof( pthread_t ) );

	Timer_start();

	struct hostent *hostInfo = resolveHostInfo( appConfig.hostName );

	if( hostInfo == NULL )
	{
		fprintf( stderr, "Unable to resolve host: %s\n", appConfig.hostName );
		return EXIT_FAILURE;
	}

	printf( "Host resolved to IP: %s\n", inet_ntoa( *((struct in_addr *)hostInfo->h_addr_list[0]) ) );

	int currentPort = appConfig.fromPort;
	while( currentPort < appConfig.toPort )
	{
		int threadsCreated = 0;
		unsigned int i = 0;
		for( i = 0; i < appConfig.numThreads; i++ )
		{
			if( currentPort <= appConfig.toPort )
			{
				struct ThreadArg *threadArg = (struct ThreadArg*)malloc( sizeof( struct ThreadArg ) );
				threadArg->hostInfo = hostInfo;
				threadArg->port = currentPort;
				threadArg->appConfig = &appConfig;
				pthread_create( &threads[ i ], NULL, threadRun, (void *)threadArg );
				currentPort++;
				threadsCreated++;
			}
		}

		for( i = 0; i < threadsCreated; i++ )
		{
			pthread_join( threads[ i ], NULL );
		}
	}

	Timer_stop();

	printf( "Elapsed time: %ld seconds\n", Timer_getElapsedTime() );

	pthread_exit( NULL );

	return EXIT_SUCCESS;
}

