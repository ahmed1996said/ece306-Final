//===========================================================================
// File Name : macros.h
//
// Description: This file contains the macros used by all the other files
//
// Author: Ahmed Al Mahrooqi
// Date: September 2018
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.1)
//===========================================================================


#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RESET_VALUE             (0)
#define PORTS                   (0x00) // PORTS
#define PWM_MODE                (0x01) // PWM_MODE
#define SET                     (0xFF)
#define RESET                   (0x00)
#define HBR_BRW                 (4)
#define HBR_CTLW                (0x5551)   


#define OFFSET                  (3)

#define TRUE                    (1)

#define IP_LENGTH               (13)
#define CARET_BUFFER            (5)
#define CR                      (0x0D)

#define TA0CCR0_INTERVAL        (6250)
#define TA0CCR1_INTERVAL        (12500)
#define TA0CCR2_INTERVAL        (625)
#define DEBOUNCE_TIME           (8)
#define FIFTY_MS                (0.05)
#define CMD_BUFFER_SIZE         (38)

#define LCD_UPDATE_TIME         (4)
#define LCD_BLINK_TIME          (10)
#define ONE_SEC_COUNT           (20)
#define ALV                     ('K')
#define PIN0                    ('9')
#define PIN1                    ('2')
#define PIN2                    ('2')
#define PIN3                    ('8')

#define MARGIN                  (300)
#define HI_WHEEL_PERIOD         (20000)

#define CHAR_0                  ('0')


#define ADC_CHAR_0              (0)
#define ADC_CHAR_1              (1)
#define ADC_CHAR_2              (2)
#define ADC_CHAR_3              (3)
#define ADC_CHAR_4              (4)

#define RIGHT_REVERSE_SPEED    (TB0CCR3)
#define RIGHT_FORWARD_SPEED    (TB0CCR4)
#define LEFT_REVERSE_SPEED     (TB0CCR5)
#define LEFT_FORWARD_SPEED     (TB0CCR6)

#define WHEEL_PERIOD            (10000)
#define WHEEL_OFF               (0)


#define TCP                     ('T')

#define FWD                     ('F')
#define RVR                     ('B')
#define LFT                     ('L')
#define RGT                     ('R')
#define INTCPT                  ('I')
#define STOP                    ('S')


#define CCR1_CASE               (2)
#define CCR2_CASE               (4)
#define OVERFLW_CASE            (14)


#define LCD_LINES               (4)
#define LCD_CHAR_NUM            (11)
#define LCD_CHAR_10             (10)

#define ONE_SEC                 (1)
#define TWO_SEC                 (20)
#define THREE_SEC               (30)
#define END_OF_SERIAL_RANGE     (0x08)


#define LEFT_SPD                (9000)
#define RIGHT_SPD               (7000)

#define TIME_SCALE              (2)

#define STEP0                    (0)
#define STEP1                    (1)
#define STEP2                    (2)
#define STEP3                    (3)
#define STEP4                    (4)
#define STEP5                    (5)
#define STEP6                    (6)
#define STEP7                    (7)
#define STEP8                    (8)
#define STEP9                    (9)
#define STEP10                   (10)

#define INDEX0                   (0)
#define INDEX1                   (1)

#define SLOWER                  ('S')
#define FASTER                  ('F')

#define START                   ('s')

#define CONVERSION_FACTOR       (48)
#define HUNDRED                 (100)
#define TEN                     (10)
#define FIVE_COUNTS             (5)

#define STOP_SIGNAL             ('$')

#define OPTION1_LIMIT           (683)
#define OPTION2_LIMIT           (1366)
#define OPTION3_LIMIT           (2049)
#define OPTION4_LIMIT           (2732)
#define OPTION5_LIMIT           (3415)

#define BIG_RIGHT               ('w')
#define BIG_LEFT                ('x')   
#define SMALL_RIGHT             ('y')
#define SMALL_LEFT              ('Z')

#define CALB                    ('B')
#define CALW                    ('W')

#define PRESS1                   (0)
#define PRESS2                   (1)
#define GRAY                     (3300)
#define CUTOFF                   (2500)

#define LF                      (0x0A)

#define LBR                     ('L')
#define HBR                     ('H')
#define IOTRST                  ('R')
#define SHOWIP                  ('P')

#define BRH                     ('l')
#define BRL                     ('h')

#define HALF                    (2)
#define BEGINNING               (0)
#define SMALL_RING_SIZE         (16)
#define RX                      (2)
#define TX                      (4)
#define NO_INTERRUPT            (0)

