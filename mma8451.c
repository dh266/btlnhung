
#include "mma8451.h"

int16_t acc_x=0, acc_y=0, acc_z=0;

int init_mma(void){
	
	I2C0_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

void read_full_xyz(void)
{
	int i;
	uint8_t data[6];
	int16_t temp[3];

	I2C0_start();
	I2C0_read_setup(MMA_ADDR, REG_XHI);

	//Read five bytes in repeated mode
	for(i=0; i<5; i++){
		data[i] = I2C0_repeated_read(0);
	}
	//Read last byte ending repeated mode
	data[i] = I2C0_repeated_read(1);

	for(i=0; i<3; i++){
		temp[i] = (int16_t)((data[2*i]<<8) | data[2*i+1]);
	}

	//Align for 14 bits
	acc_x = temp[0]/4;
	acc_y = temp[1]/4;
	acc_z = temp[2]/4;

}

void read_xyz(void){
	acc_x = (int8_t)I2C0_read_byte(MMA_ADDR, REG_XHI);
	//100ms delay
	delay(100);
	acc_y = (int8_t)I2C0_read_byte(MMA_ADDR, REG_YHI);
	//100ms delay
	delay(100);
	acc_z = (int8_t)I2C0_read_byte(MMA_ADDR, REG_ZHI);
}

void calibrate(int16_t *xval, int16_t *yval, int16_t *zval, int *xavg, int *yavg, int *zavg){
	int sum = 0, sum1 = 0, sum2 = 0;
	for(int i = 0; i<100; i++){
		read_full_xyz();
		xval[i] = acc_x;
		sum = xval[i] + sum;

		yval[i] = acc_y;
		sum1 = yval[i] + sum1;

		zval[i] = acc_z;
		sum2 = zval[i] + sum2;
	}
	delay(100);
	*xavg = sum/100;
	*yavg = sum1/100;
	*zavg = sum2/100;
}
