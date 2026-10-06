#define F_CPU 8000000UL
#include <util/delay.h>

#include "../include/LIBs/STD_Types.h"
#include "../include/LIBs/BIT_Math.h"

#include "../include/MCAL/DIO/DIO_Interface.h"
#include "../include/MCAL/UART/UART_Interface.h"
#include "../include/MCAL/UART/UART_Private.h"
#include "../include/MCAL/TIMER/TIMER_Interface.h"

#include "../include/HAL/LCD/LCD_Interface.h"

#include "../include/APP/APP_Config.h"
#include "../include/APP/APP_Interface.h"

typedef enum {
    DEV_L1 = 0,
    DEV_L2,
    DEV_L3,
    DEV_L4,
    DEV_R1,
    DEV_R2,
    DEV_FAN,
    DEV_DOOR,
    DEV_MAX
} Device_t;

typedef struct {
    u8 inPort;
    u8 inPin;
    u8 outPort;
    u8 outPin;
    const char* name;
} Channel_t;

const Channel_t DeviceChannels[DEV_MAX] = {
    [DEV_L1]   = {SW_L1_PORT,   SW_L1_PIN,   LED1_PORT,   LED1_PIN,   "L1"},
    [DEV_L2]   = {SW_L2_PORT,   SW_L2_PIN,   LED2_PORT,   LED2_PIN,   "L2"},
    [DEV_L3]   = {SW_L3_PORT,   SW_L3_PIN,   LED3_PORT,   LED3_PIN,   "L3"},
    [DEV_L4]   = {SW_L4_PORT,   SW_L4_PIN,   LED4_PORT,   LED4_PIN,   "L4"},
    [DEV_R1]   = {SW_R1_PORT,   SW_R1_PIN,   RELAY1_PORT, RELAY1_PIN, "R1"},
    [DEV_R2]   = {SW_R2_PORT,   SW_R2_PIN,   RELAY2_PORT, RELAY2_PIN, "R2"},
    [DEV_FAN]  = {SW_FAN_PORT,  SW_FAN_PIN,  FAN_PORT,    FAN_PIN,    "FAN"},
    [DEV_DOOR] = {SW_DOOR_PORT, SW_DOOR_PIN, SERVO_PORT,  SERVO_PIN,  "DOOR"}
};

u8 App_States[DEV_MAX]           = {0};
u8 App_PrevInputs[DEV_MAX]       = {0};
u8 App_DebounceCounters[DEV_MAX] = {0};

u8 DisplayPage = 0;

void SoundFeedback(void){
    DIO_u8SetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_HIGH);
    _delay_ms(40);
    DIO_u8SetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_LOW);
}

void UpdateDeviceState(Device_t dev, u8 state){
    App_States[dev] = state;

    if (dev == DEV_DOOR){
        TIMER1_voidSetOCR1Value(state ? 2500 : 500);
        UART_voidSendString(state ? "DOOR:OPEN\r\n" : "DOOR:CLOSE\r\n");
    }else{
        DIO_u8SetPinValue(DeviceChannels[dev].outPort, DeviceChannels[dev].outPin, state ? DIO_HIGH : DIO_LOW);
        UART_voidSendString(DeviceChannels[dev].name);
        UART_voidSendString(state ? ":ON\r\n" : ":OFF\r\n");
    }
}

void APP_voidInit(void){
    DIO_u8SetPinDirection(BUZZER_PORT, BUZZER_PIN, DIO_OUTPUT);

    for (u8 i = 0; i < DEV_MAX; i++){
        DIO_u8SetPinDirection(DeviceChannels[i].outPort, DeviceChannels[i].outPin, DIO_OUTPUT);
        DIO_u8EnablePullUpResistor(DeviceChannels[i].inPort, DeviceChannels[i].inPin);
        u8 initVal = DIO_u8GetPinValue(DeviceChannels[i].inPort, DeviceChannels[i].inPin);
        App_PrevInputs[i] = initVal;
        UpdateDeviceState((Device_t)i, (initVal == DIO_LOW) ? 1 : 0);
    }
}

