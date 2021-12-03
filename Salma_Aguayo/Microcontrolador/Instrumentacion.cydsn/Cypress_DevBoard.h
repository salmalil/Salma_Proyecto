#if !defined(CY_DEV_CDB_H)
#define CY_DEV_CDB_H

    
    
#include "cytypes.h"
#include "cyfitter.h"
#include "project.h"
    
    
    
/***************************************
*           API Constants
***************************************/

////////////////////////////////////////////////////
/* LCD & GLCD interface pin */
#define E                               0x08
#define RS                              0x04
#define RW                              0x02

/* LCD commands */
#define LCD_DISPLAY_8_BIT_INIT          0x03
#define LCD_DISPLAY_4_BIT_INIT          0x02
#define LCD_DISPLAY_CURSOR_OFF          0x08
#define LCD_CLEAR_DISPLAY               0x01
#define LCD_CURSOR_AUTO_INCR_ON         0x06
#define LCD_DISPLAY_CURSOR_ON           0x0E
#define LCD_DISPLAY_2_LINES_5x10        0x2C
#define LCD_DISPLAY_ON_CURSOR_OFF       0x0C
#define LCD_RESET_CURSOR_POSITION       0x03
#define LCD_CURSOR_WINK                 0x0D
#define LCD_CURSOR_BLINK                0x0F
#define LCD_CURSOR_SH_LEFT              0x10
#define LCD_CURSOR_SH_RIGHT             0x14
#define LCD_DISPLAY_SCRL_LEFT           0x18
#define LCD_DISPLAY_SCRL_RIGHT          0x1E
#define LCD_CURSOR_HOME                 0x02
#define LCD_CURSOR_LEFT                 0x04
#define LCD_CURSOR_RIGHT                0x06

/* LCD conversion routines */
#define LCD_NUMBER_OF_REMAINDERS_U32    0x0A
#define LCD_TEN                         0x0A
#define LCD_8_BIT_SHIFT                 8
#define LCD_32_BIT_SHIFT                32
#define LCD_ZERO_CHAR_ASCII             0x30
#define LCD_LETTER_CHAR_ASCII           0x37

/* LCD nibble offset and mask */
#define LCD_NIBBLE_SHIFT                0x04
#define LCD_NIBBLE_MASK                 0x0F

/* LCD Module Address Constants */
#define LCD_ROW_0_START                 0x80
#define LCD_ROW_1_START                 0xC0
#define LCD_ROW_2_START                 0x94
#define LCD_ROW_3_START                 0xD4

/* LCD position control mask */
#define LCD_COLUMN_MASK                 0x0F
#define LCD_ROW_MASK                    0x03
////////////////////////////////////////////////////
/* GLCD commands */
#define GLCD_CLEAR_DISPLAY              0x01

/* GLCD nibble offset and mask */
#define GLCD_NIBBLE_SHIFT               0x04
#define GLCD_NIBBLE_MASK                0x0F

/* GLCD Module Address Constants */
#define GLCD_ROW_0_START                0x80
#define GLCD_ROW_1_START                0x90
#define GLCD_ROW_2_START                0x88
#define GLCD_ROW_3_START                0x98

/* GLCD DDRAM control mask */
#define GLCD_CDRAM_COLUMN_MASK          0x07
#define GLCD_CDRAM_ROW_MASK             0x03

/* GLCD GDRAM control mask */
#define GLCD_GDRAM_ADDRESS_MASK         0x80
#define GLCD_GDRAM_X_MASK               0x0F
#define GLCD_GDRAM_Y_MASK               0x3F

/* GLCD-SRL API*/
#define SID                             0x80    // RW
#define SCLK                            0x40    // E
#define CS                              0x20    // RS

    
    
/*******************************************************************************
*  LCD (16x2 or 20x4)
********************************************************************************/

void init_LCD(void);
void LCD_ClearDisplay(void);
void LCD_Position(unsigned char row, unsigned char column);
void LCD_PrintHex8(unsigned int hex8);
void LCD_PrintHex16(unsigned int hex16);
void LCD_PrintHex(unsigned int hex);
void LCD_PrintNumber(unsigned long value);
void LCD_PrintString(char *text);
void LCD_PutChar(unsigned char character);
void LCD_WriteControl(unsigned char cByte);
void LCD_WriteData(unsigned char dByte);
void LCD_WriteControlNibble(unsigned char nibble);
void LCD_WriteDataNibble(unsigned char nibble);
    

    
#endif
