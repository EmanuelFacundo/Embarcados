/*
 * =====================================================================================
 *
 *       Filename:  ledStripLightControl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/31/2019 14:22:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Emanuel Facundo Pinto, emanuel.facundo14@gmail.com
 *   Organization:  
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
static volatile unsigned int flagIsrB1;
static volatile unsigned int flagtoggle;
static volatile unsigned int flagIsrB2;

static const char *seq[] = {
    "RED",
    "GREEN",
    "BLUE",
    "WHITE",
    "FADE",
    "FLASH WHITE",
    "MUSIC"
};

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define	PIN_HIGH   		(1)
#define PIN_LOW			(0)
#define TOGGLE          (0x01u)
#define BUTTON_PIN		(15) //GPIO1 
#define BUTTON2_PIN     (16) //GPIO1
#define RED_PIN			(12) //GPIO1
#define GREEN_PIN		(13) //GPIO1
#define BLUE_PIN		(14) //GPIO1

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
static void     clearPins(void);
static void 	gpioIsr(void);
static void     togle(unsigned int, unsigned int);
static void 	Delay(volatile unsigned int);
static void 	initSerial(void);
static void 	initLed(unsigned int, unsigned int, unsigned int);
static void 	initButton(unsigned int, unsigned int, unsigned int);
static void		gpioAintcConf(void);
static void 	gpioPinIntConf(unsigned int, unsigned int, unsigned int);
static void 	gpioIntTypeSet(unsigned int, unsigned int, unsigned int);
/*****************************************************************************
**                INTERNAL FUNCTION DEFINITIONS
*****************************************************************************/
/*
** The main function. Application starts here.
*/
int main(){

	flagIsrB1               = 0x0;
    flagIsrB2               = 0x0;
	flagtoggle              = 0x0;

	unsigned int modAddr 	= SOC_GPIO_1_REGS;
	unsigned int mod 		= GPIO1;
	unsigned int pin 		= 12;
	unsigned int count 		= 0;
	unsigned int fail 		= 0;
    unsigned int fade       = 0; 
    
    initSerial();
    
    ConsoleUtilsPrintf("\n\nConsoleUtilsInit OK...\n");

    DMTimer7ModuleClkConfig();
    DMTimerModeConfigure(SOC_DMTIMER_7_REGS, DMTIMER_ONESHOT_NOCMP_ENABLE);
    
    ConsoleUtilsPrintf("TIMER OK...\n");

	/*Enable IRQ in CPSR */
	IntMasterIRQEnable();
    
    ConsoleUtilsPrintf("Enable IRQ in CPSR...\n");

	/* Enabling functional clocks for GPIO instance. */
    GPIOModuleClkConfig(mod);

    ConsoleUtilsPrintf("Enable Function clocks for GPIO1 instance...\n");

    /* Selecting GPIO pin for use. */
    for (count = pin; count < 15;count++)
    {
    	initLed(modAddr, mod, count);
    }

    initButton(modAddr, mod, BUTTON_PIN);
    initButton(modAddr, mod, BUTTON2_PIN);

    ConsoleUtilsPrintf("Enable pins for use...\n");

    /* configure gpio interrupt on the INTC */
    gpioAintcConf();
    gpioPinIntConf(modAddr, GPIO_INTC_LINE_1, BUTTON_PIN);
    gpioPinIntConf(modAddr, GPIO_INTC_LINE_1, BUTTON2_PIN);
    gpioIntTypeSet(modAddr, BUTTON_PIN, GPIO_INTC_TYPE_RISE_EDGE);
    gpioIntTypeSet(modAddr, BUTTON2_PIN, GPIO_INTC_TYPE_RISE_EDGE);


    ConsoleUtilsPrintf("Configure gpio interrupt on the INTC...\n");
    
    ConsoleUtilsPrintf("\n\n<<<<  ENABLE SYSTEM  >>>>\n\n");

    ConsoleUtilsPrintf("\n<<<< OPTION %s >>>>\n", seq[flagIsrB1]); 

    while(1)
    {
        switch(flagIsrB1)
    	{
    		case 0: //RED
                if(flagIsrB2)
                {                 
                    togle(modAddr, RED_PIN);
                    Delay(2000);
                    togle(modAddr, RED_PIN);
                    Delay(500);
                }
                else
                {
                    togle(modAddr, RED_PIN);
                    Delay(200);
                    togle(modAddr, RED_PIN);
                }

                break;
    		
    		case 1: //GREEN
                if(flagIsrB2)
                {
                    togle(modAddr, GREEN_PIN);
                    Delay(2000);
                    togle(modAddr, GREEN_PIN);
                    Delay(500);
                }
                else
                {   
                    togle(modAddr, GREEN_PIN);
                    Delay(200);
                    togle(modAddr, GREEN_PIN);
                }

    			break;

    		case 2: //BLUE
                if(flagIsrB2)
                {
                    togle(modAddr, BLUE_PIN);
                    Delay(2000);
                    togle(modAddr,BLUE_PIN);
                    Delay(500);
                }
                else
                {
                    togle(modAddr, BLUE_PIN);
                    Delay(200);
                    togle(modAddr, BLUE_PIN);
                }

    			break;

    		case 3: //WHITE
                
                for(count = pin; count < 15 ;count++){
                    togle(modAddr, count);
                    Delay(5);
                    togle(modAddr, count);
                }

    			break;

    		case 4: //FADE
                
               for(count = pin; count < 15 ;count++){

                    togle(modAddr, count);    
                    Delay(500);
                    togle(modAddr, count);

                }
    		
                break;

    		case 5: //FLASH WHITE
                for(fade = 0; fade < 10 ;fade++) 
                for(count = pin; count < 15 ;count++)
                {   
                    togle(modAddr, count);
                    Delay(5);
                    togle(modAddr,count);
                }

                clearPins();
                Delay(500);

    			break;

    		case 6: //MUSIC

    			break;

    		default:
    			ConsoleUtilsPrintf("\n<<<<SYSTEM FAIL>>>>\n");
    			fail = 1;

    	}

    	if(fail) break;
    }

    ConsoleUtilsPrintf("#####  exit system  #####\n");

	return 0;
}

