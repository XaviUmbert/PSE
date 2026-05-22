/*
 * my_i2c.c
 *
 *  Created on: 8 de may. de 2026
 *      Author: practiques
 */
#include "FreeRTOS.h"
#include "semphr.h"
#include "bsp_i2c.h"


// MUTEX
static SemaphoreHandle_t mutex_i2c;

// INIT
static void INIT_MY_I2C(uint8_t addr)
{
    // Inicializar
    BSP_I2C_Init(addr);

    // Crear el mutex una vez
    mutex_i2c = xSemaphoreCreateMutex();

    if (mutex_i2c == NULL)	// Comprobar si el mutex esta bien
    {
        while (1);
    }
}

// WRITE
static bool WRITE_MY_I2C(uint8_t reg, uint8_t data)
{
    bool ok = false;

    if (xSemaphoreTake(mutex_i2c, portMAX_DELAY) == pdTRUE) // Espera a poder tomar el semaforo
    {
        ok = BSP_I2C_WriteRegister(reg, data);
        xSemaphoreGive(mutex_i2c);
    }

    return ok;
}

// READ
static bool READ_MY_I2C(uint8_t reg, uint8_t *val)
{
    bool ok = false;

    if (xSemaphoreTake(mutex_i2c, portMAX_DELAY) == pdTRUE)
    {
        ok = BSP_I2C_ReadRegister(reg, val);
        xSemaphoreGive(mutex_i2c);
    }

    return ok;
}

// TEST
static bool TEST_MY_I2C(void)
{
    bool ok = false;

    if (xSemaphoreTake(mutex_i2c, portMAX_DELAY) == pdTRUE)
    {
        ok = I2C_Test();
        xSemaphoreGive(mutex_i2c);
    }

    return ok;
}

