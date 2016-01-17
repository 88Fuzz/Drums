#ifndef __MODULE_DEFINES__
#define __MODULE_DEFINES__

#include "inc/hw_memmap.h"

/*
 * Defines for ADC SSI ports
 */

#define ADC_BASE SSI0_BASE
#define ADC_CS_BASE GPIO_PORTA_BASE
#define ADC_CS_PIN GPIO_PIN_3
//#define ADC_CS_BASE GPIO_PORTF_BASE
//#define ADC_CS_PIN GPIO_PIN_1

//1MHz CLK speed for ADC
#define ADC_CLK_SPEED 1000000

//Number of bits communcated between ADC and micro
//For every transaction between ADC and micro, there will be 3 bytes of information sent
//Documentation https://www.adafruit.com/datasheets/MCP3008.pdf
#define ADC_NUM_BITS 8


#define VOLUME_BASE GPIO_PORTD_BASE
#define VOLUME_LOW GPIO_PIN_0
#define VOLUME_MED GPIO_PIN_1
#define VOLUME_HIGH GPIO_PIN_2
#endif
