#ifndef INCLUDE_MCAL_UART_PRIVATE_H_
#define INCLUDE_MCAL_UART_PRIVATE_H_

#define UBRRH (*((volatile u8*)0x40))
#define UCSRC (*((volatile u8*)0x40))
#define UDR   (*((volatile u8*)0x2C))
#define UCSRA (*((volatile u8*)0x2B))
#define UCSRB (*((volatile u8*)0x2A))
#define UBRRL (*((volatile u8*)0x29))

#define BAUD_RATE_EQUATION ((F_CPU / (16UL * BAUD_RATE)) - 1UL)
#define UCSRC_CONTROL 0b10000110

#endif /* INCLUDE_MCAL_UART_PRIVATE_H_ */