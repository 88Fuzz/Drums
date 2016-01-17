#include <stdint.h>

#include "Initialize.h"
#include "SSIUtils.h"
#include "ModuleDefines.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

uint8_t ui8PinData=2;

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    initialize();

    while(1)
    {   
        SysCtlDelay(2000000);
        uint32_t adcValue = getADCValue(0x0);
        uint32_t why = adcValue;
    }   
}
