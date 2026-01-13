#include <main_.h>
#include <1wire.c>
#include <DS18B20.h>
#use rs232 (baud=19200,xmit=PIN_C6,rcv=PIN_C7,parity=N,bits=8,stop=1,STREAM=PC)
#use delay(clock=48000000)

#byte PORTC=0xF82
#use standard_io(C)


float temp;
int16 send_value;
void main(void){

setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);


while(TRUE){
temp=ds1820_read();

send_value=(int16)(temp*100); //kane th thermokrasia px 25.23 => 2523

fputc((send_value>>8)&0xFF,PC); //MSB

fputc(send_value&0xFF,PC); //LSB

delay_ms(5000);


}

}
