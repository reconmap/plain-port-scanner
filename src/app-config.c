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
#include "app-config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <getopt.h>

const unsigned DefaultFromPort = 1;
const unsigned DefaultToPort = 80;
const char DefaultTargetHost[] = "localhost";

extern const char *programName;

void AppConfig_setHostName( AppConfig *appConfig, const char *hostName );

void AppConfig_init( AppConfig *appConfig )
{
	AppConfig_setHostName( appConfig, DefaultTargetHost );

	appConfig->fromPort = DefaultFromPort;
	appConfig->toPort = DefaultToPort;
	appConfig->numThreads = 5;
	appConfig->showOnlyOpen = false;
	appConfig->printFormat = FORMAT_OPEN_CLOSED;
}

void AppConfig_setHostName( AppConfig *appConfig, const char *hostName )
{
	memset( appConfig->hostName, '\0', 255 );
	strncat( appConfig->hostName, hostName, 254 );
}

void AppConfig_showHelp()
{
	printf( "usage: %s [options]\n"
		"\t-f Lower bound port number (default: %d)\n"
		"\t-t Upper bound port number (default: %d)\n"
		"\t-a Target host name or address (default: %s)\n"
		"\t-o Show only open ports (default: false)\n"
		"\t-p Show minuses and pluses instead of green/red\n"
		"\t-h Help\n",
		programName,
		DefaultFromPort, DefaultToPort,
		DefaultTargetHost	
	);	
}

void AppConfig_parseCommandLine( AppConfig *appConfig, int argc, char **argv )
{
	int opt = -1;

	while( ( opt = getopt( argc, argv, "hf:t:a:op:" ) ) != -1 )
	{
		switch( opt )
		{
			case 'f':
				appConfig->fromPort = atoi( optarg );
				break;
			case 't':
				appConfig->toPort = atoi( optarg );
				break;
			case 'a':
				AppConfig_setHostName( appConfig, optarg );
				break;
			case 'o':
				appConfig->showOnlyOpen = true;
				break;
			case 'p':
				if( 0 == strncmp( optarg, "pluses-minuses", 14 ) )
				{
					appConfig->printFormat = FORMAT_PLUSES_MINUSES;
				}
				break;
			case 'h':
				AppConfig_showHelp();
				exit( 0 );
				break;
		}
	}	
}

