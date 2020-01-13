//===========================================================================
// File Name : ports.c
//
// Description: This file contains port initializations
//
// Author: Ahmed Al Mahrooqi
// Date: September 2018
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"


void Init_Port_1(void){
  // Port 1 configures LEDs, ADC and Test probe

  P1SEL0 = RESET;       // GP I/O
  P1SEL1 = RESET;       // GP I/O
  P1DIR  = RESET;       // Set P1 direction to input

  //P1_0
  P1SEL0 &= ~RED_LED;   // GP I/O
  P1SEL1 &= ~RED_LED;   // GP I/O
  P1OUT  |=  RED_LED;   // SET RED LED ON
  P1DIR  |=  RED_LED;   // SET RED LED direction to output

  //P1_1
  P1SEL0 &= ~GRN_LED;   // GP I/O
  P1SEL1 &= ~GRN_LED;   // GP I/O
  P1OUT  &= ~GRN_LED;   // SET GREEN LED ON
  P1DIR  |=  GRN_LED;   // SET GREEN LED direction to output

  //P1_2
  P1SEL0 |= V_THUMB;   //  ADC input for thumbwheel (A2)
  P1SEL1 |= V_THUMB;   //  ADC input for thumbwheel

  //P1_3
  P1SEL0 &= ~TEST_PROBE;   // GP I/O
  P1SEL1 &= ~TEST_PROBE;   // GP I/O
  P1OUT  &=  ~TEST_PROBE;   // SET TEST_PROBE OFF
  P1DIR  |=  TEST_PROBE;      // SET TEST_PROBE direction to output

  //P1_4
  P1SEL0 |=  V_DETECT_R;
  P1SEL1 |=  V_DETECT_R;

  //P1_5
  P1SEL0 |= V_DETECT_L;
  P1SEL1 |= V_DETECT_L;

  //P1_6
  P1SEL0 &= ~SD_UCB0SOMO;
  P1SEL1 |=  SD_UCB0SOMO;

  //P1_7
  P1SEL0 &= ~SD_UCB0SOMI;
  P1SEL1 |=  SD_UCB0SOMI;
}

void Init_Port_2(void){
  //Port 2 configures UCA0

  P2SEL0 = RESET;       // GP I/O
  P2SEL1 = RESET;       // GP I/O
  P2DIR  = RESET;       // Set P2 direction to input

  //P2_0
  P2SEL0 &= ~BCLUART_TXD;
  P2SEL1 |=  BCLUART_TXD;

  //P2_1
  P2SEL0 &= ~BCLUART_RXD;
  P2SEL1 |=  BCLUART_RXD;

  //P2_2
  P2SEL0 |= V_THUMB;
  P2SEL1 |= V_THUMB;

  //P2_3
  P2SEL0 &= ~P2_3;       // GP I/O
  P2SEL1 &= ~P2_3;       // GP I/O
  P2DIR  &= ~P2_3;      // SET P2_3 direction to input

  //P2_4
  P2SEL0 &= ~P2_4;       // GP I/O
  P2SEL1 &= ~P2_4;       // GP I/O
  P2DIR  &= ~P2_4;      // SET P2_4 direction to input

  //P2_5
  P2SEL0 &= ~UCA1TXD;
  P2SEL1 |=  UCA1TXD;

  //P2_6
  P2SEL0 &= ~UCA1RXD;
  P2SEL1 |=  UCA1RXD;

  //P2_7
  P2SEL0 &=  ~P2_7;
  P2SEL1 &=  ~P2_7;
  P2DIR  &=  ~P2_7;          // SET P2_3 direction to input
}

