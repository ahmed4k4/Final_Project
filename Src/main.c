#include "../include/LIBs/STD_Types.h"
#include "../include/MCAL/UART/UART_Interface.h"
#include "../include/MCAL/TIMER/TIMER_Interface.h"
#include "../include/HAL/LCD/LCD_Interface.h"
#include "../include/MCAL/EXTI/EXTI_Interface.h"
#include "../include/SERVICE/RTOS_Interface.h"
#include "../include/APP/APP_Interface.h"

int main(void){
    UART_Init();
    LCD_voidInit();
    TIMER1_voidInit();
    APP_voidInit();

    GI_voidEnable();

    RTOS_voidInitArrayFunc();
    RTOS_voidCreateTask(0, 50, 0, Task_ControlProcessing);
    RTOS_voidCreateTask(1, 1000, 0, Task_SystemDisplay);
    RTOS_voidInit();

    while (1)
    {
    }

    return 0;
}
