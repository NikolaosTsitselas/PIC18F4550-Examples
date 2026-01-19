#include <main_.h>

#use delay(clock=8000000)
#include <2416.h>
#include <flex_lcd_sim.h>
#use rs232(baud=115200,xmit=pin_c6,rcv=pin_c7,bits=8,stop=1,stream=PC,parity=N)


#use fast_io(A)
#use fast_io(B)
#use standard_io(C)


int16 voltage;
int water_level_per;
int16 duty;
int data[20];
int index=0;

int interrupt_index=0;



#int_ext1

void external_interrupt(){


int x;

if(interrupt_index<20){
x=read_ext_eeprom(interrupt_index);
fprintf(PC,"Level[%d]:%d\n\r ",interrupt_index,x);
interrupt_index++;
}

if(interrupt_index==sizeof(data)){
interrupt_index=0;
}


}




void main(void){

set_tris_a(0b00001000); //choose an3
set_tris_b(0b00000010); //rb1 input for interrupt


setup_ccp1(ccp_pwm);
setup_timer_2(t2_div_by_16,74,1); //10KHZ DCMAX =299
setup_ccp2(ccp_off);
setup_adc(adc_clock_internal);
setup_adc_ports(an0_to_an3|vss_vdd);
set_adc_channel(3);
enable_interrupts(global);
enable_interrupts(int_ext1);
ext_int_edge(1,L_TO_H);

init_ext_eeprom();







while(TRUE){
voltage=read_adc(); //0-5v
water_level_per=(voltage*100/1023); //water level percentage

if(water_level_per>100) water_level_per=100;

if(water_level_per<30){
duty=(299*80)/100;
set_pwm1_duty(duty);

}

if(water_level_per>=30 && water_level_per<70){
duty=(299*50)/100;
set_pwm1_duty(duty);
}

if(water_level_per>=70){
duty=0;
set_pwm1_duty(duty);
}

if(index<20){
data[index]=water_level_per;
write_ext_eeprom(index,data[index]);
index++;


if(index==20){
index=0;
}

}

lcd_gotoxy(1,1);
printf(lcd_putc,"Water level:%d\npercentage",water_level_per);

delay_ms(1000);



}
}
