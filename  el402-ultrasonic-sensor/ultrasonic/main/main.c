
/* Includes -----------------------------------------------------------------------*/
#include <stdio.h>
#include "util.h"
#include "soniclib.h"
#include "serial.h"

/* Private types ------------------------------------------------------------------*/
/* Private constants --------------------------------------------------------------*/
/* Private macro ------------------------------------------------------------------*/
/* Private variables --------------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------------*/
/* Private functions --------------------------------------------------------------*/


/**
* @brief    Init GPIO pins and read from the ultrasonic sensor, and set LED accordingly.
*/
int main()
{
		uint32_t distance = 0;
		char str[15];
		
		//Configure system timebase to generate 1-ms tick
    timebase_config();
	
		//Configure RCC for GPIOC and TIM2
	  platformConfig();
	
		//Configure settings for TIM2
		timerConfig();
	
		//Configure settings for GPIOC Pins used
		setGPIO();
		
	//configure serial communication
		SERIAL_config();
	  
		while(1) {
				distance = sonic_read();
    		if(distance < 10)
				{
					led(HIGH);
				}else{
					led(LOW);
				}

				sprintf(str, "Distance-> %d", distance);				
				SERIAL_write(str);
				delay(300);
								
    }
}
