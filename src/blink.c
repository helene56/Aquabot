#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

void led_task()
{   
    // Initialize the Pico SDK and CYW43 driver
    if (cyw43_arch_init()) {
        return; // Initialization failed
    }
    const uint LED_PIN = CYW43_WL_GPIO_LED_PIN;
    // gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        cyw43_arch_gpio_put(LED_PIN, 1);
        vTaskDelay(900);
        cyw43_arch_gpio_put(LED_PIN, 0);
        vTaskDelay(900);
    }
}

// int main()
// {
//     stdio_init_all();

//     xTaskCreate(led_task, "LED_Task", 1024, NULL, 1, NULL);
//     vTaskStartScheduler();

//     while(1){};
// }