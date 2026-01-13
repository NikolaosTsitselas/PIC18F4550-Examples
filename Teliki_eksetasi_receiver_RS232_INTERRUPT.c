#include <main_.h>
#include <flex_lcd_sim.h>
#use delay(clock=8000000)
#use rs232(baud=19200,xmit=PIN_C6,rcv=PIN_C7,STREAM=PIC,bits=8,parity=N,stop=1)
#use rs232(baud=9600,xmit=PIN_D0,rcv=PIN_D1,STREAM=PC,bits=8,parity=N,stop=1)

#use standard_io(C)
#use standard_io(D)

#byte PORTC=0xF82
#byte PORTD=0xF83

char value[10];
int index=0;
int data_ready=0;

#int_RDA
void rda_isr(void){

   char c;
   c=fgetc(PIC);
   
      if(c=='\r'){
      value[index]='\0';
      data_ready=1;
      index=0;
      }
      
      else
      {
         value[index]=c;
         index++;
         if(index>=9)index=0;
      }
}

void main(void){

setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);
enable_interrupts(GLOBAL);
enable_interrupts(int_rda);

lcd_init();
lcd_putc("\f");







while(TRUE){
if(data_ready==1){

   lcd_gotoxy(1,1);
   printf(lcd_putc,"Temp:%s C",value);
   fprintf(PC,"Temp:%s C\r\n",value);
   //fprintf(PC,"Hello world\r\n");
   data_ready=0;
}

}
}
