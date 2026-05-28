
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
#include "queue.h"

// Por el momento, cola dinamica
QueueHandle_t colaRaw, colaDist; //colaRaw Task 1 -> 2;; colaDist Task 2 -> 3

/*
colaRaw = xQueueCreate(30, sizeof(msg_distancia));
colaDist = xQueueCreate(30, sizeof(uint8_t));
*/

typedef struct{
	uint8_t high;
	uint8_t low;
} msg_distancia;


#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 10)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)

/***************************************************************************//**
 * @brief Simple task which is blinking led
 * @param *pParameters pointer to parameters passed to the function
 ******************************************************************************/

msg_distancia ReadDistance(){
	uint8_t status;
	uint8_t high;
	uint8_t low;
	msg_distancia msg1;
	//int timeout = 1000;

	WRITE_MY_I2C(0x00, 0x01);

	do{
		READ_MY_I2C(0x13,&status);
		//timeout--;
	}while((status & 0x07)!=0);
	//}while((status & 0x01)==0 && timeout);


	READ_MY_I2C(0x1E,&high);
	READ_MY_I2C(0x1F,&low);

	//printf("High %x \n",high);
	//printf("Low %x\n",low);

	WRITE_MY_I2C(0x0B, 0x01);
	msg1.high = high;
	msg1.low = low;
	return msg1;
}

static void Task1(void *pParameters)
{
  (void) pParameters;
  const portTickType delay = pdMS_TO_TICKS(500);

  // Variable a enviar a la Task 2
  msg_distancia msg;

  // Inicializar Lidar
  INIT_MY_I2C(0x52);

  for (;; ) {
    BSP_LedToggle(1);
    printf("Task 1\n");
    //printf("Frec CPU %lu \n",SystemCoreClock);

    msg = ReadDistance();

    printf("Test -- High: %x Low: %x\n",msg.high,msg.low);

    //enviar valor a la cola
    xQueueSend(colaRaw, &msg, 0xFFFFFFFF); //0xFFFFFFFF(portMax_DELAY): La tarea se duerme y no consume CPU hasta que la cola tenga espacio o datos disponibles.

    vTaskDelay(delay);
  }
}
static void Task2(void *pParameters)
{
  (void) pParameters;

  msg_distancia msg;

  uint16_t dist;

  xQueueReceive(colaRaw, &msg, 0xFFFFFFFF);

  dist = ((uint12_t)msg.high << 8) | msg.low;

  xQueueSend(colaDist, &dist,  0xFFFFFFFF)

}

static void Task3(void *pParameters)
{
  (void) pParameters;

  uint16_t dist;
  xQueueReceive(colaRaw, &dist, 0xFFFFFFFF);

  printf("Distancia: %x mm\n",dist);
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

  //Task 1
  xTaskCreate(Task1, (const char *) "Task 1", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);
  //Task 2 
  xTaskCreate(Task2, (const char *) "Task 2", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);
  //Task 3
  xTaskCreate(Task3, (const char *) "Task 3", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);
  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}
