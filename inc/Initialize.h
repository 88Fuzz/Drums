#ifndef __INCLUDE_INITIALIZE_H__
#define __INCLUDE_INITIALIZE_H__

//Function to initialize all peripherals needed.
void initialize();

//Initialize system clock to max speed
void initClock();

//Initialize all SSI modules
void initADC();

void initGPIO();
#endif
