#include <main_.h>
#use delay(clock=8000000)
#use rs232(baud=57600,bits=8,stop=1,parity=N,xmit=PIN_C6,rcv=PIN_C7,STREAM=PC)
#use rs232(baud=9600,bits=8,stop=1,parity=N,xmit=PIN_D0,rcv=PIN_D1,STREAM=PIC)

#use standard_io(A)
#use standard_io(C)
#use standard_io(D)

#byte PORTA=0xF80
#byte PORTC=0xF82
#byte PORTD=0xF83

char message[]={'L','A','B'};
char received[4];
char char_sent;
int index=0;
void main(void){
setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);
setup_adc(ADC_CLOCK_INTERNAL);
setup_adc_ports(AN0|VSS_VDD);
set_adc_channel(0);

fprintf(PC,"Enter secret word:\n\r");

float temp;


while(1){

char_sent=fgetc(PC);
putc(char_sent,PC);

if(char_sent==13){


received[index] = '\0'; //termatikos xaraktiras anagkaios gia na stalthei sosto string
if(received[0]=='L' && received[1]=='A' && received[2]=='B' && index==3){
temp=(read_adc()*500)/1023;
fprintf(PIC,"Temp = %.2f C\n\r",temp);

}

else {
fprintf(PC,"Wrong password\n\r");
}
index=0; //midenise to index 
}
else {
if(index<sizeof(message)){ //gia na gemisei to paketo me oses theseis einai h krufi leksi
received[index]=char_sent;
index++;
}
}

}
}
