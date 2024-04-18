/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     LM35_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : LM35
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "ADC_interface.h"

#include "LM35_interface.h"
#include "LM35_private.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
*                                     This Function initialize the pin which connected to led as output pin
*                                  ------------------------------------------------------------------------
* Parameters :
            => struct 
				=>LM35Channel -> [0...31]
				=>ADCVoltageReference : [AREF , AVCC , INTERNAL_2_56 ]
				
			=> Pointer to TEMP Variable which will return in it 
			
* return : Error State with type u8
*/
u8 LM35_u8GetTemp (LM35_CONFIG * lm35 , u8 * Copy_u8TempValue)
{
	
	u8 Local_u8ErrorState =  OK ;
	
	u16 Local_u16ADCResult ;
	u16 Local_u16AnalogValue ;
	
	u16 Local_u8ADCReference = ( lm35->ADCVoltageReference ) * 1000 ;  // To Convert from ( V --> mV )
	
	/* ADC Digital Reading  */
	Local_u8ErrorState = ADC_u8GetResultSync( lm35->LM35Channel , &Local_u16ADCResult ) ;

	/* Check for ADC Resolution  */
	
	Local_u16AnalogValue = (u16) ( ((u32)Local_u16ADCResult * (u32)Local_u8ADCReference ) / 1024UL) ;

	/* Convert ( mv --> Temp ) */
	* Copy_u8TempValue = Local_u16AnalogValue / 10 ;
	return Local_u8ErrorState;

}