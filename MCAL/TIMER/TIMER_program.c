/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     TIMER_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : TIMER
 *
 */
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h" /*You have to include TIMER_private.h before TIMER_config.h*/
#include "TIMER_config.h"


/*Global Pointer to array of Function to Hold the Call Back Function Address for Timer*/
static void (*TIMERS_pvCallBackFunc[8])(void) = {NULL} ;  /* we have 8 interrupt sources in timer  */

 /*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function Init the TIMER0 ( Prebuild Function)
 *                                                *-----------------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing  
 */
void TIMER0_voidInit(void)
{
	/*Set Configurable Modes*/
	#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

		/*Initialize Waveform Generation Mode as Normal Mode*/
		
		CLR_BIT(TCCR0 , TCCR0_WGM01) ; CLR_BIT(TCCR0 , TCCR0_WGM00) ;

		/*Set the Required Preload Value*/
		TCNT0 = TIMER0_PRELOAD_VAL ;

		/*Timer0 Overflow Interrupt Enable*/
		#if TIMER0_OVERFLOW_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_TOIE0) ;
			
		#elif TIMER0_OVERFLOW_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_TOIE0) ;
			
		#else
			
			#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
			
		#endif
		
	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE
		/*Initialize Waveform Generation Mode as PWM Mode*/
		
		CLR_BIT(TCCR0 , TCCR0_WGM01) ; SET_BIT(TCCR0 , TCCR0_WGM00) ;

		/*Set CTC PWM MODE*/
		#if TIMER0_OC0_PWM_MODE == TIMER_OC_DISCONNECTED
				
			CLR_BIT(TCCR0 , TCCR0_COM01) ; CLR_BIT(TCCR0 , TCCR0_COM00) ;
				
		#elif TIMER0_OC0_PWM_MODE == TIMER_CLR_ON_UP_SET_ON_DOWN
				
			SET_BIT(TCCR0 , TCCR0_COM01) ; CLR_BIT(TCCR0 , TCCR0_COM00) ;
				
		#elif TIMER0_OC0_PWM_MODE == TIMER_SET_ON_UP_CLR_ON_DOWN
				
			SET_BIT(TCCR0 , TCCR0_COM01) ; SET_BIT(TCCR0 , TCCR0_COM00) ;
				
		#else
			
			#error "Wrong TIMER0_CTC_PWM_MODE Config"

		#endif

		/*Set the Required CTC Value*/
		OCR0 = TIMER0_CTC_VAL ;

	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

		/*Initialize Waveform Generation Mode as CTC Mode*/
		
		SET_BIT(TCCR0 , TCCR0_WGM01) ; CLR_BIT(TCCR0 , TCCR0_WGM00) ;

		/*Set the Required CTC Value*/
		OCR0 = TIMER0_CTC_VAL ;

		/*Timer0 Compare Match Interrupt Enable*/
		#if TIMER0_CTC_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_OCIE0) ;
			
		#elif TIMER0_CTC_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_OCIE0) ;
			
		#else
			
			#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
			
		#endif
		
	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE

		/*Initialize Waveform Generation Mode as Fast PWM Mode*/
		
		SET_BIT(TCCR0 , TCCR0_WGM01) ; SET_BIT(TCCR0 , TCCR0_WGM00) ;

		/*Set OC0 Fast PWM MODE*/
		#if TIMER0_OC0_FAST_PWM_MODE == TIMER_OC_DISCONNECTED
		
			CLR_BIT(TCCR0 , TCCR0_COM01) ; CLR_BIT(TCCR0 , TCCR0_COM00) ;
				
		#elif TIMER0_OC0_FAST_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
		
			SET_BIT(TCCR0 , TCCR0_COM01) ; CLR_BIT(TCCR0 , TCCR0_COM00) ;
			
		#elif TIMER0_OC0_FAST_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
				
			SET_BIT(TCCR0 , TCCR0_COM01) ; SET_BIT(TCCR0 , TCCR0_COM00) ;
				
		#else
			
			#error "Wrong TIMER0_CTC_PWM_MODE Config"
				
		#endif

		/*Set the Required CTC Value*/
		OCR0 = TIMER0_CTC_VAL ;

	#else
		
		#error "Wrong TIMER0_WAVEFORM_GENERATION_MODE Config"

	#endif
	
	#if TIMER0_PRESCALER <= TIMER0_T0_EXTERNAL_CLOCK_SOURCE_RISING
	
		/*Set the Required Prescaler*/
		TCCR0 &= TIMER_PRESCALER_MASK ;
		TCCR0 |= TIMER0_PRESCALER ;
	
	#else 
		
		#error "Wrong TIMER0_PRESCALER Config"
		
	#endif
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function Init the TIMER1 ( Prebuild Function)
 *                                                *-----------------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing  
 */
void TIMER1_voidInit(void)
{

	/*Set Configurable Modes*/

	#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE

		/*Set Waveform generation mode as Normal mode */
		CLR_BIT(TCCR1B,TCCR1B_WGM13);  CLR_BIT(TCCR1B,TCCR1B_WGM12);  CLR_BIT(TCCR1A,TCCR1A_WGM11);  CLR_BIT(TCCR1A,TCCR1A_WGM10);
		
		/*Set the require Preload Value*/
		TCNT1 = TIMER1_PRELOAD_VAL ;

		/*Timer1 Overflow Interrupt Enable*/
		#if TIMER1_OVERFLOW_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_TOIE1) ;
			
		#elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_TOIE1) ;
			
		#else
			
			#error "Wrong TIMER1_OVERFLOW_INTERRUPT Config"
			
		#endif

	#elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE)

		/*Set Waveform generation mode as CTC modes */
		#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE
		
			SET_BIT(TCCR1B,TCCR1B_WGM13); SET_BIT(TCCR1B,TCCR1B_WGM12); CLR_BIT(TCCR1A,TCCR1A_WGM11); CLR_BIT(TCCR1A,TCCR1A_WGM10);
			
			/*Set ICR1*/
			ICR1 = TIMER1_ICR1_VAL ;
			
		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE
		
			CLR_BIT(TCCR1B,TCCR1B_WGM13); SET_BIT(TCCR1B,TCCR1B_WGM12); CLR_BIT(TCCR1A,TCCR1A_WGM11); CLR_BIT(TCCR1A,TCCR1A_WGM10);
			
		#endif

		/*Set the require CTC Values*/
		OCR1A = TIMER1_CTCA_VAL ;
		OCR1B = TIMER1_CTCB_VAL ;

		/*Set OCR1A mode*/
		#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
			
			CLR_BIT(TCCR1A , TCCR1A_COM1A1) ; CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
			
		#elif TIMER1_OCR1A_MODE == TIMER_OC_TOGGEL
			
			CLR_BIT(TCCR1A , TCCR1A_COM1A1) ; SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
			
		#elif TIMER1_OCR1A_MODE == TIMER_OC_LOW
			
			SET_BIT(TCCR1A , TCCR1A_COM1A1) ; CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
			
		#elif TIMER1_OCR1A_MODE == TIMER_OC_HIGH
			
			SET_BIT(TCCR1A , TCCR1A_COM1A1) ; SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
			
		#else
			
			#error "Wrong TIMER1_OCR1A_MODE Config"
			
		#endif

		/*Set OCR1B mode*/
		#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
			
			CLR_BIT(TCCR1A , TCCR1A_COM1B1) ; CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
			
		#elif TIMER1_OCR1B_MODE == TIMER_OC_TOGGEL
			
			CLR_BIT(TCCR1A , TCCR1A_COM1B1) ; SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
			
		#elif TIMER1_OCR1B_MODE == TIMER_OC_LOW
			
			SET_BIT(TCCR1A , TCCR1A_COM1B1) ; CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
			
		#elif TIMER1_OCR1B_MODE == TIMER_OC_HIGH
			
			SET_BIT(TCCR1A , TCCR1A_COM1B1) ; SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
			
		#else
			
			#error "Wrong TIMER1_OCR1B_MODE Config"
			
		#endif

		/*Timer1 CTC Interrupt Enable*/
		#if TIMER1_CTCA_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
			
		#elif TIMER1_CTCA_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_OCIE1A) ;
			
		#else
			
			#error "Wrong TIMER1_CTCA_INTERRUPT Config"
			
		#endif

		#if TIMER1_CTCB_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
			
		#elif TIMER1_CTCB_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_OCIE1B) ;
			
		#else
			
			#error "Wrong TIMER1_CTCB_INTERRUPT Config"
			
		#endif

	#elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE) ||(TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8_BIT_MODE)

		/*Set Waveform generation mode as PWM modes */
		#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE
		
			SET_BIT(TCCR1B,TCCR1B_WGM13); CLR_BIT(TCCR1B,TCCR1B_WGM12); SET_BIT(TCCR1A,TCCR1A_WGM11); SET_BIT(TCCR1A,TCCR1A_WGM10);
			
		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE
		
			CLR_BIT(TCCR1B,TCCR1B_WGM13); CLR_BIT(TCCR1B,TCCR1B_WGM12); SET_BIT(TCCR1A,TCCR1A_WGM11); CLR_BIT(TCCR1A,TCCR1A_WGM10);
			
		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE
		
			SET_BIT(TCCR1B,TCCR1B_WGM13); CLR_BIT(TCCR1B,TCCR1B_WGM12); CLR_BIT(TCCR1A,TCCR1A_WGM11); SET_BIT(TCCR1A,TCCR1A_WGM10);

		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE
			
			SET_BIT(TCCR1B,TCCR1B_WGM13); CLR_BIT(TCCR1B,TCCR1B_WGM12); CLR_BIT(TCCR1A,TCCR1A_WGM11); CLR_BIT(TCCR1A,TCCR1A_WGM10);
			
		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10_BIT_MODE
		
			CLR_BIT(TCCR1B,TCCR1B_WGM13); CLR_BIT(TCCR1B,TCCR1B_WGM12); SET_BIT(TCCR1A,TCCR1A_WGM11); SET_BIT(TCCR1A,TCCR1A_WGM10);
			
		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9_BIT_MODE
		
			CLR_BIT(TCCR1B,TCCR1B_WGM13); CLR_BIT(TCCR1B,TCCR1B_WGM12); SET_BIT(TCCR1A,TCCR1A_WGM11); CLR_BIT(TCCR1A,TCCR1A_WGM10);
			
		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8_BIT_MODE
		
			CLR_BIT(TCCR1B,TCCR1B_WGM13); CLR_BIT(TCCR1B,TCCR1B_WGM12); CLR_BIT(TCCR1A,TCCR1A_WGM11); SET_BIT(TCCR1A,TCCR1A_WGM10); 
			
		#else
			
			#error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
			
		#endif

		/*Set the require CTC Values*/
		OCR1A = TIMER1_CTCA_VAL ;
		OCR1B = TIMER1_CTCB_VAL ;

		/*Set ICR1*/
		#if ((TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE))
			
			ICR1 = TIMER1_ICR1_VAL ;
		
		#endif

		/*Set OCR1A mode*/
		#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
			
			CLR_BIT(TCCR1A , TCCR1A_COM1A1) ; CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
			
		#elif TIMER1_OCR1A_MODE == TIMER_CLR_ON_UP_SET_ON_DOWN
			
			SET_BIT(TCCR1A , TCCR1A_COM1A1) ; CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
			
		#elif TIMER1_OCR1A_MODE == TIMER_SET_ON_UP_CLR_ON_DOWN
			
			SET_BIT(TCCR1A , TCCR1A_COM1A1) ; SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
			
		#else
			
			#error "Wrong TIMER1_OCR1A_MODE Config"
			
		#endif

		/*Set OCR1B mode*/
		#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
			
			CLR_BIT(TCCR1A , TCCR1A_COM1B1) ; CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
			
		#elif TIMER1_OCR1B_MODE == TIMER_CLR_ON_UP_SET_ON_DOWN
			
			SET_BIT(TCCR1A , TCCR1A_COM1B1) ; CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
			
		#elif TIMER1_OCR1B_MODE == TIMER_SET_ON_UP_CLR_ON_DOWN
			
			SET_BIT(TCCR1A , TCCR1A_COM1B1) ; SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
			
		#else
			
			#error "Wrong TIMER1_OCR1B_MODE Config"
		
		#endif

		/*Timer1 PWM Interrupt Enable*/
		#if TIMER1_OVERFLOW_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_TOIE1) ;
			
		#elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_TOIE1) ;
			
		#else
			
			#error "Wrong TIMER1_OVERFLOW_INTERRUPT Config"
		
		#endif

		#if TIMER1_CTCA_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
			
		#elif TIMER1_CTCA_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_OCIE1A) ;
			
		#else
			
			#error "Wrong TIMER1_CTCA_INTERRUPT Config"
		
		#endif

		#if TIMER1_CTCB_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
			
		#elif TIMER1_CTCB_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_OCIE1B) ;
			
		#else
			
			#error "Wrong TIMER1_CTCB_INTERRUPT Config"
		
		#endif
		

	#elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8_BIT_MODE)

		/*Set Waveform generation mode as PWM modes */
		#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE
		
			SET_BIT(TCCR1B,TCCR1B_WGM13); SET_BIT(TCCR1B,TCCR1B_WGM12); SET_BIT(TCCR1A,TCCR1A_WGM11); SET_BIT(TCCR1A,TCCR1A_WGM10);
					
		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE
		
			SET_BIT(TCCR1B,TCCR1B_WGM13); SET_BIT(TCCR1B,TCCR1B_WGM12); SET_BIT(TCCR1A,TCCR1A_WGM11); CLR_BIT(TCCR1A,TCCR1A_WGM10);
			
		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10_BIT_MODE
		
			CLR_BIT(TCCR1B,TCCR1B_WGM13); SET_BIT(TCCR1B,TCCR1B_WGM12); SET_BIT(TCCR1A,TCCR1A_WGM11); SET_BIT(TCCR1A,TCCR1A_WGM10);
			
		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9_BIT_MODE
		
			CLR_BIT(TCCR1B,TCCR1B_WGM13); SET_BIT(TCCR1B,TCCR1B_WGM12); SET_BIT(TCCR1A,TCCR1A_WGM11); CLR_BIT(TCCR1A,TCCR1A_WGM10);
			
		#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8_BIT_MODE
		
			CLR_BIT(TCCR1B,TCCR1B_WGM13); SET_BIT(TCCR1B,TCCR1B_WGM12); CLR_BIT(TCCR1A,TCCR1A_WGM11); SET_BIT(TCCR1A,TCCR1A_WGM10);
			
		#else
			
			#error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
			
		#endif

		/*Set the require CTC Values*/
		OCR1A = TIMER1_CTCA_VAL ;
		OCR1B = TIMER1_CTCB_VAL ;

		/*Set ICR1*/
		#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE
		
			ICR1 = TIMER1_ICR1_VAL ;
		
		#endif

		/*Set OCR1A mode*/
		#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
			
			CLR_BIT(TCCR1A , TCCR1A_COM1A1) ; CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
			
		#elif TIMER1_OCR1A_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
			
			SET_BIT(TCCR1A , TCCR1A_COM1A1) ; CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
			
		#elif TIMER1_OCR1A_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
			
			SET_BIT(TCCR1A , TCCR1A_COM1A1) ; SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
			
		#else
			
			#error "Wrong TIMER1_OCR1A_MODE Config"
			
		#endif

		/*Set OCR1B mode*/
		#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
			
			CLR_BIT(TCCR1A , TCCR1A_COM1B1) ; CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
			
		#elif TIMER1_OCR1B_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
			
			SET_BIT(TCCR1A , TCCR1A_COM1B1) ; CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
			
		#elif TIMER1_OCR1B_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
			
			SET_BIT(TCCR1A , TCCR1A_COM1B1) ; SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
			
		#else
			
			#error "Wrong TIMER1_OCR1B_MODE Config"
		
		#endif

		/*Timer1 PWM Interrupt Enable*/
		#if TIMER1_OVERFLOW_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_TOIE1);
			
		#elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_TOIE1);
			
		#else
			
			#error "Wrong TIMER1_OVERFLOW_INTERRUPT Config"
			
		#endif

		#if TIMER1_CTCA_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
			
		#elif TIMER1_CTCA_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_OCIE1A) ;
			
		#else
			
			#error "Wrong TIMER1_CTCA_INTERRUPT Config"
			
		#endif

		#if TIMER1_CTCB_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
			
		#elif TIMER1_CTCB_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_OCIE1B) ;
			
		#else
			
			#error "Wrong TIMER1_CTCB_INTERRUPT Config"
			
		#endif

	#else
		
		#error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
		
	#endif
	
	#if TIMER1_PRESCALER <= TIMER1_T1_EXTERNAL_CLOCK_SOURCE_RISING
	
		/*Set the Required Prescaler*/
		TCCR1B &= TIMER_PRESCALER_MASK ;
		TCCR1B |= TIMER1_PRESCALER ;
		
	#else 
		
		#error "Wrong TIMER1_PRESCALER Config"
		
	#endif
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function Init the TIMER2 ( Prebuild Function)
 *                                                *-----------------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing  
 */
void TIMER2_voidInit(void)
{
	/*Set Configurable Modes*/
	#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

		/*Initialize Waveform Generation Mode as Normal Mode*/
		
		CLR_BIT(TCCR2 , TCCR2_WGM21) ; CLR_BIT(TCCR2 , TCCR2_WGM20) ;

		/*Set the Required Preload Value*/
		TCNT2 = TIMER2_PRELOAD_VAL ;

		/*Timer2 Overflow Interrupt Enable*/
		#if TIMER2_OVERFLOW_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_TOIE2) ;
			
		#elif TIMER2_OVERFLOW_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_TOIE2) ;
			
		#else
			
			#error "Wrong TIMER2_OVERFLOW_INTERRUPT Config"
		
		#endif
		
	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE
		/*Initialize Waveform Generation Mode as PWM Mode*/
		
		CLR_BIT(TCCR2 , TCCR2_WGM21) ; SET_BIT(TCCR2 , TCCR2_WGM20) ;

		/*Set OC2 PWM MODE*/
		#if TIMER2_OC2_PWM_MODE == TIMER_OC_DISCONNECTED
				
			CLR_BIT(TCCR2 , TCCR2_COM21) ; CLR_BIT(TCCR2 , TCCR2_COM20) ;
				
		#elif TIMER2_OC2_PWM_MODE == TIMER_CLR_ON_UP_SET_ON_DOWN
				
			SET_BIT(TCCR2 , TCCR2_COM21) ; CLR_BIT(TCCR2 , TCCR2_COM20) ;
				
		#elif TIMER2_OC2_PWM_MODE == TIMER_SET_ON_UP_CLR_ON_DOWN
				
			SET_BIT(TCCR2 , TCCR2_COM21) ; SET_BIT(TCCR2 , TCCR2_COM20) ;
				
		#else
			
			#error "Wrong TIMER2_CTC_PWM_MODE Config"
				
		#endif

		/*Set the Required CTC Value*/
		OCR2 = TIMER2_CTC_VAL ;

	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

		/*Initialize Waveform Generation Mode as CTC Mode*/
		
		SET_BIT(TCCR2 , TCCR2_WGM21) ; CLR_BIT(TCCR2 , TCCR2_WGM20) ;

		/*Set the Required CTC Value*/
		OCR2 = TIMER2_CTC_VAL ;

		/*Timer2 Compare Match Interrupt Enable*/
		#if TIMER2_CTC_INTERRUPT == DISABLE
		
			CLR_BIT(TIMSK , TIMSK_OCIE2) ;
			
		#elif TIMER2_CTC_INTERRUPT == ENABLE
		
			SET_BIT(TIMSK , TIMSK_OCIE2) ;
			
		#else
			
			#error "Wrong TIMER2_OVERFLOW_INTERRUPT Config"
			
		#endif
		
	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE

		/*Initialize Waveform Generation Mode as Fast PWM Mode*/
		
		SET_BIT(TCCR2 , TCCR2_WGM21) ; SET_BIT(TCCR2 , TCCR2_WGM20) ;

		/*Set CTC Fast PWM MODE*/
		#if TIMER2_OC2_FAST_PWM_MODE == TIMER_OC_DISCONNECTED
				
			CLR_BIT(TCCR2 , TCCR2_COM21) ; CLR_BIT(TCCR2 , TCCR2_COM20) ;
			
		#elif TIMER2_OC2_FAST_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
				
			SET_BIT(TCCR2 , TCCR2_COM21) ; CLR_BIT(TCCR2 , TCCR2_COM20) ;
				
		#elif TIMER2_OC2_FAST_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
				
			SET_BIT(TCCR2 , TCCR2_COM21) ; SET_BIT(TCCR2 , TCCR2_COM20) ;
				
		#else
			
			#error "Wrong TIMER2_CTC_PWM_MODE Config"
				
		#endif

		/*Set the Required CTC Value*/
		OCR2 = TIMER2_CTC_VAL ;

	#else
		
		#error "Wrong TIMER2_WAVEFORM_GENERATION_MODE Config"

	#endif
	
	#if TIMER2_PRESCALER <= TIMER2_DIVISION_FACTOR_1024
	
		/*Set the Required Prescaler*/
		TCCR2 &= TIMER_PRESCALER_MASK ;
		TCCR2 |= TIMER2_PRESCALER ;
		
	#else 
		
		#error "Wrong TIMER2_PRESCALER Config"
		
	#endif
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Preload value in TCNT0 register 
 *                                                *--------------------------------------------------------*
 * Parameters : 
 *		Copy_u8Preload => the value to be set in TCNT0 
 *		
 * return     : Nothing 
 */
void TIMER0_voidSetPreload (u8 Copy_u8Preload)
{
	TCNT0 = Copy_u8Preload ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Preload value in TCNT1 register 
 *                                                *--------------------------------------------------------*
 * Parameters : 
 *		Copy_u8Preload => the value to be set in TCNT1 
 *		
 * return     : Nothing 
 */
void TIMER1_voidSetPreload (u16 Copy_u16Preload)
{
	TCNT1 = Copy_u16Preload ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Preload value in TCNT2 register 
 *                                                *--------------------------------------------------------*
 * Parameters : 
 *		Copy_u8Preload => the value to be set in TCNT2 
 *		
 * return     : Nothing 
 */
void TIMER2_voidSetPreload (u8 Copy_u8Preload)
{
	TCNT2 = Copy_u8Preload ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the required value in OCR0 register 
 *                                                *-------------------------------------------------------*
 * Parameters : 
 *		Copy_u8CTC => the value to be set in OCR0 
 *		
 * return     : Nothing 
 */
void TIMER0_voidSetCTC (u8 Copy_u8CTC)
{
	OCR0 = Copy_u8CTC ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the required value in OCR1A register 
 *                                                *-------------------------------------------------------*
 * Parameters : 
 *		Copy_u16CTCA => the value to be set in OCR1A 
 *		
 * return     : Nothing 
 */
void TIMER1_voidSetCTCA (u16 Copy_u16CTCA)
{
	OCR1A = Copy_u16CTCA ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the required value in OCR1B register 
 *                                                *-------------------------------------------------------*
 * Parameters : 
 *		Copy_u16CTCB => the value to be set in OCR1B 
 *		
 * return     : Nothing 
 */
void TIMER1_voidSetCTCB (u16 Copy_u16CTCB)
{
	OCR1B = Copy_u16CTCB ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the required value in OCR2 register 
 *                                                *-----------------------------------------------------*
 * Parameters : 
 *		Copy_u8CTC => the value to be set in OCR2 
 *		
 * return     : Nothing 
 */
void TIMER2_voidSetCTC (u8 Copy_u8CTC)
{
	OCR2 = Copy_u8CTC ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to get the value of the TCNT0 register 
 *                                                *----------------------------------------------------*
 * Parameters : Nothing
 *		 
 * return     : the value of the TCNT0 register 
 */
u8 TIMER0_u8GetTimerCounterValue (void)
{
	return TCNT0 ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to get the value of the TCNT2 register 
 *                                                *----------------------------------------------------*
 * Parameters : Nothing
 *		 
 * return     : the value of the TCNT2 register 
 */
u8 TIMER2_u8GetTimerCounterValue (void)
{
	return TCNT2 ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to get the value of the TCNT1 register 
 *                                                *----------------------------------------------------*
 * Parameters : Nothing
 *		 
 * return     : the value of the TCNT1 register 
 */
u16 TIMER1_u16GetTimerCounterValue (void)
{
	return TCNT1 ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the waveform generation mode of TIMER0 using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8WaveMode => [TIMER_NORMAL_MODE , TIMER_PWM_MODE , TIMER_CTC_MODE , TIMER_FAST_PWM_MODE]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER0_u8SetWaveFormMode    (u8 Copy_u8WaveMode)
{
	u8 Local_u8ErrorStatus = OK ;
	
	switch(Copy_u8WaveMode)
	{
		case TIMER_NORMAL_MODE : 
		
			CLR_BIT(TCCR0 , TCCR0_WGM01) ; CLR_BIT(TCCR0 , TCCR0_WGM00) ; 
			break;
			
		case TIMER_PWM_MODE    :
		
			CLR_BIT(TCCR0 , TCCR0_WGM01) ; SET_BIT(TCCR0 , TCCR0_WGM00) ;
			break;
			
		case TIMER_CTC_MODE    :
		
			SET_BIT(TCCR0 , TCCR0_WGM01) ; CLR_BIT(TCCR0 , TCCR0_WGM00) ;
			break;
			
		case TIMER_FAST_PWM_MODE : 
		
			SET_BIT(TCCR0 , TCCR0_WGM01) ; SET_BIT(TCCR0 , TCCR0_WGM00) ;
			break;
			
		default :
			Local_u8ErrorStatus = NOK ;
			break;
	}
	
	return Local_u8ErrorStatus;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the output of OC0 Pin TIMER0 using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8OC0Out =>     [TIMER_OC_DISCONNECTED	      ,
 *							  TIMER_OC_TOGGEL	          ,
 *							  TIMER_OC_LOW			      ,
 *							  TIMER_OC_HIGH			      ,
 *                            TIMER_CLR_ON_CTC_SET_ON_TOP ,
 *						      TIMER_SET_ON_CTC_CLR_ON_TOP ,
 *						      TIMER_CLR_ON_UP_SET_ON_DOWN ,
 *						      TIMER_SET_ON_UP_CLR_ON_DOWN ]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER0_u8SetOC0Output(u8 Copy_u8OC0Out)
{
	
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8OC0Out <= TIMER_OC_HIGH)
	{
		TCCR0 &= 0b11001111;
		TCCR0 |= (Copy_u8OC0Out << 4) ;
	}
	else 
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	return Local_u8ErrorStatus;
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the output of OC1A Pin TIMER1 using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8OC1AOut =>    [TIMER_OC_DISCONNECTED	      ,
 *							  TIMER_OC_TOGGEL	          ,
 *							  TIMER_OC_LOW			      ,
 *							  TIMER_OC_HIGH			      ,
 *                            TIMER_CLR_ON_CTC_SET_ON_TOP ,
 *						      TIMER_SET_ON_CTC_CLR_ON_TOP ,
 *						      TIMER_CLR_ON_UP_SET_ON_DOWN ,
 *						      TIMER_SET_ON_UP_CLR_ON_DOWN ]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER1_u8SetOC1AOutput(u8 Copy_u8OC1AOut)
{
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8OC1AOut <= TIMER_OC_HIGH)
	{
		TCCR1A &= 0b00111111;
		TCCR1A |= (Copy_u8OC1AOut << 6) ;
	}
	else 
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	return Local_u8ErrorStatus;
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the output of OC1B Pin TIMER1 using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8OC1BOut =>    [TIMER_OC_DISCONNECTED	      ,
 *							  TIMER_OC_TOGGEL	          ,
 *							  TIMER_OC_LOW			      ,
 *							  TIMER_OC_HIGH			      ,
 *                            TIMER_CLR_ON_CTC_SET_ON_TOP ,
 *						      TIMER_SET_ON_CTC_CLR_ON_TOP ,
 *						      TIMER_CLR_ON_UP_SET_ON_DOWN ,
 *						      TIMER_SET_ON_UP_CLR_ON_DOWN ]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER1_u8SetOC1BOutput(u8 Copy_u8OC1BOut)
{
	
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8OC1BOut <= TIMER_OC_HIGH)
	{
		TCCR1A &= 0b11001111;
		TCCR1A |= (Copy_u8OC1BOut << 4) ;
	}
	else 
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	return Local_u8ErrorStatus;
	
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the output of OC2 Pin TIMER2 using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8OC2Out =>     [TIMER_OC_DISCONNECTED	      ,
 *							  TIMER_OC_TOGGEL	          ,
 *							  TIMER_OC_LOW			      ,
 *							  TIMER_OC_HIGH			      ,
 *                            TIMER_CLR_ON_CTC_SET_ON_TOP ,
 *						      TIMER_SET_ON_CTC_CLR_ON_TOP ,
 *						      TIMER_CLR_ON_UP_SET_ON_DOWN ,
 *						      TIMER_SET_ON_UP_CLR_ON_DOWN ]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER2_u8SetOC2Output(u8 Copy_u8OC2Out)
{
	
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8OC2Out <= TIMER_OC_HIGH)
	{
		TCCR2 &= 0b11001111;
		TCCR2 |= (Copy_u8OC2Out << 4) ;
	}
	else 
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	return Local_u8ErrorStatus;
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the waveform generation mode of TIMER1 using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8WaveMode =>   [TIMER1_NORMAL_MODE                          ,
 *							  TIMER1_PWM_8_BIT_MODE                       ,
 *							  TIMER1_PWM_9_BIT_MODE                       ,
 *							  TIMER1_PWM_10_BIT_MODE                      ,
 *                            TIMER1_CTC_OCR1A_MODE                       ,
 *						      TIMER1_FAST_PWM_8_BIT_MODE                  ,
 *						      TIMER1_FAST_PWM_9_BIT_MODE                  ,
 *						      TIMER1_FAST_PWM_10_BIT_MODE                 ,
 *							  TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE ,
 *							  TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE,
 * 						      TIMER1_PWM_PHASE_CORRECT_ICR1_MODE          ,
 *							  TIMER1_PWM_PHASE_CORRECT_OCR1A_MOD          ,
 *							  TIMER1_CTC_ICR1_MODE                        ,
 *							  TIMER1_FAST_PWM_ICR1_MODE                   ,
 *                            TIMER1_FAST_PWM_OCR1A_MODE]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER1_u8SetWaveFormMode(u8 Copy_u8WaveMode)
{
	
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8WaveMode <= TIMER1_FAST_PWM_OCR1A_MODE)
	{
		u8 Local_u8WaveMode1 = Copy_u8WaveMode & 0b00000011 , Local_u8WaveMode2 = Copy_u8WaveMode & 0b00001100;
		
		TCCR1A |= Local_u8WaveMode1;
		TCCR1B |= (Local_u8WaveMode2 << 2);
	}
	else 
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	return Local_u8ErrorStatus;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the waveform generation mode of TIMER2 using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8WaveMode => [TIMER_NORMAL_MODE , TIMER_PWM_MODE , TIMER_CTC_MODE , TIMER_FAST_PWM_MODE]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER2_u8SetWaveFormMode(u8 Copy_u8WaveMode)
{
	u8 Local_u8ErrorStatus = OK ;
	
	switch(Copy_u8WaveMode)
	{
		case TIMER_NORMAL_MODE : 
		
			CLR_BIT(TCCR2 , TCCR2_WGM21) ; CLR_BIT(TCCR2 , TCCR2_WGM20) ; 
			break;
			
		case TIMER_PWM_MODE    :
		
			CLR_BIT(TCCR2 , TCCR2_WGM21) ; SET_BIT(TCCR2 , TCCR2_WGM20) ;
			break;
			
		case TIMER_CTC_MODE    :
		
			SET_BIT(TCCR2 , TCCR2_WGM21) ; CLR_BIT(TCCR2 , TCCR2_WGM20) ;
			break;
			
		case TIMER_FAST_PWM_MODE : 
		
			SET_BIT(TCCR2 , TCCR2_WGM21) ; SET_BIT(TCCR2 , TCCR2_WGM20) ;
			break;
			
		default :
			Local_u8ErrorStatus = NOK ;
			break;
	}
	
	return Local_u8ErrorStatus;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to generate PWM signal from TIMER0 PIN OC0
 *                                                *-------------------------------------------------------*
 * Parameters : 
 *		Copy_u8C_POL -> [NON_INVERTING , INVERTING]
 *		Copy_u8DutyCycle -> [0:1]
 
 * return     : Error status with type u8  
 */
u8 TIMER0_u8GeneratePWM(u8 Copy_u8C_POL , f32 Copy_u8DutyCycle)
{
	
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8DutyCycle <= 1 && Copy_u8DutyCycle >= 0 )        /*validation for duty cycle */
	{
		if(Copy_u8C_POL == NON_INVERTING)
		{
			SET_BIT(TCCR0 , TCCR0_COM01) ; CLR_BIT(TCCR0 , TCCR0_COM00) ;
			OCR0 = (Copy_u8DutyCycle * 256) - 1 ;                /* D.C = (OCR0+1)/256 */
		}
		else if(Copy_u8C_POL == INVERTING)
		{
			SET_BIT(TCCR0 , TCCR0_COM01) ; SET_BIT(TCCR0 , TCCR0_COM00) ;
			OCR0 = ( (1 - Copy_u8DutyCycle) * 256) - 1 ;        /*  D.C = 1 - ((OCR0+1)/256) */
		}  
		else 
		{
			Local_u8ErrorStatus = NOK ;
		}
	}
	else 
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	return Local_u8ErrorStatus;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to generate PWM signal from TIMER1 channel B PIN OC2
 *                                                *--------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8C_POL -> [NON_INVERTING , INVERTING]
 *		Copy_u8DutyCycle -> [0:1]
 *      Copy_u16Top     ->  [3:65536]
 *
 * return     : Error status with type u8  
 */
u8 TIMER1B_u8GeneratePWM(u8 Copy_u8C_POL , f32 Copy_u8DutyCycle , u16 Copy_u16Top)
{
	
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8DutyCycle <= 1 && Copy_u8DutyCycle >= 0 ) /*validation for duty cycle */
	{
		if(Copy_u16Top >= 3)
		{
			if(Copy_u8C_POL == NON_INVERTING)
			{
				SET_BIT(TCCR1A , TCCR1A_COM1B1) ; CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
				OCR1B = (Copy_u8DutyCycle * Copy_u16Top) - 1 ;            /* D.C = (OCR1B+1)/256 */
			}
			else if(Copy_u8C_POL == INVERTING)
			{
				SET_BIT(TCCR1A , TCCR1A_COM1B1) ; SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
				OCR1B = ( (1 - Copy_u8DutyCycle) * Copy_u16Top) - 1 ;     /*  D.C = 1 - ((OCR1B+1)/256) */
			}
			else 
			{
				Local_u8ErrorStatus = NOK ;
			}
		}
		else 
		{
			Local_u8ErrorStatus = NOK ;
		}
		
	}
	else 
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	return Local_u8ErrorStatus;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to generate PWM signal from TIMER1 channel A PIN OC2
 *                                                *-----------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8C_POL -> [NON_INVERTING , INVERTING]
 *		Copy_u8DutyCycle -> [0:1]
 *      Copy_u16Top     ->  [3:65536]
 *
 * return     : Error status with type u8  
 */
u8 TIMER1A_u8GeneratePWM(u8 Copy_u8C_POL , f32 Copy_u8DutyCycle , u16 Copy_u16Top)
{
	
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8DutyCycle <= 1 && Copy_u8DutyCycle >= 0 ) /*validation for duty cycle */
	{
		if(Copy_u16Top >= 3)
		{
			if(Copy_u8C_POL == NON_INVERTING)
			{
				SET_BIT(TCCR1A , TCCR1A_COM1A1) ; CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
				OCR1A = (Copy_u8DutyCycle * Copy_u16Top) - 1 ;            /* D.C = (OCR1A+1)/256 */
			}
			else if(Copy_u8C_POL == INVERTING)
			{
				SET_BIT(TCCR1A , TCCR1A_COM1A1) ; SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
				OCR1A = ( (1 - Copy_u8DutyCycle) * Copy_u16Top) - 1 ;     /*  D.C = 1 - ((OCR1A+1)/256) */
			}
			else 
			{
				Local_u8ErrorStatus = NOK ;
			}
		}
		else 
		{
			Local_u8ErrorStatus = NOK ;
		}
		
	}
	else 
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	return Local_u8ErrorStatus;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to generate PWM signal from TIMER2 PIN OC2
 *                                                *----------------------------------------------------*
 * Parameters : 
 *		Copy_u8C_POL -> [NON_INVERTING , INVERTING]
 *		Copy_u8DutyCycle -> [0:1]
 
 * return     : Error status with type u8  
 */
u8 TIMER2_u8GeneratePWM(u8 Copy_u8C_POL , f32 Copy_u8DutyCycle)
{
	
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8DutyCycle <= 1 && Copy_u8DutyCycle >= 0 ) /*validation for duty cycle */
	{
		if(Copy_u8C_POL == NON_INVERTING)
		{
			SET_BIT(TCCR2 , TCCR2_COM21) ; CLR_BIT(TCCR2 , TCCR2_COM20) ;
			OCR2 = (Copy_u8DutyCycle * 256) - 1 ;            /* D.C = (OCR2+1)/256 */
		}
		else if(Copy_u8C_POL == INVERTING)
		{
			SET_BIT(TCCR2 , TCCR2_COM21) ; SET_BIT(TCCR2 , TCCR2_COM20) ;
			OCR2 = ( (1 - Copy_u8DutyCycle) * 256) - 1 ;     /*  D.C = 1 - ((OCR2+1)/256) */
		}
		else 
		{
			Local_u8ErrorStatus = NOK ;
		}
	}
	else 
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	return Local_u8ErrorStatus;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Prescaler of the TIMER0 (CLK) using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8Prescaler =>   [TIMER0_NO_CLOCK_SOURCE                  , 
 *							   TIMER0_NO_PRESCALER_FACTOR              , 
 *							   TIMER0_DIVISION_FACTOR_8                , 
 *							   TIMER0_DIVISION_FACTOR_64               , 
 *							   TIMER0_DIVISION_FACTOR_256              , 
 *							   TIMER0_DIVISION_FACTOR_1024             ,
 *							   TIMER0_T0_EXTERNAL_CLOCK_SOURCE_FALLING ,
 *							   TIMER0_T0_EXTERNAL_CLOCK_SOURCE_RISING  ]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER0_u8SetPrescaler (u8 Copy_u8Prescaler)
{
	
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8Prescaler <= TIMER0_T0_EXTERNAL_CLOCK_SOURCE_RISING )
	{
		
		/*Set the Required Prescaler*/
		TCCR0 &= TIMER_PRESCALER_MASK ;
		TCCR0 |= Copy_u8Prescaler ;
	
	}
	else
	{
		Local_u8ErrorStatus = NOK ;
	}
		
	
	return Local_u8ErrorStatus;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Prescaler of the TIMER1 (CLK) using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8Prescaler =>   [TIMER1_NO_CLOCK_SOURCE                  , 
 *							   TIMER1_NO_PRESCALER_FACTOR              , 
 *							   TIMER1_DIVISION_FACTOR_8                , 
 *							   TIMER1_DIVISION_FACTOR_64               , 
 *							   TIMER1_DIVISION_FACTOR_256              , 
 *							   TIMER1_DIVISION_FACTOR_1024             ,
 *							   TIMER1_T1_EXTERNAL_CLOCK_SOURCE_FALLING ,
 *							   TIMER1_T1_EXTERNAL_CLOCK_SOURCE_RISING  ]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER1_u8SetPrescaler (u8 Copy_u8Prescaler)
{
	
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8Prescaler <= TIMER1_T1_EXTERNAL_CLOCK_SOURCE_RISING )
	{
		
		/*Set the Required Prescaler*/
		TCCR1B &= TIMER_PRESCALER_MASK ;
		TCCR1B |= Copy_u8Prescaler ;
		
	}
	else
	{
		Local_u8ErrorStatus = NOK ;
	}
		
	
	return Local_u8ErrorStatus;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Prescaler of the TIMER2 (CLK) using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8Prescaler =>   [TIMER2_NO_CLOCK_SOURCE      , 
 *							   TIMER2_NO_PRESCALER_FACTOR  , 
 *							   TIMER2_DIVISION_FACTOR_8    , 
 *							   TIMER2_DIVISION_FACTOR_32   , 
 *							   TIMER2_DIVISION_FACTOR_64   , 
 *							   TIMER2_DIVISION_FACTOR_128  ,
 *							   TIMER2_DIVISION_FACTOR_256  ,
 * 							   TIMER2_DIVISION_FACTOR_1024 ]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER2_u8SetPrescaler(u8 Copy_u8Prescaler)
{
	u8 Local_u8ErrorStatus = OK ;
	
	if(Copy_u8Prescaler <= TIMER2_DIVISION_FACTOR_1024 )
	{
		
		/*Set the Required Prescaler*/
		TCCR2 &= TIMER_PRESCALER_MASK ;
		TCCR2 |= Copy_u8Prescaler ;
		
	}
	else
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	return Local_u8ErrorStatus;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the OCA Interrupt for timer1 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER1_voidOCAEnableInterrupt (void)
{
	SET_BIT( TIMSK,TIMSK_OCIE1A);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the OCA Interrupt for timer1 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER1_voidOCADisableInterrupt(void)
{
	CLR_BIT( TIMSK, TIMSK_OCIE1A);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the OCB Interrupt for timer1 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER1_voidOCBEnableInterrupt (void)
{
	SET_BIT( TIMSK,TIMSK_OCIE1B);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the OCB Interrupt for timer1 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER1_voidOCBDisableInterrupt(void)
{
	CLR_BIT( TIMSK, TIMSK_OCIE1B);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the OVF Interrupt for timer1 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER1_voidOVFEnableInterrupt (void)
{
	SET_BIT( TIMSK,TIMSK_TOIE1);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the OVF Interrupt for timer1 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER1_voidOVFDisableInterrupt(void)
{
	CLR_BIT( TIMSK, TIMSK_TOIE1);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the OC Interrupt for timer0 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER0_voidOCEnableInterrupt (void )
{
	SET_BIT( TIMSK,TIMSK_OCIE0);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the OC Interrupt for timer0 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER0_voidOCDisableInterrupt(void )
{
	CLR_BIT( TIMSK, TIMSK_OCIE0);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the OVF Interrupt for timer0 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER0_voidOVFEnableInterrupt (void )
{
	SET_BIT( TIMSK, TIMSK_TOIE0);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the OVF Interrupt for timer0 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER0_voidOVFDisableInterrupt(void )
{
	CLR_BIT( TIMSK, TIMSK_TOIE0);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the OC Interrupt for timer2 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER2_voidOCEnableInterrupt (void )
{
	SET_BIT( TIMSK,TIMSK_OCIE2);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the OC Interrupt for timer2 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER2_voidOCDisableInterrupt(void )
{
	CLR_BIT( TIMSK, TIMSK_OCIE2);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the OVF Interrupt for timer2 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER2_voidOVFEnableInterrupt (void )
{
	SET_BIT( TIMSK, TIMSK_TOIE2);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the OVF Interrupt for timer2 
 *                                                *-----------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER2_voidOVFDisableInterrupt(void )
{
	CLR_BIT( TIMSK, TIMSK_TOIE2);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This function for initialize the ICU prebuild configuration
 *                                                *----------------------------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER_voidICUInitEnable(void)
{
	/* Set trigger source as rising edge Initially  */
	#if (TIMER_ICU_INIT_STATE == TIMER_ICU_RAISING_EDGE)
		
		SET_BIT(TCCR1B,TCCR1B_ICES1);
		
	#elif(TIMER_ICU_INIT_STATE == TIMER_ICU_FALLING_EDGE)
		
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
		
	#else
		
		#error "Wrong TIMER_ICU_INIT_STATE Config"
		
	#endif
	
	#if  (TIMER_ICU_NOISE_CANCELER == ENABLE)
		
		SET_BIT(TCCR1B,TCCR1B_ICNC1);
		
	#elif(TIMER_ICU_NOISE_CANCELER == DISABLE)
		
		CLR_BIT(TCCR1B,TCCR1B_ICNC1);
	#else
		
		#error "Wrong TIMER_ICU_NOISE_CANCELER Config"
		
	#endif
	
	/* Enable Interrupt of ICU */
	#if  (TIMER1_ICR_INTERRUPT == ENABLE )
		
		SET_BIT(TIMSK,TIMSK_TICIE1);
		
	#elif(TIMER1_ICR_INTERRUPT == DISABLE)
		
		CLR_BIT(TIMSK,TIMSK_TICIE1);
		
	#else
		
		#error "Wrong TIMER_ICU_NOISE_CANCELER Config"
		
	#endif
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This func for change the trigger state (postbuild)
 *                                                *-------------------------------------------------------*
 * Parameters : 
 *		Copy_u8Edge     => [TIMER_ICU_RAISING_EDGE  , TIMER_ICU_FALLING_EDGE]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER_u8ICUSetTriggerEdge(u8 Copy_u8Edge)
{
	u8 Local_u8ErrorStatus = OK ;
	
	/* Change The trigger source as Rising edge or Falling edge */
	if (Copy_u8Edge == TIMER_ICU_RAISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copy_u8Edge == TIMER_ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else
	{
		Local_u8ErrorStatus = NOK ;
	}
	
	/*clear the flag after change the trigger edge */
	SET_BIT(TIFR , TIFR_ICF1 );
	
	return Local_u8ErrorStatus;
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the ICU Interrupt
 *                                                *-----------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER_voidICUEnableInterrupt(void)
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the ICU Interrupt
 *                                                *-----------------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER_voidICUDisableInterrupt(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to get the value of the ICR1 register 
 *                                                *----------------------------------------------------*
 * Parameters : Nothing
 *		 
 * return     : the value of the ICR1 register 
 */
u16 TIMER_u16GetICR1(void)
{
	return ICR1;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the require value in ICR1 register 
 *                                                *-----------------------------------------------------*
 * Parameters : 
 *		Copy_u16ICR1 => the value to be set in ICR1 
 *		
 * return     : Nothing 
 */
void TIMER_voidSetICR1 (u16 Copy_u16ICR1)
{
	ICR1 = Copy_u16ICR1 ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the input fuction to be ISR function to required ID
 *                                                *------------------------------------------------------------------------*
 * Parameters : 
 *      Copy_pvCallBackFunc => The Adress of ISR Func (its name)
 *
 *		Copy_u8VectorID     => [TIMER2_CTC_VECTOR_ID  , 
 *							    TIMER2_OVF_VECTOR_ID  , 
 *							    TIMER1_ICU_VECTOR_ID  , 
 *							    TIMER1_CTCA_VECTOR_ID , 
 *							    TIMER1_CTCB_VECTOR_ID , 
 *							    TIMER1_OVF_VECTOR_ID  ,
 *							    TIMER0_CTC_VECTOR_ID  ,
 * 							    TIMER0_OVF_VECTOR_ID  ]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER_u8SetCallBack(void (*Copy_pvCallBackFunc)(void) , u8 Copy_u8VectorID)
{
	u8 Local_u8ErrorState = OK ;

	if (Copy_pvCallBackFunc != NULL)
	{
		
		if(Copy_u8VectorID <= TIMER0_OVF_VECTOR_ID)
		{
			TIMERS_pvCallBackFunc[Copy_u8VectorID] = Copy_pvCallBackFunc ;
		}
		else 
		{
			Local_u8ErrorState = NOK ;
		}
		
	}
	else
	{
		Local_u8ErrorState = NOK ;
	}

	return Local_u8ErrorState ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the input fuction to be ISR function to required ID
 *                                                *------------------------------------------------------------------------*
 * Parameters :
 *		Copy_u8Prescaler     => [WDT_PS_16_3_MS , 
 *							    WDT_PS_32_5_MS , 
 *							    WDT_PS_65_MS   , 
 *							    WDT_PS_0_13_S  , 
 *							    WDT_PS_0_26_S  , 
 *							    WDT_PS_0_52_S  ,
 *							    WDT_PS_1_0_S   ,
 * 							    WDT_PS_2_1_S   ]
 *		
 * return     : Error status with type u8  
 */
u8 TIMER_u8WDTSleep(u8 Copy_u8Prescaler)
{
	
	u8 Local_u8ErrorState = OK ;
	
	if(Copy_u8Prescaler <= WDT_PS_2_1_S)
	{
		/* CLear The Prescaler bits  */
		WDTCR &= TIMER_PRESCALER_MASK ;
		/* Set The required prescaller */
		WDTCR |= Copy_u8Prescaler ;
	}
	else
	{
		Local_u8ErrorState = NOK ;
	}
	
	return Local_u8ErrorState ;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the WDT 
 *                                                *---------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER_voidWDTEnable (void)
{
	SET_BIT (WDTCR , WDTCR_WDE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the WDT 
 *                                                *---------------------------------------*
 * Parameters : Nothing
 *		
 * return     : Nothing  
 */
void TIMER_voidWDTDisable (void)
{
	/* Set Bit 3&4 at the same CLK cycle  */
	WDTCR |= 0b00011000 ;
	
	/* WDTCR_WDE = 0 */
	/* I don't care for any value in this Reg Cuz I want to Disable */
	WDTCR = 0 ;
}
/*TIMER0 Normal Mode ISR*/
void __vector_11 (void)		__attribute__((signal)) ;
void __vector_11 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER0_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER0_OVF_VECTOR_ID]() ;
	}
}

/*TIMER0 CTC Mode ISR*/
void __vector_10 (void)		__attribute__((signal)) ;
void __vector_10 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER0_CTC_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER0_CTC_VECTOR_ID]() ;
	}
}

/*TIMER1 Normal Mode ISR*/
void __vector_9 (void)		__attribute__((signal)) ;
void __vector_9 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_OVF_VECTOR_ID]() ;
	}
}

/*TIMER1 CTCB Mode ISR*/
void __vector_8 (void)		__attribute__((signal)) ;
void __vector_8 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_CTCB_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_CTCB_VECTOR_ID]() ;
	}
}

/*TIMER1 CTCA Mode ISR*/
void __vector_7 (void)		__attribute__((signal)) ;
void __vector_7 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_CTCA_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_CTCA_VECTOR_ID]() ;
	}
}

/*TIMER1 ICU ISR*/
void __vector_6 (void)		__attribute__((signal)) ;
void __vector_6 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_ICU_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_ICU_VECTOR_ID]() ;
	}
}

/*TIMER2 Normal Mode ISR*/
void __vector_5 (void)		__attribute__((signal)) ;
void __vector_5 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER2_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER2_OVF_VECTOR_ID]() ;
	}
}

/*TIMER2 CTC Mode ISR*/
void __vector_4 (void)		__attribute__((signal)) ;
void __vector_4 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER2_CTC_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER2_CTC_VECTOR_ID]() ;
	}
}
