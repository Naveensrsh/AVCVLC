//Car Signal

#include <16f884.h>         //check
#fuses INTRC,NOLVP,NOWDT 
#use delay(clock=8000000) 
//FOR HARDWARE UART
#use rs232(baud=9600,parity=N,UART1,bits=8,ERRORS) 
//FOR SOFTWARE UART
//#use rs232(baud=1200,parity=N,rcv=pin_d0,xmit=pin_d1,bits=8,errors,stream=IR)
#define LCD_RW_PIN PIN_D2
#define LCD_ENABLE_PIN PIN_D3
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <string.h>
#include <lcd.c>
//==================================================================\\
//int acc=0;
int hdlmp=0;
//int hdlmpcond=0;
char rcv=0;
//int enter=0;
int yelflag=0;//for two stage yellow trafic signal
int del=10;//setting delay time for stepper control
int emer=0;//emergency switch
char data=0;// sending data via headlamp
int j=0;
int mode=0;//changing traffic to car mode
//int hilo=0;//high or low beam
int dimflag=0;//auto dimmer flag 
//!long c=0;
int d=0;
int speedflag=0;
//====================================================================\\
#INT_RDA //kbhit use cheyyunathinu pakaram interrupt vaychu cheyyunnu
void serial_isr()
{
  output_high(pin_b3);
  rcv=getch();
}
#INT_TIMER1
void TimerOverFlow()
{
if(input(pin_b6)==0)
{
if(speedflag==1)
{
output_high(pin_b0);
delay_us(100);
output_low(pin_b0);
}
}
else
output_low(pin_b0);
}
//====================================================================\\
#INT_TIMER0
void TimerOverFlow0()
{
if(input(pin_b6)==0)
{
if(speedflag==0&&d==300)
{
output_toggle(pin_b0);
d=0;
}
d++;
}
else
output_low(pin_b0);
}
//====================================================================\\
void main(void) 
{ 
setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2);
enable_interrupts(GLOBAL);
enable_interrupts(INT_TIMER1);
enable_interrupts(INT_TIMER0);
enable_interrupts(INT_RDA);
set_timer1(0xEC78);// for 5000us delay ie 50ms
set_timer0(0x00);

