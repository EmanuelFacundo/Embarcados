#include	"gpio.h"

int flag;

#define TIME		2000000
#define TOGGLE          (0x01u)

static void delay();
static void toggle(gpioPort port, ucPinNumber pin);
	
int main(void){
	unsigned int port=MODULE0, pin=GPIO7, dir=OUTPUT;
	
	flag=0x0;	
	gpioInitModule(MODULE0);
	gpioInitModule(MODULE1);

	gpioInitPin(port, pin);
	gpioInitPin(MODULE1, GPIO23);

	gpioSetDirection(MODULE1, GPIO23, dir);
	gpioSetDirection(port, pin, dir);

	gpioSetPinValue(MODULE1, GPIO23, HIGH);
	gpioSetPinValue(port, pin, HIGH);

	while(true){
		toggle(port, pin);
		delay();
		toggle(port, pin);
		delay();
	}

	return(0);
} 

void toggle(gpioPort port, ucPinNumber pin){
	flag^=TOGGLE;

	if(flag)
		gpioSetPinValue(port, pin, HIGH);
	else
		gpioSetPinValue(port, pin, LOW);	
}

static void delay(){
	volatile unsigned int ra;
	for(ra = 0; ra < TIME; ra ++);
}

