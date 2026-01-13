#include <main_.h>
#use delay(clock=8000000)
#include <1wire.c>
#include <DS18B20.h>


#use rs232(baud=19200,xmit=PIN_C6,rcv=PIN_C7,bits=8,stop=1,parity=N,STREAM=PIC)

#use standard_io(C)
#byte PORTC=0xF82



float temp;

void main(void){

setup_ccp1(ccp_off);
setup_ccp2(ccp_off);
setup_adc(adc_off);
setup_adc_ports(no_analogs);

while(true){
temp=ds1820_read();

fprintf(PIC,"%.2f\r",temp);

delay_ms(1000);

}
}
