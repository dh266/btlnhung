#include "MKL46Z4.h"
#include "i2c.h"
#include "mma8451.h"
#include "timer.h"
#include "utility.h"
#include "slcd.h"

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
	
	calibrate(xval,yval,zval,&xavg,&yavg,&zavg);
	delay(1000);
	
	volatile static int i = 0 ;
	while(1) {
		i++;
		if(i < 100) {
		step_count = detect_step(step_count,i);
		slcd_display_decimal(step_count);
		}
		else {
			i = 0;
		}
	}
}
