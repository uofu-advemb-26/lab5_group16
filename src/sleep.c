#include <stdio.h>
#include <pico/stdlib.h>
// a loop with a sleep delay.
int main(void)
{
    int toggle = 0;
    stdio_init_all();
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    while (true) {
        toggle = !toggle;
        gpio_put(OUT_PIN, toggle);
        
        // Introduce a busy wait loop after the GPIO is toggled.
        // Busy wait sets the processor in a tight loop ( a counter loop with a noop body)

        for (volatile uint32_t i = 0; i < 200000; i++) {
            __asm volatile("nop");
        }

        sleep_ms(DELAY_MS);
    }
}