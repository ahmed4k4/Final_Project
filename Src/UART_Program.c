#include "../include/LIBs/STD_Types.h"
#include "../include/LIBs/BIT_Math.h"

#include "../include/MCAL/DIO/DIO_Interface.h"
#include "../include/MCAL/UART/UART_Interface.h"
#include "../include/MCAL/UART/UART_Config.h"
#include "../include/MCAL/UART/UART_Private.h"

#define F_CPU 8000000UL

void UART_Init(void)
{
    // Set Baud Rate
    u16 Local_u16UBRR = BAUD_RATE_EQUATION;
    UBRRH = (u8)(Local_u16UBRR >> 8);
    UBRRL = (u8)(Local_u16UBRR);

    // Set Data Size
    CLEAR_BIT(UCSRB, 2);

    // Set Frame Format
    UCSRC = UCSRC_CONTROL;

    // Enable RX and TX
    SET_BIT(UCSRB, 3);
    SET_BIT(UCSRB, 4);
}

void UART_voidSendByteAsync(u8 Copy_u8Data)
{
    // Wait for empty transmit buffer
    if(GET_BIT(UCSRA, 5) == 1)
    {
        UDR = Copy_u8Data;
    }
}

u8 UART_u8ReceiveByteAsync(void)
{
	while (GET_BIT(UCSRA, 7) == 0);
        return UDR;
}

void UART_voidSendString(u8 *Copy_u8Data){
    while(*Copy_u8Data != '\0')
    {
        while(GET_BIT(UCSRA, 5) == 0);
        UDR = *Copy_u8Data;
        Copy_u8Data++;
    }
}
