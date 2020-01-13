#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"


void Init_ADC(void){
//------------------------------------------------------------------------------
// Configure ADC12

// ADC10CTL0 Register Description
  ADC12CTL0 = RESET_STATE;
  ADC12CTL0 |= ADC12SHT0_2;     // 16 ADC clocks
  ADC12CTL0 |= ADC12SHT1_2;     // 16 ADC clocks
  ADC12CTL0 |= ADC12MSC;        // First rising edge SHI signal triggers sampling timer
  ADC12CTL0 |= ADC12ON;         // ADC12 on: turn on AtoD converter

// ADC10CTL1 Register Description
  ADC12CTL1 = RESET_STATE;
  ADC12CTL1 |= ADC12PDIV_0;     // Predivide ADC12_B clock source by 1
  ADC12CTL1 |= ADC12SHS_0;      // sample-and-hold source ADC12SC
  ADC12CTL1 |= ADC12SHP;      // SAMPCON signal is sourced from the sampling timer.
  ADC12CTL1 |= ADC12ISSH_0;     // sample-input signal is not inverted
  ADC12CTL1 |= ADC12DIV_0;      // / 1 clock divider
  ADC12CTL1 |= ADC12SSEL0;      // ADC12OSC (MODOSC)
  ADC12CTL1 |= ADC12CONSEQ_3;   // Repeat-sequence-of-channels

// ADC12CTL2 Register Description
  ADC12CTL2 = RESET_STATE;
  ADC12CTL2 |= ADC12RES_2;      // 12-bit conversion results / 14 clock cycle conversion
  ADC12CTL2 |= ADC12DF_0;       // Binary unsigned
  ADC12CTL2 |= ADC12PWRMD_0;    // Regular power mode where sample rate is not restricted

// ADC12CTL3 Register Description
  ADC12CTL3 = RESET_STATE;
  ADC12CTL3 |= ADC12ICH3MAP_0;  // external pin is selected for ADC input channel A26
  ADC12CTL3 |= ADC12ICH2MAP_0;  // external pin is selected for ADC input channel A27
  ADC12CTL3 |= ADC12ICH1MAP_0;  // external pin is selected for ADC input channel A28
  ADC12CTL3 |= ADC12ICH0MAP_0;  // external pin is selected for ADC input channel A29
  ADC12CTL3 |= ADC12TCMAP_1;    // ADC internal temperature sensor ADC input channel A30
  ADC12CTL3 |= ADC12BATMAP_1;   // ADC internal 1/2 x AVCC is ADC input channel A31
  ADC12CTL3 |= ADC12CSTARTADD_0; // 0h to 1Fh, corresponding to ADC12MEM0 to ADC12MEM31

// ADC10MCTL0 Register Description
  ADC12MCTL0 = RESET_STATE;
  ADC12MCTL0 |= ADC12WINC_0;    // Comparator window disabled
  ADC12MCTL0 |= ADC12DIF_0;     // Single-ended mode enabled
  ADC12MCTL0 |= ADC12VRSEL_0;   // VR+ = AVCC, VR- = AVSS
  ADC12MCTL0 |= ADC12INCH_2;    // channel = A2 Thumb Wheel

  ADC12MCTL1 = RESET_STATE;
  ADC12MCTL1 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL1 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL1 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL1 |= ADC12INCH_5;  // channel = A5 Left

  ADC12MCTL2 = RESET_STATE;
  ADC12MCTL2 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL2 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL2 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL2 |= ADC12INCH_4;  // channel = A4 Right

  ADC12MCTL3 = RESET_STATE;
  ADC12MCTL3 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL3 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL3 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL3 |= ADC12INCH_30; // Temp sensor

  ADC12MCTL4 = RESET_STATE;
  ADC12MCTL4 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL4 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL4 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL4 |= ADC12INCH_31; // Battery voltage monitor
  ADC12MCTL4 |= ADC12EOS;     // End of Sequence

// ADC12IER0-2 Register Descriptions
  ADC12IER0 = RESET_STATE;    // Interrupts for channels  0 - 15
  ADC12IER1 = RESET_STATE;    // Interrupts for channels 16 - 31
  ADC12IER2 = RESET_STATE;    // Interrupts for ADC12RDYIE ADC12TOVIE ADC12OVIE
                              // ADC12HIIE ADC12LOIE ADC12INIE
							  
    //ADC12IER0 |= ADC12IE4;      // Generate Interrupt for MEM2 ADC Data load//
   // ADC12IER0 |= ADC12IE2;    // Generate Interrupt for MEM2 ADC Data load
   // ADC12IER0 |= ADC12IE0;    // Enable ADC conv complete interrupt

  ADC12CTL0 |= ADC12ENC;     // enable conversion
  ADC12CTL0 |= ADC12SC;      // Start sampling
//------------------------------------------------------------------------------
}