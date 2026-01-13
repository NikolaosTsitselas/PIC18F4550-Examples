#include <main_.h>
#use delay(clock=48000000)

#use fast_io(c)

#byte PORTC=0xF82


void main(void){
set_tris_c(0x00);

setup_ccp1(CCP_OFF);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);

setup_ccp2(CCP_PWM);
setup_timer_2(T2_DIV_BY_16,74,1); //10 khz DC MAX=300 to ebala anti gia 12 khz 

int16 i;
int16 duty;
while(TRUE){


for(i=0;i<=200;i++){
duty=i*1.5; // 200 bhmata 200*1.5 = 300
set_pwm2_duty(duty);
delay_ms(30);
}

for(i=200;i>0;i--){
duty=i*1.5;
set_pwm2_duty(duty);
delay_ms(30);
}
}
}


