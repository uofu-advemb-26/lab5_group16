#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
//: a loop with a delay using a thread sleep.
void main_task(__unused void *params)
{
    int toggle = 0;
    while (1) {
        toggle = !toggle;
        gpio_put(OUT_PIN, toggle);

        for (volatile uint32_t i = 0; i < 200000; i++) {
            __asm volatile("nop");
        }

        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}

void spin_task(__unused void *params)
{
    while (1){}
}

int main(void)
{
    stdio_init_all();
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    const char *rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &task);
    xTaskCreate(spin_task, "SpinThread1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, NULL);
    xTaskCreate(spin_task, "SpinThread2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, NULL);
    vTaskStartScheduler();
    return 0;
}