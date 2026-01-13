
#define LCD_RST PIN_D0
#define LCD_CS PIN_D1
#define LCD_DC PIN_D2
#include <main_.h>
#BIT Data_Pin = 0xF81.2                       // Pin mapped to PORTB.0 
#BIT Data_Pin_Direction = 0xF93.2  
#use spi(SPI1,BAUD=1000000,MODE=3,BITS=8,STREAM=LCD_STREAM)
#include <NOKIA5110.c>

#use standard_io(D)
#use standard_io(B)

#byte PORTD=0xF83

void main(void){

LCD_Begin();
LCD_Clear();
LCD_SetContrast(50);
LCD_TextSize(1);

int seconds=50;
int minutes=59;
int hours=12;

while(TRUE){

   seconds++;
   delay_ms(1000);
   
   if(seconds>59){
   seconds=0;
   minutes++;
   LCD_Clear();
   }
   if(minutes>59){
   minutes=0;
   hours++;
   LCD_Clear();
   }
   if(hours>24){
   hours=0;
   LCD_Clear();
   }
   LCD_GotoXY(10,1);
LCD_Print("Clock:");
   LCD_GotoXY(15,10);
   printf(LCD_Print,"%d:%d:%d",hours,minutes,seconds);
   LCD_Display();
}
}
