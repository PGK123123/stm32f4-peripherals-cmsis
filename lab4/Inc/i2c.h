#ifndef I2C_H
#define I2C_H

#include "main.h"

void    i2c_init(void);
uint8_t i2cWriteRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

#endif
