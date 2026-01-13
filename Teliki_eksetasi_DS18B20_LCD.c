#include <main_.h>
#include <1wire.c>
#include <DS18B20.h>
#include <flex_lcd_sim.h>

#use  standard_io(E)
#use standard_io(B)
#use standard_io(C)


#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTE=0xF84


float temp;

void main(void){

set_tris_b(0xff);
set_tris_c(0x01);
set_tris_e(0x00);

setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);


lcd_init();
lcd_putc("\f");

while(TRUE){
temp=ds1820_read();

if(temp>=25.00){
lcd_gotoxy(1,1);
lcd_putc("THERMOSTAT OFF");
output_low(PIN_E0);
}

if(temp<=20.00){
lcd_gotoxy(1,1);
lcd_putc("THERMOSTAT ON ");
output_high(PIN_E0);
}

lcd_gotoxy(1,0);
printf(lcd_putc,"TEMP = %.2f C",temp);

}

}



