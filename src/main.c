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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "network.h"
#include "output.h"
#include "timer.h"
#include "app-config.h"
#include "threads.h"

char const *programName;

/**
 * Application entry point.
 */
int main(int argc, char **argv)
{
	pthread_t *threads = NULL;
	int numPorts = -1;
	struct ThreadOutData **outData = NULL;
	struct ThreadInData **inData;
	struct hostent *hostInfo = NULL;
	int counter = 0;
	int currentPort = -1;
	int i = 0;

	AppConfig appConfig;

	programName = argv[0];
	AppConfig_init(&appConfig);
	AppConfig_parseCommandLine(&appConfig, argc, argv);

	threads =
	    (pthread_t *) calloc(appConfig.numThreads, sizeof(pthread_t));
	numPorts = appConfig.toPort - appConfig.fromPort + 1;
	outData = malloc(sizeof(struct ThreadOutData) * numPorts);
	inData =
	    (struct ThreadInData **) malloc(sizeof(struct ThreadInData *) *
					    appConfig.numThreads);
	Timer_start();

	hostInfo = resolveHostInfo(appConfig.hostName);

	if (hostInfo == NULL) {
		fprintf(stderr, "Unable to resolve host: %s\n",
			appConfig.hostName);
		return EXIT_FAILURE;
	}

	printf("Scanning open ports on %s (%s)\n",
	       inet_ntoa(*((struct in_addr *) hostInfo->h_addr_list[0])),
	       appConfig.hostName);

	currentPort = appConfig.fromPort;
	while (currentPort <= appConfig.toPort) {
		int threadsCreated = 0;
		unsigned int i = 0;
		for (i = 0; i < appConfig.numThreads; i++) {
			if (currentPort <= appConfig.toPort) {
				inData[i] = (struct ThreadInData *)
				    malloc(sizeof(struct ThreadInData));
				memset(inData[i], 0,
				       sizeof(struct ThreadInData));
				inData[i]->hostInfo = hostInfo;
				inData[i]->port = currentPort;
				pthread_create(&threads[i], NULL,
					       threadRun,
					       (void *) inData[i]);
				currentPort++;
				threadsCreated++;
			}
		}

		for (i = 0; i < threadsCreated; i++) {
			pthread_join(threads[i],
				     (void **) &outData[counter]);
			free(inData[i]);
			counter++;
		}
	}
	free(inData);

	if (FORMAT_PLUSES_MINUSES != appConfig.printFormat) {
		printf("%-5s | %s%-10s%s | %s\n", "Port", "", "Status", "",
		       "Description");
		printf("-----------------------------------\n");
	}

	for (i = 0; i < numPorts; i++) {
		void (*printFunction) (const struct ThreadOutData *) =
		    printOpenClosed;
		if (FORMAT_PLUSES_MINUSES == appConfig.printFormat) {
			printFunction = printPlusesMinuses;
		}
		if (outData[i]->isOpen || appConfig.showOnlyOpen == 0) {
			printFunction(outData[i]);
		}
		free(outData[i]->serviceName);
		free(outData[i]);
	}
	free(outData);

	Timer_stop();

	printf("Elapsed time: %ld seconds\n", Timer_getElapsedTime());

	if (threads != NULL)
		free(threads);

	return EXIT_SUCCESS;
}
