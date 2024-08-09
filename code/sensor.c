#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define buzzer 7
#define sound_sensor_pin 26  // Change this to the appropriate analog pin

int main() {
    stdio_init_all();
    gpio_init(buzzer);
    gpio_set_dir(buzzer ,GPIO_OUT);

    // Initialize ADC (Analog-to-Digital Converter)
    adc_init();
    adc_gpio_init(sound_sensor_pin);
    adc_select_input(0);  // Select the appropriate ADC channel (0-3)

    while (true) {
        // Read analog value from the sound sensor
        uint16_t sound_value = adc_read();

        // Print the analog value to the console (optional)
        printf("Sound Sensor Value: %d\n", sound_value);

        // Example: Turn on the buzzer if the sound value is above a threshold
        if (sound_value > 500) {
            gpio_put(buzzer , true);
        } else {
            gpio_put(buzzer , false);
        }

        // Adjust sleep duration as needed
        sleep_ms(200);
    }

    return 0;
}