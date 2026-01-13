#include <main_.h>
#include <flex_lcd_sim.h>
#use delay(clock=48000000)

#byte PORTA=0xF80
#byte PORTB=0xF81
#byte PORTE=0xF83

#use standard_io(A)
#use standard_io(B)
#use standard_io(E)


float temp;
void main(void)
{
set_tris_a(0x00000001);
set_tris_b(0xff);
set_tris_e(0x00);

setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_CLOCK_INTERNAL);
setup_adc_ports(AN0|VSS_VREF);
set_adc_channel(0);

lcd_init();
lcd_putc("\f");


while(TRUE){

temp=(read_adc()*122.5)/1023;

if(temp>=25){

lcd_gotoxy(1,1);
lcd_putc("THERMOSTAT OFF");
output_low(PIN_E0);
}


if(temp<=20){


lcd_gotoxy(1,1);
lcd_putc("THERMOSTAT ON ");
output_high(PIN_E0);
}


lcd_gotoxy(1,0);
printf(lcd_putc,"TEMP = %.2f C",temp);



}


}
