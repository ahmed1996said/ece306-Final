//===========================================================================
// File Name : movements.c
//
// Description: This file contains car movement functions
//
// Author: Ahmed Al Mahrooqi
// Date: September 2018
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//===========================================================================


#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"


extern char display_line[LCD_LINES][LCD_CHAR_NUM];
extern char *display[LCD_LINES];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int left_white;
extern volatile unsigned int right_white;
extern volatile unsigned int timer;
volatile unsigned int current_time=RESET_VALUE;
extern unsigned int step3_done;
signed int time_to_travel=RESET_STATE;
extern volatile unsigned int state ;
extern unsigned int intercept_flag;
extern unsigned int stop_flag;
extern unsigned int menu_on;
extern char arch;
unsigned int forward_moving;
unsigned int reverse_moving;
extern unsigned int black;
extern unsigned int white;
extern unsigned int gray;
unsigned int dark_gray;
extern volatile unsigned int er_stop;

extern volatile unsigned int left_black;
extern volatile unsigned int right_black;
extern unsigned int temp_right;
extern unsigned int temp_left;
unsigned int white_detected;
unsigned int first_state_done=RESET_STATE;


void wheels_off(void){
// turns wheels off
LEFT_FORWARD_SPEED = WHEEL_OFF;        
RIGHT_FORWARD_SPEED = WHEEL_OFF;   

LEFT_REVERSE_SPEED =  WHEEL_OFF; 
RIGHT_REVERSE_SPEED = WHEEL_OFF;

}



void exit_circle(void){
//this function performs the set of tasks to exit the circle and stop navigating line
  
  wheels_off();
  P8OUT  &= ~IR_LED;         // turn IR_LED OFF
  TB0CCR0 = HI_WHEEL_PERIOD;
  go_forward(THREE_SEC);
  display_string_line(LCD_LINE1,"  DONE!!");  

}


void follow(void){

      TB0CCR0 = HI_WHEEL_PERIOD;
      dark_gray = black-MARGIN;
      RIGHT_REVERSE_SPEED = 7000;
      LEFT_REVERSE_SPEED  = 7000; 
      
      while(!er_stop){                                // run loop until stop signal recieved from IoT 
            temp_right=ADC_Right_Detector;   
            temp_left=ADC_Left_Detector;


            while(temp_left <= dark_gray){            // drifting to right
              temp_left=ADC_Left_Detector;      
              RIGHT_REVERSE_SPEED = WHEEL_OFF;        // turn off R wheel until back on line
            }
            RIGHT_REVERSE_SPEED = 7000;               // right wheel slower- try increasing changed from 5000
            
            while(temp_right <= dark_gray){           // drifting to left
              temp_right=ADC_Right_Detector;    
              LEFT_REVERSE_SPEED=WHEEL_OFF;           // turn off L wheel until back on line
            }
             LEFT_REVERSE_SPEED  = 7000;       
       }
      er_stop=RESET_VALUE;
            
}


void spin2(void){

wheels_off();
  temp_right=ADC_Right_Detector;
  temp_left=ADC_Left_Detector;

RIGHT_FORWARD_SPEED = 5000;


  while(temp_right<=gray && temp_left<=gray){
      temp_right=ADC_Right_Detector;
      temp_left=ADC_Left_Detector;
  }
      
wheels_off();
}


void electronic_brakes(void){
  
  wheels_off();
  LEFT_REVERSE_SPEED  =  5000; 
  RIGHT_REVERSE_SPEED = 5000;
  wait_100ms(2);
  wheels_off();
  
}


void detect_white(void){

  while(!white_detected){
      temp_right=ADC_Right_Detector;
      temp_left=ADC_Left_Detector;
      
      if(temp_right>=white && temp_left>=white){ //white detected
       wait_100ms(5);                           // wait half a second 
       temp_right=ADC_Right_Detector;           // take samples
       temp_left=ADC_Left_Detector; 
       if(temp_right>=white && temp_left>=white) //if still white,car is on white board
        white_detected=TRUE;
      }
   }
}



