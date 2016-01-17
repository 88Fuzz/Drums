#include <stdbool.h>

#include "VolumeHelper.h"
#include "ModuleDefines.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

void volumeLights(int32_t volume)
{
    if(volume < VOLUME_DIFF_THRESHOLD)
        return;

    if(volume > VOLUME_LOW_THRESHOLD)
        GPIOPinWrite(VOLUME_BASE, VOLUME_LOW, 0xff);
    else
        GPIOPinWrite(VOLUME_BASE, VOLUME_LOW, 0);

    if(volume > VOLUME_MED_THRESHOLD)
        GPIOPinWrite(VOLUME_BASE, VOLUME_MED, 0xff);
    else
        GPIOPinWrite(VOLUME_BASE, VOLUME_MED, 0);

    if(volume > VOLUME_HIGH_THRESHOLD)
        GPIOPinWrite(VOLUME_BASE, VOLUME_HIGH, 0xff);
    else
        GPIOPinWrite(VOLUME_BASE, VOLUME_HIGH, 0);
}
