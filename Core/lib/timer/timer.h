/*
 * timer.h
 *
 *  Created on: Feb 13, 2022
 *      Author: aleksa
 */

#ifndef LIB_TIMER_TIMER_H_
#define LIB_TIMER_TIMER_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>

void
timer_init (void);

bool
is_time_passed (uint32_t ms);

#endif /* LIB_TIMER_TIMER_H_ */
