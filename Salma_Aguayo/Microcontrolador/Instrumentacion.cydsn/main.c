#include "project.h"
#include <stdbool.h>
bool bandera=0;
unsigned char basico[4]={128,64,32,16};
unsigned char taxi[5]={128,64,32,16,8};
unsigned char cera[6]={128,64,32,16,8,2};
unsigned char motor[5]={128,64,32,16,4};
unsigned char total[7]={128,64,32,16,8,4,2};
unsigned char posicion=0;
bool b_serial=false;
unsigned char caracter=0;

CY_ISR(interruptUART)
{
    caracter=Serial_GetChar();
    Serial_PutChar(caracter);
    b_serial=true;
}
int main(void)
{
     LEDS_Write(0x00);
    posicion=0;
    CyGlobalIntEnable;
isrUART_StartEx(interruptUART);
Serial_Start();

    for(;;)
    {
        if(b_serial)
        {
            b_serial=false;
            switch(caracter)
            {
                case 'b':
                while(posicion!=4){
                 LEDS_Write(basico[posicion]);
                posicion++;
                CyDelay(2000);
                }
                posicion=0;
                 LEDS_Write(0);
                break;
                case 'x':
                while(posicion!=5){
                 LEDS_Write(taxi[posicion]);
                posicion++;
                CyDelay(2000);
                }
                posicion=0;
                 LEDS_Write(0);
                break;
                case 'e':
                while(posicion!=6){
                 LEDS_Write(cera[posicion]);
                posicion++;
                CyDelay(2000);
                }
                posicion=0;
                LEDS_Write(0);
                break;
                case 'm':
                while(posicion!=5){
                 LEDS_Write(motor[posicion]);
                posicion++;
                CyDelay(2000);
                }
                posicion=0;
                 LEDS_Write(0);
                break;
                case 't':
                while(posicion!=7){
                 LEDS_Write(total[posicion]);
                posicion++;
                CyDelay(2000);
                }
                posicion=0;
                 LEDS_Write(0);
                break;
            } 
        }
    }
}