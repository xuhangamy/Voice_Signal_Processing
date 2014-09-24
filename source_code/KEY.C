#include <reg52.h>
#include <absacc.h>
#include <intrins.h>
#include <stdio.h>
#define uchar           unsigned char
#define uint            unsigned short int
#define ulong           unsigned long int
/******************************************************************************
片选地址说明
******************************************************************************/
#define CS0             XBYTE[0xf8ff]
#define CS1             XBYTE[0xf9ff]
#define CS2             XBYTE[0xfaff]
#define CS3             XBYTE[0xfbff]
#define CS4             XBYTE[0xfcff]
#define CS5             XBYTE[0xfdff]
#define CS6             XBYTE[0xfeff]
#define CS7             XBYTE[0xffff]
#define CS_KEY          CS0
#define CS_LED_SEG      CS2
#define CS_LED_SEL      CS3
#define CS_ADC0809      CS4
#define CS_DAC0832      CS5
#define CS_LED          P1

uchar code str_num[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x67};
uchar idata key_h,key_l;

uchar Get_Key()	;		//返回键值--键值说明见程序未
void delay_ms(uint dl)
{
	uint cnt,i;
	for(cnt=0;cnt<dl;cnt++){
		for(i=0;i<125;i++);
	}
}

void timer1(void) interrupt 3 
{
    TR1=0;
    CS_LED_SEL=0XFD;
	CS_LED_SEG=str_num[key_h];
    delay_ms(5);
	CS_LED_SEL=0XFE;
	CS_LED_SEG=str_num[key_l];
    delay_ms(5);
	TH1=252;//(0XFFFF-1000)/256
	TL1=24; //(0XFFFF-1000)%256
        TR1=1;
}

void main()
{
	uchar idata keyval;
	CS_LED_SEL=0X00;
	CS_LED_SEG=0XFF;
	delay_ms(500);
	CS_LED_SEL=0X00;
	CS_LED_SEG=0X00;
    key_h=0;
    key_l=0;
    TMOD=0X10;
	TH1=252;
	TL1=24;
	ET1=1;
	EA=1;
	TR1=1;//启动定时器动态刷新led显示
	while(1){
		keyval=Get_Key();
		key_h=keyval/10;
		key_l=keyval%10;
		case 1://KEY1 TO AD
			{
			 	timer0_init();		
				while(ADDR<MAXAD);
			}
		break;
	}
}
uchar Get_Key()			//返回键值--键值说明见程序未
{
	bit a=1;
    uchar   idata key_num;
	uchar	idata key_orign=0xff;
	uchar	idata key_row,key_clumn;
	CS_KEY = 0x00;		//行置低
	while(a)	//判断是否有按键按下
	{
		key_orign = CS_KEY;
		key_orign &=0x0f;
		if(key_orign != 0x0f)
		{
			delay_ms(20);
			if(key_orign == (CS_KEY&0X0F))
			a=0;
		}
	}
	if((~key_orign)&0x0f)		//4*4键盘有键按下--判断键值;
	{
		key_row	= (~key_orign)&0x0f;	//记录列值
		for(key_clumn=0;key_clumn<4;key_clumn++)
		{
			CS_KEY=_crol_(0xfe,key_clumn);
			if((CS_KEY&0x0f)==key_orign)
				break;
		}
		switch((key_row)|(key_clumn<<4))
		{
			case 0x01:key_num=1;break;
			case 0x02:key_num=2;break;
			case 0x04:key_num=3;break;
			case 0x08:key_num=4;break;
			case 0x11:key_num=5;break;
			case 0x12:key_num=6;break;
			case 0x14:key_num=7;break;
			case 0x18:key_num=8;break;
			case 0x21:key_num=9;break;
			case 0x22:key_num=10;break;
			case 0x24:key_num=11;break;
			case 0x28:key_num=12;break;
			case 0x31:key_num=13;break;
			case 0x32:key_num=14;break;
			case 0x34:key_num=15;break;
			case 0x38:key_num=16;break;
			default:key_num=31;break;
		}
	}
	CS_KEY=0x00;
	while((~CS_KEY)&0x0f);
	delay_ms(20);
	while((~CS_KEY)&0x0f);
	return key_num;
}
