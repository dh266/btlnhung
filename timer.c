
#include "timer.h"

ticktime_t Ticks;

void init_systick(void){
	SysTick->LOAD = (48000000/16/1000);				//Interrupt at every 1ms
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0;								//Force reloading the counter value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk |		//Enable Systick timer
					SysTick_CTRL_ENABLE_Msk;
	NVIC_EnableIRQ(SysTick_IRQn);					//Enable Systick timer interrupt
}

ticktime_t now(){
	return Ticks;									//Returns time since startup
}

void reset_timer(){
	SysTick->VAL = 0;								//Resetting the counter to 0
}

ticktime_t get_timer(){
	return SysTick->VAL;							//Return current counter
}

void SysTick_Handler(){
	Ticks++;				//Increment ticks on each interrupt
}

ticktime_t getTicks(){
	return Ticks;			//Retuns the Ticks counter to the main code
}

void delay(uint16_t delay_time){
	uint32_t current_time = getTicks();
	while((getTicks() - current_time) <= delay_time){
		__asm volatile ("nop");
	}
}
