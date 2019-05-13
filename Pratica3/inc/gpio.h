#ifndef __GPIO_INCLUDE
#define __GPIO_INCLUDE

#include "defines.h"

enum GPIO_Pin
{
	PIN_21 = 21,
	PIN_22,
	PIN_23,
	PIN_24
	
};

typedef enum GPIO_Pin GPIO_Pin_t;

void GPIO1ModuleClkConfig();

void GPIO2ModuleClkConfig();

void GPIO1PinMuxSetup(unsigned int uPin);

void GPIO2PinMuxSetup();

void GPIO1DirModeSetWrite(GPIO_Pin_t pin);

void GPIO2DirModeSetRead(unsigned int pin);

void GPIOWriteMode(unsigned int uPin, unsigned int uValue);

unsigned int GPIORead(unsigned int pin);

#endif /* __GPIO_INCLUDE */
