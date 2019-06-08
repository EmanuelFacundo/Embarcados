/*
 * =====================================================================================
 *
 *       Filename:  gpioInterrupt.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2017 09:36:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "uart_irda_cir.h"
#include "soc_AM335x.h"
#include "interrupt.h"
#include "board.h"
#include "beaglebone.h"
#include "gpio_v2.h"
#include "consoleUtils.h"
#include "dmtimer.h"

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
static volatile unsigned int flagIsr1;
static volatile unsigned int flagIsr2;
int flagLR;
int rightOrLeft;
int pin_control;
/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define			PIN_HIGH   	1
#define        	PIN_LOW		0

#define TOGGLE          (0x01u)
#define PIN_BASE        (12)

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


#define TIMER_INITIAL_COUNT            (0xFF000000u)
#define TIMER_RLD_COUNT                (0xFFFFFF83u) //(0xFF000000u)

#define T_1MS_COUNT                     (0x5DC0u) 
#define OVERFLOW                        (0xFFFFFFFFu)
#define TIMER_1MS_COUNT                 (0x5DC0u) 

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void			Delay(volatile unsigned int mSec);
static void 		initSerial(void);
static void 		initLed(unsigned int, unsigned int, unsigned int);
static void 		initButton(unsigned int, unsigned int, unsigned int);
static void			gpioAintcConf(void);
//static unsigned int getAddr(unsigned int);
static void 		gpioIsr(void);
static int			gpioPinIntConf(unsigned int, unsigned int, unsigned int);
static void 		gpioPinIntEnable(unsigned int, unsigned int, unsigned int); 
static void 		gpioIntTypeSet(unsigned int, unsigned int, unsigned int);

void toggle(unsigned int uPin);
int left(unsigned int i);
int right(unsigned int i);
 
/******************************************************************************
**              FUNCTION DEFINITIONS
******************************************************************************/
int main(){

	rightOrLeft = 0x0;
    flagIsr1 = 0x0;
    flagIsr2 = 0x0;
    flagLR = 0x0;
    int count;
    pin_control = 0;
    int delay = 500;
	
	initSerial();
    
    DMTimer7ModuleClkConfig();
    DMTimerModeConfigure(SOC_DMTIMER_7_REGS, DMTIMER_ONESHOT_NOCMP_ENABLE);

	/* Enable IRQ in CPSR */
   	IntMasterIRQEnable();

   	GPIOModuleClkConfig(1);
	
	for(count = PIN_BASE; count < 15; count++) 
        initLed(SOC_GPIO_1_REGS, 1, count);

	initButton(SOC_GPIO_1_REGS, 1, 16);
    initButton(SOC_GPIO_1_REGS, 1, 28);

	/* configure gpio interrupt on the INTC */

	// ENABLE PIN TO INTERRUPT   	
	gpioAintcConf();
	gpioPinIntConf(SOC_GPIO_1_REGS, GPIO_INTC_LINE_1, 16);
    gpioPinIntConf(SOC_GPIO_1_REGS, GPIO_INTC_LINE_1, 28);
   	gpioIntTypeSet(SOC_GPIO_1_REGS, 16, GPIO_INTC_TYPE_RISE_EDGE);
    gpioIntTypeSet(SOC_GPIO_1_REGS, 28, GPIO_INTC_TYPE_RISE_EDGE);

    ConsoleUtilsPrintf("\n<<<< STANDARD DELAY -> %dms >>>>\n", delay);

   	while(1){

        if (flagIsr1)
        {
            
            pin_control = left(pin_control);
            
            toggle(PIN_BASE + pin_control);
            Delay(delay);
            toggle(PIN_BASE + pin_control);

        }
        if (flagIsr2)
        {
            ConsoleUtilsPrintf("\n<<<< DELAY -> %dms >>>>\n", delay);
            ConsoleUtilsPrintf("ENTER A NEW DELAY IN mSec: ");
            ConsoleUtilsScanf("%d", &delay);
            flagIsr2 = 0;
        }
        if(!flagIsr1 && !flagIsr2) 
        {
            pin_control = right(pin_control);
            toggle(PIN_BASE + pin_control);
            Delay(delay);
            toggle(PIN_BASE + pin_control);
        }

    }
	
	ConsoleUtilsPrintf("#####  exit system  #####\n");
	
	return(0);
}

