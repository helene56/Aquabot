#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "queue.h"

static QueueHandle_t xQueue = NULL;

void led_task(void *pvParamters)
{   
    // Initialize the Pico SDK and CYW43 driver
    if (cyw43_arch_init()) {
        return; // Initialization failed
    }
    const uint LED_PIN = CYW43_WL_GPIO_LED_PIN;
    uint uIValueToSend = 0;
    // gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        cyw43_arch_gpio_put(LED_PIN, 1);
        uIValueToSend = 1;
        // sends a task to the queue (first position)
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(900);
        cyw43_arch_gpio_put(LED_PIN, 0);
        uIValueToSend = 0;
        // sends a task to the queue (second position)
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(900);
    }
}

void usb_task(void *pvParamters)
{
    uint uIRecievedValue;
    
    while (1)
    {
        // reads the task, then removes it
        xQueueReceive(xQueue, &uIRecievedValue, portMAX_DELAY);

        if (uIRecievedValue == 1)
        {
            printf("LED is on\n");
        }
        if (uIRecievedValue == 0)
        {
            printf("LED is off\n");
        }
    }

}

// int main()
// {
//     stdio_init_all();
//     xQueue = xQueueCreate(1, sizeof(uint));

//     xTaskCreate(led_task, "LED_Task", 1024, NULL, 1, NULL);
//     xTaskCreate(usb_task, "USB_Task", 1024, NULL, 1, NULL);
//     vTaskStartScheduler();

//     while(1){};
// }