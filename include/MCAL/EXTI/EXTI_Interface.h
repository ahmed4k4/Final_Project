#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

// Macros for Interrupts
#define INT0 0
#define INT1 1
#define INT2 2

// Macros for Sense
#define LOW_LEVEL 0
#define ON_CHANGE 1
#define FALLING_EDGE 2
#define RAISING_EDGE 3

// Macros for Enable
#define ENABLE 1
#define DISABLE 0

u8 EXTI_u8EnableDisable(u8 Copy_u8IntNum, u8 Copy_u8Mode);
u8 EXTI_u8SetSenseCtrl(u8 Copy_u8IntNum, u8 Copy_u8Sense);
u8 EXTI_u8SetCallBack(u8 Copy_u8IntNum, void (*Copy_pf)(void));
void GI_voidEnable(void);
void GI_voidDisable(void);

#endif /* EXTI_INTERFACE_H_ */