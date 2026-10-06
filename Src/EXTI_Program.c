#include "../include/LIBs/STD_TYPES.h"
#include "../include/LIBs/BIT_MATH.h"

#include "../include/MCAL/EXTI/EXTI_Interface.h"
#include "../include/MCAL/EXTI/EXTI_Private.h"
#include "../include/MCAL/EXTI/EXTI_Config.h"

#include "../include/MCAL/DIO/DIO_Interface.h"
#include <util/delay.h>

static void (*GlobalPtrFun[3])(void) = {NULL_PTR, NULL_PTR, NULL_PTR};

u8 EXTI_u8EnableDisable(u8 Copy_u8IntNum, u8 Copy_u8Mode)
{
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if (Copy_u8IntNum <= INT2)
    {
        switch (Copy_u8IntNum)
        {
        case INT0:
            switch (Copy_u8Mode)
            {
            case ENABLE:
                SET_BIT(GICR, 6);
                break;
            case DISABLE:
                CLEAR_BIT(GICR, 6);
                break;
            }
            break;
        case INT1:
            switch (Copy_u8Mode)
            {
            case ENABLE:
                SET_BIT(GICR, 7);
                break;
            case DISABLE:
                CLEAR_BIT(GICR, 7);
                break;
            }
            break;
        case INT2:
            switch (Copy_u8Mode)
            {
            case ENABLE:
                SET_BIT(GICR, 5);
                break;
            case DISABLE:
                CLEAR_BIT(GICR, 5);
                break;
            }
            break;
        default:
            Local_u8ErrorState = STD_TYPES_NOK;
            break;
        }
    }
    else
    {
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}

u8 EXTI_u8SetSenseCtrl(u8 Copy_u8IntNum, u8 Copy_u8Sense)
{
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if (Copy_u8IntNum <= INT2)
    {
        switch (Copy_u8IntNum)
        {
        case INT0:
            switch (Copy_u8Sense)
            {
            case LOW_LEVEL:
                CLEAR_BIT(MCUCR, 0);
                CLEAR_BIT(MCUCR, 1);
                break;
            case ON_CHANGE:
                SET_BIT(MCUCR, 0);
                CLEAR_BIT(MCUCR, 1);
                break;
            case FALLING_EDGE:
                CLEAR_BIT(MCUCR, 0);
                SET_BIT(MCUCR, 1);
                break;
            case RAISING_EDGE:
                SET_BIT(MCUCR, 0);
                SET_BIT(MCUCR, 1);
                break;
            default:
                Local_u8ErrorState = STD_TYPES_NOK;
                break;
            }
            break;
        case INT1:
            switch (Copy_u8Sense)
            {
            case LOW_LEVEL:
                CLEAR_BIT(MCUCR, 2);
                CLEAR_BIT(MCUCR, 3);
                break;
            case ON_CHANGE:
                SET_BIT(MCUCR, 2);
                CLEAR_BIT(MCUCR, 3);
                break;
            case FALLING_EDGE:
                CLEAR_BIT(MCUCR, 2);
                SET_BIT(MCUCR, 3);
                break;
            case RAISING_EDGE:
                SET_BIT(MCUCR, 2);
                SET_BIT(MCUCR, 3);
                break;
            default:
                Local_u8ErrorState = STD_TYPES_NOK;
                break;
            }
            break;
        case INT2:
            switch (Copy_u8Sense)
            {
            case FALLING_EDGE:
                CLEAR_BIT(MCUCSR, 6);
                break;
            case RAISING_EDGE:
                SET_BIT(MCUCSR, 6);
                break;
            default:
                Local_u8ErrorState = STD_TYPES_NOK;
                break;
            }
            break;
        default:
            Local_u8ErrorState = STD_TYPES_NOK;
            break;
        }
    }
    else
    {
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}

u8 EXTI_u8SetCallBack(u8 Copy_u8IntNum, void (*Copy_pf)(void))
{
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if ((Copy_u8IntNum <= INT2) && (Copy_pf != NULL_PTR))
    {
        switch (Copy_u8IntNum)
        {
        case INT0:
            GlobalPtrFun[0] = Copy_pf;
            break;
        case INT1:
            GlobalPtrFun[1] = Copy_pf;
            break;
        case INT2:
            GlobalPtrFun[2] = Copy_pf;
            break;
        default:
            Local_u8ErrorState = STD_TYPES_NOK;
            break;
        }
    }
    else
    {
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}

void GI_voidEnable()
{
    SET_BIT(SREG, 7);
}

void GI_voidDisable()
{
    CLEAR_BIT(SREG, 7);
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
    if (GlobalPtrFun[0] != NULL_PTR)
    {
        GlobalPtrFun[0]();
    }
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
    if (GlobalPtrFun[1] != NULL_PTR)
    {
        GlobalPtrFun[1]();
    }
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
    if (GlobalPtrFun[2] != NULL_PTR)
    {
        GlobalPtrFun[2]();
    }
}
