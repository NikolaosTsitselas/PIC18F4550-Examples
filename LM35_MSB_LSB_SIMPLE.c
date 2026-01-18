#include <main_.h>
#use delay(clock=8000000)

#use standard_io(A)
#use standard_io(B)



float temp;
int index=0;
int16 temp_int;
int temperature[60];
int flag=0;

void main(void){

setup_ccp1(ccp_off);
setup_ccp2(ccp_off);
setup_adc(adc_clock_internal);
setup_adc_ports(an0|VSS_VDD);
set_adc_channel(0);

while(TRUE){

if(index<sizeof(temperature) && flag==0){

temp=read_adc()*500/1023;
temp_int=temp*100;

temperature[index]=temp_int&0xFF; //LSB
index++;
temperature[index]=((temp_int)>>8)&0xFF; //MSB
index++;


delay_ms(2000);
}

if(index==sizeof(temperature)){

flag=1;
}

if(flag==1){
output_high(PIN_B0); //once temperature[] is filled stop and turn on led
}









}
}
