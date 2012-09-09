#include "colors.h"

/**
 * Returns the specified color.
 */
char *Color_getString( unsigned char hl, unsigned char fg, unsigned char bg )
{
	size_t colorLen = 20 * sizeof( char );
	char *color = (char *)malloc( colorLen );
	memset( color, '\0', colorLen );
	sprintf( color, "\E[%d;%d;%dm", hl, fg, bg );
	return color;
}

/**
 * Resets previous assigned colours.
 */
void Color_reset()
{
	write( 1, COLOR_RESET_STRING, 4 );
}

