#ifndef __GPIO_INCLUDE
#define __GPIO_INCLUDE

#include "defines.h"

enum GPIO_Pin
{
	PIN_21 = 21,
	PIN_22 = 22,
	PIN_23 = 23,
	PIN_24 = 24
	
};

typedef enum GPIO_Pin GPIO_Pin_t;

void GPIO1ModuleClkConfig();

void GPIO1PinMuxSetup(unsigned int uPin);

void GPIODirModeSet(GPIO_Pin_t pin);

void GPIOWriteMode(unsigned int uPin, unsigned int uValue);



#endif /* __GPIO_INCLUDE */