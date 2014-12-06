
#include "soniclib.h"

#define ULTRASONIC_PIN GPIO_Pin_6
#define LED_PIN GPIO_Pin_9

//Create new structs for TIM and GPIO init
TIM_TimeBaseInitTypeDef T;
TIM_OCInitTypeDef TO;
GPIO_InitTypeDef GPIO_InitStructure;



/*
 * @brief	Setup RCC for GPIOC and TIM2
*/
void platformConfig(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}


/*
 * @brief	Setup TIM2 with given configurations
*/
void timerConfig(void)
{
	uint16_t PrescalerValue = 0;
  
 //Setup timer 2 with period > 50ms
 //with no clock division (running at 48MHz)
 //Period is calculated by:
 //(48e6/((Prescalar+1)*Freq) - 1
 //Where Freq = 20Hz t=0.05 s
 
 PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;
 T.TIM_Prescaler = PrescalerValue;
 T.TIM_Period = 65535 - 1;
 T.TIM_ClockDivision = 0;
 T.TIM_CounterMode = TIM_CounterMode_Up;
 TIM_TimeBaseInit(TIM2, &T);
 TIM_OC1Init(TIM2, &TO);
	
 TIM_Cmd(TIM2, ENABLE);
 	
}


/*
 * @brief	Setup GPIO structure.
 * 				Set GPIOC pin 9 as output LED and pin 6 as output pin.
*/
void setGPIO(void)
{
	GPIO_InitStructure.GPIO_Pin = LED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin =  ULTRASONIC_PIN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOC, ULTRASONIC_PIN,Bit_RESET);
}

/*
* @brief	Set led value on/off
* @param	value : value of led to set
*					 @arg HIGH: set LED on
*					 @arg LOW: set LED off
*/
void led(int value)
{
	if(value == HIGH)
	{
		GPIO_WriteBit(GPIOC, LED_PIN, Bit_SET); 
	}else{
		GPIO_WriteBit(GPIOC, LED_PIN, Bit_RESET); 
	}
}

/*
 * @brief	Set GPIOC pin 9 as output
*/
void setGPIOout(void)
{
	GPIO_InitStructure.GPIO_Pin = ULTRASONIC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}


/*
 * @brief	Set GPIOC pin 9 as input
*/
void setGPIOin(void)
{
	GPIO_InitStructure.GPIO_Pin = ULTRASONIC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*
 * @brief	Read ultrasonic data
 * @retval The distance from the sensor in cm (uint32_t)
*/
uint32_t sonic_read(void)
{
	uint32_t counterval = 0;
	setGPIOout();
	TIM_SetCounter(TIM2, 0);
	GPIO_WriteBit(GPIOC,ULTRASONIC_PIN,Bit_SET);
  while(TIM_GetCounter(TIM2) < 15);
	GPIO_WriteBit(GPIOC,ULTRASONIC_PIN,Bit_RESET);
	setGPIOin();
  //TIM_SetCounter(TIM2, 0);
  while(!GPIO_ReadInputDataBit(GPIOC,ULTRASONIC_PIN));// & (TIM_GetCounter(TIM2) < 50000));
  TIM_SetCounter(TIM2, 0);
  while(GPIO_ReadInputDataBit(GPIOC, ULTRASONIC_PIN));// & (TIM_GetCounter(TIM2) < 50000));
	counterval = TIM_GetCounter(TIM2);
  counterval = (counterval * 0.01715) + 0.8;	//value in cm
	return counterval;
}


