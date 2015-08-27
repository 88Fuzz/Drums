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
#define ADC_NUM_BITS 16

#endif
