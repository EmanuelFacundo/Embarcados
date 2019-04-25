#ifndef __GPIO_INCLUDE
#define __GPIO_INCLUDE



void GPIO1ModuleClkConfig();

void GPIO1PinMuxSetup(unsigned int PIN);

void GPIODirModeSet(unsigned int PIN);

void GPIOWriteMode(unsigned int PIN, unsigned int OUTPUT);



#endif /* __GPIO_INCLUDE */