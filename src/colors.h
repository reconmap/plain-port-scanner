#ifndef COLORS_H
#define COLORS_H

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define COLOR_RESET_STRING "\E[0m"

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

