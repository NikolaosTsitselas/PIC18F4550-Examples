#include <main_.h>

#use delay(clock=48000000) //bazoume clock 48MHz

#use standard_io(C)


#byte PORTC=0xF82





void main(void){

//THEMA 2.4
/*

//exo dilosei arxika standard_io(C) gia auto den dilono eksodous/esodous, allios tha htan set_tris_c(0x00);

int16 duty;
setup_ccp1(ccp_pwm);
setup_ccp2(ccp_off);
setup_adc(adc_off);
setup_adc_ports(no_analogs);

setup_timer_2(t2_div_by_16,41,1); //DC MAX = 167 18KHz

duty=43; //26%
set_pwm2_duty(duty);
*/

//THEMA 2.5
/*
set_tris_a(0b00001011);
setup_ccp1(ccp_off);
setup_ccp2(ccp_off);
setup_adc(adc_clock_div_32);
setup_adc_ports(an0_to_an3|vss_vdd);
set_adc_channel(1); //channel 1

*/

// THEMA 2.6
/*
set_tris_e(0xff);
set_tris_b(0b01010110);
set_tris_c(0b00000101);
set_tris_d(0b00110011);

*/


while(TRUE){



}
}
