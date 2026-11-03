# Lab 5 – Real-Time Timekeeping, Interrupt Latency, and Scheduling

## Activity 1: Jitter and Drift

Nominal period: 200 ms (100 ms per toggle).

| Program | Busy wait | Period (mean) | Jitter (std dev) | Freq | Duty | Drift over 1 hr | Image |
|---|---|---|---|---|---|---|---|
| sleep.c | No | 199.99 ms | 0 | 5.0002 Hz | 50.0 % | 0.14 s fast | [IMG_1445](drive-download-20261103T044943Z-1-001/IMG_1445.JPEG) |
| sleep.c | Yes (3.2 ms) | 206.39 ms | 0 | 4.8451 Hz | 50.0 % | 111 s slow | [IMG_1440](drive-download-20261103T044943Z-1-001/IMG_1440.JPEG) |
| sleep.c | Yes (17.6 ms) | 235.19 ms | 0 | 4.2518 Hz | 50.0 % | 539 s slow | [IMG_1447](drive-download-20261103T044943Z-1-001/IMG_1447.JPEG) |
| timer.c | No | 199.99 ms | 0 | 5.0002 Hz | 50.0 % | 0.14 s fast | [IMG_1443](drive-download-20261103T044943Z-1-001/IMG_1443.JPEG) |
| timer.c | Yes (17.6 ms) | 199.99 ms | 0 | 5.0002 Hz | 50.0 % | 0.14 s fast | [IMG_1448](drive-download-20261103T044943Z-1-001/IMG_1448.JPEG) |
| task_delay.c | No | 199.99 ms | 0 | 5.0002 Hz | 50.0 % | 0.14 s fast | [IMG_1444](drive-download-20261103T044943Z-1-001/IMG_1444.JPEG) |
| task_delay.c | Yes (17.6 ms) | 303.99 ms | 0 | 3.2896 Hz | 50.0 % | 1232 s slow | [IMG_1449](drive-download-20261103T044943Z-1-001/IMG_1449.JPEG) |
| Function generator | – | 99.999 ms | 6.0 µs | 10.000 Hz | 50.0 % | 0.04 s fast | [IMG_1452](drive-download-20261103T044943Z-1-001/IMG_1452.JPEG) |

TODO: confirm the program and busy-wait setting for IMG_1443, 1444, 1447, 1448 and 1449 (these photos weren't labelled).

- Without a busy wait, all three methods are equally accurate (about 40 ppm, 0.14 s/hr).
- sleep_ms and vTaskDelay start counting after the busy wait finishes, so the busy wait adds to every period
- timer.c isn't affected, because its repeating timer is scheduled from the start of each callback.
- The task_delay.c busy-wait run also had 2 spin threads. The 17.6 ms busy wait took about 52 ms there, because the CPU was shared among 3 tasks of equal priority

## Activity 2: Interrupt Latency

| Case | Delay (mean) | Jitter (std dev) | Image |
|---|---|---|---|
| No busy wait | 1.622 µs | 2.4 ns | [IMG_1455](drive-download-20261103T044943Z-1-001/IMG_1455.JPEG) |
| Busy wait before toggle | 17.602 ms | 0 | [IMG_1458](drive-download-20261103T044943Z-1-001/IMG_1458.JPEG) |

The busy wait added directly to the latency (1.6 µs + 17.6 ms).

## Activity 3: RTOS Scheduler



## Comparison with Other Team