void toggle(unsigned int uPin){

    flagLR ^= TOGGLE;

    if (flagLR){
        switch(uPin){
            case 12:
                GPIOPinWrite(SOC_GPIO_1_REGS,uPin,1);
                break;

            case 13:
                GPIOPinWrite(SOC_GPIO_1_REGS,uPin,1);
                break;

            case 14:
                GPIOPinWrite(SOC_GPIO_1_REGS,uPin,1);
                break;

            /*case 24:
                GPIOPinWrite(SOC_GPIO_1_REGS,uPin,1);
                break;
            */
            default:
                break;  
        }
        
    }else{
        switch(uPin){
            case 12:
                GPIOPinWrite(SOC_GPIO_1_REGS,uPin,0);
                break;

            case 13:
                GPIOPinWrite(SOC_GPIO_1_REGS,uPin,0);
                break;

            case 14:
                GPIOPinWrite(SOC_GPIO_1_REGS,uPin,0);
                break;

            /*case 24:
                GPIOPinWrite(SOC_GPIO_1_REGS,uPin,0);
                break;
            */
            default:
                break;  
        }
    }
}

int left(unsigned int i){
    if(i == 2){
        return (0);
    }
    
    return (i+1);
}

int right(unsigned int i){ 
    if(i==0){
        return (2);
    }

    return (i-1);
}

static void Delay(volatile unsigned int mSec){
   while(mSec != 0){
        DMTimerCounterSet(SOC_DMTIMER_7_REGS, 0);
        DMTimerEnable(SOC_DMTIMER_7_REGS);
        while(DMTimerCounterGet(SOC_DMTIMER_7_REGS) < TIMER_1MS_COUNT);
        DMTimerDisable(SOC_DMTIMER_7_REGS);
        mSec--;
    }
}

/*FUNCTION*-------------------------------------------------------
*
* A function which is used to initialize UART.
*END*-----------------------------------------------------------*/
static void initSerial(){
    /* Initialize console for communication with the Host Machine */
    ConsoleUtilsInit();

    /* Select the console type based on compile time check */
    ConsoleUtilsSetType(CONSOLE_UART);
}

/*FUNCTION*-------------------------------------------------------
*
* A function which is used to initialize GPIO like LED.
*END*-----------------------------------------------------------*/
static void initLed(unsigned int baseAdd, unsigned int module, unsigned int pin){
    
    	/* Selecting GPIO pin for use. */
    	GPIOPinMuxSetup(module, pin);
    
    	/* Setting the GPIO pin as an output pin. */
    	GPIODirModeSet(baseAdd, pin, GPIO_DIR_OUTPUT);
}

