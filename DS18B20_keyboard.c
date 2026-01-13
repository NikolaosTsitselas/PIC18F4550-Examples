//thermostatis me keyboard these temp !!!!




#include <main_.h>
#include <1wire.c>
#include <DS18B20.h>
#include <flex_lcd_sim.h>
#include <keypad_sim.h>


#use standard_io(B)
#use standard_io(D)
#use fast_io(C)

#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTD=0xF83

char state=1;
char k;
float High;
float Low;
int digit1;
int digit2;
float temp;
void main(void){

   //set_tris_b(0xff);
   set_tris_c(0x01);
   set_tris_d(0xff);
   
   setup_ccp1(CCP_OFF);
   setup_ccp2(CCP_OFF);
   setup_adc(ADC_OFF);
   setup_adc_ports(NO_ANALOGS);
   
   lcd_init();
   lcd_putc("\f");
   
   kbd_init();
   
   
   
while(TRUE){


switch(state){
   
         case 1:  
               lcd_gotoxy(1,1);
               lcd_putc("Give the 1st digit\n of high temp:");
               k=kbd_getc();
                  while(k!=0){
                     digit1=k&0b00001111;
                     lcd_gotoxy(15,2);
                     printf(lcd_putc,"%d",digit1);
                     delay_ms(1000);
                     lcd_putc("\f");
                     state=2;
                     break;
                  }
                  break;
          case 2: 
                  
                  lcd_gotoxy(1,1);
               lcd_putc("Give the 2nd digit\n of high temp:");
               k=kbd_getc();
                  while(k!=0){
                     digit2=k&0b00001111;
                     lcd_gotoxy(15,2);
                     printf(lcd_putc,"%d",digit2);
                     High=digit1*10+digit2;
                     delay_ms(1000);
                     lcd_putc("\f");
                     lcd_gotoxy(1,1);
                     printf(lcd_putc,"High temp= %.2f C",High);
                     delay_ms(1000);
                     lcd_putc("\f");
                     state=3;
                     break;
                  }
                  break;
             
             case 3:
                  
                 lcd_gotoxy(1,1);
               lcd_putc("Give the 1st digit\n of low temp:");
               k=kbd_getc();
                  while(k!=0){
                     digit1=k&0b00001111;
                     lcd_gotoxy(15,2);
                     printf(lcd_putc,"%d",digit1);
                     delay_ms(1000);
                     lcd_putc("\f");
                     state=4;
                     break;
                  }
                  break;
               
               case 4:
                  
                   
                  lcd_gotoxy(1,1);
               lcd_putc("Give the 2nd digit\n of low temp:");
               k=kbd_getc();
                  while(k!=0){
                     digit2=k&0b00001111;
                     lcd_gotoxy(15,2);
                     printf(lcd_putc,"%d",digit2);
                     Low=digit1*10+digit2;
                     delay_ms(1000);
                     lcd_putc("\f");
                     lcd_gotoxy(1,1);
                     printf(lcd_putc,"Low temp= %.2f C",Low);
                     delay_ms(1000);
                     lcd_putc("\f");
                     state=5;
                     break;
                  }
                  break;





case 5: 
temp=ds1820_read();




if(temp>=High){

lcd_gotoxy(1,0);
lcd_putc("Thermostat OFF");
output_low(PIN_E0);
}


if(temp<=Low){
lcd_gotoxy(1,0);
lcd_putc("Thermostat ON ");
output_high(PIN_E0);
}

lcd_gotoxy(1,1);
printf(lcd_putc,"Temp = %.2f C        ",temp);
}

   }
   
   
}








   
