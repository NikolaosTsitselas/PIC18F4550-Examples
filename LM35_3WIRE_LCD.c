#include <main_.h>
#define LCD_DATA_PIN  PIN_D0 
#define LCD_CLOCK_PIN PIN_D1 
#define LCD_EN_PIN    PIN_D2 
#include <3WireLCD.c>

#use standard_io(D)
#use fast_io(A)

#byte PORTA=0xF80
#byte PORTD=0xF83


float temp;

void main(void){

set_tris_a(0x01);

setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);

setup_adc(ADC_CLOCK_INTERNAL);
setup_adc_ports(AN0_ANALOG|VSS_VDD);

set_adc_channel(0);

lcd_initialize();
lcd_cmd(LCD_CLEAR);

while(TRUE){
temp=(read_adc()*500)/1023;

lcd_goto(1,1);
printf(lcd_out,"Temp=%.2f C",temp);




}
}
