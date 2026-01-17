#include  <main_.h>

#use delay(clock=8000000)

#use fast_io(A)

#byte PORTA=0xF80


float temp;
int temperature[40];
int16 temp_int;
int index=0;
void main(void){
set_tris_a(0b0000100);
setup_ccp1(ccp_off);
setup_ccp2(ccp_off);
setup_adc(adc_clock_internal);
setup_adc_ports(AN0_to_AN2|VSS_VDD);
set_adc_channel(2);





while(TRUE){

if(index<sizeof(temperature)){
temp=read_adc()*500/1023;
temp_int=temp*100;

temperature[index]=(temp_int>>8)&0xFF; //MSB

index++;

temperature[index]=(temp_int)&0xFF; // LSB
index++;


}

else index=0;






delay_ms(3000);
}
}
