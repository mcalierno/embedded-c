#ifndef _LCD_H_
#define _LCD_H_

#include "MKL46Z4.h"
#include <stdbool.h>

#if 1  // VREF to VLL1
/* Following configuration is used for LCD default initialization  */
#define _LCDRVEN          (1)  //
#define _LCDRVTRIM        (8)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDCPSEL         (1)          //  charge pump select 0 or 1
#define _LCDLOADADJUST    (3)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDALTDIV        (0)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDALRCLKSOURCE  (0)         // 0 -- External clock       1 --  Alternate clock

#define _LCDCLKPSL        (0)         //  Clock divider to generate the LCD Waveforms
#define _LCDSUPPLY        (1)
#define _LCDHREF          (0)          // 0 or 1
#define _LCDCLKSOURCE     (1)         // 0 -- External clock       1 --  Alternate clock
#define _LCDLCK           (1)         //Any number between 0 and 7
#define _LCDBLINKRATE     (3)         //Any number between 0 and 7


#else    //VLL3 to VDD internally
/* Following configuration is used for LCD default initialization  */
#define _LCDCLKSOURCE     (1)         // 0 -- External clock       1 --  Alternate clock
#define _LCDALRCLKSOURCE  (0)         // 0 -- External clock       1 --  Alternate clock
#define _LCDCLKPSL        (0)         //  Clock divider to generate the LCD Waveforms
#define _LCDSUPPLY        (0)
#define _LCDLOADADJUST    (3)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDALTDIV        (0)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDRVTRIM        (0)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDHREF          (0)          // 0 or 1
#define _LCDCPSEL         (1)          // 0 or 1
#define _LCDRVEN          (0)  //
#define _LCDBLINKRATE     (3)         //Any number between 0 and 7
#define _LCDLCK           (0)         //Any number between 0 and 7

#endif




/*~|~|~|~|~|~|~|~|~|~|~|~|~|~  LCD  Control Register 0  ~|~|~|~|~|~|~|~|~|~|~|~|~*/
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|*/
#define _LCDINTENABLE         (1)

/*~|~|~|~|~|~|~|~|~|~|~|~|~|~  LCD  Control Register 1  ~|~|~|~|~|~|~|~|~|~|~|~|~|*/
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|*/
#define _LCDFRAMEINTERRUPT     (0)        //0 Disabel Frame Frequency Interrupt
                                                                       //1 Enable an LCD interrupt that coincides with the LCD frame frequency
#define _LCDFULLCPLDIRIVE      (0)        // 0 GPIO shared with the LCD. Inputs levels and internal pullup reference to VDD
                                                                      // 1 If VSUPPLY=11and RVEN=0. Inputs levels and internal pullup reference to VLL3
#define _LCDWAITMODE           (0)       // 0 Allows the LCD driver and charge pump to conitnue running during wait mode
                                                                     //  1 Disable the LCD when the MCU goes into wait mode
#define _LCDSTOPMODE           (0)     // 0 Allows the LCD driver and charge pump to conitnue running during stop2 or stop3

                                                                     //  1 Disable the LCD when and charge pump when the MCU goes into stop2 or stop3

/*~|~|~|~|~|~|~|~|~|~|~|~|~|~  LCD  Voltage Supply Register  ~|~|~|~|~|~|~|~|~|~|~|~*/
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|*/
#define _LCDHIGHREF             (0)      //0 Divide input VIREG=1.0v
                                                                    //1 Do not divide the input VIREG=1.67v
#define _LCDBBYPASS             (0)      //Determines wheter the internal LCD op amp buffer is bypassed
                                                                      //0 Buffered mode
                                                                      //1 Unbuffered mode

/*~|~|~|~|~|~|~|~|~|~|~|~|~|~  LCD  Regulated Voltage Control |~|~|~|~|~|~|~|~|~|~*/
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|*/
#define _LCDCONTRAST                    (1)       //Contrast by software   0 -- Disable    1-- Enable
#define _LVLCONTRAST                    (0)       //Any number between 0  and 15, if the number is bigger the glass get darker

/*~|~|~|~|~|~|~|~|~|~|~|~|~|~  LCD  Blink Control Register ~|~|~|~|~|~|~|~|~|~|~|~*/
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|*/
#define _LCDBLINKCONTROL         (0)   //0 Disable blink mode
                                                                       //1 Enable blink mode
#define _LCDALTMODE              (0)   //0 Normal display
                                                                      //1 Alternate display for 4 backplanes or less the LCD backplane sequencer changes to otuput an alternate display
#define _LCDBLANKDISP           (0)  //0 Do not blank display
                                                                      //1 Blank display if you put it in 0 the text before blank is manteined
