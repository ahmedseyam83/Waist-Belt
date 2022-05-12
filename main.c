#include "Utils.h"
#include "Config.h"


int main(void)
{
	sei();
	DIO_Init();
	ULTRASONIC_Init();
	UART_init(9600,_8_BIT,PR_DISABLE,_1_BIT);
	Schedular_Init();
	
	
	EXI_TriggerEdge(EX_INT0,LOW_LEVEL);
	EX_SetCallBack(EX_INT0,Belt_State);
	EXI_Enable(EX_INT0);
	
	OS_TaskCreate(ULTRASONIC_Measure,20,BLOCKED);
	OS_TaskCreate(Warning_Action,20,BLOCKED);
	OS_TaskCreate(Schedular_Sleep,10,BLOCKED);
	
	
	Belt_OFF();
	
    Schedular_Start();
	
    while (1) 
    {
		OS_TaskExecution();
    }
}

