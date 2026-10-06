#include "../include/LIBs/STD_Types.h"
#include "../include/LIBs/BIT_Math.h"

#include "../include/SERVICE/RTOS_Interface.h"
#include "../include/SERVICE/RTOS_Private.h"
#include "../include/SERVICE/RTOS_Cfg.h"

RTO_TCB RTOS_ARRAY[RTOS_MAX_TASKS];

void RTOS_voidInit(void){
	TIMER0_voidSetCTCCallback(&RTOS_voidSchedular);
	TIMER0_voidInit();
}

void RTOS_voidInitArrayFunc(void){
	u8 Local_u8Counter;
	for(Local_u8Counter = 0; Local_u8Counter < RTOS_MAX_TASKS; Local_u8Counter++){
		RTOS_ARRAY[Local_u8Counter].pf = NULL_PTR;
	}
}

void RTOS_voidCreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity, u16 Copy_u16FirstDelay, void(*pf)(void)){
	if((Copy_u8Priority < RTOS_MAX_TASKS) && (pf != NULL_PTR)){
		RTOS_ARRAY[Copy_u8Priority].FirstDelay = Copy_u16FirstDelay;
		RTOS_ARRAY[Copy_u8Priority].Periodicity = Copy_u16Periodicity;
		RTOS_ARRAY[Copy_u8Priority].pf = pf;
	}
}

void RTOS_voidSchedular(void){
	u8 Local_u8Counter;
	for(Local_u8Counter = 0; Local_u8Counter < RTOS_MAX_TASKS; Local_u8Counter++){
		if(RTOS_ARRAY[Local_u8Counter].FirstDelay == 0){
			if(RTOS_ARRAY[Local_u8Counter].pf != NULL_PTR){
				RTOS_ARRAY[Local_u8Counter].pf();
			}
			RTOS_ARRAY[Local_u8Counter].FirstDelay = RTOS_ARRAY[Local_u8Counter].Periodicity - 1;
		}else{
			RTOS_ARRAY[Local_u8Counter].FirstDelay--;
		}
	}
}