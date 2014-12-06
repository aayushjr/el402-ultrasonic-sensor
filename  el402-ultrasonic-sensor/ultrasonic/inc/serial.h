#ifndef __SERIAL_H
#define __SERIAL_H

#ifdef __cplusplus
 extern ""C"" {
#endif

/* Includes -----------------------------------------------------------------------*/
#include "stm32f0xx.h"
     
/* Exported types -----------------------------------------------------------------*/

typedef struct _SERIAL_Struct {
	uint16_t size;
	uint8_t data[16];
	//uint16_t idx;
} SERIAL_Struct;    
     
/* Exported constants -------------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------------*/
/* Exported functions -------------------------------------------------------------*/
void SERIAL_config(void);
char SERIAL_read(void);
void SERIAL_write(char*);
void write(uint8_t);
void print(char*);
uint16_t SERAIL_available(void);
int checkvalidation(char*);


#ifdef __cplusplus
 }
#endif

#endif // __SERIAL_H
