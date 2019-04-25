/*
 * =====================================================================================
 *
 *       Filename:  gpio.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/04/2019 10:46:05
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

/*****************************************************************************
**                INTERNAL FUNCTIONS
*****************************************************************************/

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO1ModuleClkConfig
 *  Description:  
 * =====================================================================================
 */
void GPIO1ModuleClkConfig(){
	HWREG(SOC_PRCM_REGS + CM_PER_GPIO1_CLKCTRL) = (ENABLE_CM_PER_GPIO1_CLKCTRL<<0) | (1<<OPTFCLKEN_GPIO_1_GDBCLK);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO1PinMuxSetup
 *  Description:  
 * =====================================================================================
 */

void GPIO1PinMuxSetup(unsigned int PIN){
	switch(PIN){
		case GPIO1_INSTANCE_PIN_21:
			HWREG(GPIO_INSTANCE_ADDRESS + CONF_GPMC_A5) = (MUX_GPIO<<0);
			break;

		case GPIO1_INSTANCE_PIN_22:
			HWREG(GPIO_INSTANCE_ADDRESS + CONF_GPMC_A6) = (MUX_GPIO<<0);
			break;

		case GPIO1_INSTANCE_PIN_23:
			HWREG(GPIO_INSTANCE_ADDRESS + CONF_GPMC_A7) = (MUX_GPIO<<0);
			break;

		case GPIO1_INSTANCE_PIN_24:
			HWREG(GPIO_INSTANCE_ADDRESS + CONF_GPMC_A8) = (MUX_GPIO<<0);
			break;

		default:
			break;
	}

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIODirModeSet
 *  Description:  
 * =====================================================================================
 */

void GPIODirModeSet(unsigned int PIN){
	if(PIN > -1 && PIN < 32)
		HWREG(SOC_GPIO_1_REGS + GPIO_OE_OFFSET) &= ~(1<<PIN);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIOWriteMode
 *  Description:  
 * =====================================================================================
 */

void GPIOWriteMode(unsigned int PIN, unsigned int OUTPUT){

	switch(PIN){
		case GPIO1_INSTANCE_PIN_21:
			if(OUTPUT)
				HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1<<GPIO1_INSTANCE_PIN_21);
			else
				HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_21);
			break;

		case GPIO1_INSTANCE_PIN_22:
			if(OUTPUT)
				HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1<<GPIO1_INSTANCE_PIN_22);
			else
				HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_22);
			break;

		case GPIO1_INSTANCE_PIN_23:
			if(OUTPUT)
				HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1<<GPIO1_INSTANCE_PIN_23);
			else
				HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_23);
			break;

		case GPIO1_INSTANCE_PIN_24:
			if(OUTPUT)
				HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1<<GPIO1_INSTANCE_PIN_24);
			else
				HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_24);
			break;
		
		default:
			break;
	}
}