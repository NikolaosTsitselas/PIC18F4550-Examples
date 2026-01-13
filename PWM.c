
#include <main_.h>
#use delay(clock=48000000)

#use fast_io(c)

#byte PORTC=0xF82


void main(void){
set_tris_c(0x00);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);


setup_timer_2(T2_DIV_BY_16,74,1); //10 khz
setup_ccp2(CCP_PWM);
//int16 duty=149; //an to balo etsi douleuei
set_pwm2_duty(37); //DC MAX = 299 , DC 50% = 149 peripou
                   // alla me dinei 5vdc stathera me auth th timh
                   // eno me 74/2 =37 me dinei DC=50% 
while(TRUE){

}


}
