#include  "msp430.h"
#include  "functions.h"
#include  <string.h>
#include  "macros.h"

char adc_char[ADC_CHAR_4];
extern char display_line[LCD_LINES][LCD_CHAR_NUM];
extern volatile unsigned char update_display;



void HEXtoBCD2(int hex_value){
  int value=RESET_VALUE;
 
  adc_char[ADC_CHAR_0] = CHAR_0;
  clear_display_line(LCD_LINE2);
  
  while (hex_value > 999){
    hex_value = hex_value - 1000;
    value++;
    adc_char[ADC_CHAR_0] = 0x30 + value;
    }
  
  value = RESET_STATE;
  adc_char[ADC_CHAR_1] = 0x30 + value;
    while (hex_value > 99){
      hex_value = hex_value - 100;
      value++;
      adc_char[ADC_CHAR_1] = 0x30 + value;
    }
    
    value = RESET_STATE;
     adc_char[ADC_CHAR_2] = 0x30 + value;

    while (hex_value > 9){
      hex_value = hex_value - 10;
      value++;
    adc_char[ADC_CHAR_2] = 0x30 + value;

    }
    
  adc_char[ADC_CHAR_3] = 0x30 + hex_value;


   //for(i=RESET_STATE; i<=ADC_CHAR_3;i++)
    strncpy(display_line[LCD_LINE2], adc_char,4);
   
   //strcpy(display_line[LCD_LINE2]+4," ");

  Display_Update(RESET_VALUE,RESET_VALUE,RESET_VALUE,RESET_VALUE);


}