#define _LCDBLINKMODE           (0)  //0 Display blank during the blink period
                                                                     //1 Display alternate displat during blink period (Ignored if duty is 5 or greater)


//Calculated values
#define _LCDUSEDPINS   (_LCDFRONTPLANES + _LCDBACKPLANES)
#define _LCDDUTY       (_LCDBACKPLANES-1)         //Any number between 0 and 7
#define  LCD_WF_BASE    LCD_WF3TO0


// General definitions used by the LCD library
#define  SymbolON(LCDn,bit)     *((uint8 *)&LCD_WF_BASE + LCDn)  |=  (1<<(bit))
#define  SymbolOFF(LCDn,bit)    *((uint8 *)&LCD_WF_BASE + LCDn)  &= ~(1<<(bit))
//#define  LCD_WF(x)              *((uint8 *)&LCD_WF_BASE + x)

/*LCD Fault Detections Consts*/
#define  FP_TYPE  0x00         // pin is a Front Plane
#define  BP_TYPE  0x80         // pin is Back Plane


// Fault Detect Preescaler Options
#define FDPRS_1      0
#define FDPRS_2      1
#define FDPRS_4      2
#define FDPRS_8      3
#define FDPRS_16     4
#define FDPRS_32     5
#define FDPRS_64     6
#define FDPRS_128    7

// Fault Detect Sample Window Width Values
#define FDSWW_4           0
#define FDSWW_8           1
#define FDSWW_16          2
#define FDSWW_32          3
#define FDSWW_64          4
#define FDSWW_128         5
#define FDSWW_256         6
#define FDSWW_512         7


/*
  Mask Bit definitions used f
*/

#define     mBIT0   1
#define     mBIT1   2
#define     mBIT2   4
#define     mBIT3   8
#define     mBIT4   16
#define     mBIT5   32
#define     mBIT6   64
#define     mBIT7   128
#define     mBIT8   256
#define     mBIT9   512
#define     mBIT10   1024
#define     mBIT11   2048
#define     mBIT12   4096
#define     mBIT13   8192
#define     mBIT14   16384
#define     mBIT15   32768
#define     mBIT16   65536
#define     mBIT17   131072
#define     mBIT18   262144
#define     mBIT19   524288
#define     mBIT20   1048576
#define     mBIT21   2097152
#define     mBIT22   4194304
#define     mBIT23   8388608
#define     mBIT24   16777216
#define     mBIT25   33554432
#define     mBIT26   67108864
#define     mBIT27   134217728
#define     mBIT28   268435456
#define     mBIT29   536870912
#define     mBIT30   1073741824
#define     mBIT31   2147483648


#define    mBIT32      1
#define    mBIT33      2
#define    mBIT34      4
#define    mBIT35      8
#define    mBIT36      16
#define    mBIT37      32
#define    mBIT38      64
#define    mBIT39      128
#define    mBIT40      256
#define    mBIT41      512
#define    mBIT42      1024
#define    mBIT43      2048
#define    mBIT44      4096
#define    mBIT45      8192
#define    mBIT46      16384
#define    mBIT47      32768
#define    mBIT48      65536
#define    mBIT49      131072
#define    mBIT50      262144
#define    mBIT51      524288
#define    mBIT52      1048576
#define    mBIT53      2097152
#define    mBIT54      4194304
#define    mBIT55      8388608
#define    mBIT56      16777216
#define    mBIT57      33554432
#define    mBIT58      67108864
#define    mBIT59      134217728
#define    mBIT60      268435456
#define    mBIT61      536870912
#define    mBIT62      1073741824
#define    mBIT63      2147483648

/*^^^^^^^^^^^^^^^^      LCD HARDWARE CONECTION ^^^^^^^^^^^^^^^^^^^^^^^^*/
#define  _LCDFRONTPLANES   (8)                             // # of frontPlanes
#define  _LCDBACKPLANES    (4)                              // # of backplanes

/*
   LCD logical organization definition
    This section indicate how the LCD is distributed  how many characteres of (7-seg, 14,seg, 16 seg, or colums in case of Dot Matrix) does it contain
   First character is forced only one can be written



*/
// HARDWARE_CONFIG Changing LCD pins Allows to verify all LCD pins easily
// if HARDWARE_CONFIG  == 0 FRDM-KL46 RevB
// if HARDWARE_CONFIG  == 1 FRDM-KL46 RevA


#ifdef FRDM_REVA
#define HARDWARE_CONFIG 1
#else
#define HARDWARE_CONFIG 0
#endif


