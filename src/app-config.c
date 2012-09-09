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
}

void AppConfig_setHostName( AppConfig *appConfig, char *hostName )
{
	memset( &appConfig->hostName, '\0', 255 );
	strcat( appConfig->hostName, hostName );
}

void AppConfig_parseCommandLine( AppConfig *appConfig, int argc, char **argv )
{
	int opt = -1;

	while( ( opt = getopt( argc, argv, "f:t:h:o" ) ) != -1 )
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
		}
	}	
}

