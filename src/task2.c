#include "FreeRTOS.h"
#include "task.h"

#include "task2.h"

void Task2(void *pParameters)
{
    (void)pParameters;

    for(;;){

        msg_distancia msg;
        uint16_t dist;

        xQueueReceive(colaRaw, &msg, portMAX_DELAY);
        dist = (msg.high << 8) | msg.low;

        if(dist > 20){
            xQueueSend(colaDist, &dist, portMAX_DELAY);
        }
    }
}
