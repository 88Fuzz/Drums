#ifndef __SSI_UTILS__
#define __SSI_UTILS__

#include <stdint.h>

void flushSSI(uint32_t);
void putAndWaitSSI(uint32_t, uint32_t);
void putAndWaitADC(uint32_t);
void writeADC(uint32_t);
void writeChipSelectADC(uint8_t);

#endif
