# SPI Flash Test

A test program to get a feel for interacting with a SPI device (in this case the [W25Q64FV Flash Memory](<https://www.lcsc.com/datasheet/C97521.pdf>)).

The program reads the following informatoin and dumps it to the user through UART: 
- status register before and after a software reset (command 0x66 and 0x99)
- JEDEC ID (vendor ID) of the flash chip

