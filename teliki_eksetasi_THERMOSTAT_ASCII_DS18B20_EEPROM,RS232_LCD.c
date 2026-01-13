#include <main_.h>
#include <flex_lcd_sim.h>
#include <1wire.c>
#include <DS18B20.h>
#include <keypad_sim.h>
#include <2416.h>

#use delay(clock=8000000)

#use rs232(baud=115200,xmit=PIN_C6,rcv=PIN_C7,bits=8,stop=1,parity=N,STREAM=PC) // uart pic to pc



#use standard_io(A)
#use standard_io(B)
#use standard_io(C)
#use standard_io(D)


#byte PORTA=0xF80
#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTD=0xF83







float temp;

int16 duty; //duty = duty_per*303/100
int duty_per=50; 
char k;
int digit;
char c;
unsigned char data[20];




void main(void){

setup_ccp1(ccp_off);
setup_adc(adc_off);
setup_adc_ports(no_analogs);
setup_ccp2(ccp_pwm);
setup_timer_2(T2_DIV_BY_16,75,1); //10 khz DCMAX = 303 ~= 300

lcd_init(); // lcd init

lcd_putc("\f");

kbd_init(); //keyboard init


init_ext_eeprom(); // eeprom init



lcd_gotoxy(1,1);
lcd_putc("Thermostat\n initialize..");
delay_ms(2000); // init everything

lcd_putc("\f");

while(TRUE){

temp=ds1820_read(); //diabase temp

k=kbd_getc(); // labe ena plhktro
digit=k&0b00001111;



lcd_gotoxy(1,1);
printf(lcd_putc,"Temp=%.2f C\nPWM=%d percent",temp,duty_per);





if(digit==8){
duty_per++;
if(duty_per>100){
duty_per=100; // mhn to afiseis na paei pano apo 100
}
duty=duty_per*303/100;
set_pwm2_duty(duty);



}

if(digit==4){
duty_per--;
if(duty_per<0){
duty_per=0; // mhn to afiseis na paei kato apo 0
}
duty=duty_per*303/100;
set_pwm2_duty(duty);


}

if(k=='='){
sprintf(data,"Temp=%.2f C PWM=%d percent",temp,duty_per); // metatropi se ASCII text
for(int i=0;i<sizeof(data);i++){

write_ext_eeprom(i,data[i]);
delay_ms(20);
}
}

fprintf(PC,"Temp=%.2f C PWM=%d percent \r\n",temp,duty_per); // steile data sto PC


delay_ms(1000);




}
}
