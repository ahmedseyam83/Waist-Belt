#include "BeltControl.h"

u8 static Warning_flag1=0, Warning_flag2=0, Warning_flag3=0, Warning_flag4=0;
BELT_status state;



/**************************************** Belt State ***************************************/

/*************************************************************
 * @fn          - Belt_ON
 * @brief       - Function TURN ON BELT
 * @param[in]   - none
 * @return      - none
 * @note        - ON/OFF Vibration Unit vibrate twice each for 0.5sec when mode activated
 */
void Belt_ON(void)
{
	state=ON;
	DIO_WritePin(ONOFF_VIBRATION,HIGH);
	_delay_ms(500);
	DIO_WritePin(ONOFF_VIBRATION,LOW);
	_delay_ms(250);
	DIO_WritePin(ONOFF_VIBRATION,HIGH);
	_delay_ms(500);
	DIO_WritePin(ONOFF_VIBRATION,LOW);
	DIO_WritePin(ONOFF_LED,HIGH);
}

/*************************************************************
 * @fn          - Belt_STANDBY
 * @brief       - Function Put the belt in standby mode [Mode after first click on button post off mode]  
 * @param[in]   - none
 * @return      - none
 * @note        - ON/OFF Vibration Unit vibrate once for 0.5sec when mode activated
 */

void Belt_STANDBY(void)
{
	state=STANDBY;
	DIO_WritePin(ONOFF_VIBRATION,HIGH);
	_delay_ms(500);
	DIO_WritePin(ONOFF_VIBRATION,LOW);
	DIO_WritePin(ONOFF_LED,LOW);
	CPU_Sleep(STANDBY_MODE);
	
}

/*************************************************************
 * @fn          - Belt_OFF
 * @brief       - Function TURN OFF BELT
 * @param[in]   - none
 * @return      - none
 * @note        - ON/OFF Vibration Unit vibrate once for 1.5sec when mode activated
 */

void Belt_OFF(void)
{
	u8 static first_time=1;
	state=OFF;
	
	if (first_time==0)
	{
		DIO_WritePin(ONOFF_VIBRATION,HIGH);
		_delay_ms(1500);
		DIO_WritePin(ONOFF_VIBRATION,LOW);
	}
	first_time=0;
	DIO_WritePin(ONOFF_LED,LOW);
	CPU_Sleep(PWR_DOWN_MODE);
}

/*************************************************************
 * @fn          - Belt_State
 * @brief       - Function Choose the mode should belt be in after clicking ON/OFF button 
 * @param[in]   - none
 * @return      - none
 * @note        - Used in Interrupt Function to never be missed
 */
void Belt_State(void)
{
	WDT_Stop();
	while(!DIO_ReadPin(ONOFF_BUTTON));
	if (state == OFF)
		Belt_STANDBY();	
	else if(state == STANDBY)
		Belt_ON();
	else if(state == ON)
		Belt_OFF();
}

/*************************************** Belt Runtime **************************************/

/*************************************************************
 * @fn          - ULTRASONIC_Measure
 * @brief       - Function use Ultrasonic Sensor to measure the distance and send warning 
 * @param[in]   - none
 * @return      - none
 * @note        - none
 */

void ULTRASONIC_Measure(void)
{
	u8 ultrasonic= ULTRASONIC_GetDistance(ULTRASONIC_1);
	if (ultrasonic >=10 && ultrasonic <=50)
		Warning_flag1=1;
	else
		Warning_flag1=0;
	
	ultrasonic= ULTRASONIC_GetDistance(ULTRASONIC_2);
	if (ultrasonic >=10 && ultrasonic <=50)
		Warning_flag2=1;
	else
		Warning_flag2=0;
			
	ultrasonic= ULTRASONIC_GetDistance(ULTRASONIC_3);
	if (ultrasonic >=10 && ultrasonic <=50)
		Warning_flag3=1;
	else
		Warning_flag3=0;
		
	ultrasonic= ULTRASONIC_GetDistance(ULTRASONIC_4);
	if (ultrasonic >=10 && ultrasonic <=50)
		Warning_flag4=1;
	else
		Warning_flag4=0;
}

/*************************************************************
 * @fn          - Warning_Action
 * @brief       - Function Check Warning flags and take action according to their value 
 * @param[in]   - none
 * @return      - none
 * @note        - none
 */

void Warning_Action(void)
{
	if (Warning_flag1 ==1){
		DIO_WritePin(VIBRATION_1,HIGH);
		UART_Send(0x31);
	}
	else{
		DIO_WritePin(VIBRATION_1,LOW);
		UART_Send(0x32);
	}
	
	if (Warning_flag2 ==1){
		DIO_WritePin(VIBRATION_2,HIGH);
		UART_Send(0x33);
	}
	else if(Warning_flag3 ==0 && Warning_flag2 ==0 ){
		DIO_WritePin(VIBRATION_2,LOW);
		UART_Send(0x34);
	}
	
	if (Warning_flag3 ==1){
		DIO_WritePin(VIBRATION_2,HIGH);
		UART_Send(0x35);
	}
	else if(Warning_flag3 ==0 && Warning_flag2 ==0 ){
		DIO_WritePin(VIBRATION_2,LOW);
		UART_Send(0x36);
	}
	
	if (Warning_flag4 ==1){
		DIO_WritePin(VIBRATION_4,HIGH);
		UART_Send(0x37);
	}
	else{
		DIO_WritePin(VIBRATION_4,LOW);
		UART_Send(0x38);
	}
}