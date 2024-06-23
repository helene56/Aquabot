#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

// for now these values (voltage), need to test the sensor
#define WET 1.40f
#define DRY 2.20f

// pins
const uint moisture_sensor_pin = 26;
const uint motor_pin = 16;

bool waterer_on;

// initialize pins and initializing functions with setup function
void setup();
// read moisture level
double read_moisture();

// function to control motor and water plants
void water_plant();

int main()
{
    setup();
    while(1)
        // puts("Hello, world!");
        water_plant();
        // gpio_put(motor_pin, 0);
        // vTaskDelay(1000);
        // gpio_put(motor_pin, 1);


    return 0;
}

double read_moisture() {
    const double conversion_factor = 3.3f / (1 << 12); // Convert to voltage
    uint16_t result = adc_read(); // Read raw sensor value from ADC0
    double voltage = result * conversion_factor; // Convert raw value to voltage

    return voltage;
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

void water_plant()
{
    double moisture = read_moisture();
    // if moisture level == too dry, water else, do nothing
    if (moisture > DRY)
    {
        // turn motor on to water, water for at least 10 sec. (water needs time to go from the tube to the plant)
        printf("motor is ON\n");
        printf("voltage from moisture sensor: %f\n", moisture);
        // set to high, on
        gpio_put(motor_pin, 1);

        // when time == 10 sec, turn off motor
        vTaskDelay(800); // delay for 1000 ticks or 1 second, set to 10 sec

        printf("motor is OFF\n");

        gpio_put(motor_pin, 0);

    }
    puts("Hey moisture");
    
}
