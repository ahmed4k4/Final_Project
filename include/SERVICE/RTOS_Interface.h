#ifndef INCLUDE_SERVICE_RTOS_INTERFACE_H_
#define INCLUDE_SERVICE_RTOS_INTERFACE_H_

void RTOS_voidInit(void);
void RTOS_voidInitArrayFunc(void);
void RTOS_voidCreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity, u16 Copy_u16FirstDelay, void(*pf)(void));
void RTOS_voidSchedular(void);

#endif /* INCLUDE_SERVICE_RTOS_INTERFACE_H_ */
