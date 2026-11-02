add_compile_definitions(
    DELAY_MS=100
    IN_PIN=6
    OUT_PIN=7)

add_executable(task_delay task_delay.c)
# Number of equal-priority spin threads to start alongside main_task (1 or 2).
target_compile_definitions(task_delay PRIVATE NUM_SPIN_TASKS=1)
pico_enable_stdio_uart(task_delay 0)
pico_enable_stdio_usb(task_delay 1)
target_link_libraries(task_delay PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)
pico_add_extra_outputs(task_delay)
add_custom_target(flash_delay picotool load -f $<TARGET_FILE:task_delay> DEPENDS task_delay)


add_executable(timer timer.c)
pico_enable_stdio_uart(timer 0)
pico_enable_stdio_usb(timer 1)
target_link_libraries(timer PRIVATE pico_stdlib)
pico_add_extra_outputs(timer)
add_custom_target(flash_timer picotool load -f $<TARGET_FILE:timer> DEPENDS timer)


add_executable(sleep sleep.c)
pico_enable_stdio_uart(sleep 0)
pico_enable_stdio_usb(sleep 1)
target_link_libraries(sleep PRIVATE pico_stdlib)
pico_add_extra_outputs(sleep)
add_custom_target(flash_sleep picotool load -f $<TARGET_FILE:sleep> DEPENDS sleep)


add_executable(gpio_interrupt gpio_interrupt.c)
pico_enable_stdio_uart(gpio_interrupt 0)
pico_enable_stdio_usb(gpio_interrupt 1)
target_link_libraries(gpio_interrupt PRIVATE pico_stdlib)
pico_add_extra_outputs(gpio_interrupt)
add_custom_target(flash_gpio_interrupt picotool load -f $<TARGET_FILE:gpio_interrupt> DEPENDS gpio_interrupt)


# This is the main binary. List your C files here.
add_executable(hello_freertos
    hello_freertos.c
    )

pico_set_program_name(hello_freertos "test")
pico_set_program_version(hello_freertos "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(hello_freertos 0)
pico_enable_stdio_usb(hello_freertos 1)

# Add the libraries to the build
target_link_libraries(hello_freertos PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(hello_freertos PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(hello_freertos)

find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

add_custom_target(flash ${PICOTOOL} load -f $<TARGET_FILE:hello_freertos> DEPENDS hello_freertos)
add_custom_target(openocd_flash ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c program "$<TARGET_FILE:hello_freertos>" verify reset exit' DEPENDS hello_freertos)
