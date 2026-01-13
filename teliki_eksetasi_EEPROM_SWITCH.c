#include <main_.h>
#use delay(clock=2000000)
#include <string.h>
#include <2416.h>
#use I2C(I2C1,MASTER,FAST=400000,STREAM=SSD1306_STREAM)
#define SSD1306_RST PIN_B2

#include <SSD1306OLED.c>
#define SDA PIN_B0

#define SCL PIN_B1



#use standard_io(B)
#use standard_io(C)
#use standard_io(E)

#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTE=0xF84

char message[]={"Hello there"};




void main(void){

setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);

init_ext_eeprom();

SSD1306_Begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS); 
 SSD1306_Display(); 
 delay_ms(200);
 SSD1306_ClearDisplay();
int i;





while(TRUE){

if(INPUT(PIN_E0)==1){
   SSD1306_Gotoxy(1,1);
   SSD1306_Print("Writing...");
   
      for(i=0;i<strlen(message);i++){
         write_ext_eeprom(i,message[i]);
         delay_ms(20);
}
SSD1306_Display();
}

if(INPUT(PIN_E0)==0){
   SSD1306_Gotoxy(1,1);
   SSD1306_Print("Reading..");
   SSD1306_Gotoxy(1,15);
      for(i=0;i<strlen(message);i++){
      printf(SSD1306_Print,"%c",read_ext_eeprom(i));
      delay_ms(20);
      }

SSD1306_Display();
}

SSD1306_ClearDisplay();

}
}
