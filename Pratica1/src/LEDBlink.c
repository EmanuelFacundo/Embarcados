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

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/

#define TOGGLE 			(0X01u)
#define TRUE			(1)
#define PIN_BASE		(21)

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/

static void delay(unsigned int TIME);
static void toggle(unsigned int PIN);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int _main(){

	flag = 0x0;
	volatile unsigned int pin_control = 0x0;

	/* Ativando clocks funcionais para a instância GPIO1. */
	GPIO1ModuleClkConfig();

	/* Selionando pin GPIO[21] para o uso. */
	GPIO1PinMuxSetup(GPIO1_INSTANCE_PIN_21);
	GPIO1PinMuxSetup(GPIO1_INSTANCE_PIN_22);
	GPIO1PinMuxSetup(GPIO1_INSTANCE_PIN_23);
	GPIO1PinMuxSetup(GPIO1_INSTANCE_PIN_24);

	/* Setando o pin GPIO como pino de saida. */
	GPIODirModeSet(GPIO1_INSTANCE_PIN_21);
	GPIODirModeSet(GPIO1_INSTANCE_PIN_22);
	GPIODirModeSet(GPIO1_INSTANCE_PIN_23);
	GPIODirModeSet(GPIO1_INSTANCE_PIN_24);

	while(TRUE){

		toggle(PIN_BASE + pin_control);
		delay(50000);
		toggle(PIN_BASE + pin_control);
		delay(50000);

		pin_control = ((pin_control+1) % 4);

	}

	/* Acender o LED */
	//HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1<<GPIO1_INSTANCE_PIN_NUMBER);

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

void toggle(unsigned int PIN){
	flag ^= TOGGLE;

	if (flag){
		switch(PIN){
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
		switch(PIN){
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
	for(ra = 0; ra < TIME; ra ++);
}