void Task_ControlProcessing(void){
    if (GET_BIT(UCSRA, 7) == 1){
        u8 recChar = UDR;
        Device_t targetDev = DEV_MAX;
        u8 newState = 0;

        switch (recChar){
            case '1': targetDev = DEV_L1;   newState = 1; break;
            case '2': targetDev = DEV_L1;   newState = 0; break;
            case '3': targetDev = DEV_L2;   newState = 1; break;
            case '4': targetDev = DEV_L2;   newState = 0; break;
            case '5': targetDev = DEV_L3;   newState = 1; break;
            case '6': targetDev = DEV_L3;   newState = 0; break;
            case '7': targetDev = DEV_L4;   newState = 1; break;
            case '8': targetDev = DEV_L4;   newState = 0; break;
            case 'A': targetDev = DEV_R1;   newState = 1; break;
            case 'a': targetDev = DEV_R1;   newState = 0; break;
            case 'B': targetDev = DEV_R2;   newState = 1; break;
            case 'b': targetDev = DEV_R2;   newState = 0; break;
            case 'F': targetDev = DEV_FAN;  newState = 1; break;
            case 'f': targetDev = DEV_FAN;  newState = 0; break;
            case 'O': targetDev = DEV_DOOR; newState = 1; break;
            case 'C': targetDev = DEV_DOOR; newState = 0; break;
            default: break;
        }

        if (targetDev != DEV_MAX){
            UpdateDeviceState(targetDev, newState);
            SoundFeedback();
        }
    }

    for (u8 i = 0; i < DEV_MAX; i++){
        u8 currVal = DIO_u8GetPinValue(DeviceChannels[i].inPort, DeviceChannels[i].inPin);

        if (currVal != App_PrevInputs[i]){
            App_DebounceCounters[i]++;

            if (App_DebounceCounters[i] >= 2){
                UpdateDeviceState((Device_t)i, App_States[i] ^ 1);
                SoundFeedback();

                App_PrevInputs[i] = currVal;
                App_DebounceCounters[i] = 0;
            }
        }else{
            App_DebounceCounters[i] = 0;
        }
    }
}

void Task_SystemDisplay(void){
    DisplayPage ^= 1;
    LCD_voidDisplayClear();
    LCD_u8GoToXy(0, 0);

    if (DisplayPage == 0){
        LCD_voidSendString((u8 *)"L1:"); LCD_voidSendString(App_States[DEV_L1] ? (u8 *)"ON " : (u8 *)"OFF");
        LCD_voidSendString((u8 *)" L2:"); LCD_voidSendString(App_States[DEV_L2] ? (u8 *)"ON " : (u8 *)"OFF");

        LCD_u8GoToXy(1, 0);
        LCD_voidSendString((u8 *)"L3:"); LCD_voidSendString(App_States[DEV_L3] ? (u8 *)"ON " : (u8 *)"OFF");
        LCD_voidSendString((u8 *)" L4:"); LCD_voidSendString(App_States[DEV_L4] ? (u8 *)"ON " : (u8 *)"OFF");
    }else{
        LCD_voidSendString((u8 *)"R1:"); LCD_voidSendString(App_States[DEV_R1] ? (u8 *)"ON " : (u8 *)"OFF");
        LCD_voidSendString((u8 *)" R2:"); LCD_voidSendString(App_States[DEV_R2] ? (u8 *)"ON " : (u8 *)"OFF");

        LCD_u8GoToXy(1, 0);
        LCD_voidSendString((u8 *)"FAN:"); LCD_voidSendString(App_States[DEV_FAN] ? (u8 *)"ON " : (u8 *)"OFF");
        LCD_voidSendString((u8 *)" DR:"); LCD_voidSendString(App_States[DEV_DOOR] ? (u8 *)"OPN" : (u8 *)"CLS");
    }
}