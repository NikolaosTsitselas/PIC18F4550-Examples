#include <main_.h>
#include <1wire.c>
#include <DS18B20.h>
#include <flex_lcd_sim.h>


#use standard_io(D)
#use standard_io(C)

#byte PORTC=0xF82
#byte PORTD=0xF83



float temp;
float avg;
float sum;
float temperature[60];

void main(void){

setup_ccp1(ccp_off);
setup_ccp2(ccp_off);
setup_adc(adc_off);
setup_adc_ports(no_analogs);

lcd_init();
lcd_putc("\f");



while(TRUE){

temp=ds1820_read();

for(int i=0;i<60;i++){
temperature[i]=temp;
sum+=temperature[i];
}

avg=sum/60;

lcd_gotoxy(1,1);
printf(lcd_putc,"Temp avg=%.2f C",avg);

delay_ms(2000);



}

}
