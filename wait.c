//===========================================================================
// File Name : wait.c
//
// Description: This file contains functions that provide delays
//
// Author: Ahmed Al Mahrooqi
// Date: October 2018
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//===========================================================================


#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"

volatile unsigned int wait_counter = RESET_STATE;
volatile unsigned int wait_counter_5ms = RESET_STATE;
volatile unsigned int wait_case;
volatile unsigned int wait_case_5ms=RESET_VALUE;
extern volatile unsigned int er_stop;




void wait_5ms(int duration){                //duration=1 is 5 ms
// function to provide delay
  
  wait_case_5ms = TRUE;
  wait_counter_5ms = RESET_STATE;

   while(ALWAYS) 
  {
    if(wait_counter_5ms >= duration)
    {
       wait_counter_5ms = RESET_STATE;
       wait_case = RESET_STATE; 
       break;
    }
   } 

}

void wait_100ms(int duration){                //duration=1 is 100 ms
// function to provide delay
  int time_to_wait = duration *TIME_SCALE;
  
  wait_case = TRUE;
  wait_counter = RESET_STATE;

   while(!er_stop){
     
    if(wait_counter >= time_to_wait){
       wait_counter = RESET_STATE;
       wait_case = RESET_STATE; 
     }
    
   }
   er_stop=RESET_VALUE;

}