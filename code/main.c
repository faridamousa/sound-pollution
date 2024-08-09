#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "LCDops.h"
#include "generalOps.h"
#include "presetChars.h"
#include "presetMessages.h"
#include "hardware/adc.h"

//defining all the pins
#define buzzer 18
#define sound_sensor_pin 26
#define switch 19
#define motor 20
int LCDpins[14] = {0,1,2,3,4,5,6,7,15,16,17,16,2};

int main(){
    stdio_init_all();
  
    gpio_init(buzzer);
    gpio_set_dir(buzzer ,GPIO_OUT);

   adc_init();
    adc_gpio_init(sound_sensor_pin);
    adc_select_input(0);

    gpio_init(switch);
    gpio_set_dir(switch,GPIO_IN);

    gpio_init(motor);
    gpio_set_dir(motor ,GPIO_OUT);

    bool flag = true;
    uint16_t sound_value = adc_read();

      for(int gpio = 0; gpio < 11; gpio++){
        gpio_init(LCDpins[gpio]);
        gpio_set_dir(LCDpins[gpio], true);
        gpio_put(LCDpins[gpio], false);
    }

    while (true) {

        printf("Sound Sensor Value: %d\n", sound_value);

        if (gpio_get(switch) == 1){
            flag=false;
        }   

        // Read analog value from the sound sensor
        if(sound_value<500){
         sound_value = adc_read();
           LCDinit();
           LCDclear();
           sleep_ms(8);
           LCDgoto("00");
           LCDsendRawInstruction(0,0,"00001100");
           LCDwriteMessage("the threshold is not exceeded");
         }
    
        

        // Print the analog value to the console (optional)
        
        // Example: Turn on the buzzer if the sound value is above a threshold
        else if (sound_value > 500  && flag) {

            gpio_put(buzzer , true);
            gpio_put(motor , true);
            LCDinit();
            LCDclear();
            sleep_ms(8);
            LCDgoto("00");
            LCDsendRawInstruction(0,0,"00001100");
            LCDwriteMessage("the threshold has been exceeded");
        } else  {
            gpio_put(buzzer , false);
            gpio_put(motor ,false);
            LCDinit();
            LCDclear();
            sleep_ms(8);
            LCDgoto("00");
            LCDsendRawInstruction(0,0,"00001100");
            LCDwriteMessage("the problem is handled");
            sleep_ms(3000);
            sound_value = adc_read();
            flag = true;
        }
    }
    return 0;
    
}