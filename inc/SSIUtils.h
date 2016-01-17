#ifndef __SSI_UTILS__
#define __SSI_UTILS__

#include <stdint.h>

void flushSSI(uint32_t);
void putSSI(uint32_t, uint32_t);
void putAndWaitSSI(uint32_t, uint32_t);
uint32_t getADCValue(uint32_t);
uint32_t readADC();
void putAndWaitADC(uint32_t);
void getADCRegisterValue(uint32_t *);
void writeADC(uint32_t);
void writeAndWaitADC(uint32_t);
void writeChipSelectADC(uint8_t);

#endif
