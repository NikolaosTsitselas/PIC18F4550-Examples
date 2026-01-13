#include <main_.h>
#use delay(clock=48000000)
#use standard_io(A)
#use standard_io(B)
#use standard_io(C)
#use standard_io(D)

#byte PORTA=0xF80
#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTD=0xF83
#byte PORTE=0xF84

// THEMA 3 #use rs232(baud=57600,xmit=PIN_C6,rcv=PIN_C7,parity=N,stop=2,bits=8,STREAM=PC)
void main(void)
{

/* THEMA 1
setup_ccp2(CCP_OFF);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);
setup_ccp1(CCP_PWM);
setup_timer_2(T2_DIV_BY_16,82,1); //9KHz , DCMAX=331
int16 duty=86;
set_pwm1_duty(duty);
*/

/* THEMA 2
set_tris_a(0b00001100);
setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_CLOCK_DIV_64);
setup_adc_ports(AN0_TO_AN3|VSS_VDD);
set_adc_channel(0); // den to zitaei
*/

/* THEMA 4
set_tris_e(0x00);
set_tris_b(0b01000110);
set_tris_c(0b01000001);
set_tris_d(0b00101011);
*/
while(TRUE){
// THEMA 3 fprintf(PC,"Exams"); // h putc("Exams");

}
}

