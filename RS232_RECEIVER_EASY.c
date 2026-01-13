#include <main_.h>
#use delay(clock=8000000)
#include <flex_lcd_sim.h>

#use rs232(baud=19200,xmit=PIN_C6,rcv=PIN_C7,bits=8,stop=1,parity=N,STREAM=PIC)
#use rs232(baud=9600,xmit=PIN_D0,rcv=PIN_D1,bits=8,stop=1,parity=N,STREAM=PC)

#use standard_io(C)
#use standard_io(D)

#byte PORTC=0xF82
#byte PORTD=0xF83

char c;
char message[10];
int index=0;


void main(void){

setup_ccp1(ccp_off);
setup_ccp2(ccp_off);
setup_adc(adc_off);
setup_adc_ports(no_analogs);

lcd_init();
lcd_putc("\f");



while(true){


c = getc(PIC);


   if(c != '\r' && index < sizeof(message)){
      message[index++] = c;
   }

   if(c == '\r'){
      message[index] = '\0';
      index = 0;
      fprintf(PC,"Temp = %s C\r\n", message);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Temp = %s C",message);
   }










}
}
