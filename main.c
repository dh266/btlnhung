#include "MKL46Z4.h"
#include "i2c.h"
#include "mma8451.h"
#include "timer.h"
#include "utility.h"
#include "slcd.h"

#include "stdio.h"
#include "stdbool.h"

#define GREEN_LED_ON()       PTD->PCOR |= 1<<5 ;// Define function to turn Green LED ON
#define GREEN_LED_OFF()      PTD->PSOR |= 1<<5 ;// Define function to turn Green LED OFF

#define RED_LED_ON()       PTE->PCOR |= 1<<29 ; //Define function to turn Red LED ON
#define RED_LED_OFF()      PTE->PSOR |= 1<<29 ; //Define function to turn Red LED OFF

#define SW1 3

#define ENABLE_PULLUP_RESISTOR  3 

bool StartStopSwitchPressed = false;

void LED_Init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;// //Enabling clock
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	PORTD->PCR[5] = PORT_PCR_MUX(1) ;	//Set the PTD5 pin multiplexer to GPIO mode
	
	PTD->PDDR |= 1<<5;								//Set the pins direction to output
	
	PORTE->PCR[29] = PORT_PCR_MUX(1) ;
	
	PTE->PDDR |= 1<<29;								//Set the pins direction to output
}

void SWITCH_Init(void)
{
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
		PORTC->PCR[SW1] |= PORT_PCR_MUX(1) | ENABLE_PULLUP_RESISTOR | 1<<17 | 1<<19;
		PTC->PDDR &= (~(1<<3));
		
		PORTC->PCR[3] |= PORT_PCR_IRQC(0xA);
		NVIC_ClearPendingIRQ(31);
		NVIC_EnableIRQ(31);
}

void PORTC_PORTD_IRQHandler(void)
{
	for(int i=0;i<1000;i++);
	if ((PTC->PDIR&(1<<3))==0)
	{
		StartStopSwitchPressed=1;      	//Update the state variable for Reset Switch (Switch 1)
		PORTC->PCR[SW1] |= 1<<24; 			//Clearing the Interrupt Status Flag for Switch 1
	}
}
int16_t xval[100] = {0};
int16_t yval[100] = {0};
int16_t zval[100] = {0};

int xavg, yavg, zavg;

int16_t total_vect[100] = {0};
int16_t total_avg[100] = {0};
uint16_t step_count = 0;

int main() {
	I2C0_init();
	init_systick();
	init_mma();
	
	SWITCH_Init();
	LED_Init();
	SLCD_Init();
	calibrate(xval,yval,zval,&xavg,&yavg,&zavg);
	delay(100);
	
	char target1[100];
	volatile static int i = 0 ;
	int a = 0, tmp;
	while(1) {
		if(StartStopSwitchPressed == true) {
			StartStopSwitchPressed = false;
			a++;
		}
		if(a%2==0) {
			RED_LED_ON();
			GREEN_LED_OFF();
			tmp = step_count;
			sprintf(target1,"%d\n",tmp);
		}
		else
		{
			RED_LED_OFF();
			for(i=0;i<4;i++){
				GREEN_LED_ON();
				delay(200/20);
				step_count = detect_step(step_count,i);
				sprintf(target1,"%d\n",step_count);
			}
			for(i=0;i<4;i++){
				GREEN_LED_OFF();
				delay(800/20);
				step_count = detect_step(step_count,i);
				sprintf(target1,"%d\n",step_count);
			}
		}
		//step_count = detect_step(step_count,i);
		SLCD_WriteMsg(target1);
	}
}