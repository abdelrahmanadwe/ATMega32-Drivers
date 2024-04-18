/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    GIE_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali
 *  Layer  : MCAL
 *  SWC    : GIE
 *
 */
#ifndef GIE_PRIVATE_H_
#define GIE_PRIVATE_H_

#define SREG			*((volatile u8*) 0X5F)	/* Status Register */
#define SREG_I			7					    /* Global Interrupt Enable Bit */

#endif /* GIE_PRIVATE_H_ */