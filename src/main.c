#include <stdio.h>

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "em_chip.h"
#include "bsp.h"
#include "bsp_trace.h"

#include "task1.h"
#include "task2.h"
#include "task3.h"

// Colas
QueueHandle_t colaRaw;
QueueHandle_t colaDist;

#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 10)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)

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

    colaRaw = xQueueCreate(30, sizeof(msg_distancia));
    colaDist = xQueueCreate(30, sizeof(uint16_t));

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