void Init_Port_3(void){
  //Port 3 configures pins used for IOT module

  P3SEL0 = RESET;            // GP I/O
  P3SEL1 = RESET;           // GP I/O
  //P3DIR = RESET;            // GP I/O


  //P3_0
  P3SEL0 &= ~IOT_RESET;
  P3SEL1 &= ~IOT_RESET;
  P3OUT &= ~IOT_RESET;
  P3DIR |= IOT_RESET;              // Set direction to output

  //P3_1
  P3SEL0 &=  ~IOT_PROG_MODE;   // Set to GP I/O
  P3SEL1 &=  ~IOT_PROG_MODE;   // Set to GP I/O
  P3DIR  &=  ~IOT_PROG_MODE;   // Set direction to input

  //P3_2
  P3SEL0 &=  ~IOT_LINK;     // Set to GP I/O
  P3SEL1 &=  ~IOT_LINK;     // Set to GP I/O
  P3DIR  &=  ~IOT_LINK;     // Set direction to input

  //P3_3
  P3SEL0 &=  ~IOT_PROG_SEL;   // Set to GP I/O
  P3SEL1 &=  ~IOT_PROG_SEL;   // Set to GP I/O
  P3DIR  &=  ~IOT_PROG_SEL;   // Set direction to input

  //P3_4
  P3SEL0 |=   L_REVERSE;   // Set to GP I/O
  P3SEL1 &=  ~L_REVERSE;   // Set to GP I/O
  P3DIR |=    L_REVERSE; // Set direction to output

  //P3_5
  P3SEL0 |=  L_FORWARD;   // Set to GP I/O
  P3SEL1 &= ~L_FORWARD;   // Set to GP I/O
  P3DIR  |=  L_FORWARD; // Set direction to output

  //P3_6
  P3SEL0 |=  R_REVERSE;   // Set to GP I/O
  P3SEL1 &= ~R_REVERSE;   // Set to GP I/O
  P3DIR |=   R_REVERSE; // Set direction to output

  //P3_7
  P3SEL0 |=  R_FORWARD;   // Set to GP I/O
  P3SEL1 &= ~R_FORWARD;   // Set to GP I/O  
  P3DIR  |=  R_FORWARD; // Set direction to output

}

void Init_Port_4(void){

  //Port 4 configures the LCD screen
  P4SEL0 = RESET;            // GP I/O
  P4SEL1 = RESET;           // GP I/O
  P4DIR  = RESET;          // Set P4 direction to input

  //P4_0
  P4SEL0 &= ~SD_CS;        // GP I/O
  P4SEL1 &= ~SD_CS;       // GP I/O

  //P4_1
  P4SEL0 &= ~J4_31;       // GP I/O
  P4SEL1 &= ~J4_31;       // GP I/O

  //P4_2
  P4SEL0 &= ~J4_32;       // GP I/O
  P4SEL1 &= ~J4_32;       // GP I/O

  //P4_3
  P4SEL0 &= ~J4_33;       // GP I/O
  P4SEL1 &= ~J4_33;       // GP I/O

  //P4_4
  P4SEL0 |=   UCB1_CS_LCD; // UCB1
  P4SEL1 &=  ~UCB1_CS_LCD; //  UCB1
  P4DIR  |=   UCB1_CS_LCD; // Set direction to output

  //P4_5
  P4SEL0 &= ~P4_5;       // GP I/O
  P4SEL1 &= ~P4_5;       // GP I/O

  //P4_6
  P4SEL0 &= ~P4_6;       // GP I/O
  P4SEL1 &= ~P4_6;       // GP I/O

  //P4_7
  P4SEL0 &= ~J3_29;      // GP I/O
  P4SEL1 &= ~J3_29;      // GP I/O
}

