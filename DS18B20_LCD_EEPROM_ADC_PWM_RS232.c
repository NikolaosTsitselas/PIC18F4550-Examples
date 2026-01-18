#include <main_.h>
#use delay(clock=8000000)

#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7,stop=1,bits=8,parity=N,stream=PC)

#include <1wire.c>
#include <DS18B20.h>
#include <flex_lcd_sim.h>
#include <2416.h>
#include <keypad_sim.h>






#use fast_io(A) // for adc
#use standard_io(B) //for keypad
#use standard_io(C) // for DS18B20 , RS232
#use standard_io(D) // for LCD


#byte PORTA=0xF80
#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTD=0xF83



int data[40]; //for writing to eeprom
float temp;
int16 temp_int;
int16 duty;
int eeprom_index=0;
float voltage;
char k;


void main(void){


set_tris_a(0b00000100);
setup_ccp2(ccp_off);
setup_ccp1(ccp_pwm);
setup_timer_2(t2_div_by_16,74,1); // 10khz DCMAX=299
setup_adc(adc_clock_internal);
setup_adc_ports(an0_to_an2|VSS_VDD);
set_adc_channel(2);

lcd_init();
lcd_gotoxy(1,1);
lcd_putc("Initializing...");
delay_ms(1000);
lcd_putc("\f");

kbd_init();

init_ext_eeprom();





while(TRUE){
temp=ds1820_read();
voltage=read_adc()*5/1023;

lcd_gotoxy(1,1);
printf(lcd_putc,"Temp=%.2f C\n Voltage:%.2f V",temp,voltage);


if(temp<30){
duty=30*299/100;
set_pwm1_duty(duty);
}

if(temp>=30 && temp<40){
duty=60*299/100;
set_pwm1_duty(duty);
}


if(temp>=40){
duty=90*299/100;
set_pwm1_duty(duty);
}

k=kbd_getc();

if(k=='1'){

temp_int=temp*100;



if(eeprom_index<sizeof(data)){ // write in eeprom LSB first and MSB second of temp

data[eeprom_index]=(temp_int&0xFF); //LSB first
write_ext_eeprom(eeprom_index,data[eeprom_index]);
eeprom_index++;

data[eeprom_index]=(temp_int>>8)&0xFF; // MSB second
write_ext_eeprom(eeprom_index,data[eeprom_index]);
eeprom_index++;
}

if(eeprom_index==sizeof(data)){
output_high(PIN_A0); //led to show eeprom is filled
}
}


if(k=='2'){

for(int i=0;i<sizeof(data);i++){
fprintf(PC,"%02X\r\n",read_ext_eeprom(i)); //write to eeprom in hex
delay_ms(20);                              //for debugging purpose
}
}


delay_ms(1000);




}
}
