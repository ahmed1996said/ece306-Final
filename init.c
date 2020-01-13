//===========================================================================
// File Name : init.c
//
// Description: This file contains initial conditions
//
// Author: Ahmed Al Mahrooqi
// Date: September 2018
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"

//Global Variables
extern char display_line[LCD_LINES][LCD_CHAR_NUM];
extern char *display[LCD_LINES];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern char pwm_state;


  
  

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=RESET_STATE;i<LCD_CHAR_NUM;i++){
    display_line[RESET_STATE][i] = RESET_STATE;
    display_line[LCD_LINE1][i] = RESET_STATE;
    display_line[LCD_LINE2][i] = RESET_STATE;
    display_line[LCD_LINE3][i] = RESET_STATE;
  }
  display_line[RESET_STATE][LCD_CHAR_10] = RESET_STATE;
  display_line[LCD_LINE1][LCD_CHAR_10] = RESET_STATE;
  display_line[LCD_LINE2][LCD_CHAR_10] = RESET_STATE;
  display_line[LCD_LINE3][LCD_CHAR_10] = RESET_STATE;

  display[RESET_STATE] = &display_line[RESET_STATE][RESET_STATE];
  display[LCD_LINE1] = &display_line[LCD_LINE1][RESET_STATE];
  display[LCD_LINE2] = &display_line[LCD_LINE2][RESET_STATE];
  display[LCD_LINE3] = &display_line[LCD_LINE3][RESET_STATE];
  update_display = RESET_STATE;
  update_display_count = RESET_STATE;
  pwm_state = PORTS;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}