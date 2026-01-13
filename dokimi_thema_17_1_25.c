#include <main_.h>
#use delay(clock=8000000)
#use rs232(baud=19200,xmit=pin_c6,rcv=pin_c7,bits=8,stop=1,parity=N,stream=PC)
#include <1wire.c>
#include <DS18B20.h>


#use standard_io(C)
#byte PORTC=0xF82


float temp;
int16 temp_int;

void main(void){

setup_ccp1(ccp_off);
setup_ccp2(ccp_off);
setup_adc(adc_off);
setup_adc_ports(no_analogs);



while(true){
temp=ds1820_read();
temp_int=temp*100;
fputc((temp_int>>8)&0xFF,PC); //MSB

fputc((temp_int)&0xFF,PC);
delay_ms(1000);








}
}
