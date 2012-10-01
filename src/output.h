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
#ifndef OUTPUT_H
#define OUTPUT_H

#define COLOR_RESET_STRING "\033[0m"

#include "threads.h"

void printPlusesMinuses( struct ThreadOutData *outData );

void printOpenClosed( struct ThreadOutData *outData );

/**
 * Returns the specified color.
 */
char *Color_getString( unsigned char hl, unsigned char fg, unsigned char bg );

const char *Color_getResetString();

/**
 * Resets previous assigned colours.
 */
void Color_reset();

#endif

