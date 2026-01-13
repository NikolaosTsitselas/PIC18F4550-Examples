#include <main_.h>
#include <2416.h>

#use I2C(I2C1,MASTER,FAST=4000000,STREAM=SSD1306_STREAM)
#define SSD1306_RST PIN_B2

#include <SSD1306OLED.c>
#define SCL PIN_B1

#define SDA PIN_B0

char message[]={'H','E','L','L','O'};
char received[];
void main(void){

setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);

SSD1306_Begin(SSD1306_SWITCHCAPVCC,SSD1306_I2C_ADDRESS);
SSD1306_Display();
delay_ms(10);
SSD1306_ClearDisplay();
SSD1306_GotoXY(25,0);
SSD1306_Print("RECEIVED:"); 
SSD1306_Display();
init_ext_eeprom();




while(TRUE){

for(int i=0;i<sizeof(message);i++){
write_ext_eeprom(i, message[i]); 
  delay_ms(20);
}


SSD1306_GotoXY(15, 27);
for(i=0;i<sizeof(message);i++){
  printf(SSD1306_Print, "%c",read_ext_eeprom(i)) ;
  SSD1306_Display();
}





}
}
