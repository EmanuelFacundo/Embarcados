#ifndef __DEFINES
#define __DEFINES

#define HWREG(x)                        (*((volatile unsigned int *)(x)))
#define GPIO_INSTANCE_ADDRESS			(0x44E10000)
#define CM_PER_GPIO1_CLKCTRL 			(0xAC)
#define GPIO_CTRL               		(0x130)
#define GPIO1_INSTANCE_PIN_21			(21)
#define GPIO1_INSTANCE_PIN_22			(22)
#define GPIO1_INSTANCE_PIN_23			(23)
#define GPIO1_INSTANCE_PIN_24			(24)
#define CONF_GPMC_A5					(0x854)
#define CONF_GPMC_A6					(0x858)
#define CONF_GPMC_A7					(0x85C)
#define CONF_GPMC_A8					(0x860)
#define GPIO_OE_OFFSET					(0x134)
#define GPIO_SETDATAOUT					(0x194)
#define GPIO_CLEARDATAOUT 				(0x190)
#define SOC_PRCM_REGS                   (0x44E00000)
#define SOC_GPIO_1_REGS                 (0x4804C000)
#define OPTFCLKEN_GPIO_1_GDBCLK   		(18)
#define ENABLE_CM_PER_GPIO1_CLKCTRL		(2)
#define MUX_GPIO						(7)
#define HIGH							(1)
#define LOW								(0)


#endif /* __DEFINES */