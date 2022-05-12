#ifndef BELTCONTROL_H_
#define BELTCONTROL_H_

#include "DIO_Interface.h"
#include "ultrasonic.h"
#include "Power_Management.h"
#include "WDT.h"
#include "UART.h"

#define VIBRATION_1		PINC0
#define VIBRATION_2		PINC1
#define VIBRATION_3		
#define VIBRATION_4		PINC2
#define ONOFF_VIBRATION PIND5
#define  ONOFF_BUTTON   PIND2
#define ONOFF_LED       PINC4


typedef enum{
	OFF=0,
	ON,
	STANDBY
	}BELT_status; 




/**************************************** Belt State ***************************************/
void Belt_State(void);
void Belt_ON(void);
void Belt_STANDBY(void);
void Belt_OFF(void);

/*************************************** Belt Runtime **************************************/
void ULTRASONIC_Measure(void);
void Warning_Action(void);





#endif /* BELTCONTROL_H_ */