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
 *         Name:  GPIO2ModuleClkConfig
 *  Description:  
 * =====================================================================================
 */

void GPIO2ModuleClkConfig(){
	HWREG(SOC_PRCM_REGS + CM_PER_GPIO2_CLKCTRL) = (ENABLE_CM_PER_GPIO2_CLKCTRL<<0) | (1<<OPTFCLKEN_GPIO_2_GDBCLK);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO1PinMuxSetup
 *  Description:  
 * =====================================================================================
 */

void GPIO1PinMuxSetup(unsigned int uPin){
	
	switch(uPin){
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
 *         Name:  GPIO2PinMuxSetup
 *  Description:  
 * =====================================================================================
 */

void GPIO2PinMuxSetup(){

	HWREG(GPIO_INSTANCE_ADDRESS + CONF_GPMC_CLK) |= (MUX_GPIO<<0);

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO1DirModeSet
 *  Description:  
 * =====================================================================================
 */

void GPIO1DirModeSetWrite(GPIO_Pin_t pin){
		HWREG(SOC_GPIO_1_REGS + GPIO_OE_OFFSET) &= ~(1<<pin);
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO2DirModeSet
 *  Description:  
 * =====================================================================================
 */
void GPIO2DirModeSetRead(unsigned int pin){
	HWREG(SOC_GPIO_2_REGS + GPIO_OE_OFFSET) |= (1<<pin);
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIOWriteMode
 *  Description:  
 * =====================================================================================
 */

void GPIOWriteMode(unsigned int uPin, unsigned int uValue){

	switch(uPin){
		case GPIO1_INSTANCE_PIN_21:
			if(uValue)
				HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_21);
			else
				HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_21);
			break;

		case GPIO1_INSTANCE_PIN_22:
			if(uValue)
				HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_22);
			else
				HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_22);
			break;

		case GPIO1_INSTANCE_PIN_23:
			if(uValue)
				HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_23);
			else
				HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_23);
			break;

		case GPIO1_INSTANCE_PIN_24:
			if(uValue)
				HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_24);
			else
				HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_24);
			break;
		
		default:
			break;
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIORead
 *  Description:  
 * =====================================================================================
 */

unsigned int GPIORead(unsigned int pin){
	unsigned int temp = HWREG(SOC_GPIO_2_REGS + GPIO_DATAIN);

	return temp & (1<<pin);
}