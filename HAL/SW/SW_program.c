/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     SW_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : SW
 *
 */
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SW_interface.h"


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                     This function initialize the Pin which connected to switch as input pin
 *                                                *-------------------------------------------------------------------------*
 * Parameters :  
		=> struct SW_Data:
			->	Port         [SW_PORTx](x=A..D)
			->  Pin          [SW_PINx] (x=0..7)
			-> Pull_State    [SW_INT_PUll_UP , SW_EXT_PUll_UP , SW_EXT_PUll_DOWN ]
			
 * return : void     
 */

void SW_voidInit (SW_Data SW_Config )
{
	
	DIO_enumSetPinDirection (SW_Config.Port , SW_Config.Pin , DIO_PIN_INPUT );
	
	if(SW_Config.Pull_State == SW_INT_PUll_UP)
	{
		DIO_enumSetPinValue     (SW_Config.Port , SW_Config.Pin , DIO_PIN_HIGH  );
		
		/*                            we can use
		 * DIO_voidConnectIntPullUp      (SW_Config.Port ,  SW_Config.Pin      ); */

	}
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                     This function read the switch state
 *                                                *-------------------------------------*
 * Parameters :  
		=> struct SW_Data:
			->	Port         [SW_PORTx](x=A..D)
			->  Pin          [SW_PINx] (x=0..7)
			-> Pull_State    [SW_INT_PUll_UP , SW_EXT_PUll_UP , SW_EXT_PUll_DOWN ]
			
 * return : Switch State     [SW_PRESSED , SW_NOT_PRESSED ]   
 */


u8 SW_u8GetPressed (SW_Data SW_Config )
{
	u8 LOC_u8Result = SW_NOT_PRESSED ;
	u8 LOC_u8PinVal ;
	
	if( (SW_Config.Pull_State == SW_INT_PUll_UP) || (SW_Config.Pull_State == SW_EXT_PUll_UP) )
	{
		
		DIO_enumGetPinValue (SW_Config.Port , SW_Config.Pin , & LOC_u8PinVal );
		
		if(LOC_u8PinVal == 0)
		{
			
			LOC_u8Result = SW_PRESSED    ;
			
		}
		else if(LOC_u8PinVal == 1)
		{
			
			LOC_u8Result = SW_NOT_PRESSED ;
			
		}
		
	}
	else if(SW_Config.Pull_State == SW_EXT_PUll_DOWN)
	{
		
		DIO_enumGetPinValue (SW_Config.Port , SW_Config.Pin , & LOC_u8PinVal );
		
		if(LOC_u8PinVal == 1)
		{
			
			LOC_u8Result = SW_PRESSED    ;
			
		}
		else if(LOC_u8PinVal == 0)
		{
			
			LOC_u8Result = SW_NOT_PRESSED ;
			
		}
		
	}
	
	return LOC_u8Result ;
	
}
