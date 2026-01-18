#include <main_.h>
#use delay(clock=8000000)

#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7,stop=1,bits=8,parity=N,stream=PC)

#use standard_io(A)
#use standard_io(B)
#use standard_io(C)


#byte PORTA=0xF80
#byte PORTB=0xF81
#byte PORTC=0xF82


int flag=0;
float temp;

#int_ext1
void external_interrupt(void){
flag=1;
}


void main(void){
set_tris_b(0b00000010);
setup_ccp1(ccp_off);
setup_ccp2(ccp_off);
setup_adc(adc_clock_internal);
setup_adc_ports(an0|VSS_VDD);
set_adc_channel(0);
enable_interrupts(GLOBAL);
enable_interrupts(INT_EXT1);
ext_int_edge(1,L_TO_H);








while(TRUE){

temp=read_adc()*500/1023;

if(temp<25){
output_HIGH(PIN_B2);
output_low(PIN_B3);
output_low(PIN_B4);
}


if(temp>=25 && temp<30){
output_low(pin_b2);
output_high(pin_b3);
output_low(pin_b4);
}

if(temp>=30){
output_low(pin_b2);
output_low(pin_b3);
output_high(pin_b4);
}

if(flag==1){
fprintf(PC,"Temp= %.2f C\n\r",temp);
flag=0;
}





}
}
