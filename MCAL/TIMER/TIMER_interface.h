/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     TIMER_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : TIMER
 *
 */
 

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/* Define indexes for the global pointer to func for ISR  */
#define TIMER0_OVF_VECTOR_ID		                    7
#define TIMER0_CTC_VECTOR_ID		                    6

#define TIMER1_OVF_VECTOR_ID	                        5
#define TIMER1_CTCB_VECTOR_ID		                    4
#define TIMER1_CTCA_VECTOR_ID		                    3
#define TIMER1_ICU_VECTOR_ID		                    2
  
#define TIMER2_OVF_VECTOR_ID		                    1
#define TIMER2_CTC_VECTOR_ID		                    0


#define NON_INVERTING                                   2
#define INVERTING                                       3

#define TIMER_ICU_RAISING_EDGE                          0
#define TIMER_ICU_FALLING_EDGE                          1

#define TIMER0_NO_CLOCK_SOURCE	 	                    0
#define TIMER0_NO_PRESCALER_FACTOR 	                    1
#define TIMER0_DIVISION_FACTOR_8	 	                2
#define TIMER0_DIVISION_FACTOR_64	                    3
#define TIMER0_DIVISION_FACTOR_256	                    4
#define TIMER0_DIVISION_FACTOR_1024	                    5
#define TIMER0_T0_EXTERNAL_CLOCK_SOURCE_FALLING	        6
#define TIMER0_T0_EXTERNAL_CLOCK_SOURCE_RISING	        7

#define TIMER_CLR_ON_UP_SET_ON_DOWN                     2
#define TIMER_SET_ON_UP_CLR_ON_DOWN                     3

#define TIMER_CLR_ON_CTC_SET_ON_TOP                     2
#define TIMER_SET_ON_CTC_CLR_ON_TOP                     3

#define TIMER1_NO_CLOCK_SOURCE	 	                    0
#define TIMER1_NO_PRESCALER_FACTOR 	                    1
#define TIMER1_DIVISION_FACTOR_8	 	                2
#define TIMER1_DIVISION_FACTOR_64	                    3
#define TIMER1_DIVISION_FACTOR_256	                    4
#define TIMER1_DIVISION_FACTOR_1024	                    5
#define TIMER1_T1_EXTERNAL_CLOCK_SOURCE_FALLING	        6
#define TIMER1_T1_EXTERNAL_CLOCK_SOURCE_RISING	        7

#define TIMER1_NORMAL_MODE								0
#define TIMER1_PWM_8_BIT_MODE							1
#define TIMER1_PWM_9_BIT_MODE							2
#define TIMER1_PWM_10_BIT_MODE							3
#define TIMER1_CTC_OCR1A_MODE							4
#define TIMER1_FAST_PWM_8_BIT_MODE						5
#define TIMER1_FAST_PWM_9_BIT_MODE 						6
#define TIMER1_FAST_PWM_10_BIT_MODE						7
#define TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE		8
#define TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE	9
#define TIMER1_PWM_PHASE_CORRECT_ICR1_MODE				10
#define TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE				11
#define TIMER1_CTC_ICR1_MODE							12
#define TIMER1_FAST_PWM_ICR1_MODE						14
#define TIMER1_FAST_PWM_OCR1A_MODE						15


#define TIMER2_NO_CLOCK_SOURCE	 	                    0
#define TIMER2_NO_PRESCALER_FACTOR 	                    1
#define TIMER2_DIVISION_FACTOR_8	                    2
#define TIMER2_DIVISION_FACTOR_32 	                    3
#define TIMER2_DIVISION_FACTOR_64	                    4
#define TIMER2_DIVISION_FACTOR_128                      5
#define TIMER2_DIVISION_FACTOR_256	                    6
#define TIMER2_DIVISION_FACTOR_1024	                    7

#define TIMER_NORMAL_MODE						        0
#define TIMER_PWM_MODE							        1
#define TIMER_CTC_MODE							        2
#define TIMER_FAST_PWM_MODE						        3

#define TIMER_OC_DISCONNECTED					        0
#define TIMER_OC_TOGGEL							        1
#define TIMER_OC_LOW							        2
#define TIMER_OC_HIGH							        3

#define WDT_PS_16_3_MS                                  0
#define WDT_PS_32_5_MS                                  1
#define WDT_PS_65_MS	                                2   
#define WDT_PS_0_13_S                                   3
#define WDT_PS_0_26_S                                   4
#define WDT_PS_0_52_S                                   5
#define WDT_PS_1_0_S	                                6   
#define WDT_PS_2_1_S                                    7

