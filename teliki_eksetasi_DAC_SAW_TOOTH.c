#include <main_.h> 
#include <stdlib.h> 
#include <mcp4921_mod.c> 
#include <math.h> 
#define SPI_MODE_0  (SPI_L_TO_H | SPI_XMIT_L_TO_H)//SPI_SCK_IDLE_LOW 
int16 i,j; 
int16 sin_table [360]; 

void fill_sin_table() 
{ 
   for (i = 0; i <=360; i=i+1) 
   { 
    sin_table[i]=i*11; //360*11 = peripoy 4095
   } 
} 
void init(void){ 
set_tris_c(0x00);// PORTC output 
set_tris_b(0x00);// PORTB output 
 
} 
void main() 
{ 
   init(); 
   fill_sin_table(); 
   setup_spi(SPI_MASTER | SPI_MODE_0 | SPI_CLK_DIV_4); 
   delay_ms(100); 
 
   while(1) 
   { 
      j++; 
      if (j >= 360) 
      { 
         j = 0; 
      } 
      write_mcp4921(sin_table[j]); 
   } 
} 
