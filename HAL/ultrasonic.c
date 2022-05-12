#include "ultrasonic.h"
static volatile u16 c=0,flag=0,t1,t2;

static void Func_OVF(void)
{
	c++;
}

static void Func_ICU(void)
{
	if (flag==0)
	{
		t1=ICR1;
		flag=1;
		Timer1_InputCaptureEdge(FALLING);
	}
	else if (flag==1)
	{
		t2=ICR1;
		flag=2;
		Timer1_InputCaptureEdge(RISING);
		Timer1_OVF_InterruptDisable();
		Timer1_ICU_InterruptDisable();
	}
}

void ULTRASONIC_Init(void)
{
	/***you can use timer another mode except timer using icu in top ***/
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_DISCONNECTED);
	Timer1_OVF_SetCallBack(Func_OVF);
	Timer1_ICU_SetCallBack(Func_ICU);
}



void ULTRASONIC_Start(ULTRASONIC_type ultrasonic_pin)
{
	if (flag==0)
	{
		DIO_WritePin(ultrasonic_pin,HIGH);
		_delay_us(10);
		DIO_WritePin(ultrasonic_pin,LOW);
		Timer1_ICU_InterruptEnable();
		Timer1_OVF_InterruptDisable();
	}
}


u8 ULTRASONIC_GetDistanceNoBlock(u8*Pdistance)
{
	u8 distance;
	u16 time;
	if (flag==2)
	{
		time= t2-t1+((u32)c*65535);
		distance= time/58;
		*Pdistance = distance;
		Timer1_OVF_InterruptEnable();
		return 1;
	}
	return 0;	
}


u8 ULTRASONIC_GetDistance(ULTRASONIC_type ultrasonic_pin)
{
	u8 distance;
	u16 time;
	c=0;
	flag=0;
	DIO_WritePin(ultrasonic_pin,HIGH);
	_delay_us(10);
	DIO_WritePin(ultrasonic_pin,LOW);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	while(flag<2);
	time=t2-t1+((u32)c*65535);
	distance = time/58;
	Timer1_ICU_InterruptDisable();
	return distance;
	
}

u8 ULTRASONIC_GetDistance2(ULTRASONIC_type ultrasonic_pin)
{
	u8 distance;
	u16 time;
	DIO_WritePin(ultrasonic_pin,HIGH);
	_delay_us(10);
	DIO_WritePin(ultrasonic_pin,LOW);
	while(!DIO_ReadPin(BUTTON));
	TCNT1=0;
	while(DIO_ReadPin(BUTTON));
	time=TCNT1;
	distance = time/58;
	return distance;
	
}