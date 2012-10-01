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
#include "output.h"

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"

void printPlusesMinuses( struct ThreadOutData *outData )
{
	printf( "%c%u\n", ( outData->isOpen? '+': '-' ), outData->port );
}

void printOpenClosed( struct ThreadOutData *outData )
{
	char *statusColor = Color_getString( 1, 37, ( outData->isOpen? 42: 41 ) );

	printf( "Port %d (%s) is %s%s%s\n", 
		outData->port,
		outData->serviceName,
		statusColor,
		( outData->isOpen? "OPEN": "CLOSED" ),
		COLOR_RESET_STRING
	);
	FREE_NULL( statusColor );
}

/**
 * Returns the specified color.
 */
char *Color_getString( unsigned char hl, unsigned char fg, unsigned char bg )
{
	size_t colorLen = 20 * sizeof( char );
	char *color = (char *)malloc( colorLen );
	memset( color, '\0', colorLen );
	sprintf( color, "\033[%d;%d;%dm", hl, fg, bg );
	return color;
}

/**
 * Resets previous assigned colours.
 */
void Color_reset()
{
	write( 1, COLOR_RESET_STRING, 4 );
}

