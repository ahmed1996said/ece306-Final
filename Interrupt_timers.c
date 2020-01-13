//===========================================================================
// File Name : interrupt_timers.c
//
// Description: This file contains timer interrupts
//
// Author: Ahmed Al Mahrooqi
// Date: September 2018
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"

volatile unsigned int lcd_update_count = RESET_STATE;

extern volatile unsigned int b1;
extern volatile unsigned int debounce1;
extern volatile unsigned int debounce1_count;
extern volatile unsigned char update_display;
volatile unsigned int timer_a0;
volatile unsigned int timer_a3;

volatile unsigned int led_blink_count = RESET_STATE;


extern volatile unsigned int b2;
extern volatile unsigned int debounce2;
extern volatile unsigned int debounce2_count;

extern volatile unsigned int wait_counter;
extern volatile unsigned int wait_case;
extern volatile unsigned int wait_case_5ms;
extern volatile unsigned int wait_counter_5ms;
extern volatile unsigned int timer;
extern unsigned int adc_on;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
//----------------------------------------------------------------------------
// Capture Compare R0 every 50 ms
   lcd_update_count++;
   //led_blink_count++;
   
   if(adc_on)
   ADC12IER0 |= ADC12IE2;
   
    //timer ++;
    //timer_a0++;
    
  if(wait_case)
      wait_counter++;
  
  TA0CCR0 += TA0CCR0_INTERVAL;         // Add Offset to TACCR0 
  
//----------------------------------------------------------------------------
}


#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
//----------------------------------------------------------------------------
// TimerA0 1-2, Overflow Interrupt Vector (TAIV) handler
//----------------------------------------------------------------------------
  
switch(__even_in_range(TA0IV,OVERFLW_CASE)){
  case RESET_STATE: break;                  // No interrupt
  
  case CCR1_CASE:   // CCR1 = 100 ms
  //Timer interrupt for debounce
    
    if(debounce1){
  debounce1_count++;              //increment debounce counter
  //P5OUT &= ~LCD_BACKLITE;
  P1OUT |= RED_LED;
  TA0CCTL0 &= ~CCIE;   
    }
    
  if(debounce2){
  debounce2_count++;              //increment debounce counter
  //P5OUT &= ~LCD_BACKLITE;
  P1OUT |= RED_LED;
  TA0CCTL0 &= ~CCIE;              // disable LCD timer
    }


    
  if(debounce1_count >= DEBOUNCE_TIME)
  {
     debounce1_count = RESET_STATE;
     debounce1 = RESET_STATE;
     TA0CCTL1 &= ~CCIE;         // disable timer CCR1
     P5IE |= BUTTON1;          // enable button interrupt
     TA0CCTL0 |= CCIE;         // enable LCD timer interrupt
     //P5OUT |= LCD_BACKLITE;   // enable LCD backlight
     P1OUT &= ~RED_LED;
     
  }
  
    if(debounce2_count >= DEBOUNCE_TIME)
  {
     debounce2_count = RESET_STATE;
     debounce2 = RESET_STATE;
     TA0CCTL1 &= ~CCIE;         // disable timer CCR1
     P5IE |= BUTTON2;          // enable button interrupt
     TA0CCTL0 |= CCIE;         // enable LCD timer interrupt
     //P5OUT |= LCD_BACKLITE;   // enable LCD backlight
     P1OUT &= ~RED_LED;

  }
  
  TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
  break;
  
  case CCR2_CASE: // CCR2 = 100 ms
     if(wait_case_5ms)
      wait_counter_5ms++;
   TA0CCR2 += TA0CCR2_INTERVAL;  // Add Offset to TACCR2
  break;
  
  case OVERFLW_CASE: // overflow
  //...... Add What you need happen in the interrupt ......
  break;
  default: break;
}
//----------------------------------------------------------------------------
}




