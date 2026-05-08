/*
 * helper_functions.c
 *
 *  Created on: 02 de abr. de 2023
 *      Author: Marius Monton
 */

#include "em_device.h"

/**
 * @brief write implementation for stdio.h
 *
 * It sends all output data to ITM
 */
int _write(int file, const char *ptr, int len) {

	(void) file;

    int x;
    for (x = 0; x < len; x++) {
       ITM_SendChar (*ptr++);
    }
    return (len);
}

