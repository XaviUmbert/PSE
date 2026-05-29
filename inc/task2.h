#ifndef TASK2_H_
#define TASK2_H_

#include <stdint.h>
#include "queue.h"
#include "task1.h"

// Cola compartida
extern QueueHandle_t colaRaw;
extern QueueHandle_t colaDist;

void Task2(void *pParameters);

#endif