lcd_init(); // intialize lcd
lcd_gotoxy(1,1);
lcd_putc(" VEHICLE  PANEL ");
lcd_gotoxy(1,2);
lcd_putc("  KL 01 A 4973  ");
delay_ms(1000);
//lcd_putc('\f');//lcd.clear();
//=====================================================================\\
   while(TRUE)
   {
       lcd_gotoxy(1,1);
       lcd_putc(" VEHICLE  PANEL ");
       lcd_gotoxy(1,2);
       lcd_putc("  KL 01 A 4973  ");
  
   
   //[[1]]
   
   if(input(pin_c2)==1)//mode switch... traffic or car...
   {
   mode=1;
   }
   else
   {
   mode=0;
   }
   
//==================================================================\\
 
 if(mode==1)
 {
 
 
    //[[4]]
   
//! if(input(pin_b6)==1)//switch for accelerator [[[CHANGE IT TO something else]]]
//!  {
//! // acc=1;
//! output_HIGH(pin_b0);
//! delay_ms(del);// delay interrupt vaychu ittal kollayrunnu..[vendaee]samayam illa!!
//! output_LOW(pin_b0);
//! delay_ms(del);
//!  }
//!  else
//!  {
//! // acc=0;
//! output_low(pin_b0);
//!  }
//!  
  //[[2]]
  emer=input(pin_b5);//EMERGENCY SWITCH INPUT
  
  
//!  if(acc==1)
//! {
//! output_HIGH(pin_b0);
//! delay_ms(del);// delay interrupt vaychu ittal kollayrunnu..[vendaee]samayam illa!!
//! output_LOW(pin_b0);
//! delay_ms(del);
//! }
//! else
//! {
//! output_low(pin_b0);
//! }
 
 
 
 //====================================================================\\
 
 
 
 // switch based high or low beam..
 
 // [[3]]
   if(input(pin_c0)==1)//switch for checking high or low beam...
   {
   output_high(pin_c1);//bright light
   }
   else
   {
   output_low(pin_c1);  ///dimmm
   }  
   
  
//======================================================================\\   
//!if(!kbhit())
//!c=0;

//!if(c<=9999)
//!c++;
//if(kbhit())                                                       //&&c==0)
//{
//c=1;
delay_ms(1);//to make sure that data is stored in register..
output_low(pin_b3);//chumma oru rasam!! receive cheyyundo ennu ariyan mathram!!
//for(c=0;c<2;c++)
//rcv=getc();
// rcv=getc();rcv=getc();
//if(kbhit())
//fgetc();
//! fgetc();
//! 
 
 
 

//printf(lcd_putc,"\f",);
//lcd_gotoxy(1,2);
// printf(lcd_putc,"%c",rcv);
 //if(strcmp(rcv,'H')==0)
 //{
 //del=30;
 //}
 output_low(pin_d0);//when not in ir mode turn off ir led...

if(strcmp(rcv,'R')==0)//for Red light (stop)  [[condition 1]]
 {
// if(kbhit())
 // fgetc();
 //output_high(pin_b7);
 lcd_gotoxy(1,1);
 lcd_putc('\f');
 lcd_putc("    WARNING!    ");
 lcd_gotoxy(1,2);
 lcd_putc("      STOP      ");
 delay_ms(1000);
 lcd_putc('\f');
 lcd_gotoxy(1,1);
 lcd_putc(" TRAFFIC SIGNAL ");
 lcd_gotoxy(1,2);
 lcd_putc("    VIOLATED    ");
 delay_ms(1000);
 lcd_putc('\f');//clear 
 if(emer==1)
 data='E';
 else
 data='N';
 hdlmp=1;
// enter=1;


rcv=0;/////////////////////////////



 }
 else if(strcmp(rcv,'Y')==0)//yellow accdnt prone area signal [[2nd condiion]]
 {
  yelflag=!yelflag;
  //enter=1;
  // if(emer==1)
  // data='E';
  // else
  // data='N';
 if(yelflag==1)//first accdnt prone area light post
 {
 
 lcd_putc('\f');
 lcd_gotoxy(1,1);
 lcd_putc("    WARNING!    ");
 delay_ms(1000);
 speedflag=1;
 lcd_gotoxy(1,1);
 lcd_putc(" SPEED LIMITED  ");
 lcd_gotoxy(1,2);
 lcd_putc("     15 KMPH    ");
 delay_ms(1000);
  
 
 
 rcv=0;////////////////////////////////////////
 
 
 if(emer==1)
 {
 data='E';
 hdlmp=1;
 }
 else
 {
 data='N';
 }

// set_timer1(0x8AD0);//for 30000us delay ie 30ms
 del=30;// speed korakkan... del value kootiyal speed korayum!!
 }
 
 else if(yelflag==0)//2nd traffic accdnt prone area post
 {
 lcd_putc('\f');
 lcd_gotoxy(1,1);
 lcd_putc("SPEED LIMIT     ");
 lcd_gotoxy(1,2);
 lcd_putc("         ENDS...");
 
 
 rcv=0;/////////////////////////////////////////////
 
 speedflag=0;
 //set_timer1(0xEC78);// for 10000us delay ie 10ms
 del=10;   // max speed ... product aakumbol change cheyyendi varum.!!
 delay_ms(1000);
 }
  }
 
 
//==========================================================================\\


 if(hdlmp==1)// loop for transmision
 {
 //output_high(pin_b1);//for turning on high beam//turning highbeam or even both in future stages
 //output_high(pin_b2);//for turning on low beam
 for(j=0;j<5;j++)
 putc(data);//data 5 pravishyam transmitt cheyyum..for safety..lol..
 //but delay vende?? nokam??
// output_low(pin_b1);//for turning off high beam
// output_low(pin_b2);//for turning off low beam
 hdlmp=0;
 }//if closed
 

 
 //  }//if kbhit closed
   
   
   
 }//mode if closing
 
else // car mode else opens

{

// [[3]]
   if(input(pin_c0)==1&&dimflag==0)//switch for checking high or low beam...
   {
   output_high(pin_c1);//bright light
   }
   else
   {
   output_low(pin_c1);  ///dimmm
   }  
   
   


output_high(pin_d0);// ir on chey//ee carinte ir light on chey..? car mode select cheyumbol mathrame on aavullu..
if(input(pin_c3)==1)//ir detected[frm other car]
{
dimflag=1;
output_low(pin_c1);//pettannu dim cheyyan!!!
 lcd_putc('\f');
 lcd_gotoxy(1,1);
 lcd_putc("  BRIGHT LIGHT  ");
 lcd_gotoxy(1,2);
 lcd_putc("    REGULATED   ");
 delay_ms(2000);
}
else
{

if(dimflag==1)
{
 lcd_putc('\f');
 lcd_gotoxy(1,1);
 lcd_putc("  BRIGHT LIGHT  ");
 lcd_gotoxy(1,2);
 lcd_putc("    REVERTED    ");
 if(input(pin_c0)==1)
 output_high(pin_c1);//pettanu thanne light thirich aakum..
 delay_ms(2000);
 lcd_putc('\f');
}
 dimflag=0;
}



}// ELSE LOOP CLOSES... car modinte loop theernu!!


//=====================================================================\\



 
 
 
//!  /* else
//!   {
//!   output_low(pin_b3);
//!   enter=0;
//!   }*/
//!
//!//output_low(pin_b3);
//! 
   
   }   //while loop closed
   
   
   
   
   }    //void main closed
   
 //======================================================================\\
