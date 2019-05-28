/*
 * =====================================================================================
 *
 *       Filename:  LEDBlink.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/04/2019 20:50:49
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Emanuel Facundo Pinto, emanuel.facundo14@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include "gpio.h"

int flagIsr;
int flagLR;
int rightOrLeft;

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/

#define TOGGLE 			(0x01u)
#define PIN_BASE		(21)

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void gpioIsr(void);
void gpioAintcConfigure();
void delay(unsigned int TIME);
void toggle(unsigned int PIN);
int left(unsigned int i);
int right(unsigned int i);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(){

	rightOrLeft = 0x0;
	flagIsr = 0x0;
	flagLR = 0x0;
	unsigned int pin = 21, count = 0;
	volatile unsigned int pin_control = 1;

	/*Ativando IRQ in CPSR */
	IntMasterIRQEnable();

	/*-----------------------------------------------------------------------------
	 *  initialize GPIO and UART modules
	 *-----------------------------------------------------------------------------*/
	gpioInitModule(GPIO1);
	
	/*-----------------------------------------------------------------------------
	 *  initialize pin of mudule
	 *-----------------------------------------------------------------------------*/
	for(count = pin; count < 25 ;count++)
		gpioPinMuxSetup(GPIO1, count, OUTPUT);

	gpioPinMuxSetup(GPIO1, 18, INPUT);

	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	for(count = pin; count < 25 ;count++)
		gpioSetDirection(GPIO1, count, OUTPUT);
	
	gpioSetDirection(GPIO1, 18, INPUT);

	/* configure gpio interrupt on the INTC */
    gpioAintcConfigure();

    gpioPinIntConfig(GPIO_INTC_LINE_1, 18);
   
    /* Enable interrupt generation on detection of a rising or a falling edge.*/
    gpioIntTypeSet(SOC_GPIO_1_REGS, 18, GPIO_INTC_TYPE_RISE_EDGE);

	while(TRUE){

		if(flagIsr){

			rightOrLeft ^= TOGGLE;

			if (rightOrLeft)
			{
				pin_control = right(pin_control);
			
				toggle(PIN_BASE + pin_control);
				delay(300000);
				toggle(PIN_BASE + pin_control);
			}
			else
			{
				pin_control = left(pin_control);

				toggle(PIN_BASE + pin_control);
				delay(300000);
				toggle(PIN_BASE + pin_control);
			}

		}else{

			if (rightOrLeft)
			{
				pin_control = right(pin_control);
			
				toggle(PIN_BASE + pin_control);
				delay(300000);
				toggle(PIN_BASE + pin_control);
			}
			else
			{
				pin_control = left(pin_control);

				toggle(PIN_BASE + pin_control);
				delay(300000);
				toggle(PIN_BASE + pin_control);
			}

		}
	}

	/* Acender o LED. */
	//HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_21);

	/* Apagar o LED. */
	//HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_NUMBER);

	return 0;
} /* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  toggle
 *  Description:  
 * =====================================================================================
 */
void toggle(unsigned int uPin){

	flagLR ^= TOGGLE;

	if (flagLR){
		switch(uPin){
			case 21:
				gpioSetPinValue(GPIO1, uPin, HIGH);
				break;

			case 22:
				gpioSetPinValue(GPIO1, uPin, HIGH);
				break;

			case 23:
				gpioSetPinValue(GPIO1, uPin, HIGH);
				break;

			case 24:
				gpioSetPinValue(GPIO1, uPin, HIGH);
				break;

			default:
				break;	
		}
		
	}else{
		switch(uPin){
			case 21:
				gpioSetPinValue(GPIO1, uPin, LOW);
				break;

			case 22:
				gpioSetPinValue(GPIO1, uPin, LOW);
				break;

			case 23:
				gpioSetPinValue(GPIO1, uPin, LOW);
				break;

			case 24:
				gpioSetPinValue(GPIO1, uPin, LOW);
				break;

			default:
				break;	
		}
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delay
 *  Description:  
 * =====================================================================================
 */
void delay(unsigned int TIME){
	volatile unsigned int ra;
	for(ra = 0; ra < TIME;ra++);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  left_or_right
 *  Description:  
 * =====================================================================================
 */
int left(unsigned int i){
	if(i == 3){
		return (0);
	}
	
	return (i+1);
}

int right(unsigned int i){ 
	if(i==0){
		return (3);
	}

	return (i-1);
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : gpioIsr
* Comments      : DMTimer interrupt service routine. This will 
* send a character to serial.
*END*-----------------------------------------------------------*/    
static void gpioIsr(void) {
	flagIsr ^= TOGGLE;
  // include action here			
	/* Clear wake interrupt	*/
	//HWREG(SOC_GPIO_1_REGS + 0x3C) |= (1<<28);
	//HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) |= (1<<21);

	
	HWREG(SOC_GPIO_1_REGS + 0x2C) = 0xFFFFFFFF;
}

/c    ccj ç4s/cxfg/f////xfgxfggggggggg//////////gddddddddddddddddddddddddddddddddddddddddddddddddsssssssssssssssssssffd/dddd//////////sssssssssssssssssssssssssssssssssssss/////sssss///ff////ffdfd/f///f
*
* Function Name : gpioAintcconfigure
* Comments      : Do the necessary gpio configurations on to AINTC.
*END*-----------------------------------------------------------*/
void gpioAintcConfigure(){

    /* Initialize the ARM interrupt control */
    IntAINTCInit();
 
    /* Registering gpioIsr */
    IntRegister(SYS_INT_GPIOINT1A, gpioIsr);
    
    /* Set the priority */
    IntPrioritySet(SYS_INT_GPIOINT1A, 0, AINTC_HOSTINT_ROUTE_IRQ);
    
    /* Enable the system interrupt */
    IntSystemEnable(SYS_INT_GPIOINT1A);
   
}
