#include <main_.h>
#include <math.h>
#include <1wire.c>
#include <DS18B20.h>


#use standard_io(A)
#use fast_io(B)
#use standard_io(E)
#byte PORTA=0xF80
#byte PORTB=0xF81
#byte PORTE=0xF84
#use I2C(MASTER,I2C1,FAST=400000, stream= SSD1306_STREAM)
#define SSD1306_RST PIN_B2
#include <SSD1306OLED.c>
#define SDA PIN_B0
#define SCL PIN_B1


float temp;
void main(void){
set_tris_b(0xff);
set_tris_c(0x00);
setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);


SSD1306_Begin(SSD1306_SWITCHCAPVCC,SSD1306_I2C_ADDRESS);
SSD1306_Display();
SSD1306_ClearDisplay();
SSD1306_SetTextWrap(false);
SSD1306_TextSize(1);
//delay_ms(1000); // gia enarksi ds18b20
while(TRUE){
temp=ds1820_read();
delay_ms(1000);

if(temp>=25){

SSD1306_GotoXY(1,40);
SSD1306_Print("Thermostat OFF");
output_low(PIN_E0);
SSD1306_Display();
}

if(temp<=18){


SSD1306_GotoXY(1,40);
SSD1306_Print("Thermostat ON ");
output_high(PIN_E0);

SSD1306_Display();

}

SSD1306_GotoXY(1,0);
printf(SSD1306_Print,"Temp=%.2f C",temp);
SSD1306_Display();
}




}
