/*
 * TIMER_Interface.h
 *
 *  Created on: Sep 2, 2026
 *      Author: hp
 */

#ifndef INCLUDE_MCAL_TIMER_TIMER_INTERFACE_H_
#define INCLUDE_MCAL_TIMER_TIMER_INTERFACE_H_

// Macros for TIMER0 Modes
#define NORMAL_MODE 			0
#define CTC_MODE 				1
#define FAST_PWM_MODE 			2
#define PWM_PHASE_CORRECT_MODE  3

/*************************************** TIMER0 ***************************************/
void TIMER0_voidInit(void);
void TIMER0_voidSetPreloadValue(u8 Copy_u8PreloadValue);
void TIMER0_voidSetOCR0Value(u8 Copy_u8OCR0Value);
void TIMER0_voidSetOVFCallback(u8 * Copy_u8PtrToFunc);
void TIMER0_voidSetCTCCallback(u8 * Copy_u8PtrToFunc);


/*************************************** TIMER1 ***************************************/
void TIMER1_voidInit(void);
void TIMER1_voidSetOCR1Value(u16 Copy_u16Value);

/*************************************** ICU ***************************************/
void TIMER1_ICU_voidInit(void);
void TIMER1_ICU_voidSetTriggerEdge(u8 Copy_u8Edge);
u16 TIMER1_ICU_u16ReadCaptureValue(void);
void TIMER1_ICU_voidClearFlag(void);
void TIMER1_ICU_voidEnableInterrupt(void);
void TIMER1_ICU_voidSetCallBack(u8 * Copy_u8PtrToFunc);

/*************************************** WDT ***************************************/
void TIMER_WDT_voidEnable(void);
void TIMER_WDT_voidDisable(void);
void TIMER_WDT_voidReset(void);

#endif /* INCLUDE_MCAL_TIMER_TIMER_INTERFACE_H_ */
