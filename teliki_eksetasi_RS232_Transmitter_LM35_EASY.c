#include <main_.h>
#include <string.h>
#use delay(clock=8000000)
#use rs232(baud=57600,xmit=PIN_D0,rcv=PIN_D1,bits=8,stop=1,parity=N,STREAM=PC)
#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7,bits=8,stop=1,parity=N,STREAM=PIC)

#use standard_io(C)
#use standard_io(A)
#use standard_io(D)

#byte PORTA=0xF80
#byte PORTC=0xF82
#byte PORTD=0xF83

float temp;
char c;
char message[100];
int index=0;


void main(void){

setup_ccp1(ccp_off);
setup_ccp2(ccp_off);
setup_adc(ADC_CLOCK_INTERNAL);
setup_adc_ports(AN0|VSS_VDD);
set_adc_channel(0);








while(TRUE){

c=getc(PC);
fprintf(PC,"%c",c);

if(index<100 && c!=13){

message[index]=c;
index++;
}

if(index==sizeof(message) || c==13){

message[index]='\0';

if(message[0]=='L'&& message[1]=='A' && message[2]=='B' && index==3){
temp=read_adc()*500/1023;
fprintf(PIC,"Temp=%.2f C\n\r",temp);
}
else fprintf(PIC,"ERROR\n\r");


index=0;
}







}
}
