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
#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

enum
{
	FORMAT_OPEN_CLOSED = 0,
	FORMAT_PLUSES_MINUSES
};

struct _AppConfig
{
	char hostName[255];
	unsigned short fromPort;
	unsigned short toPort;
	unsigned char numThreads;
	unsigned char showOnlyOpen;
	unsigned char printFormat;
};

typedef struct _AppConfig AppConfig;

void AppConfig_init( AppConfig *appConfig );

void AppConfig_setHostName( AppConfig *appConfig, char *hostName );

void AppConfig_parseCommandLine( AppConfig *appConfig, int argc, char **argv );

#endif

