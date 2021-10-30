/**
* This code reads a keyboard consisting of 10 keys and displays corresponding
* number on a 7 segment display.
* Based on the 8051 microcontroller.
*/

#include <reg51.h>

//7 segment display port segment A -> LSB, decimal point -> MSB
#define DISPLAY_PORT P2
//use entire port for keys 0->7
#define KEY_PORT0 P1
//2 pins of second port for keys 8->9
#define KEY_PORT1 P3
//select pins of second port
#define PORT1_0 2
#define PORT1_1 3
//second port masks
#define KEY_PORT1_MASK (~((1<<PORT1_0)|(1<<PORT1_1)))
#define KEY_PORT1_0 (~(1<<PORT1_0)) //value of port when corresponding button pulls pin down
#define KEY_PORT1_1 (~(1<<PORT1_1))
//timer0 initial values
#define INITIAL_TL0 0xCC
#define INITIAL_TH0 0xD4

const char disp_7seg[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void delay()
{
	TL0 = (INITIAL_TL0);
	TH0 = (INITIAL_TH0);
	TR0 = 1;
	while(!TF0);
	TR0 = 0;
	TF0 = 0;
}

char getKeyNo(char port0, char port1)
{
	switch(port0)
	{
		case 0xfe:
			return 0;
		case 0xfd:
			return 1;
		case 0xfb:
			return 2;
		case 0xf7:
			return 3;
		case 0xef:
			return 4;
		case 0xdf:
			return 5;
		case 0xbf:
			return 6;
		case 0x7f:
			return 7;
	}
	port1 |= (KEY_PORT1_MASK);
	switch(port1)
	{
		case 0xfb:
			return 8;
		case 0xf7:
			return 9;
	}
	return 0xff;
}

char keydown()
{
	return ~(((KEY_PORT1) | (KEY_PORT1_MASK)) & KEY_PORT0);
}

void getkey()
{
	//set keyboard ports as input
	KEY_PORT0 = 0xff;
	KEY_PORT1 = 0xff;
	while(!keydown());
}

//convert key number to 7 segment display (DP G F E D C B A)
//return values are complemented for common anode display
char keyTo7Seg(char key)
{
	switch(key)
	{
		case 0:
			return ~0x3f;
		case 1:
			return ~0x06;
		case 2:
			return ~0x5b;
		case 3:
			return ~0x4f;
		case 4:
			return ~0x66;
		case 5:
			return ~0x6d;
		case 6:
			return ~0x7d;
		case 7:
			return ~0x07;
		case 8:
			return ~0x7f;
		case 9:
			return ~0x6f;
	}
	return 0xff;
}

char key_buffer;

int main()
{
	//initialize timers
	TMOD |= 0x11;
	TMOD &= 0xFD;

	while(1)
	{
		getkey();
		delay();
		getkey();
		key_buffer = getKeyNo(KEY_PORT0, KEY_PORT1);
		P2 = keyTo7Seg(key_buffer);
	}
}
