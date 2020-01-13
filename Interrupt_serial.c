#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h" 

extern volatile unsigned int A0_rx_ring_wr;
extern volatile unsigned int A3_rx_ring_wr;

extern volatile unsigned int A0_rx_ring_rd;
extern volatile unsigned int A3_rx_ring_rd;

extern volatile char A0_Char_Rx[SMALL_RING_SIZE];
extern volatile char A3_Char_Rx[SMALL_RING_SIZE];
extern unsigned volatile int UCA3_index;
extern char test_command[SMALL_RING_SIZE];
extern char recieved[SMALL_RING_SIZE];
extern volatile unsigned int transmit_done;
unsigned int recieved_flag_A0=RESET_VALUE;
unsigned int recieved_flag_A3=RESET_VALUE;
unsigned char rx_temp_A0;
unsigned char rx_temp_A3;
unsigned int A0_recieve_complete;
unsigned volatile int command_recieved=RESET_VALUE;
unsigned volatile int command_recieved3=RESET_VALUE;
char temp;
extern volatile unsigned int command_complete;
extern unsigned volatile int command_complete_A3;
extern unsigned volatile int command_recieved_A3;
extern unsigned int temp_index;
unsigned int index_a3;
unsigned int temp_index3;
extern char process_buffer[SMALL_RING_SIZE];
char process_buffer3[SMALL_RING_SIZE];
char command_buffer3[CMD_BUFFER_SIZE];
volatile unsigned int command_index;
char temp_A3;
volatile unsigned int i_recieved;
volatile unsigned int ip_length;
volatile unsigned int ip_recieved;
volatile unsigned int p=RESET_VALUE;
unsigned int find_ip=TRUE;
char ip_address[SMALL_RING_SIZE];
unsigned int ip_found;
extern volatile unsigned int cmd_cnt;
unsigned int caret_index[CARET_BUFFER];
unsigned int copy_ip;
volatile unsigned int er_stop;



//------------------------------------------------------------------------------

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  
    switch(__even_in_range(UCA0IV,END_OF_SERIAL_RANGE)){
      
       case NO_INTERRUPT: // Vector 0 - no interrupt
         break;
          
       case RX: // Vector 2 - RXIFG
            
         temp = UCA0RXBUF;                       // RX -> A0_Char_Rx character
         
         
         if(temp == CARET)                           // if CARET, we got a command
            command_recieved=TRUE; 
             
         if(command_recieved){
            process_buffer[temp_index++]=temp;             //if command, save to process buffer, deal with in main
            if(temp == LF){
              command_recieved=RESET_VALUE;
              command_complete=TRUE;                     // command recieve complete, deal with in main
              }
         }else{            
            while (!(UCA3IFG & UCTXIFG));                               // USCI_A3 TX buffer ready?
            UCA3TXBUF=temp;                     //if not command, send out to UCA3
         }
        
       if(temp_index >= (SMALL_RING_SIZE))
         temp_index = BEGINNING;            // Circular buffer back to beginning
               
            break;
            
          default: break;
   }
}
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
#pragma vector=EUSCI_A3_VECTOR
__interrupt void eUSCI_A3_ISR(void){
  

switch(__even_in_range(UCA3IV,END_OF_SERIAL_RANGE)){
 
 case NO_INTERRUPT: // Vector 0 - no interrupt
        break;
          
 case RX: // Vector 2 - RXIFG   

   
    temp_A3 = UCA3RXBUF;
    process_buffer3[temp_index3]=temp_A3; 
    
    if(temp_A3==STOP_SIGNAL)
      er_stop=TRUE;
 
    // find IP on start up         
     if(find_ip) {  
         if(temp_A3== '1'){            
            ip_recieved=TRUE;
          }
         if(ip_recieved)
         {
          ip_address[p]=temp_A3; 
          p++;
          ip_length++;
          if(ip_length>=IP_LENGTH){
            ip_recieved=RESET_VALUE;
            ip_length=RESET_VALUE;
            find_ip=RESET_VALUE;
            ip_recieved=RESET_VALUE;
            ip_found = TRUE;
          }
         }
       }          
    //--------------- 
     
    //check if command recieved from IoT 
      if(temp_A3 == CARET){                         // if CARET, we got a command
            command_recieved_A3=TRUE;
            caret_index[cmd_cnt] = index_a3;       // save indexes of commands in an int array
            cmd_cnt++;
      }

             
         if(command_recieved_A3){
            command_buffer3[index_a3]=temp_A3;     //if command, save to command buffer
            if(temp_A3 == LF|| temp==0x20){
              command_recieved_A3=RESET_VALUE;
              command_complete_A3=TRUE;              // command recieve complete, deal with in main
              }
         }
            
    //-------------     
      
         
         while (!(UCA0IFG & UCTXIFG)); // USCI_A3 TX buffer ready?
         UCA0TXBUF = temp_A3;
         
          if(++temp_index3 >= (SMALL_RING_SIZE))
            temp_index3 = BEGINNING;            // Circular buffer back to beginning
                  
          if(++index_a3 >= (CMD_BUFFER_SIZE))
            index_a3 = BEGINNING;            // Circular buffer back to beginning
          
          
        break;
 
        default:break;
 }
}
//------------------------------------------------------------------------------
