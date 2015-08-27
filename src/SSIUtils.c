#include <stdint.h>

#include "SSIUtils.h"
#include "ModuleDefines.h"

#include "driverlib/ssi.h"
#include "driverlib/gpio.h"

void flushSSI(uint32_t base)
{
    uint32_t tmp;
    while((SSIDataGetNonBlocking(base,&tmp))!=0);
}

void putAndWaitSSI(uint32_t base, uint32_t data)
{
    SSIDataPutNonBlocking(base, data);
    while(SSIBusy(base));
}

void putAndWaitADC(uint32_t data)
{
    writeChipSelectADC(0);
    writeADC(data);
    writeChipSelectADC(0xff);
}

void writeADC(uint32_t data)
{
    putAndWaitSSI(ADC_BASE, data);
}

void writeChipSelectADC(uint8_t data)
{
    GPIOPinWrite(ADC_CS_BASE, ADC_CS_PIN, data);
}
