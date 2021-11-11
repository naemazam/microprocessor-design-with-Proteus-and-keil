#include<reg51.h>

sbit led=P1^0; //Led connected to port-1 pin#0

void delay()
{
int count=0;
 while(count!=500)
  {
   TMOD=0x01;  //16-bit timer0 selected
   TH0=0xF8;   // Loading high byte in TH
   TL0=0xCC;   // Loaded low byte in TL
   TR0=1;      // Running the timer
    while(!TF0);   //Checking the timer flag register if it is not equal to 1 
   TR0 = 0;      // If TF0=1 stop the timer
   TF0 = 0;      // Clear the Timer Flag bit for next calculation

   count++;
  }

}

void main()
{
P1=0x00;   //Port-1 Declared Output

while(1)     // Constantly  running while loop.
{
led=1;    // LED glows here
delay();  // Delay for 1 second 
led=0;    // LED switch off
delay();  // Delay for 1 second
}

}  