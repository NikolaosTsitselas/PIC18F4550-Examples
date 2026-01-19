#include <main_.h>
#use delay(clock=8000000)
#include <2416.h>
#use rs232(baud=115200,xmit=pin_c6,rcv=pin_c7,stop=1,bits=8,stream=PC,parity=N)


#use fast_io(A)
#use fast_io(B)
#use standard_io(C)
#use standard_io(D)




int16 duty;
int16 adc;
int index=0;
int interrupt_index=0;
int8 adc_value[60]; //30 times, so 30*2=60 positions




#int_ext
void external_interrupt(){

 int16 value;
   int8 lsb, msb;

   interrupt_index = 0;

   while(interrupt_index < index) { //or 60 instead of index

      lsb = adc_value[interrupt_index];
      interrupt_index++;
      msb = adc_value[interrupt_index];
      interrupt_index++;

      value = ((int16)msb << 8) | lsb;

      fprintf(PC, "ADC[%u] = %Lu\r\n", interrupt_index/2, value);
      
      //%u = unsinged  int8
      //%Lu = unsigned int16
      
   }


}



void main(void){

set_tris_a(0b00000010); //AN1 ADC
set_tris_b(0b00000001); // RB0 input
setup_ccp1(ccp_pwm);
setup_timer_2(t2_div_by_16,74,1); //10 Khz, DCMAX=299
setup_ccp2(ccp_off);
setup_adc(adc_clock_internal);
setup_adc_ports(an0_to_an1|vss_vdd);
set_adc_channel(1);
delay_us(20);

init_ext_eeprom();


 
enable_interrupts(global);
enable_interrupts(INT_EXT);
ext_int_edge(0,L_TO_H);




while(TRUE){
adc=read_adc();

if(adc<300){

duty=(299*20)/100;
set_pwm1_duty(duty);

}

if(adc>=300 && adc<700){

duty=(299*50)/100;
set_pwm1_duty(duty);
}


if(adc>=700){

duty=(299*80)/100;
set_pwm1_duty(duty);
}


if(index<sizeof(adc_value)){

adc_value[index]=(adc)&0xFF; //LSB
write_ext_eeprom(index,adc_value[index]);
index++;

adc_value[index]=(adc>>8)&0xFF; //MSB
write_ext_eeprom(index,adc_value[index]);
index++;
}

if(index==sizeof(adc_value)){

output_high(PIN_D0);
}


}
}



