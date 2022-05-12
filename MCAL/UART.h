#ifndef UART_H_
#define UART_H_

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "Config.h"

#define NINE_BITS   0
#define OTHER_BITS  1
#define NO_BITS     OTHER_BITS

typedef enum{
	TX_INT=0,
	RX_INT
}UARTINTERRUPTSOURCE_type;

typedef enum{
	RX_OK=0,
	RX_FE,
	RX_DOR,
	RX_PE
	}UARTERROR_type;


typedef enum{
	_1_BIT=0,
	_2_BIT,
	_5_BIT,
	_6_BIT,
	_7_BIT,
	_8_BIT,
	_9_BIT
	}BITS_number;

typedef enum{
	PR_EVEN,
	PR_ODD,
	PR_DISABLE
	}UARTPARITY_status;

void UART_init(u16 Baud,BITS_number framebits,UARTPARITY_status status,BITS_number stopbits);

#if (NO_BITS == OTHER_BITS)
void UART_Send(u8 data);
void UART_SendNoBlock(u8 data);
u8 UART_Receive(void);
u8 UART_ReceiveNoBlock(void);
u8 UART_ReceiveDataNoBlock(u8*pdata);

#elif (NO_BITS == NINE_BITS)
void UART_Send(u16 data);
void UART_SendNoBlock(u16 data);
u16 UART_Receive(void);
u16 UART_ReceiveNoBlock(void);
u8 UART_ReceiveDataNoBlock(u16*pdata);

#endif

UARTERROR_type UART_Receive_Status(void);
void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);
void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);
void UART_SetCallBack(UARTINTERRUPTSOURCE_type source,void(*localpf)(void));


#endif /* UART_H_ */