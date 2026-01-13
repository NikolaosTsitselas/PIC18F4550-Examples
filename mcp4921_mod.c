#define DAC_SELECT PIN_C0
#define latch_dac PIN_C1

void write_mcp4921(int16 value_1)
{
   // Prepare the first value
   if(value_1 > 0x0FFF)            //Limit value of DAC A value with no rollover
   {
      value_1 = 0x0FFF;
   }

// Set control bits
   bit_clear(value_1, 15);                    // Write to DAC A
   bit_set(value_1, 13);                       // Output gain = 1 // clear bit makes gain 2
   bit_set(value_1, 12);                       // Output enabled
   output_low(DAC_SELECT);           //select DAC IC /CS
   spi_write(make8(value_1,1));         //write upper byte
   spi_write(make8(value_1,0));         //write lower byte
   output_high(DAC_SELECT);         //unselect DAC /CS   

   // Latch both values onto the analogue outputs
   output_low(latch_dac);
                              
   delay_cycles(1);
   output_high(latch_dac);
}