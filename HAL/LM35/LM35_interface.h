/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     LM35_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : LM35
 *
 */

#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

typedef struct
{
	u8 LM35Channel ;
	u8 ADCVoltageReference ;       /* [AREF , AVCC , INTERNAL_2_56 ]  */
          
} LM35_CONFIG ;
	
u8 LM35_u8GetTemp (LM35_CONFIG * lm35 , u8 * Copy_u8TempValue) ;

#endif