#include <main_.h>
#include <flex_lcd_sim.h>

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
unsigned int duty_per=50; 
char k;
int digit;

unsigned char data[30];
int flag=0;



void main(void){

setup_ccp1(ccp_off);
setup_adc(ADC_CLOCK_INTERNAL);
setup_adc_ports(AN0|VSS_VDD);
set_adc_channel(0);
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



duty=duty_per*303/100;
set_pwm2_duty(duty);


while(TRUE){

temp=read_adc()*500/1023; //diabase temp

k=kbd_getc(); // labe ena plhktro
digit=k&0b00001111;





if(flag==0){


lcd_gotoxy(1,1);
printf(lcd_putc,"Temp=%.1fC MODE:\nPWM=%d perc AUTO",temp,duty_per);

if(digit==2){ //set mode to manual
flag=1; // den thelei break giati spaei to while loop
}

if(temp>25){
lcd_putc("\f");
lcd_gotoxy(1,1);
lcd_putc("THERMOSTAT OFF\n reducing temp");
delay_ms(2000);
lcd_gotoxy(1,1);
printf(lcd_putc,"Temp=%.1fC MODE:\nPWM=%d perc AUTO",temp,duty_per);
duty_per--;

if(duty_per<0){
duty_per=0;
set_pwm2_duty(duty);
}
}

if(temp<15){

lcd_putc("\f");
lcd_gotoxy(1,1);
lcd_putc("THERMOSTAT ON\n increasing temp");
delay_ms(2000);
lcd_gotoxy(1,1);
printf(lcd_putc,"Temp=%.1fC MODE:\nPWM=%d perc AUTO",temp,duty_per);
duty_per++;

if(duty_per>100){
duty_per=100;
set_pwm2_duty(duty);
}


}




if(k=='='){
sprintf(data,"Temp=%.2f C PWM=%d percent MODE:AUTO",temp,duty_per); // metatropi se ASCII text
for(int i=0;i<data[i]!='\0';i++){ //mexri na parei to '\0' allios bazeis sizeof(data) kai grafeis se olo to buffer

write_ext_eeprom(i,data[i]);
delay_ms(20);
}
}

fprintf(PC,"Temp=%.1f C PWM=%d percent MODE:AUTOL \r\n",temp,duty_per); // steile data sto PC


delay_ms(1000);







}

if(flag==1){ //manual mode
lcd_gotoxy(1,1);

printf(lcd_putc,"Temp=%.1fC MODE:\nPWM=%d perc MANU",temp,duty_per);





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


if(digit==2){ //set mode to auto
flag=0; //se tetoies katastaseis den thelei break giati spaei to while loop

}










if(k=='='){
sprintf(data,"Temp=%.2f C PWM=%d percent MODE:MANUAL",temp,duty_per); // metatropi se ASCII text
for(int i=0;i<data[i]!='\0';i++){

write_ext_eeprom(i,data[i]);
delay_ms(20);
}
}

fprintf(PC,"Temp=%.1f C PWM=%d percent MODE:MANUAL \r\n",temp,duty_per); // steile data sto PC


delay_ms(1000);




}

}
}