#define _CHARNUM    (4)  //number of chars that can be written
#define _CHAR_SIZE   (2)  // Used only when Dot Matrix is used
#define _LCDTYPE     (2)  //indicate how many LCD_WF are required to write a single Character / or Colum in case of DOT matrix LCD

/*
  Following definitons indicate how Charaters are associated to waveform
*/
/* Hardware configuration  */
#if HARDWARE_CONFIG == 0
#undef DOT_MATRIX

// LCD PIN1 to LCDWF0  Rev B
#define   CHAR1a    37 // LCD Pin 5
#define   CHAR1b    17 // LCD Pin 6
#define   CHAR2a    7 // LCD Pin 7
#define   CHAR2b    8 // LCD Pin 8
#define   CHAR3a    53 // LCD Pin 9
#define   CHAR3b    38 // LCD Pin 10
#define   CHAR4a    10 // LCD Pin 11
#define   CHAR4b    11 // LCD Pin 12
#define   CHARCOM0    40 // LCD Pin 1
#define   CHARCOM1    52 // LCD Pin 2
#define   CHARCOM2    19 // LCD Pin 3
#define   CHARCOM3    18 // LCD Pin 4

/*Special Symbols */
#define SPECIAL_SYMBOL_COUNT   4

#define   _LCD_DP1_ON()      SymbolON(17,0)
#define   _LCD_DP2_ON()      SymbolON(8,0)
#define   _LCD_DP3_ON()      SymbolON(38,0)
#define   _LCD_COL_ON()      SymbolON(11,0)

#define   _LCD_DP1_OFF()      SymbolOFF(17,0)
#define   _LCD_DP2_OFF()      SymbolOFF(8,0)
#define   _LCD_DP3_OFF()      SymbolOFF(38,0)
#define   _LCD_COL_OFF()      SymbolOFF(11,0)



// LCD PIN1 to LCDWF2   for FRDM-KL46Z
#elif HARDWARE_CONFIG == 1
#define   CHAR1a    37 // LCD Pin 5
#define   CHAR1b    17 // LCD Pin 6
#define   CHAR2a    7 // LCD Pin 7
#define   CHAR2b    8 // LCD Pin 8
#define   CHAR3a    12 // LCD Pin 9
#define   CHAR3b    26 // LCD Pin 10
#define   CHAR4a    10 // LCD Pin 11
#define   CHAR4b    11 // LCD Pin 12
#define   CHARCOM0    51 // LCD Pin 1
#define   CHARCOM1    52 // LCD Pin 2
#define   CHARCOM2    19 // LCD Pin 3
#define   CHARCOM3    16 // LCD Pin 4

#define SPECIAL_SYMBOL_COUNT   4


#define   _LCD_DP1_ON()      SymbolON(17,0)
#define   _LCD_DP2_ON()      SymbolON(8,0)
#define   _LCD_DP3_ON()      SymbolON(26,0)
#define   _LCD_COL_ON()      SymbolON(11,0)

#define   _LCD_DP1_OFF()      SymbolOFF(17,0)
#define   _LCD_DP2_OFF()      SymbolOFF(8,0)
#define   _LCD_DP3_OFF()      SymbolOFF(26,0)
#define   _LCD_COL_OFF()      SymbolOFF(11,0)



#endif


/*Ascii Codification table information */
#define ASCCI_TABLE_START '0'   // indicates which is the first Ascii character in the table
#define ASCCI_TABLE_END   'Z'   // indicates which is the first Ascii character in the table
#define BLANK_CHARACTER   '>'  // Inidicate which ASCII character is a blank character (depends on ASCII table)

#define _ALLON 0xFF     // Used for ALL_on function


#define SEGDP 0x01
#define SEGC  0x02
#define SEGB  0x04
#define SEGA  0x08

#define SEGD  0x01
#define SEGE  0x02
#define SEGG  0x04
#define SEGF  0x08


/* Fault detect initial limits */

/* Fault detect initial parameters and limits */
#define FAULTD_FP_FDPRS  FDPRS_32
#define FAULTD_FP_FDSWW  FDSWW_128
#define FAULTD_BP_FDPRS  FDPRS_64
#define FAULTD_BP_FDSWW  FDSWW_128

#define FAULTD_FP_HI  127
#define FAULTD_FP_LO  110
#define FAULTD_BP_HI  127
#define FAULTD_BP_LO  110
#define FAULTD_TIME   6

////////////

void LCDInitialise(void);
void LCDAllSegments(int mode);
void LCDDP(int pos, bool on);
void LCDDP1(int mode);
void LCDDP2(int mode);
void LCDDP3(int mode);
void LCDColon(bool on);
void LCDBlink(int blink);
void LCDWriteChar(char lbValue);
void LCDWrite(const char * format, ...);

#endif
