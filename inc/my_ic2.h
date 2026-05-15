/*
 * my_ic2.h
 *
 *  Created on: 8 de may. de 2026
 *      Author: practiques
 */

#ifndef INC_MY_IC2_H_
#define INC_MY_IC2_H_

#include <stdbool.h>
#include <cstdint>

static void INIT_MY_I2C(uint8_t addr);

// WRITE
static bool WRITE_MY_I2C(uint8_t reg, uint8_t data);

// READ
static bool READ_MY_I2C(uint8_t reg, uint8_t *val);

// TEST
static bool TEST_MY_I2C(void);

#endif /* INC_MY_IC2_H_ */
