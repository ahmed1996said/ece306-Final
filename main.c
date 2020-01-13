//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Ahmed Al Mahrooqi
//  Sep 2018
//  Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"

// Global Variables

extern char display_line[LCD_LINES][LCD_CHAR_NUM];
extern char *display[LCD_LINES];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile unsigned int lcd_update_count;
extern volatile unsigned int b1;
unsigned int intercept_flag=RESET_VALUE;


extern volatile unsigned int b2 ;
volatile unsigned int b2_count=RESET_VALUE;
volatile unsigned int b1_count=RESET_VALUE;
extern volatile unsigned int led_blink_count;

volatile unsigned int timer_count=RESET_VALUE;

extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;

volatile unsigned int state = RESET_VALUE;
unsigned int start_sampling = RESET_VALUE;
extern volatile char one_time;
unsigned volatile int debounce_count = RESET_STATE;

char pwm_state;
char chosen_direction;

unsigned int cutoff;
volatile unsigned int timer;
unsigned int step3_done=RESET_VALUE;
unsigned int temp_time=RESET_STATE;

unsigned volatile int UCA3_index;


volatile unsigned int transmit_done;
unsigned int j;
extern unsigned int recieved_flag_A0;
extern unsigned int recieved_flag_A3;

extern unsigned char rx_temp_A0;
extern unsigned char rx_temp_A3;

unsigned int A0_index=0;
extern volatile char A0_Char_Rx[SMALL_RING_SIZE];
extern volatile char A3_Char_Rx[SMALL_RING_SIZE];

extern volatile unsigned int A3_rx_ring_wr;
extern volatile unsigned int A0_rx_ring_wr;

volatile unsigned int command_complete_A3=RESET_VALUE;
volatile unsigned int command_recieved_A3=RESET_VALUE;

char process_buffer[SMALL_RING_SIZE];
unsigned int temp_index=RESET_VALUE;
extern unsigned int A0_recieve_complete;
unsigned int cmd_index;
unsigned int time_requested;

unsigned int current_thumb;
char option;
unsigned int password=RESET_VALUE;

volatile unsigned int command_complete;
extern volatile unsigned int command_index;
extern volatile unsigned int command_recieved;
unsigned int menu_on=TRUE;
extern char process_buffer3[SMALL_RING_SIZE];

extern char ip_address[SMALL_RING_SIZE];
extern unsigned int ip_found;
extern unsigned int index_a3;
extern char command_buffer3[CMD_BUFFER_SIZE];
unsigned int a;
unsigned int b;
unsigned int c;
unsigned int ii;
extern unsigned int caret_index[CARET_BUFFER];
volatile unsigned int cmd_cnt;
unsigned int temp_right;
unsigned int temp_left;
unsigned int white=1850;
unsigned int black=3200;
unsigned int gray =2525;
extern char arch;
unsigned int adc_on=TRUE;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variokaakmnqh1ables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_ADC();                          // Initialize ADC configurations
  Init_LEDs();                         // Initialize LEDs
  clear_display();                     
  Init_Serial();
  lcd_BIG_mid();
  
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
 //clear_display();

  enable_display_update();
  Display_Update(LCD_LINE0,LCD_LINE0,LCD_LINE0,LCD_LINE0);
  P5OUT &= ~LCD_BACKLITE; 
  command_recieved = RESET_VALUE;
  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------

  while(ALWAYS) {                      


// Commands recieved from IoT    
 if(command_complete_A3)
   service_IOT_command();
 
// Intercept line 
 if(intercept_flag)
    intercept_and_follow();
      
// Show IP Address
 if(ip_found)
    print_ip_address();

// Auto-reconnect when dissociated
 if( strstr(process_buffer3,"Dis")||strstr(process_buffer3,"DIS") )
   reconnect_connection();  
 
 
// BUTTON 1 POLLING 
 if(b1){   
  // When button 1 pressed, perform action depending on option selected on menu   
    switch(option){     
      case START:
            menu_on=RESET_VALUE;
            adc_on = RESET_VALUE;
            display_string_line(LCD_LINE1,"  Wait...");
           break;
           
      case TCP:              //establish TCP connection on specified port 
           out_string_A3("AT+NSTCP=9228,1");
           wait_100ms(TWO_COUNTS);
           if(strstr(process_buffer3,"OK")){
            display_string_line(LCD_LINE2,"   OK");
            wait_100ms(FOUR_COUNTS);
            clear_display_line(LCD_LINE2); 
           }
           out_string_A3("AT+WKEEPALIVE=10");
           break;
           
      case IOTRST:          //Release IOT_RESET
           P3OUT  |=  IOT_RESET;
           display_string_line(LCD_LINE2,"   DONE!");
           wait_100ms(TWO_COUNTS);
           clear_display_line(LCD_LINE2);
           break;
           
      case SHOWIP:          //Show IP Address
           ip_found=TRUE;
           break;
           
      case CALW:          // calibrate white
            P8OUT  |= IR_LED;                   //turn IR LED on
            wait_100ms(FOUR_COUNTS);    
            temp_right= ADC_Right_Detector;
            temp_left=  ADC_Left_Detector;
            P8OUT  &= ~IR_LED;
            white = (temp_right + temp_left) / 2;
            gray=(white+black)/2;
            HEXtoBCD2(white);
            wait_100ms(FOUR_COUNTS);
            clear_display_line(LCD_LINE2);
           break;
           
      case CALB:          // calibrate black
            P8OUT  |= IR_LED;
            wait_100ms(FOUR_COUNTS);
            temp_right= ADC_Right_Detector;
            temp_left=  ADC_Left_Detector;
            P8OUT  &= ~IR_LED;
            black = (temp_right + temp_left) / 2;
            gray=(white+black)/2;
            HEXtoBCD2(black);
            wait_100ms(FOUR_COUNTS);
            clear_display_line(LCD_LINE2);
           break;     
    default:break;     
   }
         b1 = RESET_STATE;
  }
    
// BUTTON 2 polling  
  if(b2){                //go back to menu
          clear_display();
          menu_on=TRUE;
          adc_on=TRUE;
          lcd_BIG_mid();
      b2 = RESET_STATE;
    } 
    
    
// Thumbwheel menu polling   
  if(menu_on)
    main_menu();

// Performs actions every 200ms  
  timer_polling();               
    
 Display_Process();
  } 
//------------------------------------------------------------------------------
}