/*Timer0 functions*/
void TIMER0_voidInit               (void                                  );
void TIMER0_voidSetPreload         (u8 Copy_u8Preload                     );
void TIMER0_voidSetCTC             (u8 Copy_u8CTC                         );
u8   TIMER0_u8SetWaveFormMode      (u8 Copy_u8WaveMode                    );
u8   TIMER0_u8SetPrescaler         (u8 Copy_u8Prescaler                   );
u8   TIMER0_u8GeneratePWM          (u8 Copy_u8C_POL , f32 Copy_u8DutyCycle);
u8   TIMER0_u8SetOC0Output         (u8 Copy_u8OC0Out                      );
u8   TIMER0_u8GetTimerCounterValue (void                                  );

void TIMER0_voidOCEnableInterrupt  (void                                  );
void TIMER0_voidOCDisableInterrupt (void                                  );
void TIMER0_voidOVFEnableInterrupt (void                                  );
void TIMER0_voidOVFDisableInterrupt(void                                  );

/*Timer1 functions*/
void TIMER1_voidInit                (void                                                    );
void TIMER1_voidSetPreload          (u16 Copy_u16Preload                                     );
void TIMER1_voidSetCTCA             (u16 Copy_u16CTCA                                        );
void TIMER1_voidSetCTCB             (u16 Copy_u16CTCB                                        );
u8   TIMER1_u8SetWaveFormMode       (u8 Copy_u8WaveMode                                      );
u8   TIMER1_u8SetPrescaler          (u8 Copy_u8Prescaler                                     );
u8   TIMER1_u8SetOC1AOutput         (u8 Copy_u8OC0Out                                        );
u8   TIMER1B_u8GeneratePWM          (u8 Copy_u8C_POL , f32 Copy_u8DutyCycle , u16 Copy_u16Top);
u8   TIMER1A_u8GeneratePWM          (u8 Copy_u8C_POL , f32 Copy_u8DutyCycle , u16 Copy_u16Top);
u8   TIMER1_u8SetOC1BOutput         (u8 Copy_u8OC0Out                                        );
u16  TIMER1_u16GetTimerCounterValue (void                                                    );

void TIMER1_voidOCAEnableInterrupt  (void                                  );
void TIMER1_voidOCADisableInterrupt (void                                  );
void TIMER1_voidOCBEnableInterrupt  (void                                  );
void TIMER1_voidOCBDisableInterrupt (void                                  );
void TIMER1_voidOVFEnableInterrupt  (void                                  );
void TIMER1_voidOVFDisableInterrupt (void                                  );

/*Timer2 functions*/
void TIMER2_voidInit               (void                                  );
void TIMER2_voidSetPreload         (u8 Copy_u8Preload                     );
void TIMER2_voidSetCTC             (u8 Copy_u8CTC                         );
u8   TIMER2_u8SetWaveFormMode      (u8 Copy_u8WaveMode                    );
u8   TIMER2_u8SetPrescaler         (u8 Copy_u8Prescaler                   );
u8   TIMER2_u8GeneratePWM          (u8 Copy_u8C_POL , f32 Copy_u8DutyCycle);
u8   TIMER2_u8SetOC2Output         (u8 Copy_u8OC2Out                      );
u8   TIMER2_u8GetTimerCounterValue (void                                  );

void TIMER2_voidOCEnableInterrupt  (void                                  );
void TIMER2_voidOCDisableInterrupt (void                                  );
void TIMER2_voidOVFEnableInterrupt (void                                  );
void TIMER2_voidOVFDisableInterrupt(void                                  );

/*ICU functions*/
void TIMER_voidICUInitEnable       (void            );
u8   TIMER_u8ICUSetTriggerEdge     (u8 Copy_u8Edge  );
void TIMER_voidICUEnableInterrupt  (void            );
void TIMER_voidICUDisableInterrupt (void            );
u16  TIMER_u16GetICR1              (void            );
void TIMER_voidSetICR1             (u16 Copy_u16ICR1);

u8 TIMER_u8SetCallBack(void (*Copy_pvCallBackFunc)(void) , u8 Copy_u8VectorID);

/*WDT functions*/
u8   TIMER_u8WDTSleep     (u8 Copy_u8Prescaler);
void TIMER_voidWDTEnable  (void               );
void TIMER_voidWDTDisable (void               );


#endif /* TIMER_INTERFACE_H_ */