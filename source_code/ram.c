#include<reg52.h>
#include <absacc.h>
#define RAM   XBYTE[0x0000] 

#define CS0             XBYTE[0xf8ff]
#define CS1             XBYTE[0xf9ff]
#define CS2             XBYTE[0xfaff]
#define CS3             XBYTE[0xfbff]
#define CS4             XBYTE[0xfcff]
#define CS5             XBYTE[0xfdff]
#define CS6             XBYTE[0xfeff]
#define CS7             XBYTE[0xffff]
#define CS_LED_SEG      CS2
#define CS_LED_SEL      CS3
#define CS_LED          P1
#define uchar           unsigned char
#define uint            unsigned  int
uchar code str_num[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x67};
uchar dis[3];
uint s;

void delay_ms(uint dl)
{
	uint cnt,k;
	for(cnt=0;cnt<dl;cnt++)
	{
		for(k=0;k<125;k++);
	}
}

void LED_light(uchar num)
{
	 dis[0]=(uchar)(num/100);
     dis[1]=(uchar)((num-dis[0]*100)/10);
     dis[2]=(uchar)(num-dis[0]*100-dis[1]*10);
          for(s=0;s<3;s++)
		  {
              CS_LED_SEL=(0XFB>>s)|0XF8;
              CS_LED_SEG=str_num[dis[s]];	
		  }
}

uchar xdata *pl=&RAM;


void main()
{
	uint i,j;
	uchar shownum;
	for(i=0;i<256;i++)
    {
	*(pl+i)=i;
	}
	delay_ms(5);
	while(1)
	{
		for(j=0;j<256;j++)
		{
		shownum=*(pl+j);
		LED_light(shownum);
		}
	}
}