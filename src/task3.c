#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"

#include "task3.h"

void Task3(void *pParameters)
{
    (void)pParameters;

    printf("Distancias recibidas:\n");

    for(;;){

        uint16_t dist;
        xQueueReceive(colaDist, &dist, portMAX_DELAY);

        if(dist < 100){

            BSP_LedSet(0);
            BSP_LedSet(1);
            printf("LED ON ");

        }else{

            BSP_LedClear(0);
            BSP_LedClear(1);
            printf("LED OFF ");
        }

        printf("Distancia: %d cm\n", dist / 10);
    }
}