void Init_Port_5(void){
  //Port 5 configures the SPI bus, LCD reset, and Buttons

  P5SEL0 = RESET;                // GP I/O
  P5SEL1 = RESET;                // GP I/O
  P5DIR  = RESET;                // Set P5 direction to input

  //P5_0
  P5SEL0 |= SPI_UCB1SIMO;        // USCI_B1 SIMO pin
  P5SEL1 &= ~SPI_UCB1SIMO;       // USCI_B1 SIMO pin

  //P5_1
  P5SEL0 |= SPI_UCB1SOMI;        // USCI_B1 SOMI pin
  P5SEL1 &= ~SPI_UCB1SOMI;       // USCI_B1 SOMI pin

  //P5_2
  P5SEL0 |= SPI_UCB1CLK;         // USCI_B1 SCLK pin
  P5SEL1 &= ~SPI_UCB1CLK;        // USCI_B1 SCLK pin

  //P5_3
  P5SEL0 &= ~RESET_LCD;          // Set GP I/O for RESET_LCD
  P5SEL1 &= ~RESET_LCD;          // Set GP I/O for RESET_LCD
  P5OUT |= RESET_LCD;            // Set RESET_LCD Off [High]
  P5DIR |= RESET_LCD;            // Set RESET_LCD direction to output

  //P5_4
  P5SEL0 &= ~P5_4_UNUSED;        // Set GP I/O for P5_4_UNUSED
  P5SEL1  &= ~P5_4_UNUSED;        // Set GP I/O for P5_4_UNUSED
  P5DIR   &= ~P5_4_UNUSED;         // Set RESET_LCD direction to input

  //P5_5
  P5SEL0 &= ~BUTTON2;            // Set GP I/O for BUTTON2
  P5SEL1 &= ~BUTTON2;            // Set GP I/O for BUTTON2
  P5OUT |= BUTTON2;              // Configure pullup resistor
  P5DIR &= ~BUTTON2;             // Direction = input
  P5REN |= BUTTON2;              // Enable pullup resistor
  P5IES |= BUTTON2;           // P5.5 Hi/Lo edge interrupt
  P5IFG &= ~BUTTON2;          // Clear all P5.6 interrupt flags
  P5IE |= BUTTON2;            // P5.5 interrupt enabled

  //P5_6
  P5SEL0 &= ~BUTTON1;            // Set GP I/O for BUTTON1
  P5SEL1 &= ~BUTTON1;            // Set GP I/O for BUTTON1
  P5OUT |= BUTTON1;              // Configure pullup resistor
  P5DIR &= ~BUTTON1;             // Direction = input
  P5REN |= BUTTON1;              // Enable pullup resistor
  P5IES |= BUTTON1;           // P5.6 Hi/Lo edge interrupt
  P5IFG &= ~BUTTON1;          // Clear all P5.5 interrupt flags
  P5IE |= BUTTON1;            // P5.6 interrupt enabled

  //P5_7
  P5SEL0 &= ~LCD_BACKLITE;       // Set GP I/O for LCD_BACKLITE
  P5SEL1 &= ~LCD_BACKLITE;       // Set GP I/O for LCD_BACKLITE
  P5OUT |= LCD_BACKLITE;         // Set LCD_BACKLITE On [High]
  P5DIR |= LCD_BACKLITE;         // Set LCD_BACKLITE direction to output
}

void Init_Port_6(void){
  //Port 6 configures UCA3 transmit and recieve functions

  P6SEL0 = RESET;                // GP I/O
  P6SEL1 = RESET;                // GP I/O
  P6DIR  = RESET;               // Set P6 direction to input

  //P6_0
  P6SEL0 |=    UCA3TXD;
  P6SEL1 &=   ~UCA3TXD;

  //P6_1
  P6SEL0 |=    UCA3RXD;
  P6SEL1 &=   ~UCA3RXD;

  //P6_2
  P6SEL0 &=    ~J1_5;    //GP I/O
  P6SEL1 &=    ~J1_5;    //GP I/O
  P6DIR  &=    ~J1_5;    //Set direction to input

  //P6_3
  P6SEL0 &=   ~MAG_INT;    //GP I/O
  P6SEL1 &=   ~MAG_INT;    //GP I/O
  P6DIR  &=   ~MAG_INT;    //Set direction to input

  //P6_4
  P6SEL0 &=   ~P6_4;    //GP I/O
  P6SEL1 &=   ~P6_4;    //GP I/O
  P6DIR  &=   ~P6_4;    //Set direction to input

  //P6_5
  P6SEL0 &=   ~P6_5;    //GP I/O
  P6SEL1 &=   ~P6_5;    //GP I/O
  P6DIR  &=   ~P6_5;    //Set direction to input

  //P6_6
  P6SEL0 &=   ~P6_6;    //GP I/O
  P6SEL1 &=   ~P6_6;    //GP I/O
  P6DIR  &=   ~P6_6;    //Set direction to input

  //P6_7
  P6SEL0 &=   ~P6_7;    //GP I/O
  P6SEL1 &=   ~P6_7;    //GP I/O
  P6DIR  &=   ~P6_7;    //Set direction to input
}

