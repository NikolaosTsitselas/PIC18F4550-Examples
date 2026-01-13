#include <main_.h>
#use delay(clock=8000000)
#include <1wire.c>
#include <DS18B20.h>

#use rs232(baud=19200, xmit=PIN_C6,rcv=PIN_C7,STREAM=PIC,bits=8,parity=N,stop=1)


#byte PORTC=0xF82

#use standard_io(C)

float temp;

void main(void){

setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);

while(TRUE){
temp=ds1820_read();

fprintf(PIC,"%.2f\r",temp);
delay_ms(5000);


}
}

