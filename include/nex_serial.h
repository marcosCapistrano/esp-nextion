#ifndef NEX_SERIAL_H
#define NEX_SERIAL_H

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

typedef struct s_nex_serial_t *nex_serial_t;
typedef struct s_nex_serial_t {
	QueueHandle_t uart_queue;
} s_nex_serial_t;


nex_serial_t nex_serial_init();
void nex_serial_event_task(void* pvParameters);

#endif