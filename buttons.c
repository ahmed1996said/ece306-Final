#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"
volatile unsigned int b1 = RESET_STATE;
volatile unsigned int debounce1 = RESET_STATE;
volatile unsigned int debounce1_count = RESET_STATE;

volatile unsigned int b2 = RESET_STATE;
extern volatile unsigned int b2_count;
extern volatile unsigned int b1_count;

volatile unsigned int debounce2 = RESET_STATE;
volatile unsigned int debounce2_count = RESET_STATE;



#pragma vector=PORT5_VECTOR
__interrupt void BUTTON_interrupt(void) {

// BUTTON 1
  if (P5IFG & BUTTON1) { 
      
     b1 = TRUE;                // BUTTON1 is pressed
     
     debounce1 = TRUE;         // BUTTON1 is being debounced
     debounce1_count = RESET_STATE;
     P5IE  &= ~BUTTON1;
     TA0CCTL1 |= CCIE;         // enable timer interrupt CCR1 

     P5IFG &= ~BUTTON1;        // disable switch interrupt
     
}


// BUTTON 2
if (P5IFG & BUTTON2) {
  
     b2 = TRUE;         // BUTTON2 is pressed
             
     debounce2 = TRUE;         // BUTTON2 is being debounced
     debounce2_count = RESET_STATE;
     P5IE  &= ~BUTTON2;
     TA0CCTL1 |= CCIE;         // enable timer interrupt CCR1                     
     P5IFG &= ~BUTTON2;        // disable switch interrupt
  

}
// Enable the Timer Interrupt for the debounce.
//------------------------------------------------------------------------------
}

