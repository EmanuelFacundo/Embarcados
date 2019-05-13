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
#include "defines.h"

int flag;
int rightOrLeft;

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/

#define TOGGLE 			(0x01u)
#define TRUE			(1)
#define PIN_BASE		(21)

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/

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
int _main(){

	rightOrLeft = 0x0;
	flag = 0x0;
	volatile unsigned int pin_control = 1;

	/* Ativando clocks funcionais para a instância GPIO1 e GPIO2. */
	//HWREG(SOC_PRCM_REGS + CM_PER_GPIO1_CLKCTRL) = (ENABLE_CM_PER_GPIO1_CLKCTRL<<0) | (1<<OPTFCLKEN_GPIO_1_GDBCLK);
	GPIO1ModuleClkConfig();
	GPIO2ModuleClkConfig();


	/* Selionando pin GPIO para o uso. */
	//HWREG(GPIO_INSTANCE_ADDRESS + CONF_GPMC_A5) = (MUX_GPIO<<0);
	GPIO1PinMuxSetup(GPIO1_INSTANCE_PIN_21);
	GPIO1PinMuxSetup(GPIO1_INSTANCE_PIN_22);
	GPIO1PinMuxSetup(GPIO1_INSTANCE_PIN_23);
	GPIO1PinMuxSetup(GPIO1_INSTANCE_PIN_24);
	GPIO2PinMuxSetup(GPIO2_INSTANCE_PIN_1);
	


	/* Setando o pin GPIO como pino de saida ou entrada. */
	//HWREG(SOC_GPIO_1_REGS + GPIO_OE_OFFSET) &= ~(1<<GPIO1_INSTANCE_PIN_21);
	GPIO1DirModeSetWrite(GPIO1_INSTANCE_PIN_21);
	GPIO1DirModeSetWrite(GPIO1_INSTANCE_PIN_22);
	GPIO1DirModeSetWrite(GPIO1_INSTANCE_PIN_23);
	GPIO1DirModeSetWrite(GPIO1_INSTANCE_PIN_24);
	GPIO2DirModeSetRead(GPIO2_INSTANCE_PIN_1);

	while(TRUE){

		if(GPIORead(GPIO2_INSTANCE_PIN_1)){

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
	flag ^= TOGGLE;

	if (flag){
		switch(uPin){
			case GPIO1_INSTANCE_PIN_21:
				GPIOWriteMode(GPIO1_INSTANCE_PIN_21, HIGH);
				break;

			case GPIO1_INSTANCE_PIN_22:
				GPIOWriteMode(GPIO1_INSTANCE_PIN_22, HIGH);
				break;

			case GPIO1_INSTANCE_PIN_23:
				GPIOWriteMode(GPIO1_INSTANCE_PIN_23, HIGH);
				break;

			case GPIO1_INSTANCE_PIN_24:
				GPIOWriteMode(GPIO1_INSTANCE_PIN_24, HIGH);
				break;

			default:
				break;	
		}
		
	}else{
		switch(uPin){
			case GPIO1_INSTANCE_PIN_21:
				GPIOWriteMode(GPIO1_INSTANCE_PIN_21, LOW);
				break;

			case GPIO1_INSTANCE_PIN_22:
				GPIOWriteMode(GPIO1_INSTANCE_PIN_22, LOW);
				break;

			case GPIO1_INSTANCE_PIN_23:
				GPIOWriteMode(GPIO1_INSTANCE_PIN_23, LOW);
				break;

			case GPIO1_INSTANCE_PIN_24:
				GPIOWriteMode(GPIO1_INSTANCE_PIN_24, LOW);
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
