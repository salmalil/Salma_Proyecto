#include "project.h"
#include "CyLib.h"
#include "Cypress_DevBoard.h"



///////////////////////////////////////////////
/* LCD (16x2 or 20x4) */
///////////////////////////////////////////////

void init_LCD(void) {    // Función de inicialización del módulo de display (16x2 ó 20x4)
    LCD_Write(0xFC);
    LCD_Write(0xFF);
    LCD_Write(LCD_Read() & (~0xFC));

    /* INIT CODE */
    CyDelay(80);                                                        /* Delay 40 ms */
    LCD_WriteControlNibble(LCD_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    CyDelay(10);                                                         /* Delay 5 ms */
    LCD_WriteControlNibble(LCD_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    CyDelay(30);                                                        /* Delay 15 ms */
    LCD_WriteControlNibble(LCD_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    CyDelay(2);                                                         /* Delay 1 ms */
    LCD_WriteControlNibble(LCD_DISPLAY_4_BIT_INIT);    /* Selects 4-bit mode */
    CyDelay(10);                                                         /* Delay 5 ms */

    LCD_WriteControl(LCD_CURSOR_AUTO_INCR_ON);    /* Incr Cursor After Writes */
    LCD_WriteControl(LCD_DISPLAY_CURSOR_ON);      /* Turn Display, Cursor ON */
    LCD_WriteControl(LCD_DISPLAY_2_LINES_5x10);   /* 2 Lines by 5x10 Characters */
    LCD_WriteControl(LCD_DISPLAY_CURSOR_OFF);     /* Turn Display, Cursor OFF */
    LCD_WriteControl(LCD_CLEAR_DISPLAY);          /* Clear LCD Screen */
    LCD_WriteControl(LCD_DISPLAY_ON_CURSOR_OFF);  /* Turn Display ON, Cursor OFF */
    LCD_WriteControl(LCD_RESET_CURSOR_POSITION);  /* Set Cursor to 0,0 */
    CyDelay(10);
}
void LCD_ClearDisplay(void) {    // Función de limpieza total de la pantalla
    LCD_WriteControl(LCD_CLEAR_DISPLAY);
    CyDelay(2);
}
void LCD_Position(unsigned char row, unsigned char column) {    // Función de posicionamiento de cursor en pantalla
/*
 * row      -> Fila donde va a empezar a escribir       (0-3)
 * column   -> Columna donde va a empezar a escribir    (0-15)

 * LCD_Position(1,6);
 */
    row = (LCD_ROW_MASK & row);

    switch(row) {
        case 0:
            LCD_WriteControl(LCD_ROW_0_START + (LCD_COLUMN_MASK & column));
            break;
        case 1:
            LCD_WriteControl(LCD_ROW_1_START + (LCD_COLUMN_MASK & column));
            break;
        case 2:
            LCD_WriteControl(LCD_ROW_2_START + (LCD_COLUMN_MASK & column));
            break;
        case 3:
            LCD_WriteControl(LCD_ROW_3_START + (LCD_COLUMN_MASK & column));
            break;
        default:
            break;
    }
}
void LCD_PrintHex8(unsigned int hex8) {    // Función de escritura de número hexadecimal de 8 bits - Función de conversión de número decimal a hexadecimal de 8 bits
/*
 * hex8 -> Número o variable a imprimir en formato hexadecimal
 *
 * LCD_PrintHex8(0xFE);
 * LCD_PrintHex8(254);
 * LCD_PrintHex8(x);
 */
    static unsigned char i;
    static unsigned int aux;
    static unsigned char shift = 8;
    static unsigned char length = 1;

    for(i = 0; i <= length; i++) {
        aux = hex8;
        if(i < length) {
            aux = (aux >> shift);
            shift -= 4;
        }
        aux &= 0x000F;
        if(aux < 10) {
            LCD_PutChar(aux + LCD_ZERO_CHAR_ASCII);
        }
        else {
            LCD_PutChar(aux + LCD_LETTER_CHAR_ASCII);
        }
    }
}
void LCD_PrintHex16(unsigned int hex16) {    // Función de escritura de número hexadecimal de 16 bits - Función de conversión de número decimal a hexadecimal de 16 bits
/*
* hex16 -> Número o variable a imprimir en formato hexadecimal
*
* LCD_PrintHex16(0xFFFE);
* LCD_PrintHex16(65534);
* LCD_PrintHex16(x);
*/
    static unsigned char i;
    static unsigned int aux;
    static unsigned char shift = 12;
    static unsigned char length = 3;

    for(i = 0; i <= length; i++) {
        aux = hex16;
        if(i < length) {
            aux = (aux >> shift);
            shift -= 4;
        }
        aux &= 0x000F;
        if(aux < 10) {
            LCD_PutChar(aux + LCD_ZERO_CHAR_ASCII);
        }
        else {
            LCD_PutChar(aux + LCD_LETTER_CHAR_ASCII);
        }
    }
}
void LCD_PrintHex(unsigned int hex) {    // Función de escritura de número hexadecimal hasta de 16 bits - Función de conversión de número decimal a hexadecimal hasta de 16 bits
/*
* hex -> Número o variable a imprimir en formato hexadecimal
*
* LCD_PrintHex(0x01);
* LCD_PrintHex(1);
* LCD_PrintHex(x);
*/
    static unsigned char i;
    static unsigned int aux;
    static unsigned char shift;
    static unsigned char length;

    if(hex > 4095) {
        length = 3;
        shift = 12;
    }
    else {
        if(hex > 255) {
            length = 2;
            shift = 8;
        }
        else {
            if(hex > 15) {
                length = 1;
                shift = 4;
            }
            else {
                length = 0;
                shift = 0;
            }
        }
    }

    for(i = 0; i <= length; i++) {
        aux = hex;
        if(i < length) {
            aux = (aux >> shift);
            shift -= 4;
        }
        aux &= 0x000F;
        if(aux < 10) {
            LCD_PutChar(aux + LCD_ZERO_CHAR_ASCII);
        }
        else {
            LCD_PutChar(aux + LCD_LETTER_CHAR_ASCII);
        }
    }
}
void LCD_PrintNumber(unsigned long value) {    // Función de impresión de número decimal de 32 bits
/*
 * value -> Número entero a imprimirse

 * LCD_PrintNumber(5894);
 * LCD_PrintNumber(x);
 */
    static unsigned char tmpDigit;
    char number[LCD_NUMBER_OF_REMAINDERS_U32 + 1];
    static unsigned char digIndex = LCD_NUMBER_OF_REMAINDERS_U32;

    /* Esta API convertirá un número decimal a string; y este string va a ser
     * llenado del fin al inicio. Configurar primero caracter de terminación.
     */
    number[digIndex] = '\0';
    digIndex--;

    /* Cargar éstos en orden inverso */
    while(value >= LCD_TEN) {
    /* Extraer dígito decimal, indexado por 'digIndex', desde 'value',
     * y convertirlo a un caracter tipo ASCII
     */
        tmpDigit = ((value % LCD_TEN) + LCD_ZERO_CHAR_ASCII);
        number[digIndex] = tmpDigit;
        value /= LCD_TEN;
        digIndex--;
    }

    /* Extraer el último dígito decimal 'digIndex', desde 'value',
     * y convertirlo a un caracter tipo ASCII
     */
    tmpDigit = ((value % LCD_TEN) + LCD_ZERO_CHAR_ASCII);
    number[digIndex] = tmpDigit;

    while(digIndex < LCD_TEN) {
        LCD_PutChar(number[digIndex]);
        digIndex++;
    }
}
void LCD_PrintString(char *text) {    // Función de impresión en pantalla de cadena alfanumérica
/*
 * text -> Texto entre comillas a imprimir

 * LCD_PrintString("Texas DevBoard");
 */
    char *c;

    c = text;
    while((c != 0) && (*c != 0)) {
        LCD_WriteData(*c);
        c++;
    }
}
void LCD_PutChar(unsigned char character) {    // Función de impresión de caracter simple
/*
 * character -> Caracter simple a imprimir

 * LCD_PutChar('°');
 * LCD_PutChar(0xDF);
 */
    LCD_WriteData(character);
}
void LCD_WriteControl(unsigned char cByte) {
    static unsigned char nibble;

    //delay_ms(10); // 10
    nibble = cByte >> LCD_NIBBLE_SHIFT;

    /* Escribir nibble más significativo */
    LCD_WriteControlNibble(nibble);
    nibble = cByte & LCD_NIBBLE_MASK;

    /* Escribir nibble menos significativo */
    LCD_WriteControlNibble(nibble);
    //delay_ms(5); // 5
}
void LCD_WriteData(unsigned char dByte) {
    static unsigned char nibble;

    //delay_ms(10); // 10
    nibble = dByte >> LCD_NIBBLE_SHIFT;

    /* Escribir nibble más significativo */
    LCD_WriteDataNibble(nibble);
    nibble = dByte & LCD_NIBBLE_MASK;

    /* Escribir nibble menos significativo */
    LCD_WriteDataNibble(nibble);
    //delay_ms(5); // 5
}
void LCD_WriteControlNibble(unsigned char nibble) {
    static unsigned char dPort = 0x00;

    dPort = (nibble << LCD_NIBBLE_SHIFT);
    dPort &= (~RS);

    LCD_Write(dPort | 0x03);
    LCD_Write(LCD_Read() | E);
    CyDelay(2);    // 2
    LCD_Write(LCD_Read() & ~E);
}
void LCD_WriteDataNibble(unsigned char nibble) {
    static unsigned char dPort = 0x00;

    dPort = (nibble << LCD_NIBBLE_SHIFT);
    dPort |= RS;

    LCD_Write(dPort | 0x03);
    LCD_Write(LCD_Read() | E);
    CyDelay(2);    // 2
    LCD_Write(LCD_Read() & ~E);
}
