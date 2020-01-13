//===========================================================================
// File Name : led.c
//
// Description: This file contains initializations for LEDs
//
// Author: Ahmed Al Mahrooqi
// Date: September 2018
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"



void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P1OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}