void intercept(void) {
  // make an arc, look for black line when white board detected
  
  wheels_off();
  TB0CCR0 = HI_WHEEL_PERIOD;
  
  switch(arch){
    case BIG_RIGHT:
          RIGHT_FORWARD_SPEED = 9000;
          LEFT_FORWARD_SPEED =  8000;
        break;
        
    case SMALL_RIGHT:
          RIGHT_FORWARD_SPEED = 8000;
          LEFT_FORWARD_SPEED =  7500;
        break;
        
    case BIG_LEFT:
          RIGHT_FORWARD_SPEED = 9000;
          LEFT_FORWARD_SPEED =  3000;
        break;
        
    case SMALL_LEFT:
          RIGHT_FORWARD_SPEED = 9000;
          LEFT_FORWARD_SPEED =  6000;
        break;
  default:break;
  }
  
  P8OUT  |= IR_LED;                     //turn IR LED on
  wait_100ms(5);                
  temp_right=ADC_Right_Detector;        //take ADC samples
  temp_left=ADC_Left_Detector;
 
  while(temp_right>=white && temp_left>=white){
      temp_right=ADC_Right_Detector;
      temp_left=ADC_Left_Detector;
  }
// detect_white();
// white traced, now look for black line
// travel straight
   
  while(temp_right<gray && temp_left<gray){   
      temp_right=ADC_Right_Detector;
      temp_left=ADC_Left_Detector;
  }
    electronic_brakes();
}

void intercept_and_follow(void){

   switch(state){
    case STEP1:                        // Intercept black line
            menu_on=RESET_VALUE;
            display_string_line(LCD_LINE1,"Intercept");
            intercept();
            state=STEP2;
            break;   
            
    case STEP2:                       // Stop at black line, turn towards line
            display_string_line(LCD_LINE1,"  Stop");
            wait_100ms(THREE_COUNTS);
            display_string_line(LCD_LINE1,"  Turn");
            spin2();
            state=STEP3;
            break;  
            
    case STEP3:                       // follow line
            display_string_line(LCD_LINE1,"  Follow..");
            wait_100ms(THREE_COUNTS);
            follow();
            TB0CCR0 = WHEEL_PERIOD;  
            state=STEP4;
            break;      
            
    case STEP4:                       // Exit circle
          state=RESET_STATE;
          intercept_flag=RESET_VALUE; 
          exit_circle();
          break;
   default:break;
   }
}


void go_forward(int duration){  
  wheels_off();
  
  //lcd_BIG_mid();
  forward_moving=TRUE;
  display_string_line(LCD_LINE1,"  Forward");
  
  RIGHT_FORWARD_SPEED = 9000;
  LEFT_FORWARD_SPEED =  6600;

  wait_100ms(duration);
  clear_display_line(LCD_LINE1);
  forward_moving=RESET_VALUE;
  wheels_off();
  //lcd_4line();
}

void go_reverse(int duration){   
  wheels_off();
  reverse_moving=TRUE;
  display_string_line(LCD_LINE1,"  Reverse");
  //lcd_BIG_mid();
  
  RIGHT_REVERSE_SPEED = 9000;
  LEFT_REVERSE_SPEED =  6600;

  wait_100ms(duration);
  clear_display_line(LCD_LINE1);
  reverse_moving=RESET_VALUE;
  wheels_off();
  //lcd_4line();
}

void turn_right(int duration){  
  wheels_off();
  //lcd_BIG_mid();
  display_string_line(LCD_LINE1,"  Right");
  
  
  LEFT_FORWARD_SPEED =  LFSPEED;

  wait_100ms(duration);
  clear_display_line(LCD_LINE1);
  wheels_off();
  //lcd_4line();
}

void turn_left(int duration){  
  wheels_off();
  //lcd_BIG_mid();
  display_string_line(LCD_LINE1,"  Left");
                      
  RIGHT_FORWARD_SPEED = RFSPEED;
 // LEFT_FORWARD_SPEED =  LFSPEED;

  wait_100ms(duration);
  clear_display_line(LCD_LINE1);
  wheels_off();
  //lcd_4line();
}

