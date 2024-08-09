#include <stdio.h>
#include "pico/stdlib.h"

#define motor 0
int main() {
    stdio_init_all();
    gpio_init(motor);
    gpio_set_dir(motor ,GPIO_OUT);
    gpio_put(motor , true);
}