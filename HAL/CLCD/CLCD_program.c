/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     CLCD_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : CLCD
 *
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_extrachar.h"


/***************************************************************************************/

/*

###########  8 Bits Mode                                 ###########  4 Bits Mode
 -------------                 ------------               -------------                 ------------  
 | ATmega32  |                 |   LCD    |               | ATmega32  |                 |   LCD    | 
 |           |                 |          |               |           |                 |          |
 |        PA7|---------------->|D7        |               | PA3 or PA7|---------------->|D7        |  
 |        PA6|---------------->|D6        |               | PA2 or PA6|---------------->|D6        |
 |        PA5|---------------->|D5        |               | PA1 or PA5|---------------->|D5        |
 |        PA4|---------------->|D4        |               | PA0 or PA4|---------------->|D4        |
 |        PA3|---------------->|D3        |               |           |                 |          |
 |        PA2|---------------->|D2        |               |        PC2|---------------->|E         |
 |        PA1|---------------->|D1        |               |        PC1|---------------->|RW        |
 |        PA0|---------------->|D0        |               |        PC0|---------------->|RS        |
 |           |                 |          |               |           |                 |          |
 |        PC2|---------------->|E         |               |           |                 |          |
 |        PC1|---------------->|RW        |               |           |                 |          |
 |        PC0|---------------->|RS        |               |           |                 |          |
 -----------                   ------------               -------------                 ------------
 */
/***************************************************************************************/


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function Apply initialization sequence for LCD module
 *                                                *------------------------------------------------------------------------*
 * Parameters : nothing
 * return     : nothing 
 */
void CLCD_voidInit          ( void )
{
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    8 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	
	#if CLCD_MODE == 8
	
		_delay_ms(50);       // must wait more than 30 ms befor any action (VDD rises to 4.5 v)
		
		DIO_enumSetPortDirection  (CLCD_DATA_PORT    , DIO_PORT_OUTPUT          );
		DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_OUTPUT );
		DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_OUTPUT );
		DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_OUTPUT );
		
		CLCD_voidSendCommand   (CLCD_HOME  );
		_delay_ms(10);
		
		CLCD_voidSendCommand   (EIGHT_BITS );
		_delay_ms(1);
		
		CLCD_voidSendCommand   (CLCD_DISPLAY_CURSOR );
		_delay_ms(1);
		
		CLCD_voidClearScreen ();
		
		CLCD_voidSendCommand   (CLCD_ENTRY_MODE );
		_delay_ms(1);
	
	 /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    4 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	 
	#elif CLCD_MODE == 4
	
		_delay_ms(50);       // maust wait more than 30 ms befor any action (VDD rises to 4.5 v)
		
		#if CLCD_DATA_NIBBLE == CLCD_HIGH_NIBBLE
		
			DIO_enumSetPinDirection   (CLCD_DATA_PORT , DIO_PIN4 , DIO_PIN_OUTPUT );
			DIO_enumSetPinDirection   (CLCD_DATA_PORT , DIO_PIN5 , DIO_PIN_OUTPUT );
			DIO_enumSetPinDirection   (CLCD_DATA_PORT , DIO_PIN6 , DIO_PIN_OUTPUT );
			DIO_enumSetPinDirection   (CLCD_DATA_PORT , DIO_PIN7 , DIO_PIN_OUTPUT );
			
		#elif CLCD_DATA_NIBBLE == CLCD_LOW_NIBBLE    
	
			DIO_enumSetPinDirection   (CLCD_DATA_PORT , DIO_PIN0 , DIO_PIN_OUTPUT );
			DIO_enumSetPinDirection   (CLCD_DATA_PORT , DIO_PIN1 , DIO_PIN_OUTPUT );
			DIO_enumSetPinDirection   (CLCD_DATA_PORT , DIO_PIN2 , DIO_PIN_OUTPUT );
			DIO_enumSetPinDirection   (CLCD_DATA_PORT , DIO_PIN3 , DIO_PIN_OUTPUT );
			
		#else
			
			#error "Wrong CLCD_DATA_NIBBLE Config"
			
		#endif
		
	
		DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_OUTPUT );
		DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_OUTPUT );
		DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_OUTPUT );
		
		CLCD_voidSendCommand   (CLCD_HOME  );
		_delay_ms(10);
		
		CLCD_voidSendCommand   (FOUR_BITS );
		_delay_ms(1);
		
		CLCD_voidSendCommand   (CLCD_DISPLAY_CURSOR );
		_delay_ms(1);
		
		CLCD_voidClearScreen ();
		
		CLCD_voidSendCommand   (CLCD_ENTRY_MODE );
		_delay_ms(1);
		
	#else
		
		#error "Wrong CLCD_MODE Config"
		
	#endif 
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function send data to the port which is defined in config.h
 *                                                *------------------------------------------------------------------------*
 * Parameters : 
 *		=> Copy_u8Data --> Data that you want to display (for every location )
 * return     : nothing 
 */
