#include "../include/LIBs/STD_TYPES.h"
#include "../include/LIBs/BIT_MATH.h"
#include "../include/MCAL/DIO/DIO_Interface.h"
#include "../include/MCAL/DIO/DIO_Private.h"
#include "../include/MCAL/DIO/DIO_Config.h"

u8 DIO_u8SetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction){
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if((Copy_u8Port <= PORTD) && ((Copy_u8Direction == DIO_INPUT) || (Copy_u8Direction == DIO_OUTPUT))){
        switch(Copy_u8Port){
            case PORTA: DDRA_REG = Copy_u8Direction; break;
            case PORTB: DDRB_REG = Copy_u8Direction; break;
            case PORTC: DDRC_REG = Copy_u8Direction; break;
            case PORTD: DDRD_REG = Copy_u8Direction; break;
            default : Local_u8ErrorState = STD_TYPES_NOK; break;
        }
    }else{
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}

u8 DIO_u8SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction){
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if((Copy_u8Port <= PORTD) && (Copy_u8Pin <= PIN7) && ((Copy_u8Direction == DIO_INPUT) || (Copy_u8Direction == DIO_OUTPUT))){
        switch(Copy_u8Port){
            case PORTA:
                if(Copy_u8Direction == DIO_INPUT){
                    CLEAR_BIT(DDRA_REG, Copy_u8Pin);
                }else{
                    SET_BIT(DDRA_REG, Copy_u8Pin);
                }
            break;
            case PORTB:
                if(Copy_u8Direction == DIO_INPUT){
                    CLEAR_BIT(DDRB_REG, Copy_u8Pin);
                }else{
                    SET_BIT(DDRB_REG, Copy_u8Pin);
                }
            break;
            case PORTC:
                if(Copy_u8Direction == DIO_INPUT){
                    CLEAR_BIT(DDRC_REG, Copy_u8Pin);
                }else{
                    SET_BIT(DDRC_REG, Copy_u8Pin);
                }
            break;
            case PORTD:
                if(Copy_u8Direction == DIO_INPUT){
                    CLEAR_BIT(DDRD_REG, Copy_u8Pin);
                }else{
                    SET_BIT(DDRD_REG, Copy_u8Pin);
                }
            break;
            default : Local_u8ErrorState = STD_TYPES_NOK; break;
        }
    }else{
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}

u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value){
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if((Copy_u8Port <= PORTD)){
        switch(Copy_u8Port){
            case PORTA: PORTA_REG = Copy_u8Value; break;
            case PORTB: PORTB_REG = Copy_u8Value; break;
            case PORTC: PORTC_REG = Copy_u8Value; break;
            case PORTD: PORTD_REG = Copy_u8Value; break;
            default : Local_u8ErrorState = STD_TYPES_NOK; break;
        }
    }else{
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}

u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value){
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if((Copy_u8Port <= PORTD) && (Copy_u8Pin <= PIN7) && ((Copy_u8Value == DIO_LOW) || (Copy_u8Value == DIO_HIGH))){
        switch(Copy_u8Port){
            case PORTA:
                if(Copy_u8Value == DIO_LOW){
                    CLEAR_BIT(PORTA_REG, Copy_u8Pin);
                }else{
                    SET_BIT(PORTA_REG, Copy_u8Pin);
                }
            break;
            case PORTB:
                if(Copy_u8Value == DIO_LOW){
                    CLEAR_BIT(PORTB_REG, Copy_u8Pin);
                }else{
                    SET_BIT(PORTB_REG, Copy_u8Pin);
                }
            break;
            case PORTC:
                if(Copy_u8Value == DIO_LOW){
                    CLEAR_BIT(PORTC_REG, Copy_u8Pin);
                }else{
                    SET_BIT(PORTC_REG, Copy_u8Pin);
                }
            break;
            case PORTD:
                if(Copy_u8Value == DIO_LOW){
                    CLEAR_BIT(PORTD_REG, Copy_u8Pin);
                }else{
                    SET_BIT(PORTD_REG, Copy_u8Pin);
                }
            break;
            default : Local_u8ErrorState = STD_TYPES_NOK; break;
        }
    }else{
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin){
    u8 Local_u8GetValue = DIO_LOW;
    if((Copy_u8Port <= PORTD) && (Copy_u8Pin <= PIN7)){
        switch(Copy_u8Port){
            case PORTA: Local_u8GetValue = GET_BIT(PINA_REG, Copy_u8Pin); break;
            case PORTB: Local_u8GetValue = GET_BIT(PINB_REG, Copy_u8Pin); break;
            case PORTC: Local_u8GetValue = GET_BIT(PINC_REG, Copy_u8Pin); break;
            case PORTD: Local_u8GetValue = GET_BIT(PIND_REG, Copy_u8Pin); break;
            default : Local_u8GetValue = DIO_LOW; break;
        }
    }else{
        Local_u8GetValue = DIO_LOW;
    }
    return Local_u8GetValue;
}

u8 DIO_u8GetPortValue(u8 Copy_u8Port, u8 *Copy_Pu8ReturnedValue){
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if((Copy_u8Port <= PORTD) && (Copy_Pu8ReturnedValue != NULL_PTR)){
        switch(Copy_u8Port){
            case PORTA: *Copy_Pu8ReturnedValue = PINA_REG; break;
            case PORTB: *Copy_Pu8ReturnedValue = PINB_REG; break;
            case PORTC: *Copy_Pu8ReturnedValue = PINC_REG; break;
            case PORTD: *Copy_Pu8ReturnedValue = PIND_REG; break;
            default : Local_u8ErrorState = STD_TYPES_NOK; break;
        }
    }else{
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}

u8 DIO_u8TogglePinValue(u8 Copy_u8Port, u8 Copy_u8Pin){
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if((Copy_u8Port <= PORTD) && (Copy_u8Pin <= PIN7)){
        switch(Copy_u8Port){
            case PORTA: TOGGLE_BIT(PORTA_REG, Copy_u8Pin); break;
            case PORTB: TOGGLE_BIT(PORTB_REG, Copy_u8Pin); break;
            case PORTC: TOGGLE_BIT(PORTC_REG, Copy_u8Pin); break;
            case PORTD: TOGGLE_BIT(PORTD_REG, Copy_u8Pin); break;
            default : Local_u8ErrorState = STD_TYPES_NOK; break;
        }
    }else{
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}

u8 DIO_u8EnablePullUpResistor(u8 Copy_u8Port, u8 Copy_u8Pin){
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if((Copy_u8Port <= PORTD) && (Copy_u8Pin <= PIN7)){
        switch(Copy_u8Port){
            case PORTA: CLEAR_BIT(SFIOR,PUD); CLEAR_BIT(DDRA_REG, Copy_u8Pin); SET_BIT(PORTA_REG, Copy_u8Pin); break;
            case PORTB: CLEAR_BIT(SFIOR,PUD); CLEAR_BIT(DDRB_REG, Copy_u8Pin); SET_BIT(PORTB_REG, Copy_u8Pin); break;
            case PORTC: CLEAR_BIT(SFIOR,PUD); CLEAR_BIT(DDRC_REG, Copy_u8Pin); SET_BIT(PORTC_REG, Copy_u8Pin); break;
            case PORTD: CLEAR_BIT(SFIOR,PUD); CLEAR_BIT(DDRD_REG, Copy_u8Pin); SET_BIT(PORTD_REG, Copy_u8Pin); break;
            default : Local_u8ErrorState = STD_TYPES_NOK; break;
        }
    }else{
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}