static void clearPins(){

    GPIOPinWrite(SOC_GPIO_1_REGS, RED_PIN, 0);
    Delay(5);
    GPIOPinWrite(SOC_GPIO_1_REGS, GREEN_PIN, 0);
    Delay(5);
    GPIOPinWrite(SOC_GPIO_1_REGS, BLUE_PIN, 0);

}
static void togle(unsigned int baseAdd, unsigned int uPin){
    flagtoggle ^= TOGGLE;

    if(flagtoggle)
        GPIOPinWrite(baseAdd,uPin,1);
    else
        GPIOPinWrite(baseAdd,uPin,0);

}
/*FUNCTION*-------------------------------------------------------
*
* Function Name : gpioIsr
* Comments      : DMTimer interrupt service routine. This will 
* send a character to serial.
*END*-----------------------------------------------------------*/    
static void gpioIsr(void) {
    if(GPIOPinIntStatus(SOC_GPIO_1_REGS, GPIO_INTC_LINE_1, BUTTON_PIN))
    {
        flagIsrB1 = (flagIsrB1 + 1) % 7;
        ConsoleUtilsPrintf("\n<<<< BUTTON1 PRESS >>>>\n");
        /*	Clear wake interrupt	*/
        GPIOPinIntClear(SOC_GPIO_1_REGS, GPIO_INTC_LINE_1, BUTTON_PIN);
    }

    if(GPIOPinIntStatus(SOC_GPIO_1_REGS, GPIO_INT_LINE_1, BUTTON2_PIN))
    {
        flagIsrB2 ^= TOGGLE;
        ConsoleUtilsPrintf("\n<<<< BUTTON2 PRESS >>>>\n");
        /* Clear wake interrupt  */ 
        GPIOPinIntClear(SOC_GPIO_1_REGS, GPIO_INT_LINE_1, BUTTON2_PIN);
    }
    
    ConsoleUtilsPrintf("\n<<<< OPTION %s >>>>\n", seq[flagIsrB1]);

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
static void gpioPinIntConf(unsigned int baseAdd,
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