/*FUNCTION*-------------------------------------------------------
*
* A function which is used to initialize GPIO like BUTTON.
*END*-----------------------------------------------------------*/
static void initButton(unsigned int baseAdd, unsigned int module, unsigned int pin){
    
    	/* Selecting GPIO pin for use. */
    	GPIOPinMuxSetup(module, pin);
    
    	/* Setting the GPIO pin as an output pin. */
    	GPIODirModeSet(baseAdd, pin, GPIO_DIR_INPUT);
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : gpioAintcconfigure
* Comments      : Do the necessary gpio configurations on to AINTC.
*END*-----------------------------------------------------------*/
static void gpioAintcConf(void){

    /* Initialize the ARM interrupt control */
    IntAINTCInit();
 
    /* Registering gpioIsr */
    IntRegister(SYS_INT_GPIOINT1A, gpioIsr); 
    
    /* Set the priority */
    IntPrioritySet(SYS_INT_GPIOINT1A, 0, AINTC_HOSTINT_ROUTE_IRQ);
    
    /* Enable the system interrupt */
    IntSystemEnable(SYS_INT_GPIOINT1A);
   
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : gpioIsr
* Comments      : DMTimer interrupt service routine. This will 
* send a character to serial.
*END*-----------------------------------------------------------*/    
static void gpioIsr(void) {

    if(GPIOPinIntStatus(SOC_GPIO_1_REGS, GPIO_INTC_LINE_1, 16))
    {
        flagIsr1 ^= TOGGLE;
        ConsoleUtilsPrintf("\n<<<< BUTTON 1 PRESS >>>>\n");
        GPIOPinIntClear(SOC_GPIO_1_REGS, GPIO_INTC_LINE_1, 16);
    
    }
    if(GPIOPinIntStatus(SOC_GPIO_1_REGS, GPIO_INTC_LINE_1, 28))
    {
        flagIsr2 ^= TOGGLE;
        ConsoleUtilsPrintf("\n<<<< BUTTON 2 PRESS >>>>\n");
        GPIOPinIntClear(SOC_GPIO_1_REGS, GPIO_INTC_LINE_1, 28);

    }

    	/*	Clear wake interrupt	*/

	

}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : gpioPinIntConfig
* Comments      :
*END*-----------------------------------------------------------*/
static int gpioPinIntConf(unsigned int baseAdd, unsigned int intLine,
                  unsigned int pinNumber){

    	/* Setting interrupt GPIO pin. */
    	gpioPinIntEnable(baseAdd,
               intLine,
               pinNumber);
    
    	return(0);
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : GPIOPinIntEnable
* Comments      : This API enables the configured interrupt event on a specified input
* GPIO pin to trigger an interrupt request.
*
* \param  baseAdd     The memory address of the GPIO instance being used
* \param  intLine     This specifies the interrupt request line on which the
*                     interrupt request due to the transitions on a specified
*                     pin be propagated
* \param  pinNumber   The number of the pin in the GPIO instance
*
* 'intLine' can take one of the following two values:
* - GPIO_INT_LINE_1 - interrupt request be propagated over interrupt line 1\n
* - GPIO_INT_LINE_2 - interrupt request be propagated over interrupt line 2\n
* 
* 'pinNumber' can take one of the following values:
* (0 <= pinNumber <= 31)\n
*
* \return None
*
*END*-----------------------------------------------------------*/
static void gpioPinIntEnable(unsigned int baseAdd,
                      unsigned int intLine,
                      unsigned int pinNumber){
    if(GPIO_INTC_LINE_1 == intLine){
        HWREG(baseAdd + GPIO_IRQSTATUS_SET(0)) = (1 << pinNumber);
    }else{
        HWREG(baseAdd + GPIO_IRQSTATUS_SET(1)) = (1 << pinNumber);
    }
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : gpioIntTypeSet
* Comments      : This API configures the event type for a specified 
* input GPIO pin. Whenever the selected event occurs on that GPIO pin 
* and if interrupt generation is enabled for that pin, the GPIO module 
* will send an interrupt to CPU.
*
* \param  baseAdd    The memory address of the GPIO instance being used
* \param  pinNumber  The number of the pin in the GPIO instance
* \param  eventType  This specifies the event type on whose detection,
*                    the GPIO module will send an interrupt to CPU,
*                    provided interrupt generation for that pin is enabled.
*
* 'pinNumber' can take one of the following values:
* (0 <= pinNumber <= 31)\n
*
* 'eventType' can take one of the following values:
* - GPIO_INT_TYPE_NO_LEVEL - no interrupt request on occurence of either a
*   logic LOW or a logic HIGH on the input GPIO pin\n
* - GPIO_INT_TYPE_LEVEL_LOW - interrupt request on occurence of a LOW level
*   (logic 0) on the input GPIO pin\n
* - GPIO_INT_TYPE_LEVEL_HIGH - interrupt request on occurence of a HIGH level
*   (logic 1) on the input GPIO pin\n
* - GPIO_INT_TYPE_BOTH_LEVEL - interrupt request on the occurence of both the
*   LOW level and HIGH level on the input GPIO pin\n
* - GPIO_INT_TYPE_NO_EDGE -  no interrupt request on either rising or
*   falling edges on the pin\n
* - GPIO_INT_TYPE_RISE_EDGE - interrupt request on occurence of a rising edge
*   on the input GPIO pin\n
* - GPIO_INT_TYPE_FALL_EDGE - interrupt request on occurence of a falling edge
*   on the input GPIO pin\n
* - GPIO_INT_TYPE_BOTH_EDGE - interrupt request on occurence of both a rising
*   and a falling edge on the pin\n
*
* \return  None
*
* \note  A typical use case of this API is explained below:
* 
*        If it is initially required that interrupt should be generated on a
*        LOW level only, then this API can be called with
*        'GPIO_INT_TYPE_LEVEL_LOW' as the parameter.
*        At a later point of time, if logic HIGH level only should be made as
*        the interrupt generating event, then this API has to be first called
*        with 'GPIO_INT_TYPE_NO_LEVEL' as the parameter and later with
*        'GPIO_INT_TYPE_LEVEL_HIGH' as the parameter. Doing this ensures that
*        logic LOW level trigger for interrupts is disabled.
*END*-----------------------------------------------------------*/
static void gpioIntTypeSet(unsigned int baseAdd,
                    unsigned int pinNumber,
                    unsigned int eventType){
    eventType &= 0xFF;

    switch(eventType)
    {

        case GPIO_INT_TYPE_NO_LEVEL:

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_LEVEL_LOW:

            /* Enabling logic LOW level detect interrupt geenration. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) |= (1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_LEVEL_HIGH:

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);
            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);
        
        break;

        case GPIO_INT_TYPE_BOTH_LEVEL:
            
            /* Enabling logic LOW level detect interrupt geenration. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) |= (1 << pinNumber);

            /* Enabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) |= (1 << pinNumber);

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);
            
        break;

        case GPIO_INT_TYPE_NO_EDGE:
            
            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_RISE_EDGE:

            /* Enabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) |= (1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_FALL_EDGE:

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Enabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) |= (1 << pinNumber);

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        case GPIO_INT_TYPE_BOTH_EDGE:

            /* Enabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) |= (1 << pinNumber);

            /* Enabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) |= (1 << pinNumber);

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        default:
        break;
    }
}

/******************************* End of file *********************************/
