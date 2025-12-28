/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    GIE_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali
 *  Layer  : MCAL
 *  SWC    : GIE
 *
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_private.h"

/*--------------------------------------------------------------------------------------------------------------
 * Breif      : This Function used to enable General Interrupt Enable (GIE)
 * Parameters : Nothing
 * return     : Nothing
*/
void GIE_voidEnable (void)
{
	SET_BIT (SREG , SREG_I) ;
}
/*----------------------------------------------------------------------------------------------------------------
 * Breif      : This Function used to disable General Interrupt Enable (GIE)
 * Parameters : Nothing
 * return     : Nothing
*/
void GIE_voidDisable (void)
{
	CLR_BIT (SREG , SREG_I) ;
}