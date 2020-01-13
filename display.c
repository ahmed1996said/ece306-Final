//===========================================================================
// File Name : display.c
//
// Description: This file contains functions that updates the display with strings
//
// Author: Ahmed Al Mahrooqi
// Date: October 2018
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"

extern char display_line[LCD_LINES][LCD_CHAR_NUM];
extern char *display[LCD_LINES];
extern volatile unsigned char update_display;


void clear_display_line(int linenum){

  strcpy(display_line[linenum], "          ");
  
  //update_string(display_line[linenum], linenum);
  //enable_display_update(); 
  Display_Update(RESET_VALUE,RESET_VALUE,RESET_VALUE,RESET_VALUE);  
  //update_display = TRUE;    
  
}

void display_string_line(int linenum,char *text){
  int new_text = strcmp(display_line[linenum], text);
  
  if( new_text )   
  {
  clear_display_line(linenum);
  
  strcpy(display_line[linenum], text);
  
  //update_string(display_line[linenum], linenum);
  //enable_display_update();   
  Display_Update(RESET_VALUE,RESET_VALUE,RESET_VALUE,RESET_VALUE);
  //update_display = TRUE;  
  
  }

}


void clear_display(void){
clear_display_line(LCD_LINE0);
clear_display_line(LCD_LINE1);
clear_display_line(LCD_LINE2);
clear_display_line(LCD_LINE3);

}