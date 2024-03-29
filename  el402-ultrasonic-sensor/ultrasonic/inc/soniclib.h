/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SONICLIB_H
#define __SONICLIB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stm32f0xx.h>
	
/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
#define	OUTPUT	1
#define INPUT	0
	
#define HIGH	1
#define	LOW		0

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void setGPIO(void);
uint32_t sonic_read(void);
void led(int);
void timerConfig(void);
void platformConfig(void);
/*void pinMode(uint8_t, int);
void digitalWrite(uint8_t, int);
int digitalRead(uint8_t);
int analogRead(uint8_t);
void analogWrite(uint8_t, uint16_t);
void platform_config(void);
	*/
	
#ifdef __cplusplus
} // extern "C"
#endif	
#endif