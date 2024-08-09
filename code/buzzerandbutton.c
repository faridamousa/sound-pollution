#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define switch 10
#define buzzer 7

int main() {
    stdio_init_all();
    gpio_init(switch);
    gpio_init(buzzer);
    gpio_set_dir(buzzer ,GPIO_OUT);
    bool flag = false;
    gpio_set_dir(switch, GPIO_IN);
    gpio_put(buzzer , false);
    while (true)
    {
        if(gpio_get(switch) == 1){
            if(!flag){
                gpio_put(buzzer , true);
                flag = true;
            }else{
                gpio_put(buzzer , false);
                flag = false;
            }
        }
    }
    
}