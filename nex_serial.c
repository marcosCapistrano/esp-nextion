// #include "nex_serial.h"

// #include <stdio.h>
// #include <string.h>

// #include "driver/uart.h"
// #include "esp_log.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/semphr.h"
// #include "freertos/task.h"

// #define EX_UART_NUM UART_NUM_2
// #define PATTERN_CHR_NUM (3)

// #define BUF_SIZE (1024)
// #define RD_BUF_SIZE (BUF_SIZE)

// static const char* TAG = "uart_events";
// static QueueHandle_t uart_queue;

// nex_serial_t nex_serial_init() {
//     nex_serial_t nex_serial = (nex_serial_t)malloc(sizeof(s_nex_serial_t));

//     const uart_port_t uart_num = UART_NUM_2;
//     uart_config_t uart_config = {
//         .baud_rate = 115200,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
//         .source_clk = UART_SCLK_APB,
//     };

//     QueueHandle_t uart_queue;

//     // Install UART driver using an event queue here
//     ESP_ERROR_CHECK(uart_driver_install(uart_num, BUF_SIZE * 2,
//                                         BUF_SIZE * 2, 10, &uart_queue, 0));
//     // Configure UART parameters
//     ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

//     // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
//     ESP_ERROR_CHECK(uart_set_pin(uart_num, 4, 5, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

//     // Setup UART buffered IO with event queue

//     nex_serial->uart_queue = uart_queue;
//     ESP_LOGI(TAG, "%p", uart_queue);

//     ESP_LOGI(TAG, "nexserial OK");
//     return nex_serial;
// }

// void nex_serial_event_task(void* pvParameters) {
//     esp_log_level_set(TAG, ESP_LOG_INFO);

//     /* Configure parameters of an UART driver,
//      * communication pins and install the driver */
//     uart_config_t uart_config = {
//         .baud_rate = 115200,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
//         .source_clk = UART_SCLK_APB,
//     };
//     //Install UART driver, and get the queue.
//     uart_driver_install(EX_UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 20, &uart0_queue, 0);
//     uart_param_config(EX_UART_NUM, &uart_config);

//     //Set UART log level
//     esp_log_level_set(TAG, ESP_LOG_INFO);
//     //Set UART pins (using UART0 default pins ie no changes.)
//     uart_set_pin(EX_UART_NUM, 4, 5, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

//     uart_event_t event;
//     size_t buffered_size;
//     uint8_t* dtmp = (uint8_t*)malloc(RD_BUF_SIZE);

//     ESP_LOGI(TAG, "nextask OK");
//     for (;;) {
//         // Waiting for UART event.
//         // ESP_LOGI(TAG, "looping...");
//         if (xQueueReceive(uart_queue, (void*)&event, portMAX_DELAY)) {
//             bzero(dtmp, RD_BUF_SIZE);
//             ESP_LOGI(TAG, "uart[%d] event:", uart_num);
//             switch (event.type) {
//                 // Event of UART receving data
//                 /*We'd better handler data event fast, there would be much more data events than
//                 other types of events. If we take too much time on data event, the queue might
//                 be full.*/
//                 case UART_DATA:
//                     ESP_LOGI(TAG, "[UART DATA]: %d", event.size);
//                     uart_read_bytes(uart_num, dtmp, event.size, portMAX_DELAY);
//                     ESP_LOGI(TAG, "[DATA EVT]:");
//                     // uart_write_bytes(uart_num, (const char*)dtmp, event.size);
//                     break;
//                 // Event of HW FIFO overflow detected
//                 case UART_FIFO_OVF:
//                     ESP_LOGI(TAG, "hw fifo overflow");
//                     // If fifo overflow happened, you should consider adding flow control for your application.
//                     // The ISR has already reset the rx FIFO,
//                     // As an example, we directly flush the rx buffer here in order to read more data.
//                     uart_flush_input(uart_num);
//                     xQueueReset(uart_queue);
//                     break;
//                 // Event of UART ring buffer full
//                 case UART_BUFFER_FULL:
//                     ESP_LOGI(TAG, "ring buffer full");
//                     // If buffer full happened, you should consider encreasing your buffer size
//                     // As an example, we directly flush the rx buffer here in order to read more data.
//                     uart_flush_input(uart_num);
//                     xQueueReset(uart_queue);
//                     break;
//                 // Event of UART RX break detected
//                 case UART_BREAK:
//                     ESP_LOGI(TAG, "uart rx break");
//                     break;
//                 // Event of UART parity check error
//                 case UART_PARITY_ERR:
//                     ESP_LOGI(TAG, "uart parity error");
//                     break;
//                 // Event of UART frame error
//                 case UART_FRAME_ERR:
//                     ESP_LOGI(TAG, "uart frame error");
//                     break;
//                 // UART_PATTERN_DET
//                 case UART_PATTERN_DET:
//                     uart_get_buffered_data_len(uart_num, &buffered_size);
//                     int pos = uart_pattern_pop_pos(uart_num);
//                     ESP_LOGI(TAG, "[UART PATTERN DETECTED] pos: %d, buffered size: %d", pos, buffered_size);
//                     if (pos == -1) {
//                         // There used to be a UART_PATTERN_DET event, but the pattern position queue is full so that it can not
//                         // record the position. We should set a larger queue size.
//                         // As an example, we directly flush the rx buffer here.
//                         uart_flush_input(uart_num);
//                     } else {
//                         uart_read_bytes(uart_num, dtmp, pos, 100 / portTICK_PERIOD_MS);
//                         uint8_t pat[PATTERN_CHR_NUM + 1];
//                         memset(pat, 0, sizeof(pat));
//                         uart_read_bytes(uart_num, pat, PATTERN_CHR_NUM, 100 / portTICK_PERIOD_MS);
//                         ESP_LOGI(TAG, "read data: %s", dtmp);
//                         ESP_LOGI(TAG, "read pat : %s", pat);
//                     }
//                     break;
//                 // Others
//                 default:
//                     ESP_LOGI(TAG, "uart event type: %d", event.type);
//                     break;
//             }
//         }
//     }

//     free(dtmp);
//     dtmp = NULL;
//     vTaskDelete(NULL);
// }
