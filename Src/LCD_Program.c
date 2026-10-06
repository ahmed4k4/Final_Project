#include "../include/LIBs/STD_TYPES.h"
#include "../include/LIBs/BIT_MATH.h"

#include "../include/MCAL/DIO/DIO_Interface.h"

#include "../include/HAL/LCD/LCD_Interface.h"
#include "../include/HAL/LCD/LCD_Private.h"
#include "../include/HAL/LCD/LCD_Config.h"

#include <util/delay.h>

void LCD_voidInit(void){
    DIO_u8SetPortDirection(LCD_DATA_PORT, DIO_OUTPUT);
    DIO_u8SetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_OUTPUT);
    DIO_u8SetPinDirection(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_OUTPUT);
    DIO_u8SetPinDirection(LCD_CONTROL_PORT, LCD_E_PIN, DIO_OUTPUT);

    DIO_u8SetPortValue(LCD_DATA_PORT, DIO_LOW);
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_LOW);
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_LOW);
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_LOW);

    // Wait for 35ms
    _delay_ms(35);
    // Send Function Set Command
    LCD_voidSendCmnd(0b00111000);
    // Wait for 45ms
    _delay_ms(45);
    // Display ON/OFF
    LCD_voidSendCmnd(0b00001111);
    // Wait for 45us
    _delay_us(45);
    // Display Clear
    LCD_voidSendCmnd(0b00000001);
    // Wait for 2ms
    _delay_ms(2);
    // Entry Set Mode
    LCD_voidSendCmnd(0b00000110);
}

void LCD_voidSendCmnd(u8 Copy_u8Cmnd){
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_LOW); //RS   =0
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_LOW); //RW    =0
    DIO_u8SetPortValue(LCD_DATA_PORT, Copy_u8Cmnd);
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_HIGH); //E     =1
    _delay_us(1);
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_LOW); //E     =0
}

void LCD_voidSendData(u8 Copy_u8Data){
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_HIGH); //RS   =1
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_LOW); //RW    =0
    DIO_u8SetPortValue(LCD_DATA_PORT, Copy_u8Data);
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_HIGH); //E     =1
    _delay_us(1);
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_LOW); //E     =0
}

u8 LCD_u8GoToXy(u8 Copy_u8LineNum, u8 Copy_u8Location){
    u8 Local_u8ErrorState = STD_TYPES_OK;
    if(Copy_u8Location <= 39){
        switch(Copy_u8LineNum){
            case 0:
                LCD_voidSendCmnd(LCD_LINDE1_ADRESS + Copy_u8Location);
                break;
            case 1:
                LCD_voidSendCmnd(LCD_LINDE2_ADRESS + Copy_u8Location);
                break;
            default:
                Local_u8ErrorState = STD_TYPES_NOK;
                break;
        }
    }else{
        Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState;
}

void LCD_voidDisplayClear(void){
    // Display Clear
    LCD_voidSendCmnd(0b00000001);
    // Wait for 2ms
    _delay_ms(2);
}

void LCD_voidSendString(u8 *Copy_pu8Data){
    while(*Copy_pu8Data != NULL_PTR){
        LCD_voidSendData(*Copy_pu8Data);
        Copy_pu8Data++;
    }
}

void LCD_voidDisplayNumber(s32 Copy_s32Number){
    u32 Local_u32Number = 1;
    if(Copy_s32Number == 0){
        LCD_voidSendData('0');
        return;
    }
    if(Copy_s32Number < 0){
        LCD_voidSendData('-');
        Copy_s32Number = -Copy_s32Number;
    }
    while (Copy_s32Number != 0){
        Local_u32Number = (Local_u32Number * 10) + (Copy_s32Number % 10);
        Copy_s32Number /= 10;
    }
    while (Local_u32Number != 1){
        LCD_voidSendData(Local_u32Number % 10 + '0');
        Local_u32Number /= 10;
    }
    
}

void LCD_voidDisplaySpecialCharacter(u8 *Copy_pu8Pattern, u8 Copy_u8Location)
{
    LCD_voidSendCmnd(0x40 + (Copy_u8Location * 8));

    for (u8 i = 0; i < 8; i++)
    {
        LCD_voidSendData(Copy_pu8Pattern[i]);
    }

    LCD_voidSendCmnd(0x80);
}
