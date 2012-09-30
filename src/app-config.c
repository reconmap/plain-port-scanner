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
#include "app-config.h"

AppConfig* AppConfig_new()
{
	AppConfig *appConfig = (AppConfig*)malloc( sizeof( AppConfig ) );
	return appConfig;
}

void AppConfig_init( AppConfig *appConfig )
{
	AppConfig_setHostName( appConfig, "localhost" );

	appConfig->fromPort = 80;
	appConfig->toPort = 80;
	appConfig->numThreads = 5;
	appConfig->showOnlyOpen = 0;
	appConfig->printFormat = FORMAT_OPEN_CLOSED;
}

void AppConfig_setHostName( AppConfig *appConfig, char *hostName )
{
	memset( &appConfig->hostName, '\0', 255 );
	strncat( appConfig->hostName, hostName, 254 );
}

void AppConfig_parseCommandLine( AppConfig *appConfig, int argc, char **argv )
{
	int opt = -1;

	while( ( opt = getopt( argc, argv, "f:t:h:op:" ) ) != -1 )
	{
		switch( opt )
		{
			case 'f':
				appConfig->fromPort = atoi( optarg );
				break;
			case 't':
				appConfig->toPort = atoi( optarg );
				break;
			case 'h':
				AppConfig_setHostName( appConfig, optarg );
				break;
			case 'o':
				appConfig->showOnlyOpen = 1;
				break;
			case 'p':
				if( 0 == strncmp( optarg, "pluses-minuses", 14 ) )
				{
					appConfig->printFormat = FORMAT_PLUSES_MINUSES;
				}
				break;

		}
	}	
}

