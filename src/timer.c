#include "timer.h" 

/**
 * Records the start time.
 */
void Timer_start()
{
	timerConfig.beginTime = time( NULL );
}

/**
 * Records the end time.
 */
void Timer_stop()
{
	timerConfig.endTime = time( NULL );
}

/**
 * Returns the number of seconds between the beginning and end date.
 *
 * @return time_t
 */
time_t Timer_getElapsedTime()
{
	return ( timerConfig.endTime - timerConfig.beginTime );
}

