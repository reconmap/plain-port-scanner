#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

#include "app-config.h"

struct ThreadArg
{
	struct hostent *hostInfo;
	unsigned short port;
	AppConfig *appConfig;
};

void *threadRun( void *arg );

#endif

