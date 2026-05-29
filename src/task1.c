#include "FreeRTOS.h"
#include "task.h"

#include "my_i2c.h"

#include "task1.h"

msg_distancia ReadDistance(){

    uint8_t status;
    uint8_t high;
    uint8_t low;

    msg_distancia msg1;

    WRITE_MY_I2C(0x00, 0x01);

    do{
        READ_MY_I2C(0x13, &status);
    }while((status & 0x07) != 0);

    READ_MY_I2C(0x1E, &high);
    READ_MY_I2C(0x1F, &low);

    WRITE_MY_I2C(0x0B, 0x01);

    msg1.high = high;
    msg1.low = low;

    return msg1;
}

void Task1(void *pParameters)
{
    (void)pParameters;

    const portTickType delay = pdMS_TO_TICKS(500);

    msg_distancia msg;

    INIT_MY_I2C(0x52);

    for(;;){
        msg = ReadDistance();
        xQueueSend(colaRaw, &msg, portMAX_DELAY);
        vTaskDelay(delay);
    }
}
