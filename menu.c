//------------------------------------------------------------------------------
//
//  Description: This file contains menu items for thumbhweel
//
//
//  Ahmed Al Mahrooqi
//  November 2018
//  Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"

extern unsigned int current_thumb;
extern char option;
unsigned int i;
extern volatile unsigned int ADC_Thumb;



void main_menu(void){

      current_thumb=ADC_Thumb;
      if(current_thumb < OPTION1_LIMIT){
       display_string_line(LCD_LINE1," ->Start");
       option=START;
      }
   
      if(current_thumb >= OPTION1_LIMIT && current_thumb < OPTION2_LIMIT){
       display_string_line(LCD_LINE1," ->Cal Blk");
       option =CALB;
      }
      
     if(current_thumb >= OPTION2_LIMIT && current_thumb < OPTION3_LIMIT){
       display_string_line(LCD_LINE1," ->Cal Wht");
       option =CALW;
      }

     if(current_thumb >= OPTION3_LIMIT && current_thumb < OPTION4_LIMIT){
       display_string_line(LCD_LINE1," ->Show IP");
       option =SHOWIP;
      }
      
      
      if(current_thumb >= OPTION4_LIMIT && current_thumb < OPTION5_LIMIT){
       display_string_line(LCD_LINE1," ->TCP"); 
       option=TCP;
      }
      
      
      if(current_thumb > OPTION5_LIMIT){
       display_string_line(LCD_LINE1," ->IoT_RST");
       option =IOTRST;
      }
    

}