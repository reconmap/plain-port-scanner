#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

struct _AppConfig
{
	char hostName[255];
	unsigned short fromPort;
	unsigned short toPort;
	unsigned char numThreads;
	unsigned char showOnlyOpen;
};

typedef struct _AppConfig AppConfig;

AppConfig* AppConfig_new();

void AppConfig_init( AppConfig *appConfig );

void AppConfig_setHostName( AppConfig *appConfig, char *hostName );

void AppConfig_parseCommandLine( AppConfig *appConfig, int argc, char **argv );

#endif

