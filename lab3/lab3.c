#include<reg51.h>
#define GPIO_DIG P1 //Define the p1 port we are going to use 

void Delay10ms (unsigned int c); // This is a Global function  we declare Delay here 

// Define global variable here we define segment code for 0 to 9 serialy                                                                            
unsigned char code DIG_CODE[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 
                              0x7F, 0x6F}; 

	// main function 														
	void main(void)
	{ unsigned char i = 0; // define a variable i, the value of i is 0
		while(1){ // loop counter
			GPIO_DIG = ~DIG_CODE[i]; // start counting value of DIG_code from 0
			i++; // value of i increase i = i+1
			if(i == 10) // if it run 10 times 
			{
				i = 0;  //value of i will 0 again 
			}
			Delay10ms(50); // delay 
		}
	}
	
	void Delay10ms(unsigned int c) //0us error
	{ unsigned char a,b;
		
		for(;c>0;c--) // c already assigned before
		{ for(b=38;b>0;b--) //b will run untill its being 0 , value of b will decrease 
			// b = b-1
			{
				for(a=130;a>0;a--); // a also run 130 times untill it's being zero 
			}
		
		} //naem azam 
	
	}