#include "UART.h"


static void (*Pf_TXINT)(void)=NULLPTR;
static void (*Pf_RXINT)(void)=NULLPTR;

void UART_init(u16 Baud,BITS_number framebits,UARTPARITY_status status,BITS_number stopbits)
{
	// Baud Rate 
	u16 BaudRate = (((F_CPU/(Baud*16UL)))-1);
	UBRRL = BaudRate;
	UBRRH = (BaudRate >>8);
	
	// Frame Select
	SET_BIT(UCSRC,URSEL);
	switch(framebits)
	{
		case _5_BIT:
		CLEAR_BIT(UCSRC,UCSZ0);
		CLEAR_BIT(UCSRC,UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		break;
		case _6_BIT:
		SET_BIT(UCSRC,UCSZ0);
		CLEAR_BIT(UCSRC,UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		break;
		case _7_BIT:
		CLEAR_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		break;
		case _8_BIT:
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		break;
		case _9_BIT:
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		SET_BIT(UCSRB,UCSZ2);
		break;
	}
	
	switch(status)
	{
		case PR_EVEN:
		CLEAR_BIT(UCSRC,UPM0);
		SET_BIT(UCSRC,UPM1);
		break;
		case PR_ODD:
		SET_BIT(UCSRC,UPM0);
		SET_BIT(UCSRC,UPM1);
		break;
		case PR_DISABLE:
		CLEAR_BIT(UCSRC,UPM0);
		CLEAR_BIT(UCSRC,UPM1);
		break;
	}
	
	switch(stopbits)
	{
		case _1_BIT:
		CLEAR_BIT(UCSRC,USBS);
		break;
		case _2_BIT:
		SET_BIT(UCSRC,USBS);
		break;
	}
	//Enable transmitter,receiver
	
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
}
#if (NO_BITS == OTHER_BITS)

void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
}

void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_Receive(void)
{
	while (!READ_BIT(UCSRA,RXC));
	return UDR;
}

u8 UART_ReceiveDataNoBlock(u8*pdata) //Lose in Data If The user sends data fast
{
	if (READ_BIT(UCSRA,RXC))
	{
		*pdata=UDR;
		return 1;
	}
	else
	return 0;
	
}

#elif (NO_BITS == NINE_BITS)

void UART_Send(u16 data)
{
	while(!READ_BIT(USCRA,UDRE));	
	
	if ( (data & 0x0100) == 1)
	SET_BIT(UCSRB,TXB8);
	else if ( (data & 0x0100) ==0)
	CLEAR_BIT(UCSRB,TXB8);
	
	UDR= data;
}

void UART_SendNoBlock(u16 data)
{
	if ( (data & 0x0100) == 1)
	SET_BIT(UCSRB,TXB8);
	else if ( (data & 0x0100) ==0)
	CLEAR_BIT(UCSRB,TXB8);
	
	UDR=data;
}

u16 UART_Receive(void)
{
	u16 data;
	while (!READ_BIT(UCSRA,RXC));
	
	data = READ_BIT(UCSRB,RXB8); //Edit if error runtime
	data = (data <<8);
	data |= UDR;
	
	return data;
}

u16 UART_ReceiveNoBlock(void)
{
	u16 data;
	data = READ_BIT(UCSRB,RXB8); //Edit if error runtime
	data = (data <<8);
	data |= UDR;
	
	return data;
}

u8 UART_ReceiveDataNoBlock(u16*pdata) //Lose in Data If The user sends data fast
{
	if (READ_BIT(UCSRA,RXC))
	{
		u16 data;
		data = READ_BIT(UCSRB,RXB8); //Edit if error runtime
		data = (data <<8);
		data |= UDR;
		*pdata=data;
		return 1;
	}
	else
	return 0;
	
}

#endif
UARTERROR_type UART_Receive_Status(void)
{
	if(READ_BIT(UCSRA,PE))
		return RX_PE;
	else if(READ_BIT(UCSRA,FE))
		return RX_FE;
	else if(READ_BIT(UCSRA,DOR))
		return RX_DOR;
	else
		return RX_OK;
}




void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}
void UART_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,RXCIE);
}
void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}
void UART_TX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,TXCIE);
}

void UART_SetCallBack(UARTINTERRUPTSOURCE_type source,void(*localpf)(void))
{
	switch(source)
	{
		case TX_INT:
		Pf_TXINT=localpf;
		break;
		case RX_INT:
		Pf_RXINT=localpf;
		break;
	}
	
}

ISR(UART_TX_vect)
{
	if(Pf_TXINT!=NULLPTR)
	{
		Pf_TXINT();
	}
}

ISR(UART_RX_vect)
{
	if (Pf_RXINT!=NULLPTR)
	{
		Pf_RXINT();
	}
}

