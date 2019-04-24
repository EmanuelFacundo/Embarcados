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

#include	"hw_types.h"
#include	"soc_AM335x.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/

#define GPIO_INSTANCE_ADDRESS			(SOC_GPIO_1_REGS)
#define GPIO1_INSTANCE_PIN_NUMBER		(21)


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

	/* Selionando pin GPIO[21] para o uso. */

	/* Ativando modulo GPIO. */

	/* Resetando modulo GPIO. */

	/* Setando o pin GPIO como pino de saida. */


	return 0;
} /* ----------  end of function main  ---------- */

