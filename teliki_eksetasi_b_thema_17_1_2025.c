#include <main_.h>
#use delay(clock=48000000)
#use standard_io(C)
#use fast_io(A)
#use standard_io(B)
#use standard_io(D)
#use standard_io(E)
#byte PORTE=0xF84
#byte PORTB=0xF81
#byte PORTD=0xF83
#byte PORTC=0xF82
#byte PORTA=0xF80


void main(void){
/* THEMA 4
setup_ccp1(CCP_OFF);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);

setup_ccp2(CCP_PWM);
setup_timer_2(T2_DIV_BY_16,52,1); //DC MAX = 211 = > 40% = 
int16 duty=84;
set_pwm2_duty(duty);
*/

/* THEMA 5
set_tris_a(0b00001101);
setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_CLOCK_DIV_32);
setup_adc_ports(AN0_to_AN3_ANALOG|VSS_VDD);

set_adc_channel(0);
*/

/* THEMA 6
set_tris_e(0xff);
set_tris_a(0b10101001);
set_tris_b(0b10101001);
set_tris_c(0b10000001);
set_tris_d(0b11001100);

*/
while(TRUE){}

}
