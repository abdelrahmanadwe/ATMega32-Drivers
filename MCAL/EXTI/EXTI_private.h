/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      EXTI_private.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : EXTI
 *
 */
 
#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define MCUCR_REG   *((volatile u8 *)0x55)
#define MCUCSR_REG  *((volatile u8 *)0x54)
#define GICR_REG    *((volatile u8 *)0x5B)
#define GIFR_REG    *((volatile u8 *)0x5A)

#ifndef NULL

#define NULL 0
 
#endif 


#endif /* EXTI_PRIVATE_H_ */
