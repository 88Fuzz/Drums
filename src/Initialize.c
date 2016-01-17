#include "Initialize.h"
#include "SSIUtils.h"
#include "ModuleDefines.h"

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"

/*
 * Function to initialize all peripherals needed.
 */
void initialize()
{
    initClock();
    initADC();
    initGPIO();
}

/*
 * Initialize system clock to max speed
 */
void initClock()
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
}

/*
 * Initialize all SSI modules
 */
void initADC()
{
    uint32_t sysClockSpeed = SysCtlClockGet();

    //Enable port A3 to be a gpio pin to manually control chip select.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(ADC_CS_BASE, ADC_CS_PIN);

    //configure SPI communication between micros
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    //GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_2|GPIO_PIN_4);

    SSIConfigSetExpClk(ADC_BASE, sysClockSpeed, SSI_FRF_MOTO_MODE_0,
            SSI_MODE_MASTER, ADC_CLK_SPEED, ADC_NUM_BITS);
    SSIEnable(ADC_BASE);
    flushSSI(ADC_BASE);

    writeChipSelectADC(0xff);
}

void initGPIO()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeGPIOOutput(VOLUME_BASE, VOLUME_LOW|VOLUME_MED|VOLUME_HIGH);
}
