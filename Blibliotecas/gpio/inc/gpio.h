#ifndef __GPIO
#define __GPIO

/*
 * =====================================================================================
 *
 *       Filename:  gpio.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/05/2019 12:23:07
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Emanuel Facundo Pinto, emanuel.facundo14@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

/*-----------------------------------------------------------------------------
 *  init ENUMs
 *-----------------------------------------------------------------------------*/
typedef enum{
   MODE_0 = 0,
   MODE_1,
   MODE_2,
   MODE_3,
   MODE_4,
   MODE_5,
   MODE_6,
   MODE_7
   
}pinmode_t;

typedef enum _pinLevel{
	LOW,
	HIGH
}pinLevel;				/* ----------  end of enum pinLevel  ---------- */

typedef enum _gpioPin{
	GPIO0,
	GPIO1,
	GPIO2,
	GPIO3,
	GPIO4,
	GPIO5,
	GPIO6,
	GPIO7,
	GPIO8,
	GPIO9,
	GPIO10,
	GPIO11,
	GPIO12,
	GPIO13,
	GPIO14,
	GPIO15,
	GPIO16,
	GPIO17,
	GPIO18,
	GPIO19,
	GPIO20,
	GPIO21,
	GPIO22,
	GPIO23,
	GPIO24,
	GPIO25,
	GPIO26,
	GPIO27,
	GPIO29,
	GPIO30,
	GPIO31
}gpioPins;				/* ----------  end of enum gpioPort  ---------- */	

typedef enum _gpioPort{
	MODULE0,
	MODULE1,
	MODULE2,
	MODULE3
}gpioPort;				/* ----------  end of enum gpioPort  ---------- */

typedef enum _pinDirection{
	OUTPUT,
	INPUT
}pinDirection;				/* ----------  end of enum pinDirection  ---------- */


/*-----------------------------------------------------------------------------
 *  Function prototype
 *-----------------------------------------------------------------------------*/

void gpioModuleClkConfig(gpioPort port);

#endif /* __GPIO */