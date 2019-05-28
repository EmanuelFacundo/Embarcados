#ifndef GPIO_H_
#define GPIO_H_

/*
 * =====================================================================================
 *
 *       Filename:  gpio.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/02/2017 10:39:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "clock_module.h"
#include "control_module.h"
#include "pad.h"
#include "interrupt.h"
#include "soc_AM335x.h"
#include "hw_types.h"


#define GPIO_IRQSTATUS_SET(n)   (0x34 + (n * 4))
#define GPIO_IRQSTATUS_CLR(n)   (0x3C + (n * 4))
#define GPIO_LEVELDETECT(n)   	(0x140 + (n * 4))

#define GPIO_REVISION           0x000
#define GPIO_SYSCONFIG          0x010
#define GPIO_EOI                0x020
#define GPIO_IRQSTATUS_RAW_0    0x024
#define GPIO_IRQSTATUS_RAW_1    0x028
#define GPIO_IRQSTATUS_0        0x02C
#define GPIO_IRQSTATUS_1        0x030
#define GPIO_IRQSTATUS_SET_0    0x034
#define GPIO_IRQSTATUS_SET_1    0x038
#define GPIO_IRQSTATUS_CLR_0    0x03C
#define GPIO_IRQSTATUS_CLR_1    0x040
#define GPIO_IRQWAKEN_0         0x044
#define GPIO_IRQWAKEN_1         0x048
#define GPIO_SYSSTATUS          0x114
#define GPIO_CTRL               0x130
#define GPIO_OE                 0x134
#define GPIO_DATAIN             0x138
#define GPIO_DATAOUT            0x13C
#define GPIO_RISINGDETECT       0x148
#define GPIO_FALLINGDETECT      0x14C
#define GPIO_DEBOUNCENABLE      0x150
#define GPIO_DEBOUNCINGTIME     0x154
#define GPIO_CLEARDATAOUT       0x190
#define GPIO_SETDATAOUT         0x194

/* Values denoting the Interrupt Line number to be used. */
#define GPIO_INTC_LINE_1                  (0x0)
#define GPIO_INTC_LINE_2                  (0x1)

/*
** Values used to enable/disable interrupt generation due to level
** detection on an input GPIO pin.
*/
#define GPIO_INTC_TYPE_NO_LEVEL           (0x01)
#define GPIO_INTC_TYPE_LEVEL_LOW          (0x04)
#define GPIO_INTC_TYPE_LEVEL_HIGH         (0x08)
#define GPIO_INTC_TYPE_BOTH_LEVEL         (0x0C)

/*
** Values used to enable/disable interrupt generation due to edge
** detection on an input GPIO pin.
*/
#define GPIO_INTC_TYPE_NO_EDGE            (0x80)
#define GPIO_INTC_TYPE_RISE_EDGE          (0x10)
#define GPIO_INTC_TYPE_FALL_EDGE          (0x20)
#define GPIO_INTC_TYPE_BOTH_EDGE          (0x30)


/*-----------------------------------------------------------------------------
 *  GPIO pin number type (0-31)
 *-----------------------------------------------------------------------------*/
typedef unsigned char ucPinNumber;

/*-----------------------------------------------------------------------------
 *  init ENUMs
 *-----------------------------------------------------------------------------*/
typedef enum _pinLevel{
	LOW,
	HIGH
}pinLevel;				/* ----------  end of enum pinLevel  ---------- */

typedef enum _gpioPort{
	GPIO0,
	GPIO1,
	GPIO2,
	GPIO3
}gpioPort;				/* ----------  end of enum gpioPort  ---------- */

typedef enum _pinDirection{
	OUTPUT,
	INPUT
}pinDirection;				/* ----------  end of enum pinDirection  ---------- */



/*-----------------------------------------------------------------------------
 *  Function prototype
 *-----------------------------------------------------------------------------*/
void gpioInitModule(gpioPort );
void gpioPinMuxSetup(gpioPort ,ucPinNumber, pinDirection );
void gpioAintcConfigure(unsigned int );
void gpioIntTypeSet(unsigned int ,unsigned int ,unsigned int );
int  gpioPinIntConfig(unsigned int ,unsigned int );
void gpioSetDirection(gpioPort ,ucPinNumber ,pinDirection );	
int  gpioGetDirection(ucPinNumber ,ucPinNumber );
void gpioSetPinValue(gpioPort ,ucPinNumber ,pinLevel );
unsigned int gpioGetPinValue(gpioPort ,ucPinNumber );
	
#endif /*GPIO_H_ */
