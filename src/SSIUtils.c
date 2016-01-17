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

void putSSI(uint32_t base, uint32_t data)
{
    SSIDataPutNonBlocking(base, data);
}

uint32_t getADCValue(uint32_t channel)
{
    uint8_t data = 0x01;
    if(channel > 8)
        return 0;

    writeChipSelectADC(0);

    writeADC(data);
    data = (data << 7) | (channel << 4);
    writeADC(data);
    writeAndWaitADC(0);

    writeChipSelectADC(0xff);

    return readADC();
}

void putAndWaitADC(uint32_t data)
{
    writeChipSelectADC(0);
    writeADC(data);
    writeChipSelectADC(0xff);
}

uint32_t readADC()
{
    uint32_t retVal = 0, tmp = 0;

    getADCRegisterValue(&tmp);
    tmp = 0;
    getADCRegisterValue(&retVal);
    getADCRegisterValue(&tmp);
    retVal <<= 8;
    retVal |= tmp;
    
    return retVal;
}

void getADCRegisterValue(uint32_t *data)
{
    SSIDataGetNonBlocking(ADC_BASE, data);
}

void writeADC(uint32_t data)
{
    putSSI(ADC_BASE, data);
}

void writeAndWaitADC(uint32_t data)
{
    putAndWaitSSI(ADC_BASE, data);
}

void writeChipSelectADC(uint8_t data)
{
    GPIOPinWrite(ADC_CS_BASE, ADC_CS_PIN, data);
}
