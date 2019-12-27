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
#include "output.h"

#define QUOTE(n) #n
#define COLOR(r,g,b) "\033[" QUOTE(r) ";" QUOTE(g) ";" QUOTE(b) "m"

#include <stdio.h>

void printPlusesMinuses(const struct ThreadOutData *outData)
{
	printf("%c%u\n", (outData->isOpen ? '+' : '-'), outData->port);
}

void printOpenClosed(const struct ThreadOutData *outData)
{
	const char *color =
	    outData->isOpen ? COLOR(1, 37, 42) : COLOR(1, 37, 41);

	printf("%5d | %s%10s%s | %s\n",
	       outData->port,
	       color, (outData->isOpen ? "OPEN" : "CLOSED"), COLOR_RESET_STRING,
	       (outData->serviceName ? outData->serviceName : "")
	      );
}