void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    8 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	
	#if CLCD_MODE == 8
	
		DIO_enumSetPortValue    (CLCD_DATA_PORT , Copy_u8Data                 );
		DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_HIGH   );
		DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW    );
		CLCD_voidSendFallingEdge();
	
	 /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    4 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	 
	#elif CLCD_MODE == 4
	
		DIO_enumSetPinValue (CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_HIGH );
		DIO_enumSetPinValue (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW );
		#if CLCD_DATA_NIBBLE == CLCD_HIGH_NIBBLE
		
			DIO_enumWriteHighNibbles(CLCD_DATA_PORT , (Copy_u8Data>>4) );    // send the most 4 bits of data to high nibbles
			CLCD_voidSendFallingEdge();                                
			DIO_enumWriteHighNibbles(CLCD_DATA_PORT , Copy_u8Data      );   // send the least 4 bits of data to high nibbles	
			CLCD_voidSendFallingEdge();             
			
		#elif CLCD_DATA_NIBBLE == CLCD_LOW_NIBBLE    
		
			DIO_enumWriteLowNibbles (CLCD_DATA_PORT , (Copy_u8Data>>4) );    // send the most 4 bits of data to low nibbles
			CLCD_voidSendFallingEdge();                                
			DIO_enumWriteLowNibbles (CLCD_DATA_PORT , Copy_u8Data      );   // send the least 4 bits of data to low nibbles	
			CLCD_voidSendFallingEdge();
			
		#else
			
			#error "Wrong CLCD_DATA_NIBBLE Config"
			
		#endif
		
	#else
		
		#error "Wrong CLCD_MODE Config"
		
	#endif 

}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                       This Function Interface to send the configuration commands to the LCD Driver
 *                                                *------------------------------------------------------------------------*
 * Parameters : 
 *		=> Copy_u8Command --> Command number
 * return     : nothing 
 */
void CLCD_voidSendCommand(u8 Copy_u8Command )
{
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    8 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	
	#if CLCD_MODE == 8
	
		DIO_enumSetPortValue    (CLCD_DATA_PORT , Copy_u8Command              );
		DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RS ,DIO_PIN_LOW     );
		DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW    );
		CLCD_voidSendFallingEdge();
	
	 /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    4 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	 
	#elif CLCD_MODE == 4
	
		DIO_enumSetPinValue (CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_LOW    );
		DIO_enumSetPinValue (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW    );
		
		#if CLCD_DATA_NIBBLE == CLCD_HIGH_NIBBLE
		
			DIO_enumWriteHighNibbles(CLCD_DATA_PORT , (Copy_u8Command>>4) );    // send the most 4 bits of data to high nibbles
			CLCD_voidSendFallingEdge();                                
			DIO_enumWriteHighNibbles(CLCD_DATA_PORT , Copy_u8Command      );   // send the least 4 bits of data to high nibbles	
			CLCD_voidSendFallingEdge();             
			
		#elif CLCD_DATA_NIBBLE == CLCD_LOW_NIBBLE    
		
			DIO_enumWriteLowNibbles (CLCD_DATA_PORT , (Copy_u8Command>>4) );    // send the most 4 bits of data to low nibbles
			CLCD_voidSendFallingEdge();                                
			DIO_enumWriteLowNibbles (CLCD_DATA_PORT , Copy_u8Command      );   // send the least 4 bits of data to low nibbles	
			CLCD_voidSendFallingEdge();
			
		#else
			
			#error "Wrong CLCD_DATA_NIBBLE Config"
			
		#endif
			
	#else
		
		#error "Wrong CLCD_MODE Config"
		
	#endif 

}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function send a pulse (falling edge ) to Enable Pin
 *                                                *-------------------------------------------------------------*
 * Parameters : nothing
 * return     : nothing 
 */

