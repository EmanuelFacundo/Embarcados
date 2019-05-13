#ifndef __DEFINES
#define __DEFINES

#define HWREG(x)                        (*((volatile unsigned int *)(x)))
#define SOC_PRCM_REGS                   (0x44E00000)
#define GPIO_CTRL               		(0x130)
#define SOC_GPIO0_REGS					(0x44E07000)
#define SOC_GPIO1_REGS                  (0x4804C000)
#define SOC_GPIO2_REGS					(0x481AC000)
#define SOC_GPIO3_REGS					(0x481AE000)
#define GPIO_INSTANCE_ADDRESS			(0x44E10000)
#define CM_WKUP_GPIO0_CLKCTRL			(0x8)
#define CM_PER_GPIO1_CLKCTRL 			(0xAC)
#define CM_PER_GPIO2_CLKCTRL			(0xB0)
#define CM_PER_GPIO3_CLKCTRL			(0xB4)
#define ENABLE_GPIO_CLKCTRL				(2)
#define OPTFCLKEN_GPIO_GDBCLK			(18)
#define GPIO_REVISION		           	(0x000)
#define GPIO_SYSCONFIG          		(0x010)
#define GPIO_EOI               			(0x020)
#define GPIO_IRQSTATUS_RAW_0    		(0x024)
#define GPIO_IRQSTATUS_RAW_1    		(0x028)
#define GPIO_IRQSTATUS_0        		(0x02C)
#define GPIO_IRQSTATUS_1        		(0x030)
#define GPIO_IRQSTATUS_SET_0    		(0x034)
#define GPIO_IRQSTATUS_SET_1    		(0x038)
#define GPIO_IRQSTATUS_CLR_0    		(0x03C)
#define GPIO_IRQSTATUS_CLR_1    		(0x040)
#define GPIO_IRQWAKEN_0         		(0x044)
#define GPIO_IRQWAKEN_1         		(0x048)
#define GPIO_SYSSTATUS          		(0x114)
#define GPIO_CTRL               		(0x130)
#define GPIO_OE                 		(0x134)
#define GPIO_DATAIN             		(0x138)
#define GPIO_DATAOUT            		(0x13C)
#define GPIO_LEVELDETECT0       		(0x140)
#define GPIO_LEVELDETECT1       		(0x144)
#define GPIO_RISINGDETECT       		(0x148)
#define GPIO_FALLINGDETECT      		(0x14C)
#define GPIO_DEBOUNCENABLE      		(0x150)
#define GPIO_DEBOUNCINGTIME     		(0x154)
#define GPIO_CLEARDATAOUT       		(0x190)
#define GPIO_SETDATAOUT         		(0x194)







#endif /* __DEFINES */