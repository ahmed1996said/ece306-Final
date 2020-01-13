#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h" 

volatile unsigned int A0_rx_ring_wr;
volatile unsigned int A3_rx_ring_wr;

volatile unsigned int A0_rx_ring_rd;
volatile unsigned int A3_rx_ring_rd;

volatile unsigned int usb_rx_ring_rd;

volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;

volatile char A0_Char_Rx[SMALL_RING_SIZE];
volatile char A3_Char_Rx[SMALL_RING_SIZE];

unsigned int here=RESET_VALUE;
extern unsigned int command;
extern char process_buffer[SMALL_RING_SIZE];
extern volatile unsigned int command_complete;
extern unsigned int temp_index;



void out_character_A0(char character){

// The while loop will stall as long as the Flag is not set [port is busy]
 while (!(UCA0IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
 UCA0TXBUF = character;

}

void out_string_A0(char *character){
char message_string[SMALL_RING_SIZE];

// The while loop will stall as long as the Flag is not set [port is busy]
 while (!(UCA0IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
 
  strcpy(message_string,character);
  
  for(int x=RESET_VALUE; x<=SMALL_RING_SIZE ;x++){
    out_character_A0(message_string[x]);
    if(message_string[x+1]==NULL) break;
  }
  
  out_character_A0(CR);
  out_character_A0(LF);
 
}

void out_character_A3(char character){

// The while loop will stall as long as the Flag is not set [port is busy]
 while (!(UCA3IFG & UCTXIFG)); // USCI_A3 TX buffer ready?
 UCA3TXBUF = character;
 
}

void out_string_A3(char *character){

  char message_string[SMALL_RING_SIZE];
// The while loop will stall as long as the Flag is not set [port is busy]
 while (!(UCA3IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
 
  strcpy(message_string,character);
  
  for(int x=RESET_VALUE; x<=SMALL_RING_SIZE ;x++){
    out_character_A3(message_string[x]);
    if(message_string[x+1]==NULL) break;
  }
  
  out_character_A3(CR);
  out_character_A3(LF);
 
}
/*
void fram_commands(void){
    switch(process_buffer[temp_index-OFFSET]){    // interrogate command
      case CARET:              // Confirm communication
        out_string_A0("Here!");
        break;
        
     case SLOWER:              //9,600Hz
        Init_Serial_UCA0(BRL);
        Init_Serial_UCA3(BRL);
        out_string_A0("BR = 9600");    
        break;
        
     case FASTER:             //115,200Hz
        Init_Serial_UCA0(BRH);
        Init_Serial_UCA3(BRH); 
        out_string_A0("BR = 115,200");
        break;  
    default:break;
    }
    command_complete=RESET_VALUE;
    
 }

*/



//----------------------------------------------------------------------------
void Init_Serial_UCA0(char BR){
  //default baud rate set to 115,200Hz
 int i;
 
  for(i=RESET_VALUE; i<SMALL_RING_SIZE; i++){
    A0_Char_Rx[i] = RESET;         // USB Rx Buffer
    }
  
    A0_rx_ring_wr = BEGINNING;
    A0_rx_ring_rd = BEGINNING;
    
    usb_tx_ring_wr = BEGINNING;
    usb_tx_ring_rd = BEGINNING;
    
    
    // Configure UART 0
        
      UCA0CTLW0 = RESET_VALUE;                  // Use word register
      UCA0CTLW0 |= UCSWRST;           // Set Software reset enable
      UCA0CTLW0 |= UCSSEL__SMCLK;     // Set SMCLK as fBRCLK
      

      
    UCA0BRW = HBR_BRW;             // 115,200 Baud
    UCA0MCTLW = HBR_CTLW ;
    //display_string_line(3," 115,200Hz");
    
//    if(BR ==BRL)
//    {
//      UCA0BRW = 52;             // 9,600 Baud
//      UCA0MCTLW = 0x4911 ;
//      display_string_line(3," 9,600Hz");       
//    }
//    
//    
//     if(BR == 'k')       //"high" baud rate = 460,800 Hz
//     {
//       UCA0BRW = 1;             // 460,800 Baud
//       UCA0MCTLW = 0x4A11 ;
//       display_string_line(3," 460,800Hz");
//     }
    
   // UCA0CTL1 &= ~UCSWRST; // Release from reset
      UCA0CTLW0 &= ~UCSWRST;
     UCA0IE |= UCRXIE; // Enable RX interrupt
    
//--------------------------------------------------------------------------------------------------------------------    
}


void Init_Serial_UCA3(char BR){
  //default baud rate set to 460,800Hz
 int i;
 
  for(i=RESET_VALUE; i<SMALL_RING_SIZE; i++){
    A3_Char_Rx[i] = RESET;         // USB Rx Buffer
    }
  
    A3_rx_ring_wr = BEGINNING;
    A3_rx_ring_rd = BEGINNING;

    
 /*   for(i=0; i<LARGE_RING_SIZE; i++){ // May not use this
      USB_Char_Tx[i] = 0x00;         // USB Tx Buffer
      }
    */
    
    usb_tx_ring_wr = BEGINNING;
    usb_tx_ring_rd = BEGINNING;
    
    
    // Configure UART 3
        
      UCA3CTLW0 = RESET_VALUE;                  // Use word register
      UCA3CTLW0 |= UCSWRST;           // Set Software reset enable
      UCA3CTLW0 |= UCSSEL__SMCLK;     // Set SMCLK as fBRCLK
      
    UCA3BRW = HBR_BRW;             // 115,200 Baud
    UCA3MCTLW = HBR_CTLW ;
    //display_string_line(3," 115,200Hz");
        
//    if(BR ==BRL)
//    {
//      UCA3BRW = 52;             // 9,600 Baud
//      UCA3MCTLW = 0x4911 ;
//      display_string_line(3," 9,600Hz");       
//    }
//    
//    
//    if(BR == 'k')       //"high" baud rate = 460,800 Hz
//    {
//      UCA3BRW = 1;             // 460,800 Baud
//      UCA3MCTLW = 0x4A11 ;
//      display_string_line(3," 460,800Hz");
//    }
      
    //UCA3CTL1 &= ~UCSWRST; // Release from reset
      UCA3CTLW0 &= ~UCSWRST;
    UCA3IE |= UCRXIE; // Enable RX interrupt      

    
//--------------------------------------------------------------------------------------------------------------------    
}

void Init_Serial(void){
Init_Serial_UCA0(BRH);  
Init_Serial_UCA3(BRH);
}