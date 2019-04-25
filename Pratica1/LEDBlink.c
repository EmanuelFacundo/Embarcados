/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/04/2019 20:50:49
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Emanuel , emanuel.facundo14@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
/*
#include	"hw_types.h"
#include	"soc_AM335x.h"
*/
/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/

#define GPIO_INSTANCE_ADDRESS			(SOC_GPIO_1_REGS)
#define GPIO1_INSTANCE_PIN_NUMBER		(21)
#define CM_PER_GPIO1_CLKCTRL 			(0xAC)
#define GPIO_CTRL               		(0x130)
#define SOC_PRCM_REGS                   (0x44E00000)
#define HWREG(x)                        (*((volatile unsigned int *)(x)))
#define SOC_CONTROL_REGS                (0x44E10000)
#define CONF_GPMC_A5					(0x854)
#define GPIO1_BASE						(0x4804C000)
#define GPIO_OE_OFFSET					(0x134)
#define GPIO_SETDATAOUT					(0x194)



/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int _main(){

	/* Ativando clocks funcionais para a instância GPIO1. */
	HWREG(SOC_PRCM_REGS + CM_PER_GPIO1_CLKCTRL) = (2<<0) | (1<<18);	

	/* Selionando pin GPIO[21] para o uso. */
	HWREG(SOC_CONTROL_REGS + CONF_GPMC_A5) = (7<<0);

	/* Setando o pin GPIO como pino de saida. */
	HWREG(GPIO1_BASE + GPIO_OE_OFFSET) &= ~(1<<21);

	/* Acender o LED */
	HWREG(GPIO1_BASE + GPIO_SETDATAOUT) = (1<<21);
	






	return 0;
} /* ----------  end of function main  ---------- */

