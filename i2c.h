
#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "MKL46Z4.h"

void I2C0_init(void);

void I2C0_wait(void);

void I2C0_busy(void);

void I2C0_start(void);

void I2C0_read_setup(uint8_t dev, uint8_t address);

uint8_t I2C0_repeated_read(uint8_t flag);

uint8_t I2C0_read_byte(uint8_t dev, uint8_t address);

void I2C0_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif
