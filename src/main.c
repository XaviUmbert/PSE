
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
#include "my_i2c.h"


#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 10)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)

/***************************************************************************//**
 * @brief Simple task which is blinking led
 * @param *pParameters pointer to parameters passed to the function
 ******************************************************************************/
uint16_t ReadDistance(){
	uint8_t status;
	uint8_t high;
	uint8_t low;
	int timeout = 1000;

	WRITE_MY_I2C(0x00, 0x01);

	do{
		READ_MY_I2C(0x13,&status);
		timeout--;
	}while((status & 0x01)==0 && timeout);


	READ_MY_I2C(0x1E,&high);
	READ_MY_I2C(0x1F,&low);

	WRITE_MY_I2C(0x00, 0x01);

	return (high << 8) | low;
}

static void LedBlink(void *pParameters)
{
  (void) pParameters;
  const portTickType delay = pdMS_TO_TICKS(500);

  uint16_t dist;

  for (;; ) {
    BSP_LedToggle(1);
    printf("Task 1\n");
    //printf("Frec CPU %lu \n",SystemCoreClock);
    INIT_MY_I2C(0x52);

    dist = ReadDistance();
    printf("Test %d mm /n",dist);

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
