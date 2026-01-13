
// SE AUTO TO ARXEIO THA BREIS METATROPI FLOAT SE HEX, ASCII , EGRAFI SE EEPROM KAI EMFANISI APO EEPROM SE LCD ALLA KAI RS232 !!






#include <main_.h>
#use delay(clock=48000000)


#use rs232(baud=115200,xmit=PIN_C6,rcv=PIN_C7,bits=8,stop=1,parity=N,STREAM=PC)


#include <flex_lcd_sim.h>
#include <1wire.c>
#include <DS18B20.h>
#include <2416.h>






#use standard_io(A)
#use standard_io(B)
#use standard_io(C)
#use standard_io(D)


#byte PORTA=0xF80
#byte PORTB=0xF81
#byte PORTC=0xF82
#byte PORTD=0xF83


float temp;
float temp_read;
unsigned char temperature[10];
//int digit1,digit2,digit3,digit4;
char k;

void main(void){

setup_ccp1(ccp_off);
setup_ccp2(ccp_off);
setup_adc(adc_off);
setup_adc_ports(no_analogs);

lcd_init();
lcd_putc("\f");

init_ext_eeprom();







while(TRUE){
temp=ds1820_read();

lcd_gotoxy(1,1);
printf(lcd_putc,"Temp = %.2f C",temp);

//===================================================================================
// metatropi apo float se hex

memcpy(temperature,&temp,sizeof(float)); // metatropi se HEX


//=====================================================================================

//rs 232 steile to HEX Sto PC
for(int i=0;i<sizeof(temperature);i++){
k=temperature[i];
fprintf(PC,"%c",k);
if(k==0x00) break;
}


//=============================================================================
//egrafi sthn eeprom to hex

for( i=0;i<sizeof(temperature);i++){ // pare ta dedomena os hex
write_ext_eeprom(i,temperature[i]);
delay_ms(20);

}

// ============================================================================


//metatropi se ascii text
sprintf(temperature,"%.2f",temp); // metatropi se ascii text


//=============================================================================

// steile ASCII text me RS232 sto pc 

for(i=0;i<sizeof(temperature);i++){
k=temperature[i];
if(k=='\0') break;
fprintf(PC,"%c",k);
}

//==============================================================================

// egrafi ASCII text sthn eeprom


for( i=0;i<sizeof(temperature);i++){
write_ext_eeprom(i,temperature[i]);

delay_ms(20);
}


//==============================================================================
// an thelo na to balo se lcd apo eeprom an ta exo steilei sthn eeprom os ASCII
lcd_gotoxy(1,1);
lcd_putc("Temp :");
lcd_gotoxy(10,1);
for(i=0;i<sizeof(temperature);i++){
printf(lcd_putc,"%c",read_ext_eeprom(i));

if(read_ext_eeprom(i)=='\0') break;

delay_ms(20);
}



//==================================================================
//an ta steilo os hex tote prepei ksana metatropi se float diladi

for(i=0;i<sizeof(temperature);i++){
temperature[i]=read_ext_eeprom(i);

delay_ms(20);
}


// ==================================================================
// metatropi hex se float
memcpy(&temp_read,temperature,sizeof(float));

lcd_gotoxy(1,1);
printf(lcd_putc,"Temp= %.2f C",temp_read);



delay_ms(1000);

}





}

