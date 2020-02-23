#include <ccscAnalogRead.h>

#define led pin_c0
#define exled pin_c1

int16 readAnalog(int8);

int16 pot = 0;

void main()
{
   set_tris_c(0x00);
   set_tris_a(0xff);
   set_tris_b(0xff);
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_2|ADC_TAD_MUL_0);
   
   ext_int_edge(2,L_TO_H);
   enable_interrupts(INT_EXT2);
   enable_interrupts(GLOBAL);

   
   output_low(exled);
   
   
   while(TRUE)
   {
      pot = readAnalog(0);
      if(pot>512)
         output_high(led);
      else
         output_low(led);
   }

}


int16 readAnalog(int8 ch){
   set_adc_channel(ch);
   return read_adc();
}


#INT_EXT2
void  EXT_isr(void) 
{
   clear_interrupt(INT_EXT2);
   delay_ms(10);
   output_toggle(exled);
   
}
