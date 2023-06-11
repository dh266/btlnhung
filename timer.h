
#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include "MKL46Z4.h"

typedef uint32_t ticktime_t;


void init_systick(void);

ticktime_t now();

void reset_timer();

ticktime_t get_timer();

ticktime_t getTicks();

void delay(uint16_t delay_time);

#endif /* TIMER_H_ */
