#include<reg52.h>
#include <absacc.h>
#define RAM       XBYTE[0x0000] 
#define CS0             XBYTE[0xf8ff]//74HC245
#define CS1             XBYTE[0xf9ff]//74HC245
#define CS2             XBYTE[0xfaff]//74HC573
#define CS3             XBYTE[0xfbff]//74HC573
#define CS4             XBYTE[0xfcff]//ADC0809
#define CS5             XBYTE[0xfdff]//ADC0832
#define CS6             XBYTE[0xfeff]
#define CS7             XBYTE[0xffff]
#define CS_ADC0809      CS4
#define CS_DAC0832      CS5
#define uchar           unsigned char
#define uint            unsigned  int

uint *pl=&RAM;
uint ADDR=0;
sbit EOC=P1^0;
sbit E=P1^3;
sbit F=P1^4;
sbit G=P1^5;
uchar idata DATA;
///////////////////////////////////////////////////////
void delay(uint i)
{
 while(i--);
}

///////////////////////////////////////////////////////
void main()
{

	TMOD=0X01;
	TH0=0XFF;
	TL0=0X83;
	EA=1;
	ET0=1;//timer0
	TR0=1;
	while(1);
}
///////////////////////////////////////////////////////
void timer0() interrupt 1
{
	 //	TR1=0;
	if(ADDR<0XFF)
	{
		DATA=0X00;
	    CS_ADC0809=0x00;
    	delay(2);
     	while(EOC!=1);
		G=0;
    	delay(8);
		DATA=CS_ADC0809;
		*(pl+ADDR)=DATA;
		ADDR++;						
	}
		TH0=0XFF;
		TL0=0X83;
	//	TR1=1;
}

