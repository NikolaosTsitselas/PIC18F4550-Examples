#include <main_.h>
#include <keypad_sim.h>
#include <flex_lcd_sim.h>
#use delay(clock=48000000)

#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTD=0xF83

#use standard_io(B)
#use standard_io(C)
#use standard_io(D)


int state=1;
int16 duty;
int temp;
int digit1,digit2;
char k;
void main(void){
set_tris_d(0xff);
set_tris_c(0x00);

setup_adc(ADC_OFF);
setup_adc_ports(NO_ANALOGS);
setup_ccp1(CCP_OFF);
setup_ccp2(CCP_PWM);
setup_timer_2(T2_DIV_BY_16,45,1); //16 KHZ DC MAX=184

lcd_init();
lcd_putc("\f");

kbd_init();

while(TRUE){
switch(state){


   case 1: lcd_gotoxy(1,1);
           lcd_putc("Enter monades PWM:");
           k=kbd_getc();
           while(k!=0){
           digit1=k&0b00001111; //monades
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
           digit2=k&0b00001111; //dekades
           lcd_gotoxy(1,2);
           printf(lcd_putc,"%d",digit2);
           delay_ms(1000);
           lcd_putc("\f");
           state=3;
           break;
           }
           break;
           
     case 3:
              temp=digit2*10 + digit1;
              duty=temp*1.84;
              //duty=(temp*184)/100; isos na mporouse kai etsi na ginei
              //set_pwm2_duty(duty);
              set_pwm2_duty(duty);
              
              lcd_gotoxy(1,1);
              printf(lcd_putc,"PWM DUTY : %d",temp);
              lcd_gotoxy(1,2);
              lcd_putc("Press any button to reset");
              k=kbd_getc();
              while(k!=0){
              state=1;
              break;
              }
              break;
}
              



}
}
