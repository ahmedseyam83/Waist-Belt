#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "DIO_Interface.h"
#include "Timers.h"
#include <util/delay.h>




#define  BUTTON   PIND5

typedef enum{
	  ULTRASONIC_1=8,
	  ULTRASONIC_2,
	  ULTRASONIC_3,
	  ULTRASONIC_4
	}ULTRASONIC_type; 


void ULTRASONIC_Init(void);
u8 ULTRASONIC_GetDistance(ULTRASONIC_type ultrasonic_pin);
u8 ULTRASONIC_GetDistance2(ULTRASONIC_type ultrasonic_pin);
void ULTRASONIC_Start(ULTRASONIC_type ultrasonic_pin);
u8 ULTRASONIC_GetDistanceNoBlock(u8*Pdistance);



#endif /* ULTRASONIC_H_ */