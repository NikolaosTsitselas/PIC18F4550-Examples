#include <main_.h>
#include <flex_lcd_sim.h>
#include <keypad_sim.h>


#use standard_io(A)
#use standard_io(B)
#use standard_io(C)
#use standard_io(D)


#byte PORTA=0xF80
#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTD=0xF83


int16 duty;
int duty_per;
char k;
int digit1,digit2;
int state=1;

void main(void){

setup_ccp1(ccp_off);
setup_adc(adc_off);
setup_adc_ports(no_analogs);
setup_ccp2(ccp_pwm);
setup_timer_2(t2_div_by_16,46,1); //16khz DCMAX = 187

kbd_init();
lcd_init();
lcd_gotoxy(1,1);
lcd_putc("Engine control\n initialize...");
delay_ms(1000);
lcd_putc("\f");



while(TRUE){

switch(state) { 

case 1: lcd_gotoxy(1,1); 
        lcd_putc("Enter monades PWM:");
        k=kbd_getc();
        while(k!=0){
        digit1=k&0b00001111;
        lcd_gotoxy(1,2);
        printf(lcd_putc,"%d",digit1);
        delay_ms(1000);
        lcd_putc("\f");
        state=2;
        break;
        }
        break;
        
case 2: lcd_gotoxy(1,1);
        lcd_putc("Enter dekades PWM:");
        k=kbd_getc();
        while(k!=0){
        digit2=k&0b00001111;
        lcd_gotoxy(1,2);
        printf(lcd_putc,"%d",digit2);
        delay_ms(1000);
        lcd_putc("\f");
        state=3;
        break;
        }
        break;
        
case 3: duty_per=digit1+digit2*10;
        duty=duty_per*187/100;
        set_pwm2_duty(duty);
        lcd_gotoxy(1,1);
        printf(lcd_putc,"PWM:%d percent",duty_per);
        lcd_gotoxy(1,2);
        lcd_putc("press any key to rst");
        k=kbd_getc();
        if(k!=0){
        lcd_putc("\f");
        digit1=0;
        digit2=0;
        duty_per=0;
        duty=0;
        state=1;
        }
        
       





}



}
}
