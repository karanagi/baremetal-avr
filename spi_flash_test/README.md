# SPI Flash Test

A test program to get a feel for interacting with a SPI device (in this case the [W25Q64FV Flash Memory](<https://www.lcsc.com/datasheet/C97521.pdf>)).

The program reads the following informatoin and dumps it to the user through UART: 
- status register before and after a software reset (command 0x66 and 0x99)
- JEDEC ID (vendor ID) of the flash chip

The only issue is, however, the initial value (default value) of the status registers for this particular break-out board is unknown, so I am not able to confirm if the output I am getting is actually what it's supposed to be.

```console
Before reset:                                              
status1: 0x90                                              
status2: 0x2                                               
                                                           
After reset:                                               
status1: 0x90                                              
status2: 0x2                                               
                                                           
Manufacturer id: 0xef                                      
Memory type id: 0x40                                       
Capacity id: 0x17         
```
