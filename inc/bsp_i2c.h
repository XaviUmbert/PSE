/*
 * bsp_i2c.h
 *
 *  Created on: 02 de abr. de 2023
 *      Author: Marius Monton
 */
#ifndef INC_BSP_I2C_H_
#define INC_BSP_I2C_H_

#include <stdbool.h>

/**
 * @brief Initializes I2C subsystem
 * @param addr I2C address of device to access
 */
void BSP_I2C_Init(uint8_t addr);

/**
 * @brief Write register using default I2C bus
 * @param reg register to write
 * @param data data to write
 * @return true on success
 */
bool BSP_I2C_WriteRegister(uint8_t reg, uint8_t data);

/**
 * @brief Read register from I2C device
 * @param reg Register to read
 * @param val Value read
 * @return true on success
 */
bool BSP_I2C_ReadRegister(uint8_t reg, uint8_t *val);

/**
 * @brief Test function
 */
bool I2C_Test();





#endif /* INC_BSP_I2C_H_ */
