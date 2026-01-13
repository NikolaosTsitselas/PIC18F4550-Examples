#include <main_.h>
#include <2416.h>
#include <string.h>
#use I2C(I2C1,MASTER,FAST=400000,STREAM=SSD1306_STREAM)
#define SSD1306_RST PIN_B2

#include <SSD1306OLED.c>

#define SCL PIN_B1

#define SDA PIN_B0

#use standard_io(B)
#use standard_io(C)
#use standard_io(D)

#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTD=0xF83

char message[]={"Hello world"};

void main(void){
SSD1306_Begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS); 
  SSD1306_ClearDisplay();      // clear the display buffer 
  SSD1306_SetTextWrap(false);  // disable text wrap 
  SSD1306_Gotoxy(1,1);
  SSD1306_Print("Receiving..");
  SSD1306_Display();

init_ext_eeprom();

for(int i=0;i<strlen(message);i++){
write_ext_eeprom(i,message[i]);
delay_ms(20);
}

SSD1306_Gotoxy(10,10);
for(i=0;i<strlen(message);i++){
SSD1306_Print(read_ext_eeprom(i));
SSD1306_Display();
delay_ms(20);
}






while(TRUE){}


}
