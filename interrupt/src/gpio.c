/*
 * =====================================================================================
 *
 *       Filename:  gpio.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/02/2017 10:50:03
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "gpio.h"

/*-----------------------------------------------------------------------------
 * insert [pin, port], get CM_conf adress
 * Datasheet 4.3.2
 *-----------------------------------------------------------------------------*/
static const CONTROL_MODULE GPIO_CTRL_MODULE_ARRAY[32][4] = {
    //p0                          //p1                          //p2                          //p3
   {CM_conf_mdio                 ,CM_conf_gpmc_ad0             ,CM_conf_gpmc_csn3            ,CM_conf_mii1_col       },//.0
   {CM_conf_mdc                  ,CM_conf_gpmc_ad1             ,CM_conf_gpmc_clk             ,CM_conf_mii1_crs       },//.1
   {CM_conf_spi0_sclk            ,CM_conf_gpmc_ad2             ,CM_conf_gpmc_advn_ale        ,CM_conf_mii1_rx_er     },//.2
   {CM_conf_spi0_d0              ,CM_conf_gpmc_ad3             ,CM_conf_gpmc_oen_ren         ,CM_conf_mii1_tx_en     },//.3
   {CM_conf_spi0_d1              ,CM_conf_gpmc_ad4             ,CM_conf_gpmc_wen             ,CM_conf_mii1_rx_dv     },//.4
   {CM_conf_spi0_cs0             ,CM_conf_gpmc_ad5             ,CM_conf_gpmc_ben0_cle        ,CM_conf_i2c0_sda       },//.5
   {CM_conf_spi0_cs1             ,CM_conf_gpmc_ad6             ,CM_conf_lcd_data0            ,CM_conf_i2c0_scl       },//.6
   {CM_conf_ecap0_in_pwm0_out    ,CM_conf_gpmc_ad7             ,CM_conf_lcd_data1            ,CM_conf_emu0           },//.7
   {CM_conf_lcd_data12           ,CM_conf_uart0_ctsn           ,CM_conf_lcd_data2            ,CM_conf_emu1           },//.8
   {CM_conf_lcd_data13           ,CM_conf_uart0_rtsn           ,CM_conf_lcd_data3            ,CM_conf_mii1_tx_clk    },//.9
   {CM_conf_lcd_data14           ,CM_conf_uart0_rxd            ,CM_conf_lcd_data4            ,CM_conf_mii1_rx_clk    },//.10
   {CM_conf_lcd_data15           ,CM_conf_uart0_txd            ,CM_conf_lcd_data5            ,-1                     },//.11
   {CM_conf_uart1_ctsn           ,CM_conf_gpmc_ad12            ,CM_conf_lcd_data6            ,-1                     },//.12
   {CM_conf_uart1_rtsn           ,CM_conf_gpmc_ad13            ,CM_conf_lcd_data7            ,CM_conf_usb1_drvvbus   },//.13
   {CM_conf_uart1_rxd            ,CM_conf_gpmc_ad14            ,CM_conf_lcd_data8            ,CM_conf_mcasp0_aclkx   },//.14
   {CM_conf_uart1_txd            ,CM_conf_gpmc_ad15            ,CM_conf_lcd_data9            ,CM_conf_mcasp0_fsx     },//.15
   {CM_conf_mii1_txd3            ,CM_conf_gpmc_a0              ,CM_conf_lcd_data10           ,CM_conf_mcasp0_axr0    },//.16
   {CM_conf_mii1_txd2            ,CM_conf_gpmc_a1              ,CM_conf_lcd_data11           ,CM_conf_mcasp0_ahclkr  },//.17
   {CM_conf_usb0_drvvbus         ,CM_conf_gpmc_a2              ,CM_conf_mii1_rxd3            ,CM_conf_mcasp0_aclkr   },//.18
   {CM_conf_xdma_event_intr0     ,CM_conf_gpmc_a3              ,CM_conf_mii1_rxd2            ,CM_conf_mcasp0_fsr     },//.19
   {CM_conf_xdma_event_intr1     ,CM_conf_gpmc_a4              ,CM_conf_mii1_rxd1            ,CM_conf_mcasp0_axr1    },//.20
   {CM_conf_mii1_txd1            ,CM_conf_gpmc_a5              ,CM_conf_mii1_rxd0            ,CM_conf_mcasp0_ahclkx  },//.21
   {CM_conf_gpmc_ad8             ,CM_conf_gpmc_a6              ,CM_conf_lcd_vsync            ,-1                     },//.22
   {CM_conf_gpmc_ad9             ,CM_conf_gpmc_a7              ,CM_conf_lcd_hsync            ,-1                     },//.23
   {-1                           ,CM_conf_gpmc_a8              ,CM_conf_lcd_pclk             ,-1                     },//.24
   {-1                           ,CM_conf_gpmc_a9              ,CM_conf_lcd_ac_bias_en       ,-1                     },//.25
   {CM_conf_gpmc_ad10            ,CM_conf_gpmc_a10             ,CM_conf_mmc0_dat3            ,-1                     },//.26
   {CM_conf_gpmc_ad11            ,CM_conf_gpmc_a11             ,CM_conf_mmc0_dat2            ,-1                     },//.27
   {CM_conf_mii1_txd0            ,CM_conf_gpmc_ben1            ,CM_conf_mmc0_dat1            ,-1                     },//.28
   {CM_conf_rmii1_ref_clk        ,CM_conf_gpmc_csn0            ,CM_conf_mmc0_dat0            ,-1                     },//.29
   {CM_conf_gpmc_wait0           ,CM_conf_gpmc_csn1            ,CM_conf_mmc0_clk             ,-1                     },//.30
   {CM_conf_gpmc_wpn             ,CM_conf_gpmc_csn2            ,CM_conf_mmc0_cmd             ,-1                     },//.31
};



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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioCheckValidPortPin
 *  Description:  
 * =====================================================================================
 */
