/*
 * TIMER_Cfg.h
 *
 *  Created on: Sep 2, 2026
 *      Author: hp
 */

#ifndef INCLUDE_MCAL_TIMER_TIMER_CFG_H_
#define INCLUDE_MCAL_TIMER_TIMER_CFG_H_

/*
 * NORMAL_MODE 0
 * CTC_MODE 1
 * FAST_PWM_MODE 2
 * PWM_PHASE_CORRECT_MODE 3
 */
#define TIMER0_MODE CTC_MODE

/*
 * NO Clk 0b000
 * CLK/ No Prescalar 0b001
 * CLK/ Prescalar(8) 0b010
 * CLK/ Prescalar(64) 0b011
 */
#define TIMER0_CLK_CONFIGURATION 0b011

#define OCR0_Value 99

/*
 * Disconnected --> 0
 * Toggle on Compare Match --> 1
 * Clear on Compare Match --> 2
 * Set on Compare Match --> 3
 */
#define TIMER0_OC0_MODE 0

#define ICU_RISING_EDGE 1
#define ICU_FALLING_EDGE 0

#define ICU_INITIAL_EDGE ICU_RISING_EDGE

#endif /* INCLUDE_MCAL_TIMER_TIMER_CFG_H_ */
