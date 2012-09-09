#include "threads.h"
#include "colors.h"
#include "network.h"

void *threadRun( void *arg )
{
	struct ThreadArg *threadArg = (struct ThreadArg *)arg;
	char portStatus = checkPortStatus( threadArg->hostInfo, threadArg->port );
	if( portStatus == PortStatus_Open || threadArg->appConfig->showOnlyOpen == 0 )
	{
		printf( "Port %d is %s%s%s\n", 
			threadArg->port,
			Color_getString( 1, 37, ( PortStatus_Closed == portStatus  ? 41 : 42 ) ),
			( PortStatus_Closed == portStatus ? "CLOSED" : "OPEN" ),
			COLOR_RESET_STRING
		);
	}
	return NULL;
}

