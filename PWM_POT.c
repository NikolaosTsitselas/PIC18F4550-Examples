#include <main_.h>

#use delay(clock=48000000)

#use standard_io(A)
#use standard_io(C)

#byte PORTA=0xF80
#byte PORTC=0xF83



void main(void){

setup_ccp1(CCP_PWM);
setup_ccp2(CCP_PWM);
setup_timer_2(T2_DIV_BY_16,62,1); //DC MAX == 251

setup_adc(ADC_CLOCK_INTERNAL);
setup_adc_ports(AN0_to_AN1|VSS_VDD);




int16 duty1;
int16 duty2;



while(TRUE){

set_adc_channel(0);

delay_us(20);
duty1=(read_adc()*0.25);
set_pwm1_duty(duty1);


set_adc_channel(1);
delay_us(20);
duty2=read_adc()*0.25;
set_pwm2_duty(duty2);




}
}
