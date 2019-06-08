#include "hw_control_AM335x.h"
#include "soc_AM335x.h"
#include "beaglebone.h"
#include "gpio_v2.h"
#include "uart_irda_cir.h"
#include "board.h"
#include "hw_types.h"
#include "consoleUtils.h"

#define WTD_BASE 0x44E35000

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define		PIN_HIGH   	1
#define        	PIN_LOW		0

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void Delay(unsigned int count);
static void resetBoard();
/*****************************************************************************
**                INTERNAL FUNCTION DEFINITIONS
*****************************************************************************/
/*
** The main function. Application starts here.
*/
int main(){
	unsigned int modAddr=SOC_GPIO_1_REGS, mod=GPIO1, pin=21, dir=GPIO_DIR_OUTPUT;
    	/* Enabling functional clocks for GPIO instance. */
    	GPIOModuleClkConfig(mod);
    
    	/* Selecting GPIO pin for use. */
    	GPIOPinMuxSetup(mod, pin);
		GPIOPinMuxSetup(mod, 12);
    
	switch (mod) {
		case GPIO0:
			modAddr = SOC_GPIO_0_REGS;	
			break;
		case GPIO1:	
			modAddr = SOC_GPIO_1_REGS;	
			break;
		case GPIO2:	
			modAddr = SOC_GPIO_2_REGS;	
			break;
		case GPIO3:	
			modAddr = SOC_GPIO_3_REGS;	
			break;
		default:	
			break;
	}/* -----  end switch  ----- */

    	/* Setting the GPIO pin as an output pin. */
    	GPIODirModeSet(modAddr, pin, dir);
		GPIODirModeSet(modAddr, 12, 1);

   	while(1){
        	/* Driving a logic HIGH on the GPIO pin. */
			if(GPIOPinRead(SOC_GPIO_1_REGS,12)){
				resetBoard();
			}else{
				GPIOPinWrite(modAddr, pin, PIN_HIGH);

		    	Delay(0x1FFFFF);
	
        	/* Driving a logic LOW on the GPIO pin. */
	        	GPIOPinWrite(modAddr, pin, PIN_LOW);

				Delay(0x1FFFFF);
			}
    	}

	return(0);
} 

static void resetBoard(){

	HWREG(SOC_PRM_DEVICE_REGS + 0x0) |= 0b11;
	

}

/*
** A function which is used to generate a delay.
*/
static void Delay(unsigned int count)
{
    while(count--);
}



/******************************* End of file *********************************/