static void CLCD_voidSendFallingEdge (void)
{
	
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_HIGH );
	_delay_ms(1);
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_LOW  );
	_delay_ms(1);
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                     This Function clear LCD
 *                                                *-----------------------------------------------*
 * Parameters : nothing
 * return     : nothing 
 */
void CLCD_voidClearScreen ( void )
{
	
	CLCD_voidSendCommand  ( CLCD_ClEAR );
	_delay_ms(10); //wait more than 1.53 ms
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function send string to the port which is defined in config.h
 *                                                *------------------------------------------------------------------------*
 * Parameters :  
 *		=> Copy_u8ptrString  --> Pointer to the string
 * return     : nothing 
 */

void CLCD_voidSendString  (const u8 * Copy_u8PrtStrign )
{
	u8 LOC_u8Iterator = 0;
	while( Copy_u8PrtStrign[LOC_u8Iterator] != '\0' )
	{
		CLCD_voidSendData( Copy_u8PrtStrign[LOC_u8Iterator] );
		LOC_u8Iterator++ ;
	}
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function send  integer number to the port which is defined in config.h
 *                                                *----------------------------------------------------------------------------*
 * Parameters :  
 *		=> Copy_s32Number  --> Number that you want to display
 * return     : nothing 
 */

void CLCD_voidSendIntNumber(s32 Copy_s32Number)
{
	
	u32 LOC_u32Reverse = 1 ;
	
	if(Copy_s32Number == 0 )
	{
		CLCD_voidSendData( '0' );
	}
	else
	{
		if(Copy_s32Number<0)
		{
			CLCD_voidSendData( '-' );
			Copy_s32Number = (-1* Copy_s32Number);
		}
		while (Copy_s32Number != 0)
		{
			LOC_u32Reverse = (LOC_u32Reverse * 10 ) + (Copy_s32Number % 10);
			Copy_s32Number /= 10 ;
		}
		while (LOC_u32Reverse != 1)
		{
			CLCD_voidSendData( (LOC_u32Reverse % 10 ) + 48 );
			LOC_u32Reverse /= 10 ;
		}
		
	}
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function shift the entire display to the right cursor follows the display shift
 *                                                *------------------------------------------------------------------------------------*
 * Parameters : nothing
 * return     : nothing 
 */
void CLCD_voidShiftDisplayRight( void )
{
	CLCD_voidSendCommand(CLCD_SHIFT_DISPLAY_RIGHT);
	_delay_ms(1);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function shift the entire display to the left cursor follows the display shift
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : nothing
 * return     : nothing 
 */
void CLCD_voidShiftDisplayLeft( void )
{
	CLCD_voidSendCommand(CLCD_SHIFT_DISPLAY_LEFT);
	_delay_ms(1);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function shift the the cursor to the right
 *                                                *-------------------------------------------------*
 * Parameters : nothing
 * return     : nothing 
 */
void CLCD_voidShiftCursorRight (void )
{
	CLCD_voidSendCommand(CLCD_SHIFT_CURSOR_RIGHT);
	_delay_ms(1);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function shift the the cursor to the left
 *                                                *-------------------------------------------------*
 * Parameters : nothing
 * return     : nothing 
 */
void CLCD_voidShiftCursorLeft  (void )
{
	CLCD_voidSendCommand(CLCD_SHIFT_CURSOR_LEFT);
	_delay_ms(1);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function Set DDRAM address to (0x00) and Returns shifted display to its original position
 *                                                *----------------------------------------------------------------------------------------------*
 * Parameters : nothing
 * return     : nothing
 */
void CLCD_voidReturnHome( void )
{
	CLCD_voidSendCommand   (CLCD_HOME  );
	_delay_ms(10); //wait more than 1.53 ms
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function send  floating number to the port which is defined in config.h
 *                                                *----------------------------------------------------------------------------*
 * Parameters :  
 *		=> Copy_f64Number  --> Number that you want to display
 * return     : nothing 
 */

void CLCD_voidSendFloatNumber(f64 Copy_f64Number)
{
	CLCD_voidSendIntNumber   ( (s32) Copy_f64Number);
	if(Copy_f64Number < 0)
	{
		Copy_f64Number *= -1;
	}
	Copy_f64Number = (f64)Copy_f64Number - (s32)Copy_f64Number;

	if( Copy_f64Number != 0)
	{
		CLCD_voidSendData( '.' );
		for(u8 LOC_u8Iterator = 0; LOC_u8Iterator < NUMBER_OF_FRACTION_DIGITS ; LOC_u8Iterator++)
		{
			Copy_f64Number *=10;
			CLCD_voidSendIntNumber( (s32) Copy_f64Number);
			Copy_f64Number = (f64)Copy_f64Number - (s32)Copy_f64Number;
		}

	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function set the cursor position
 *                                                *-------------------------------------------*
 * Parameters :
 *       => Copy_u8Row --> row number (CLCD_ROW_1 or CLCD_ROW_2)
 *		 => Copy_u8Col --> column number (CLCD_COL_1 ... CLCD_COL_16)
 * return     : nothing
 *
 * Hint       :-
 *		In This function we send a command which =0b1xxxxxxx
 *		MSB = 1  ===> refers that it is command to set cursor
 *		xxxxxxx  ===> refers to AC ( Address Counter 7Bits / DDRAM Locations 128Location )
 */

void CLCD_voidSetPosition (u8 Copy_u8ROW , u8 Copy_u8Col )
{
	u8 LOC_u8Data ;
	
	if( (Copy_u8ROW < CLCD_ROW_1 ) || (Copy_u8ROW > CLCD_ROW_2 ) || (Copy_u8Col < CLCD_COL_1) || (Copy_u8Col > CLCD_COL_16 ) )
	{
		
		LOC_u8Data = CLCD_SET_CURSOR ;
		
	}
	else if(Copy_u8ROW == CLCD_ROW_1)
	{
		
		LOC_u8Data = ( ( CLCD_SET_CURSOR ) + ( Copy_u8Col - 1 ) );
	
	}
	else if(Copy_u8ROW == CLCD_ROW_2)
	{
		
		LOC_u8Data = ( ( CLCD_SET_CURSOR ) + (64) + ( Copy_u8Col - 1 ) );
		
	}
	
	CLCD_voidSendCommand  ( LOC_u8Data );
	_delay_ms(1);
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function send extra char
 *                                                *----------------------------------*
 * Parameters :
 *      => Copy_u8Row --> row number    (CLCD_ROW_1 or CLCD_ROW_2  )
 *		=> Copy_u8Col --> column number (CLCD_COL_1 ... CLCD_COL_16)
 * return     : nothing
 *
 * Hint       :-
 *	    Address Counter can refer to CGRAM and DDRAM
 */

void CLCD_voidSendExtraChar( u8 Copy_u8Row , u8 Copy_u8Col )
{

	u8 LOC_u8Iterator = 0 ;
	
	/* 1- Go To CGRAM            */
	CLCD_voidSendCommand( CLCD_CGRAM );  // Make AC refers to the first Place/Address at CGRAM


	/* 2- Draw Character in CGRAM        */
	/* Hint : it will be copied to DDRAM automatically */
	for( LOC_u8Iterator = 0 ; LOC_u8Iterator < (sizeof(CLCD_u8ExtraChar) / sizeof(CLCD_u8ExtraChar[0])) ; LOC_u8Iterator++)
	{

		CLCD_voidSendData( CLCD_u8ExtraChar[LOC_u8Iterator] );
		
	}


	/* 3- Back (AC) To DDRAM          */
	CLCD_voidSetPosition(Copy_u8Row,Copy_u8Col);


	/* 4- Send Character Address */
	for( LOC_u8Iterator = 0 ; LOC_u8Iterator < 8 ; LOC_u8Iterator++ )
	{

		CLCD_voidSendData( LOC_u8Iterator );
		
	}

}
