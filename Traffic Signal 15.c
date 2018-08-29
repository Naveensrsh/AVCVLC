//Traffic Signal

#include <16f884.h>
#fuses INTRC,NOLVP,NOWDT
#use delay(clock=8000000) 
#use rs232(baud=9600,parity=N,UART1,bits=8,ERRORS) 
#define LCD_RW_PIN PIN_D2
#define LCD_ENABLE_PIN PIN_D3
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <string.h>
#include <lcd.c>
int flag=0;
//int enter=0;
int data=0;
int rcv=0;
//int i=0;
int j=0;
void main(void) 
{ 
lcd_init(); // intialize lcd
lcd_gotoxy(1,1);
lcd_putc(" TRAFFIC SIGNAL ");
delay_ms(1000);
//lcd_putc('\f');//lcd.clear();

   //delay_ms(1000); 
   while(TRUE) 
   { 
   lcd_gotoxy(1,1);
   lcd_putc(" TRAFFIC SIGNAL ");
  if(input(pin_b5)==1)
  flag=1;
  else
  flag=0;
  
 /* if(input(pin_b5)&&enter==0)//switch for traffic signal interchange
  {
  flag=!flag;
  enter=1;
  }
  else if(input(pin_b5)==0)
  {
  enter=0;
  }*/
  
 if(flag==0)
 {
 data='R';//for red light
 output_high(pin_b7);
 output_low(pin_b6);
  putc(data); 
  //delay_ms(100);
 }
 else
 {
 data='Y';//for yellow light
 output_high(pin_b6);
 output_low(pin_b7);
  putc(data); 
  //delay_ms(100);
 }
 
 if(kbhit())
 {
  rcv=getc(); //receive data from vehicles
  if(strcmp(rcv,'N')==0)//for normal car 1
 {
 lcd_putc('\f');
 lcd_gotoxy(1,1);
 lcd_putc("TRAFFIC VIOLATED");
 lcd_gotoxy(1,2);
 lcd_putc("  KL 01 A 4973  ");
 for(j=0;j<=200;j++)//ivide chuimma delay ittal athrem neram data snd cheyilla.
 //.so led brightness kooduthal aayirikkum..
 //so aa delay kku pakaram data send cheythukondu delay ...
 {
 putc(data);
 delay_ms(10);
 }
 //delay_ms(2000);
 lcd_putc('\f');
 }
 else if(strcmp(rcv,'E')==0)//emergency cases [[car 1]]
 {
 lcd_putc('\f');
 lcd_gotoxy(1,1);
 lcd_putc(" EMERGENCY CASE ");
 lcd_gotoxy(1,2);
 lcd_putc("  KL 01 A 4973  ");
  for(j=0;j<=200;j++)//ivide chuimma delay ittal athrem neram data snd cheyilla.
 //.so led brightness kooduthal aayirikkum..
 //so aa delay kku pakaram data send cheythukondu delay ...
 {
 putc(data);
 delay_ms(10);
 }
// delay_ms(2000);
 lcd_putc('\f');
 }
 
 }
 
// for(i=48;i<123;i++)
   //{
   //fprintf(usa,"%d",i);
     
     // lcd_gotoxy(1,2);
      //printf(lcd_putc,"\f%d",i);
     // delay_ms(1000); 
      //putc('
  // } 
/*data=65;
 printf("%c",data); //transmission of data from traffic signal
 printf(lcd_putc,"%d",data);
 delay_ms(100);
 lcd_putc('\f');*/
 
   
  }
   }
   
   
   
   
   
   //delay_ms(10); 
 /*if(!strcmp(rcv,'7'))//for normal car 2
 {
 lcd_gotoxy(1,1);
 lcd_putc("TrafficViolation");
 lcd_gotoxy(1,2);
 lcd_putc("  KL 01 A 5961");
 }
 else if(!strcmp(rcv,'8'))//emergency cases [[car 2]]
 {
 lcd_gotoxy(1,1);
 lcd_putc(" Emergency Case");
 lcd_gotoxy(1,2);
 lcd_putc("  KL 01 A 5961");
 }*/
 
 
 
 
 
 
 
 
  
  
  
  
    
      //putc('
 //  } 
 //  }
//} 
//This way a character will be sent every second 
