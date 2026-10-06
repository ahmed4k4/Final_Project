/*
 * TIMER_Program.c
 *
 *  Created on: Sep 2, 2026
 *      Author: hp
 */

#include "../include/LIBs/STD_TYPES.h"
#include "../include/LIBs/BIT_MATH.h"

#include "../Include/MCAL/DIO/DIO_Interface.h"
#include "../Include/MCAL/TIMER/TIMER_Interface.h"
#include "../Include/MCAL/TIMER/TIMER_Private.h"
#include "../Include/MCAL/TIMER/TIMER_Cfg.h"

static void (*TIMER0_OVF_CALLBACK)(void) = NULL_PTR;
static void (*TIMER0_CTC_CALLBACK)(void) = NULL_PTR;

void TIMER0_voidInit(void)
{
#if TIMER0_MODE == NORMAL_MODE
	// Set Wave Generation to Normal Mode
	CLEAR_BIT(TCCR0, 3);
	CLEAR_BIT(TCCR0, 6);

	// Turn On OVF INT
	SET_BIT(TIMSK, 0);
	CLEAR_BIT(TIMSK, 1);

	// Start Timer by setting CLK
	TCCR0 &= 0b11111000;
	TCCR0 |= TIMER0_CLK_CONFIGURATION; // 000 | 010 ==> 010

#elif TIMER0_MODE == CTC_MODE
	// Set Wave Generation to CTC Mode
	SET_BIT(TCCR0, 3);
	CLEAR_BIT(TCCR0, 6);

	// OC0 must be cleared in PWM modes
	CLEAR_BIT(TCCR0, 7);

	// Turn On CTC INT
	CLEAR_BIT(TIMSK, 0);
	SET_BIT(TIMSK, 1);

	// Set OCR0 Value
	OCR0 = OCR0_Value;

	// Set OCR0 Mode
	TCCR0 &= ~(0b00000011 << 4);	 // 0b00000011 << 4 --> ~0b00110000 -> 11001111
	TCCR0 |= (TIMER0_OC0_MODE << 4); // 0b00000011 << 4 --> 0b00110000

	// Start Timer by setting CLK
	TCCR0 &= 0b11111000;
	TCCR0 |= TIMER0_CLK_CONFIGURATION; // 000 | 010 ==> 010

#endif
}

void TIMER0_voidSetPreloadValue(u8 Copy_u8PreloadValue)
{
	TCNT0 = Copy_u8PreloadValue;
}

void TIMER0_voidSetOCR0Value(u8 Copy_u8OCR0Value)
{
	OCR0 = Copy_u8OCR0Value;
}

void TIMER0_voidSetOVFCallback(u8 *Copy_u8PtrToFunc)
{
	if (Copy_u8PtrToFunc != NULL_PTR)
	{
		TIMER0_OVF_CALLBACK = Copy_u8PtrToFunc;
	}
}
void TIMER0_voidSetCTCCallback(u8 *Copy_u8PtrToFunc)
{
	if (Copy_u8PtrToFunc != NULL_PTR)
	{
		TIMER0_CTC_CALLBACK = Copy_u8PtrToFunc;
	}
}

// Vector of OVF
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if (TIMER0_OVF_CALLBACK != NULL_PTR)
	{
		TIMER0_OVF_CALLBACK();
	}
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if (TIMER0_CTC_CALLBACK != NULL_PTR)
	{
		TIMER0_CTC_CALLBACK();
	}
}

/*************************************** TIMER1 ***************************************/

void TIMER1_voidInit(void){
	// Select TIMER1 Mode ==> Mode 14
	CLEAR_BIT(TCCR1A, 0);
	SET_BIT(TCCR1A, 1);
	SET_BIT(TCCR1B, 3);
	SET_BIT(TCCR1B, 4);

	// Non Inverting Mode
	CLEAR_BIT(TCCR1A, 6);
	SET_BIT(TCCR1A, 7);

	// ICR1 Value
	ICR1LH = 19999;

	// OCR1A
	OCR1ALH = 1500;

	// Start Timer
	CLEAR_BIT(TCCR1B, 0);
	SET_BIT(TCCR1B, 1);
	CLEAR_BIT(TCCR1B, 2);
}

void TIMER1_voidSetOCR1Value(u16 Copy_u16Value){
	OCR1ALH = Copy_u16Value;
}
