Lab 5 Report - Group 16

Code is on the branch "charbel_real_time" with a PR to be merged to main.

**Activity 1 - Jitter:**
  - What we did: We added a busy-wait loop after each GPIO toggle in sleep.c, timer.c, and task_delay.c.
  - What we saw: The target period is 200ms. The drift is calculated as (period - 200)/(200*3600 seconds).

  sleep.c - 199.99 ms w/o busy-wait, 235.19 ms with busy-wait = +633 sec drift (per hour)
  timer.c - 199.99 ms w/o busy-wait, 199.99 ms with busy-wait = -0.18 sec drift (per hour)
  task_delay.c - 199.99 ms w/o busy-wait, 303.99 ms with busy-wait = +1872 sec drift (per hour)

  Observations: 
  - Jitter was below what the oscilloscope could measure
  - sleep.c and task_delay.c drift because they wait 100 ms after the work, so the busy-wait gets added every cycle.
  - timer.c doesn't drift because it fires on a fixed schedule.
  - task_delay.c drifts most because the other two tasks share the CPU and slow the busy wait down.
  - There is a slight drift because the pico runs slightly fast.

 ** Activity 2 - Interrupt latency:**
  - What we did: We added the same busy loop but put it in the interrupt handler before the GPIO toggle.
  - What we observed: We measured the delay from the waveform generator sync to the pico output pin.

  Without the busy-wait: 1.62 us, Std. dev - 2.4 ns
  With the busy-wait: 17.60 ms, Std dev - 0.0 s

  Observations:
  - The work done in the handler before the toggle adds directly to the latency.
  - 

  **Activity 3 - RTOS Scheduler:**
  - What we did: task_delay.c now uses vTaskDelay(1) and runs alongside one or two while(1) tasks at the same priority.
  - Predictions: 
      - 
