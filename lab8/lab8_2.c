#include<reg52.h>
#define lcd_data P2

sbit rs=P0^0;
sbit rw=P0^1;
sbit en=P0^2;

void delay()
{
unsigned int i,j;
for(i=0;i<3000;i++)
for(j=0;j<2;j++);
}

void command(unsigned int comand) //Sending initialing commands to lcd
{
P2=comand; rw=0; rs=0; en=0;
en=1;
en=0;
}

void lcddata(char value) //Sending data to be displayed on lcd screen
{
P2=value; rw=0; rs=1; en=0;
delay();
en=1;
delay();
en=0;
}

void lcd() //Initialing lcd
{
command(0x30); delay(); command(0x30); delay(); command(0x30);
delay(); command(0x38); delay(); command(0x01); delay(); command(0x0F);
delay(); command(0x0C); delay(); 
command(0x80); //Lcd rirst row selected for data printing
delay();
}

void main()
{
lcd(); //First initialize 16x2 lcd, 5x7 matrix display, cursor off

lcddata(' '); lcddata('!'); delay(); lcddata('!'); delay(); lcddata('N');
delay(); lcddata('A'); delay(); lcddata('E'); delay(); lcddata('M');
delay(); lcddata('-'); delay(); lcddata('A'); delay(); lcddata('Z');
delay(); lcddata('A'); delay(); lcddata('M'); delay(); lcddata('!');
delay(); lcddata('!'); delay(); lcddata(' '); delay(); lcddata(' ');
delay();

command(0xC0); //Command to jump to second row of lcd
	delay(); lcddata('I'); delay(); lcddata('D'); delay(); lcddata(':');
delay(); lcddata(' '); delay(); lcddata('L'); delay(); lcddata('2');
delay(); lcddata('0'); delay(); lcddata('1'); delay(); lcddata('9');
delay(); lcddata('3'); delay(); lcddata('0'); delay(); lcddata('0');
delay(); lcddata('2'); delay(); lcddata('7'); delay(); lcddata(' ');
delay(); lcddata(' ');
delay();
}