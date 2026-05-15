/*
 * bsp_i2c.h
 *
 *  Created on: 02 de abr. de 2023
 *      Author: Marius Monton
 */
#ifndef INC_BSP_I2C_H_
#define INC_BSP_I2C_H_

#include <stdint.h>
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
 * @brief Write multiple bytes to I2C device starting at a register
 * @param reg Register to write first
 * @param data Bytes to write
 * @param count Number of bytes to write
 * @return true on success
 */
bool BSP_I2C_WriteMulti(uint8_t reg, const uint8_t *data, uint8_t count);

/**
 * @brief Read register from I2C device
 * @param reg Register to read
 * @param val Value read
 * @return true on success
 */
bool BSP_I2C_ReadRegister(uint8_t reg, uint8_t *val);

/**
 * @brief Read multiple bytes from I2C device starting at a register
 * @param reg Register to read first
 * @param dst Buffer to store results
 * @param count Number of bytes to read
 * @return true on success
 */
bool BSP_I2C_ReadMulti(uint8_t reg, uint8_t *dst, uint8_t count);

/**
 * @brief Test function
 */
bool I2C_Test();





#endif /* INC_BSP_I2C_H_ */
