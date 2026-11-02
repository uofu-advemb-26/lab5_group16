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
        vTaskDelay(1);
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
    for (int i = 0; i < NUM_SPIN_TASKS; i++) {
        xTaskCreate(spin_task, "SpinThread", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, NULL);
    }
    vTaskStartScheduler();
    return 0;
}