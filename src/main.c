
#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#include "em_chip.h"
#include "bsp.h"
#include "bsp_trace.h"

#include "bsp_i2c.h"

#include "Wire.h"
#include "VL53L0X.h"
#include "VL53L0X.c"

VL53L0X sensor;

#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 10)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)

/***************************************************************************//**
 * @brief Simple task which is blinking led
 * @param *pParameters pointer to parameters passed to the function
 ******************************************************************************/
static void LedBlink(void *pParameters)
{
  (void) pParameters;
  const portTickType delay = pdMS_TO_TICKS(500);
  uint16_t valorSensor;
  for (;; ) {
    BSP_LedToggle(1);
    printf("Task 1\n");

    // Inicializar
    BSP_I2C_Init(0x52);

    // Comprobar registros del sensor
    //printf("Test %d/n",I2C_Test());

    //valorSensor
    valorSensor = sensor.readRangeContinuousMillimeters();
    if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

    vTaskDelay(delay);
  }
}

/***************************************************************************//**
 * @brief  Main function
 ******************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();
  /* If first word of user data page is non-zero, enable Energy Profiler trace */
  BSP_TraceProfilerSetup();

  /* Initialize LED driver */
  BSP_LedsInit();
  /* Setting state of leds*/
  BSP_LedSet(0);
  BSP_LedSet(1);

  /*Create two task for blinking leds*/
  xTaskCreate(LedBlink, (const char *) "LedBlink1", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}
