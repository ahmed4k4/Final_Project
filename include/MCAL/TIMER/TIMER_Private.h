/*
 * TIMER_Private.h
 *
 *  Created on: Sep 2, 2026
 *      Author: hp
 */

#ifndef INCLUDE_MCAL_TIMER_TIMER_PRIVATE_H_
#define INCLUDE_MCAL_TIMER_TIMER_PRIVATE_H_

#define TIMSK (*(volatile u8 *)0x59)
#define TIFR  (*(volatile u8 *)0x58)
#define TCCR0 (*(volatile u8 *)0x53)
#define TCNT0 (*(volatile u8 *)0x52)
#define OCR0  (*(volatile u8 *)0x5C)


#define TCCR1A (*(volatile u8 *)0x4F)
#define TCCR1B (*(volatile u8 *)0x4E)
#define TCNT1H (*(volatile u8 *)0x4D)
#define TCNT1L (*(volatile u8 *)0x4C)
#define TCNT1LH (*(volatile u16 *)0x4C)
#define OCR1AH (*(volatile u8 *)0x4B)
#define OCR1AL (*(volatile u8 *)0x4A)
#define OCR1ALH (*(volatile u16 *)0x4A)
#define OCR1BH (*(volatile u8 *)0x49)
#define OCR1BL (*(volatile u8 *)0x48)
#define OCR1BLH (*(volatile u16 *)0x48)
#define ICR1H (*(volatile u8 *)0x47)
#define ICR1L (*(volatile u8 *)0x46)
#define ICR1LH (*(volatile u16 *)0x46)


#define WDTCR (*(volatile u16 *)0x41)

#endif /* INCLUDE_MCAL_TIMER_TIMER_PRIVATE_H_ */
