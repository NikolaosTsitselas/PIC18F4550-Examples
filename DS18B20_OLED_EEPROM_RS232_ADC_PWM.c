

#include <main_.h>
#use delay(clock=8000000)
#include <1wire.c>
#include <DS18B20.h>
#include <2416.h>

#use rs232(baud=115200,xmit=pin_c6,rcv=pin_c7,bits=8,stop=1,parity=N,STREAM=PC)

#define SSD1306_RST PIN_B2

#use I2C(I2C1,MASTER,FAST=400000,STREAM=SSD1306_STREAM)

#include <SSD1306OLED.c>
#define SDA PIN_B0
#define SCL PIN_B1


#use standard_io(A)
#use standard_io(B)
#use standard_io(C)
#use standard_io(D)
#use standard_io(E)


#byte PORTA=0xF80
#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTD=0xF83



int16 duty;
int duty_per;
float temp;
char data[30];
int1 flag=0;
int1 triggered=0;

void main(void){

setup_ccp1(ccp_off);
setup_ccp2(ccp_pwm);
setup_adc(ADC_CLOCK_INTERNAL);
setup_adc_ports(AN0|VSS_VDD);
set_adc_channel(0);

setup_timer_2(T2_DIV_BY_16,75,1); //10khz DCMAX= 303

SSD1306_Begin(SSD1306_SWITCHCAPVCC,SSD1306_I2C_ADDRESS);
SSD1306_Display();
SSD1306_cleardisplay();

init_ext_eeprom();





while(TRUE){

temp=ds1820_read();
duty=read_adc()*0.303; //duty
duty_per=duty*100/303; //percentage


if(duty_per>100){
duty_per=100;
}

if(duty_per<0){
duty_per=0;
}


set_pwm2_duty(duty);

if(temp>30 && triggered==0){
flag=1;
triggered=1;
}

if(temp<30 && triggered==1){
triggered=0;
}

if(flag==1){
sprintf(data,"Temp=%.2f C,PWM Duty=%d percentage",temp,duty_per);
for(int i=0;i<data[i]!='\0';i++){
write_ext_eeprom(i,data[i]);
delay_ms(20);
}
flag=0;
}

SSD1306_Gotoxy(1,1);
printf(SSD1306_print,"Temp=%.2f C\n PWM Duty = %d percent",temp,duty_per);
SSD1306_Display();


fprintf(PC,"Temp=%.2f C PWM Duty=%d Percent\n\r",temp,duty_per);


delay_ms(1000);

}


}