#define CARET                   ('^')
#define FIRST_HALF              (7)
#define SECOND_HALF             (7)
#define CORRECTION_FACTOR       (1)

#define ONE_COUNT               (1)
#define TWO_COUNTS              (2)
#define THREE_COUNTS            (3)
#define FOUR_COUNTS             (4)
#define FIFTEEN_COUNTS          (15)
#define TRAVEL_TIME             (35)

#define RRSPEED                 (4000)
#define LRSPEED                 (4000)

#define RFSPEED                 (8000)
#define LFSPEED                 (6000)

#define SPIN_SPEED              (4000)

#define LCD_LINE0               (0)
#define LCD_LINE1               (1)
#define LCD_LINE2               (2)
#define LCD_LINE3               (3)
#define time_25                 (25)
#define time_50                 (50)
#define time_75                 (75)
#define time_100                (100)
#define time_125                (125)

//PORT 1 pins
#define RED_LED               (0x01) // RED LED -   P1_0_LED1
#define GRN_LED               (0x02) // GREEN LED - P1_1_LED2
#define V_THUMB               (0x04) // ADC for Thumb wheel
#define TEST_PROBE            (0x08) // GP I/O to check code operation
#define V_DETECT_R            (0x10) // ADC for Right Detector
#define V_DETECT_L            (0x20) // ADC for Left Detector
#define SD_UCB0SOMO           (0x40) // SPI mode - slave in/master out for SD Card
#define SD_UCB0SOMI           (0x80) // SPI mode - slave out/master in for SD Card

//PORT_2 pins
#define BCLUART_TXD           (0x01)
#define BCLUART_RXD           (0x02) 
#define SD_SPICLK             (0x04) 
#define P2_3                  (0x08) 
#define P2_4                  (0x10) 
#define UCA1TXD               (0x20) 
#define UCA1RXD               (0x40) 
#define P2_7                  (0x80) 

//PORT_3 pins
#define IOT_RESET            (0x01) // RESET
#define IOT_PROG_MODE        (0x02) // IOT_PROG_MODE
#define IOT_LINK             (0x04) // IOT_LINK
#define IOT_PROG_SEL         (0x08) // IOT_PROG_SEL
#define L_REVERSE            (0x10) // Left Reverse
#define L_FORWARD            (0x20) // Left Forward
#define R_REVERSE            (0x40) // Right Reverse
#define R_FORWARD            (0x80) // Right Forward

//PORT_4 pins
#define SD_CS                (0x01) 
#define J4_31                (0x02)
#define J4_32                (0x04)
#define J4_33                (0x08)
#define UCB1_CS_LCD          (0x10)
#define P4_5                 (0x20)
#define P4_6                 (0x40)
#define J3_29                (0x80)



//PORT_5 pins
#define SPI_UCB1SIMO          (0x01)  // UCB1SIMO
#define SPI_UCB1SOMI          (0x02)  // UCB1SOMI
#define SPI_UCB1CLK           (0x04)  // SPI mode - clock output—UCB1CLK
#define RESET_LCD             (0x08)  // LCD Reset
#define P5_4_UNUSED           (0x10)  // UNUSED
#define BUTTON2               (0x20)  // Button 2
#define BUTTON1               (0x40)  // Button 1
#define LCD_BACKLITE          (0x80)  // LCD Backlite


//PORT_6 pins
#define UCA3TXD               (0X01)  // 
#define UCA3RXD               (0X02)  // 
#define J1_5                  (0X04)  // 
#define MAG_INT               (0X08)  // 
#define P6_4                  (0X10)  // 
#define P6_5                  (0X20)  // 
#define P6_6                  (0X40)  // 
#define P6_7                  (0X80)  // 


//PORT_7 pins 
#define I2CSDA               (0x01)
#define I2CSCL               (0x02)
#define SD_DETECT            (0x04)
#define J4_36                (0x08)
#define P7_4                 (0x10)
#define P7_5                 (0x20)
#define P7_6                 (0x40)
#define P7_7                 (0x80)

//PORT_8 pins
#define IR_LED               (0x01)
#define OPT_INT              (0x02)
#define TMP_INT              (0x04)
#define INT2                 (0x08)


//PORT_J pins
#define PJ_0                 (0x01)
#define PJ_1                 (0x02)
#define PJ_2                 (0x04)
#define PJ_3                 (0x08)
#define LFXIN                (0x10)
#define LFXOUT               (0x20)
#define HFXIN                (0x40)
#define HFXOUT               (0x80)

