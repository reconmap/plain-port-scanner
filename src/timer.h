#ifndef TIMER_H
#define TIMER_H

#include <time.h>

/**
 * Structure that holds timing information.
 */
struct TimerConfig
{
	time_t beginTime;
	time_t endTime;
} timerConfig;

/**
 * Records the start time.
 */
void Timer_start();

/**
 * Records the end time.
 */
void Timer_stop();

/**
 * Returns the number of seconds between the beginning and end date.
 *
 * @return time_t
 */
time_t Timer_getElapsedTime();

#endif