static bool gpioCheckValidPortPin(gpioPort port, ucPinNumber pin){
   if((port < GPIO0) || (port > GPIO3)){
      // TODO: raise error (port is either too big or negative: /port)
      return(false);
   }
   if((pin < 0) || (pin > 31)){
      // TODO: raise error (pin is either too big or negative: /pin)
      return(false);
   }
   return(true);
}/* -----  end of function gpioCheckValidPortPin  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioCheckValidDirection
 *  Description:  
 * =====================================================================================
 */
static bool gpioCheckValidDirection(pinDirection dir){
	if((dir!=INPUT) && (dir!=OUTPUT)){
      		// TODO: raise error (direction not valid: /dir)
      		return(false);
   	}
   	return(true);
}/* -----  end of function gpioCheckValidDirection  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioInitModule
 *  Description:  
 * =====================================================================================
 */
void gpioInitModule(gpioPort port){
	if(gpioCheckValidPortPin(port, 0)){  // pin 0 always exist
    		unsigned int setting = (1<<18) | (0x2<<0);   //enable functional clock & enable module, TRM 8.1.12.1.29
      		switch(port){
        		case GPIO0:
           			return;        // GPIO0 doesnt have a clock module register, TRM 8.1.12.1
            		break;
         		case GPIO1:
            			ckmSetCLKModuleRegister(CKM_PER_GPIO1_CLKCTRL, setting);
            			while((ckmGetCLKModuleRegister(CKM_PER_GPIO1_CLKCTRL) & (0x3<<16)) != 0)
            		break;
         		case GPIO2:
            			ckmSetCLKModuleRegister(CKM_PER_GPIO2_CLKCTRL, setting);
            			while((ckmGetCLKModuleRegister(CKM_PER_GPIO2_CLKCTRL) & (0x3<<16)) != 0) 
            		break;
         		case GPIO3:
            		break;
         		default:
            			// TODO: raise error (not possible, checked port before: /port)
            		break;
      		}
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioinitPin
 *  Description:  
 * =====================================================================================
 */
void gpioPinMuxSetup(gpioPort port, ucPinNumber pin, pinDirection dir){
	if(gpioCheckValidPortPin(port, pin)){
					
					CONTROL_MODULE module = GPIO_CTRL_MODULE_ARRAY[pin][port];  // get conf <module> <pin> for port/pin combination
					padSetMode(module, MODE_7);  //set mode to GPIO, Datasheet 4.3.2
					
					if(dir == INPUT){
									unsigned int temp = cmGetCtrlModule(module);
      						temp |= CONTROL_CONF_GPMC_SLEWCTRL | 	/* Slew rate slow */
									CONTROL_CONF_GPMC_RXACTIVE |	/* Receiver enabled */
									(CONTROL_CONF_GPMC_PUDEN & (~CONTROL_CONF_GPMC_PUDEN)) | /* PU_PD enabled */
									(CONTROL_CONF_GPMC_PUTYPESEL & (~CONTROL_CONF_GPMC_PUTYPESEL));
									cmSetCtrlModule(module, temp);
									
					}
	}
}



/*FUNCTION*-------------------------------------------------------
*
* Function Name : gpioPinIntConfig
* Comments      :
*END*-----------------------------------------------------------*/
int gpioPinIntConfig(unsigned int intLine,
                  unsigned int pinNumber){

    /* Setting interrupt GPIO pin. */
    gpioPinIntEnable(SOC_GPIO_1_REGS,
               intLine,
               pinNumber);
    
    return(0);
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : gpioAintcconfigure
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
void gpioIntTypeSet(unsigned int baseAdd,
                    unsigned int pinNumber,
                    unsigned int eventType){
    eventType &= 0xFF;

    switch(eventType)
    {

        case GPIO_INTC_TYPE_NO_LEVEL:

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        case GPIO_INTC_TYPE_LEVEL_LOW:

            /* Enabling logic LOW level detect interrupt geenration. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) |= (1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

        break;

        case GPIO_INTC_TYPE_LEVEL_HIGH:

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Enabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) |= (1 << pinNumber);

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);
        
        break;

        case GPIO_INTC_TYPE_BOTH_LEVEL:
            
            /* Enabling logic LOW level detect interrupt geenration. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) |= (1 << pinNumber);

            /* Enabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) |= (1 << pinNumber);

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);
            
        break;

        case GPIO_INTC_TYPE_NO_EDGE:
            
            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

        break;

        case GPIO_INTC_TYPE_RISE_EDGE:

            /* Enabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) |= (1 << pinNumber);

            /* Disabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        case GPIO_INTC_TYPE_FALL_EDGE:

            /* Disabling rising edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

            /* Enabling falling edge detect interrupt generation. */
            HWREG(baseAdd + GPIO_FALLINGDETECT) |= (1 << pinNumber);

            /* Disabling logic LOW level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

            /* Disabling logic HIGH level detect interrupt generation. */
            HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        break;

        case GPIO_INTC_TYPE_BOTH_EDGE:

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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpiosetDirection
 *  Description:  
 * =====================================================================================
 */
void gpioSetDirection(gpioPort port, ucPinNumber pin, pinDirection dir){
	unsigned int addr_temp, val_temp;

		if(gpioCheckValidPortPin(port,pin)){
    		if(gpioCheckValidDirection(dir)){	
					switch (port) {
						case GPIO0:
						break;
						case GPIO1:	
								// GPIOx base + output enable offset, TRM 2.1 & 25.4.1.16
        				addr_temp = SOC_GPIO_1_REGS + GPIO_OE;     
								// not overwriting previous port setting
								val_temp =  HWREG(addr_temp);
						break;
						case GPIO2:
								// GPIOx base + output enable offset, TRM 2.1 & 25.4.1.16
        				addr_temp = SOC_GPIO_2_REGS + GPIO_OE;     
								// not overwriting previous port setting
								val_temp =  HWREG(addr_temp);		
						break;
						case GPIO3:
						break;
						default:	
						break;
					}/* -----  end switch  ----- */
        	
					val_temp &= ~(1<<pin);
      		val_temp |= (dir<<pin);
        		
					// writing new port setting
					HWREG(addr_temp) = val_temp;
     	}
   	}
}/* -----  end of function gpioSetDirection  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioGetDirection
 *  Description:  
 * =====================================================================================
 */
int gpioGetDirection(gpioPort port, ucPinNumber pin){
	unsigned int addr_temp, val_temp;

	if(gpioCheckValidPortPin(port,pin)){
		switch (port) {
			case GPIO0:	
				// GPIOx base + output enable offset, TRM 2.1 & 25.4.1.16
    				addr_temp = SOC_GPIO_0_REGS + GPIO_OE;      
    				val_temp = HWREG(addr_temp);
			break;
			case GPIO1:
				// GPIOx base + output enable offset, TRM 2.1 & 25.4.1.16
    				addr_temp = SOC_GPIO_1_REGS + GPIO_OE;      
    				val_temp = HWREG(addr_temp);
			break;
			case GPIO2:	
			
			break;
			case GPIO3:	
			
			break;
			default:	
			
			break;
		}/* -----  end switch  ----- */


   		if(val_temp & (1<<pin)){ // masking for wanted pin
         		return(INPUT);
      		}else{
        		return(OUTPUT);
      		}
   	}else{
   		return(-1);     // isn't a valid port/pin combination or doesnt exist
   	}
}/* -----  end of function gpioSetPinValue  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioSetPinValue
 *  Description:  
 * =====================================================================================
 */
void gpioSetPinValue(gpioPort port, ucPinNumber pin, pinLevel value){
	unsigned int addr_temp, val_temp;

	if(value == HIGH){
		if(gpioCheckValidPortPin(port,pin)){
			switch (port) {
				case GPIO0:	
				break;
				case GPIO1:
					// GPIOx base + set data out offset, TRM 2.1 & 25.4.1.26
      		addr_temp = SOC_GPIO_1_REGS + GPIO_SETDATAOUT;
					val_temp = 1<<pin;
				break;
				case GPIO2:	
					// GPIOx base + set data out offset, TRM 2.1 & 25.4.1.26
      		addr_temp = SOC_GPIO_2_REGS + GPIO_SETDATAOUT;
					val_temp = 1<<pin;	
				break;
				case GPIO3:	
				break;
				default:	
				break;
			}/* -----  end switch  ----- */
      HWREG(addr_temp) |= val_temp;
   	}
	}else{
		if(gpioCheckValidPortPin(port,pin)){
			switch (port) {
				case GPIO0:
				break;
				case GPIO1:
					// GPIOx base+clear data out offset, TRM 2.1 & 25.4.1.25
      					addr_temp = SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT;        			
					val_temp = 1<<pin;
				break;
				case GPIO2:
					// GPIOx base+clear data out offset, TRM 2.1 & 25.4.1.25
      					addr_temp = SOC_GPIO_2_REGS + GPIO_CLEARDATAOUT;        			
					val_temp = 1<<pin;		
				break;
				case GPIO3:	
				break;
				default:	
				break;
			}/* -----  end switch  ----- */
      			HWREG(addr_temp) &= val_temp;
   		}
	}
}/* -----  end of function gpioGetPinValue  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioGetPinValue
 *  Description:  
 * =====================================================================================
 */
unsigned int gpioGetPinValue(gpioPort port, ucPinNumber pin){
  	unsigned int addr_temp, val_temp;
 
	if(gpioCheckValidPortPin(port,pin)){
		switch (port) {
			case GPIO0:
			break;
			case GPIO1:
					addr_temp = SOC_GPIO_1_REGS + GPIO_DATAIN; // GPIOx base + data in offset, TRM 2.1 & 25.4.1.17
      		val_temp = HWREG(addr_temp);
			break;
			case GPIO2:	
			break;
			case GPIO3:	
			break;
			default:	
			break;
		}	
    
		if(val_temp & (1<<pin)){
    	return(HIGH);
    }else{
    	return(LOW);
    }

   	}else{
    		return(-1);  // isnt a valid port/pin combination or doesnt exist
   	}
}/* -----  end of function gpiogetPinValue  ----- */

