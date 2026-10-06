#ifndef INCLUDE_MCAL_UART_INTERFACE_H_
#define INCLUDE_MCAL_UART_INTERFACE_H_

void UART_Init(void);
void UART_voidSendByteAsync(u8 Copy_u8Data);
u8 UART_u8ReceiveByteAsync(void);
void UART_voidSendString(u8 *Copy_u8Data);

#endif /* INCLUDE_MCAL_UART_INTERFACE_H_ */