#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"

volatile unsigned int ADC_Thumb;
volatile unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ir_on;


 
#pragma vector = ADC12_B_VECTOR
__interrupt void ADC12_ISR(void){
 switch(__even_in_range(ADC12IV, ADC12IV__ADC12RDYIFG)){
 case ADC12IV__NONE: break; // Vector 0: No interrupt
 case ADC12IV__ADC12OVIFG: break; // Vector 2: ADC12MEMx Overflow
 case ADC12IV__ADC12TOVIFG: break; // Vector 4: Conversion time overflow
 case ADC12IV__ADC12HIIFG: break; // Vector 6: ADC12BHI
 case ADC12IV__ADC12LOIFG: break; // Vector 8: ADC12BLO
 case ADC12IV__ADC12INIFG: break; // Vector 10: ADC12BIN
 case ADC12IV__ADC12IFG0: break; // Vector 12: ADC12MEM0 Interrupt
 case ADC12IV__ADC12IFG1: break; // Vector 14: ADC12MEM1 Interrupt
 case ADC12IV__ADC12IFG2: // Vector 16: ADC12MEM2 Interrupt
 ADC_Thumb = ADC12MEM0; // A02 ADC10INCH_2
 ADC_Right_Detector = ADC12MEM1; // A05 ADC10INCH_4
 ADC_Left_Detector = ADC12MEM2; // A04 ADC10INCH_5
 ADC12IER0 &=~ ADC12IE2;
 break;
 case ADC12IV__ADC12IFG3: break; // Vector 18: ADC12MEM3
 case ADC12IV__ADC12IFG4: break; // Vector 20: ADC12MEM4
 case ADC12IV__ADC12IFG5: break; // Vector 22: ADC12MEM5
 case ADC12IV__ADC12IFG6: break; // Vector 24: ADC12MEM6
 case ADC12IV__ADC12IFG7: break; // Vector 26: ADC12MEM7
 case ADC12IV__ADC12IFG8: break; // Vector 28: ADC12MEM8
 case ADC12IV__ADC12IFG9: break; // Vector 30: ADC12MEM9
 case ADC12IV__ADC12IFG10: break; // Vector 32: ADC12MEM10
 case ADC12IV__ADC12IFG11: break; // Vector 34: ADC12MEM11
 case ADC12IV__ADC12IFG12: break; // Vector 36: ADC12MEM12
 case ADC12IV__ADC12IFG13: break; // Vector 38: ADC12MEM13
 case ADC12IV__ADC12IFG14: break; // Vector 40: ADC12MEM14
 case ADC12IV__ADC12IFG15: break; // Vector 42: ADC12MEM15
 case ADC12IV__ADC12IFG16: break; // Vector 44: ADC12MEM16
 case ADC12IV__ADC12IFG17: break; // Vector 46: ADC12MEM17
 case ADC12IV__ADC12IFG18: break; // Vector 48: ADC12MEM18
 case ADC12IV__ADC12IFG19: break; // Vector 50: ADC12MEM19
 case ADC12IV__ADC12IFG20: break; // Vector 52: ADC12MEM20
 case ADC12IV__ADC12IFG21: break; // Vector 54: ADC12MEM21
 case ADC12IV__ADC12IFG22: break; // Vector 56: ADC12MEM22
 case ADC12IV__ADC12IFG23: break; // Vector 58: ADC12MEM23
 case ADC12IV__ADC12IFG24: break; // Vector 60: ADC12MEM24
 case ADC12IV__ADC12IFG25: break; // Vector 62: ADC12MEM25
 case ADC12IV__ADC12IFG26: break; // Vector 64: ADC12MEM26
 case ADC12IV__ADC12IFG27: break; // Vector 66: ADC12MEM27
 case ADC12IV__ADC12IFG28: break; // Vector 68: ADC12MEM28
 case ADC12IV__ADC12IFG29: break; // Vector 70: ADC12MEM29
 case ADC12IV__ADC12IFG30: break; // Vector 72: ADC12MEM30
 case ADC12IV__ADC12IFG31: break; // Vector 74: ADC12MEM31
 case ADC12IV__ADC12RDYIFG: break; // Vector 76: ADC12RDY
 default: break;
 }
}