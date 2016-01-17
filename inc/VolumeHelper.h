#ifndef __VOLUME_HELPER__
#define __VOLUME_HELPER__

#include <stdint.h>

#define MAX_VOLUME 1023
#define VOLUME_LOW_THRESHOLD 0
#define VOLUME_MED_THRESHOLD MAX_VOLUME/3
#define VOLUME_HIGH_THRESHOLD VOLUME_MED_THRESHOLD*2

void volumeLights(uint16_t);

#endif
