#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

// Macros for PORTS
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

// Macros for PINS
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

// Macros for PIN DIRECTION
#define DIO_INPUT 0
#define DIO_OUTPUT 0xff

// Macros for PIN Values
#define DIO_LOW 0
#define DIO_HIGH 1

// Macros for PULL UP
#define PUD 2

u8 DIO_u8SetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);
u8 DIO_u8SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);
u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);
u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);
u8 DIO_u8GetPortValue(u8 Copy_u8Port, u8 *Copy_Pu8ReturnedValue);
u8 DIO_u8TogglePinValue(u8 Copy_u8Port, u8 Copy_u8Pin);
u8 DIO_u8EnablePullUpResistor(u8 Copy_u8Port, u8 Copy_u8Pin);

#endif /* DIO_INTERFACE_H_ */
