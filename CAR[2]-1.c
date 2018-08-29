#include <16f884.h>         //check
#fuses INTRC,NOLVP,NOWDT 
#use delay(clock=8000000) 
//#device ADC=10
//int16 value=0;
//int dimflag=0;//auto dimmer flag 
void main(void) 
{ 
//setup_adc_ports(sAN13); 
//set_adc_channel(13); 
//setup_adc(ADC_CLOCK_DIV_8); 
delay_ms(1);
  while(TRUE)
   {
      //value=read_adc();
      output_high(pin_d3);//dim light always on
      if(input(pin_d1)==1)//ir detected
      {
        output_low(pin_d2);//bright light
        delay_ms(2000);
      }
      else
      {
        output_high(pin_d2);  ///dimmm
      }  
   }
}
