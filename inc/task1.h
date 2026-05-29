#ifndef TASK1_H_
#define TASK1_H_

#include <stdint.h>
#include "queue.h"

typedef struct{
    uint8_t high;
    uint8_t low;
} msg_distancia;

// Cola compartida
extern QueueHandle_t colaRaw;

void Task1(void *pParameters);

#endif
