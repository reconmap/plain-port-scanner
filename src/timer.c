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
#include "timer.h"

struct TimerConfig timerConfig;

/**
 * Records the start time.
 */
void Timer_start()
{
	timerConfig.beginTime = time(NULL);
}

/**
 * Records the end time.
 */
void Timer_stop()
{
	timerConfig.endTime = time(NULL);
}

/**
 * Returns the number of seconds between the beginning and end date.
 *
 * @return time_t
 */
time_t Timer_getElapsedTime()
{
	return (timerConfig.endTime - timerConfig.beginTime);
}