void Init_Port_7(void){
  // Port 7 configured all pins to GP I/O
  P7SEL0 = RESET;          // GP I/O
  P7SEL1 = RESET;          // GP I/O
  P7DIR  = RESET;          // Set P7 direction to input

  //P7_0
  P7SEL0 &= ~I2CSDA;      // GP I/O
  P7SEL1 &= ~I2CSDA;      // GP I/O

  //P7_1
  P7SEL0 &= ~I2CSCL;      // GP I/O
  P7SEL1 &= ~I2CSCL;      // GP I/O

  //P7_2
  P7SEL0 &= ~SD_DETECT;      // GP I/O
  P7SEL1 &= ~SD_DETECT;      // GP I/O

  //P7_3
  P7SEL0 &= ~J4_36;      // GP I/O
  P7SEL1 &= ~J4_36;      // GP I/O

  //P7_4
  P7SEL0 &= ~P7_4;       // GP I/O
  P7SEL1 &= ~P7_4;       // GP I/O

  //P7_5
  P7SEL0 &= ~P7_5;       // GP I/O
  P7SEL1 &= ~P7_5;       // GP I/O

  //P7_6
  P7SEL0 &= ~P7_6;       // GP I/O
  P7SEL1 &= ~P7_6;       // GP I/O

  //P7_7
  P7SEL0 &= ~P7_7;       // GP I/O
  P7SEL1 &= ~P7_7;       // GP I/O
}

void Init_Port_8(void){
  //Port 8 configures the IR LED

  P8SEL0 = RESET;               // GP I/O
  P8SEL1 = RESET;               // GP I/O
  P8DIR  = RESET;              // Set P8 direction to input

  //P8_0
  P8SEL0 &= ~IR_LED;            // GP I/O
  P8SEL1 &= ~IR_LED;            // GP I/O
  P8DIR  |=  IR_LED;            // set direction to output
  P8OUT  &= ~IR_LED;            // IR_LED off

  //P8_1
  P8SEL0 &= ~OPT_INT;             // GP I/O
  P8SEL1 &= ~OPT_INT;             // GP I/O

  //P8_2
  P8SEL0 &= ~TMP_INT;             // GP I/O
  P8SEL1 &= ~TMP_INT;             // GP I/O

  //P8_3
  P8SEL0 &= ~INT2;             // GP I/O
  P8SEL1 &= ~INT2;             // GP I/O
}

void Init_Port_J(void){
  //Port J configures the Low and High Frequencey

  //PJSEL0 = RESET;                // GP I/O
  //PJSEL1 = RESET;                // GP I/O
  PJDIR  = RESET;               // Set PJ direction to input
  PJOUT  = RESET;               // Set PJ direction to input

  //PJ_0
  PJSEL0 &= ~PJ_0;                // GP I/O
  PJSEL1 &= ~PJ_0;                // GP I/O

  //PJ_1
  PJSEL0 &= ~PJ_1;                // GP I/O
  PJSEL1 &= ~PJ_1;                // GP I/O

  //PJ_2
  PJSEL0 &= ~PJ_2;                // GP I/O
  PJSEL1 &= ~PJ_2;                // GP I/O

  //PJ_3
  PJSEL0 &= ~PJ_3;                // GP I/O
  PJSEL1 &= ~PJ_3;                // GP I/O

  //PJ_4
  PJSEL0 |= LFXIN;                 // LFXIN
  PJSEL1 &= ~LFXIN;                // LFXIN

  //PJ_5
  PJSEL0 |= LFXOUT;                 // LFXOUT
  PJSEL1 &= ~LFXOUT;                // LFXOUT

  //PJ_6
  PJSEL0 |= HFXIN;                 // HFXIN
  PJSEL1 &= ~HFXIN;                // HFXIN

  //PJ_7
  PJSEL0 |=  HFXOUT;                // HFXOUT
  PJSEL1 &= ~HFXOUT;                // HFXOUT
}

void Init_Ports(void){
  Init_Port_1();
  Init_Port_2();
  Init_Port_3();
  Init_Port_4();
  Init_Port_5();
  Init_Port_6();
  Init_Port_7();
  Init_Port_8();
  Init_Port_J();
}
