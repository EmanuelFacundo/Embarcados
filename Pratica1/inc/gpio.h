#ifndef __GPIO_INCLUDE
#define __GPIO_INCLUDE



static void GPIO1ModuleClkConfig();

static void GPIO1PinMuxSetup(unsigned int PIN);

static void GPIODirModeSet(unsigned int PIN);

static void GPIOWriteMode(unsigned int PIN, unsigned int OUTPUT);



#endif /* __GPIO_INCLUDE */