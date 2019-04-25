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
 *         Author:  Francisco Emanuel Facundo Pinto, emanuel.facundo14@gmail.com
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
#define TIME 							(2000000)
#define GPIO_INSTANCE_ADDRESS			(0x44E10000)
#define GPIO1_INSTANCE_PIN_NUMBER		(21)
#define CM_PER_GPIO1_CLKCTRL 			(0xAC)
#define GPIO_CTRL               		(0x130)
#define SOC_PRCM_REGS                   (0x44E00000)
#define HWREG(x)                        (*((volatile unsigned int *)(x)))
#define CONF_GPMC_A5					(0x854)
#define SOC_GPIO_1_REGS                 (0x4804C000)
#define GPIO_OE_OFFSET					(0x134)
#define GPIO_SETDATAOUT					(0x194)
#define GPIO_CLEARDATAOUT 				(0x190)
#define OPTFCLKEN_GPIO_1_GDBCLK   		(18)



/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/

static void delay();

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int _main(){

	/* Ativando clocks funcionais para a instância GPIO1. */
	HWREG(SOC_PRCM_REGS + CM_PER_GPIO1_CLKCTRL) = (2<<0) | (1<<OPTFCLKEN_GPIO_1_GDBCLK);	

	/* Selionando pin GPIO[21] para o uso. */
	HWREG(GPIO_INSTANCE_ADDRESS + CONF_GPMC_A5) = (7<<0);

	/* Setando o pin GPIO como pino de saida. */
	HWREG(SOC_GPIO_1_REGS + GPIO_OE_OFFSET) &= ~(1<<GPIO1_INSTANCE_PIN_NUMBER);

	/* Acender o LED */
	HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1<<GPIO1_INSTANCE_PIN_NUMBER);

	/* Apagar o LED. */
	HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1<<GPIO1_INSTANCE_PIN_NUMBER);



	return 0;
} /* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delay
 *  Description:  
 * =====================================================================================
 */

static void delay(){
	volatile unsigned int ra;
	for(ra = 0; ra < TIME; ra ++);
}