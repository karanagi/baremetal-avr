#ifndef		__ADC_H
#define		__ADC_H

#include <stdint.h>

void adc_init();
void adc_disable();
uint16_t adc_read();

#endif
