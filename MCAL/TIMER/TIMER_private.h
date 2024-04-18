/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     TIMER_private.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : TIMER
 *
 */
 

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_


#define TIMSK			*((volatile u8*)0X59)
/*TIMSK bits*/
#define TIMSK_TOIE0		0
#define TIMSK_OCIE0		1
#define TIMSK_TOIE1		2
#define TIMSK_OCIE1B	3
#define TIMSK_OCIE1A	4
#define TIMSK_TICIE1	5
#define TIMSK_TOIE2		6
#define TIMSK_OCIE2		7


#define TIFR			*((volatile u8*)0X58)
/*TIFR bits*/
#define TIFR_TOV0		0
#define TIFR_OCF0		1
#define TIFR_TOV1		2
#define TIFR_OCF1B		3
#define TIFR_OCF1A		4
#define TIFR_ICF1		5
#define TIFR_TOV2		6
#define TIFR_OCV2		7


/*Timer0 registers*/
#define TCCR0			*((volatile u8*)0X53)
#define TCNT0			*((volatile u8*)0X52)
#define OCR0			*((volatile u8*)0X5C)

/*Timer0 bits*/
#define TCCR0_FOC0      7
#define TCCR0_WGM00		6
#define TCCR0_COM01		5
#define TCCR0_COM00		4
#define TCCR0_WGM01		3
#define TCCR0_CS02      2
#define TCCR0_CS01		1
#define TCCR0_CS00		0


/*Timer1*/
#define TCCR1A			*((volatile u8 *)0X4F)
#define TCCR1B			*((volatile u8 *)0X4E)
#define TCNT1H          *((volatile u8 *)0x4D)
#define TCNT1L          *((volatile u8 *)0x4C)
#define TCNT1			*((volatile u16*)0X4C)    /* u16 for HIGH & LOW */
#define OCR1AL          *((volatile u8 *)0x4A)
#define OCR1AH          *((volatile u8 *)0x4B)
#define OCR1A			*((volatile u16*)0X4A)    /* u16 for HIGH & LOW */
#define OCR1BL          *((volatile u8 *)0x48)
#define OCR1BH          *((volatile u8 *)0x49)
#define OCR1B			*((volatile u16*)0X48)    /* u16 for HIGH & LOW */
#define ICR1H           *((volatile u8 *)0x47)
#define ICR1L           *((volatile u8 *)0x46)
#define ICR1			*((volatile u16*)0X46)    /* u16 for HIGH & LOW */

/*Timer1 bits*/
#define TCCR1A_COM1A1		7
#define TCCR1A_COM1A0		6
#define TCCR1A_COM1B1		5
#define TCCR1A_COM1B0		4
#define TCCR1A_WGM11		1
#define TCCR1A_WGM10		0

#define TCCR1B_ICNC1		7
#define TCCR1B_ICES1		6
#define TCCR1B_WGM13		4
#define TCCR1B_WGM12		3

/*Timer2*/
#define TCCR2			*((volatile u8*)0X45)
#define TCNT2			*((volatile u8*)0X44)
#define TCNT2			*((volatile u8*)0X44)
#define OCR2			*((volatile u8*)0X43)



/*Timer2 bits*/
#define TCCR2_WGM20		6
#define TCCR2_COM21		5
#define TCCR2_COM20		4
#define TCCR2_WGM21		3

#define WDTCR           *((volatile u8*)0x41)
/* WDTCR Bits */
#define		WDTCR_WDTOE 			4
#define		WDTCR_WDE				3
#define		WDTCR_WDP2				2
#define		WDTCR_WDP1				1
#define		WDTCR_WDP0				0

#define TIMER_PRESCALER_MASK					        0b11111000 /* This Value also could use for bit masking */

#endif /* TIMER_PRIVATE_H_ */