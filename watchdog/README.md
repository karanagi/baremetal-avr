# Watch Dog Timer Demo

This directory includes a test implementation of a software reset using the watch dog timer. 

When a user pushes a button the watch dog timer is enabled, all interrupts are disabled, and the program enters an infinite loop until the watch dog timer expires. Here, a push button is being used for the sake of controlling the timing of the software reset, instead of some other factor.

A timer is configured early in the boot sequence to trigger every 1ms. The watch dog timer is reset with the associated interrupt handler, preventing the micro controller from resetting.

It would have been nice if I didn't have to set up another timer, but it seems like the watch dog timer is either not disabled in time, or not disabled at all upon calling `wdt_disable()`, even when placed in the `.init3` section. 
