//===========================================================================
// File Name : IoT.c
//
// Description: This file contains IoT commands
//
// Author: Ahmed Al Mahrooqi
// Date: September 2018
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"

extern unsigned int index_a3;
extern char command_buffer3[CMD_BUFFER_SIZE];
extern unsigned int a;
extern unsigned int b;
extern unsigned int c;
extern unsigned int cmd_index;
extern unsigned int time_requested;
extern unsigned int password;
unsigned int ctr;
extern unsigned int menu_on;
extern char display_line[LCD_LINES][LCD_CHAR_NUM];
extern unsigned int find_ip;
extern char ip_address[SMALL_RING_SIZE];
extern unsigned int ip_found;
unsigned int stop_flag=RESET_VALUE;
unsigned int reconnect_cnt;
extern volatile unsigned int reconnect;
char arch; 

extern unsigned int ii;
extern volatile unsigned int cmd_cnt;
extern unsigned int caret_index[CARET_BUFFER];
extern volatile unsigned int command_complete_A3;
extern unsigned int intercept_flag;
extern volatile unsigned int state ;
extern unsigned int adc_on;

void increment_cmd_index(void){
         if(++cmd_index >= CMD_BUFFER_SIZE)
           cmd_index = BEGINNING;
}


void check_password(void){
  
    increment_cmd_index();
    switch(command_buffer3[cmd_index]){    
      case PIN0:                        // check password
          increment_cmd_index();
          if(command_buffer3[cmd_index] == PIN1){
              increment_cmd_index();
            if(command_buffer3[cmd_index] == PIN2){
                increment_cmd_index();
              if(command_buffer3[cmd_index] == PIN3){
                 increment_cmd_index();
                password=TRUE;
              }
              else password=RESET_VALUE;
            }
          }              
        break;
    default:break;
    }
}


void interrogate_command(void){


  switch(command_buffer3[cmd_index]){    
  
         case FWD:                      //forward('F')
           increment_cmd_index();
           
           a=(command_buffer3[cmd_index]-CONVERSION_FACTOR)*HUNDRED;
           increment_cmd_index();
           
           b = (command_buffer3[cmd_index]-CONVERSION_FACTOR)*TEN;
           increment_cmd_index();
                 
           c= command_buffer3[cmd_index]-CONVERSION_FACTOR;   
           
           time_requested=a+b+c;
           
           //time requested = 1 =>100ms, 10 => 1s
           go_forward(time_requested);
           
          break;
          
          case RVR:             //backward ('B')
           increment_cmd_index();
           
           a=(command_buffer3[cmd_index]-CONVERSION_FACTOR)*HUNDRED;
           increment_cmd_index();
           
           b = (command_buffer3[cmd_index]-CONVERSION_FACTOR)*TEN;
           increment_cmd_index();
                 
           c= command_buffer3[cmd_index]-CONVERSION_FACTOR;   
           
           time_requested=a+b+c;
           
           //time requested = 1 =>100ms, 10 => 1s
           go_reverse(time_requested);
          break;
          
         case RGT:            //Right ('R')
           increment_cmd_index();
           
           a=(command_buffer3[cmd_index]-CONVERSION_FACTOR)*HUNDRED;
           increment_cmd_index();
           
           b = (command_buffer3[cmd_index]-CONVERSION_FACTOR)*TEN;
           increment_cmd_index();
                 
           c= command_buffer3[cmd_index]-CONVERSION_FACTOR;   
           
           time_requested=a+b+c;
           
           //time requested = 1 =>100ms, 10 => 1s
           turn_right(time_requested);
          break;
          
        case LFT:             // left ('L')
           increment_cmd_index();
           
           a=(command_buffer3[cmd_index]-CONVERSION_FACTOR)*HUNDRED;
           increment_cmd_index();
           
           b = (command_buffer3[cmd_index]-CONVERSION_FACTOR)*TEN;
           increment_cmd_index();
                 
           c= command_buffer3[cmd_index]-CONVERSION_FACTOR;   
           
           time_requested=a+b+c;
           
           //time requested = 1 =>100ms, 10 => 1s
           turn_left(time_requested);
          break;
          
        case INTCPT:                // intercept ('I')
                                    // format = (I<size><direction>), size= B (big arch),S= (small arch)
                                    //                                direction= L (left), R (right)
           increment_cmd_index();
           
           if(command_buffer3[cmd_index]=='B'){
             increment_cmd_index();
             if(command_buffer3[cmd_index]=='R'){
               arch=BIG_RIGHT;
             }
             else arch=BIG_LEFT;
           }
           else{
            if(command_buffer3[cmd_index]=='S'){
             increment_cmd_index();
             if(command_buffer3[cmd_index]=='R'){
               arch=SMALL_RIGHT;
             }
             else arch=SMALL_LEFT;
           }
           }
           adc_on=TRUE;  
           state=STEP1;
           intercept_flag=TRUE;
           break;
         
         default:break;
      
         }//switch statement end
    
    }

void service_IOT_command(void){

   ii=RESET_VALUE;
    while(ii <= cmd_cnt - CORRECTION_FACTOR) // service multiple commands
    {
        cmd_index=caret_index[ii];      // check first command, then second,etc..       
        check_password();               //check if PIN correct
    
        if(password)       //if correct, continue command interrogation
          interrogate_command();       
        ii++;
    }
    
  cmd_cnt=RESET_VALUE; 
  command_complete_A3=RESET_VALUE;  



}

void reconnect_connection(void) {
   wait_100ms(FOUR_COUNTS);
   out_string_A3("AT+NSTCP=9228,1");
   wait_100ms(TWO_COUNTS);
   reconnect_cnt++;
   

   if(reconnect_cnt >= TWO_COUNTS){
      if(reconnect_cnt>=THREE_COUNTS)
        out_string_A3("AT+WKEEPALIVE=3"); 
      else
      out_string_A3("AT+WKEEPALIVE=5");
    }
   else
    out_string_A3("AT+WKEEPALIVE=8"); 
}




void print_ip_address(void){
    lcd_4line();
    menu_on=RESET_VALUE;        // clear menu items
    clear_display();
    display_string_line(LCD_LINE0,"SSID: ncsu");
    display_string_line(LCD_LINE1,"IP :");
    
    strncpy(display_line[LCD_LINE2], ip_address,FIRST_HALF);    // print 1st half on line2
    strncpy(display_line[LCD_LINE3], ip_address+SECOND_HALF,SECOND_HALF);  // print 2nd half on line 3 
    
    ip_found=RESET_VALUE;


}



