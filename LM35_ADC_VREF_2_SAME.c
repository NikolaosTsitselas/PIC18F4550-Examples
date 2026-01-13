#include <main_.h>
#include <math.h>
#include <flex_lcd_sim.h>

#use standard_io(A)
#use standard_io(B)
#use standard_io(C)
#use standard_io(D)
#use standard_io(E)

#byte PORTA=0xF80
#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTD=0xF83
#byte PORTE=0xF84
float temp=0.00;

void main(void){
set_tris_a(0x00001111);
set_tris_b(0x00);
set_tris_e(0x00);
setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_CLOCK_INTERNAL);
setup_adc_ports(AN0_TO_AN3_ANALOG|VSS_VREF);
set_adc_channel(0);
lcd_init();
lcd_putc("\f");


while(TRUE){

temp=(read_adc()*122.5)/1023;

if(temp<=24){
   output_high(PIN_E0);
   lcd_gotoxy(1,1);
   lcd_putc("THERMOSTAT ON ");
}

if(temp>=25){
   output_low(PIN_E0);
   lcd_gotoxy(1,1);
   lcd_putc("THERMOSTAT OFF");
}
lcd_gotoxy(1,2);
printf(lcd_putc,"TEMP = %.2f C",temp);
   

}

}
