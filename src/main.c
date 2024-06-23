#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include "queue.h"

// for now these values (voltage), need to test the sensor
#define WET 1.40f
#define DRY 2.20f
#define DELAY (pdMS_TO_TICKS(10000)) // Delay for 10000 milliseconds or 10 seconds


const uint moisture_sensor_pin = 26;
const uint motor_pin = 16;


// static QueueHandle_t xQueue = NULL;

// function prototypes
void setup();
double read_moisture();
void water_plant_task(); //Task


int main()
{
    setup();

    xTaskCreate(water_plant_task, "water_plant_Task", 1024, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1);
}


void setup()
{
    stdio_init_all();
    adc_init(); //initiliaze adc module
    adc_gpio_init(moisture_sensor_pin);
    adc_select_input(0); // selects ADC0 as the input

    // initialise motor pin as output
    gpio_init(motor_pin);
    gpio_set_dir(motor_pin, GPIO_OUT);
    // set to low, off
    gpio_put(motor_pin, 0);
}

double read_moisture() 
{
    const double conversion_factor = 3.3f / (1 << 12); // Convert to voltage
    double voltage;
    uint16_t result = adc_read(); // Read raw sensor value from ADC0
    voltage = result * conversion_factor; // Convert raw value to voltage

    return voltage;
}

void water_plant_task()
{
    double moisture = read_moisture();
    // if moisture level == too dry, water else, do nothing
    while(1)
    {
        double moisture = read_moisture();
        // if moisture level == too dry, water else, do nothing
        if (moisture > DRY)
        {
            // turn motor on to water, water for at least 10 sec. (water needs time to go from the tube to the plant)
            // set to high, on
            gpio_put(motor_pin, 1);
            printf("motor is ON\n");
            printf("voltage from moisture sensor: %f\n", moisture);

        }
        vTaskDelay(DELAY); // delay a bit
        gpio_put(motor_pin, 0);
        printf("motor is OFF\n");
        printf("voltage from moisture sensor: %f\n", moisture);
        vTaskDelay(DELAY); // delay the next reading
        
        }   
}