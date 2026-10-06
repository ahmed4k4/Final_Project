#ifndef INCLUDE_SERVICE_RTOS_PRIVATE_H_
#define INCLUDE_SERVICE_RTOS_PRIVATE_H_

typedef struct{
	u16 FirstDelay;
	u16 Periodicity;
	void(*pf)(void);
}RTO_TCB;

#endif /* INCLUDE_SERVICE_RTOS_PRIVATE_H_ */
