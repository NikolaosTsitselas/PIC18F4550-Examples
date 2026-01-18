#include <main_.h>

#use delay(clock=48000000)
#use fast_io(A)
#use standard_io(C)

#byte PORTA=0xF80
#byte PORTC=0xF82





int16 duty;
int duty_per; //duty percentage


void main(void){
set_tris_a(0b00010000);
setup_ccp2(ccp_off);
setup_ccp1(ccp_pwm);
setup_timer_2(t2_div_by_16,50,1); // DC MAX = 203, F = 15 KHZ
setup_adc(adc_clock_internal);
setup_adc_ports(an0_to_an4|VSS_VDD);
set_adc_channel(4); // channel 4 => RA4





while(TRUE){

duty_per=10+(70*read_adc()/1023); // OFFSET 10%

if(duty_per > 80) duty_per = 80; // an ksefigei
if(duty_per < 10) duty_per = 10; // paromoios


duty=duty_per*203/100;




set_pwm1_duty(duty);






delay_ms(2000);

}
}
