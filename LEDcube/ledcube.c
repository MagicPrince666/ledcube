#include "STC12C5A60S2.H"
#include<intrins.h>
#include"move.h"
#include"FFT.H"			 //FFT(快速傅里叶变换)功能头文件
#define u8 unsigned char 
#define u16 unsigned int
sbit ST=P4^5;
sbit DAT=P3^7;
sbit SH=P4^6;
sbit KEY1=P3^2;
sbit KEY2=P3^3;
sbit KEY3=P3^4;
unsigned int tim0=0,tim1=0;
unsigned char ADC_Count=0,LINE=15,G=0,T,flag=1;
unsigned char code cen[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
//unsigned char code cen[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
unsigned char code tablew[]={0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF}; 
unsigned char buffer[8];
void delay(unsigned int x)
{
  unsigned char y;
  for(x;x;x--)
   for(y=110;y;y--);
}
void hc595(unsigned char dat)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
     if((dat<<i)&0x80)
  	 DAT=1;
	 else
	 DAT=0;
	 SH=0;
	 //_nop_();
	 SH=1;
  }  
}
void hc595out()
{
  ST=0;
  ST=1;
}
void gaodu(u8 high)//
{
    u8 i;
	for(i=0;i<8;i++)
    hc595(high);	   //发送段选数据
	hc595out();
}
void display(u16 time,u8 dat)
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<1;z++)
  {
    while(tim1<time)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(dat);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void display_yanhua(u16 time,u8 yiwei)
{
  unsigned char x,y,z;
  u16 light;
  TR0=1;
  TR1=1;
  for(z=0;z<6;z++)
  {
    while(tim1<100)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(yanhua[0][y][x]<<yiwei);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[y]>>(7-z);
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  for(z=1;z<6;z++)
  {
    while(tim1<time)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(yanhua[z][y][x]<<yiwei);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
              for(light=(6-z)*80;light;light--);
			  P2=0x00;
			  for(light=z*100;light;light--);
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displaycube(u16 time)
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<26;z++)
  {
    while(tim1<time)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(cube[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displaycube2(u16 time)
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<8;z++)
  {
    while(tim1<time)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(cube2[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displaysnow()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<14;z++)
  {
    while(tim1<50)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(snow[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}

void displayy_table()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<6;z++)
  {
    while(tim1<200)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(y_table[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}


void displayhart_table(shu)
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<2;z++)
  {
    while(tim1<shu*10)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(hart_table[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displaysin_cube_table()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<14;z++)
  {
    while(tim1<60)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(sin_cube_table[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displayx_table()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<6;z++)
  {
    while(tim1<200)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(x_table[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displayz_table()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<6;z++)
  {
    while(tim1<200)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(z_table[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}

void displayyx_table()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<26;z++)
  {
    while(tim1<200)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(yx_table[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}

void displayxz_table()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<26;z++)
  {
    while(tim1<200)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(xz_table[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}

void displaybianxing()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<11;z++)
  {
    while(tim1<200)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(bianxing[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displayshandian()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<22;z++)
  {
    while(tim1<100)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		  
		  hc595(shandian[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displayrain()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<8;z++)
  {
    while(tim1<60)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		  
		   hc595(rain[0][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=_crol_(cen[y],(7-z));
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displayloudou(u16 time)
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<8;z++)
  {
    while(tim1<time)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(king[7-z][7-y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displayking()
{
  u8 x,y,z,i=0,j=0,num;
  u8 Cube[8][8];
  for(x=0;x<8;x++)
    for(y=0;y<8;y++)
	  Cube[x][y]=0x00;
  TR0=1;
  TR1=1;
  for(i=0;i<8;i++)
  {
    if(i<4)z=-8*i+28;
	else z=8*i-28;
	j=i;
	for(num=0;num<z;num++)
	{
	  if(i<4)
	  {
		  switch(num/(z/4))
	      {
		    case 0:{Cube[i][j]|=Cube[i][j]>>1|cen[7-i];}break;
			case 1:{Cube[i][j++]|=cen[i];}break;
			case 2:{Cube[i][7-i]|=Cube[i][7-i]<<1|cen[i];}break;
			case 3:{Cube[i][j]|=Cube[i][j]|cen[7-i];j--;}break;
		  }
	  }
	  else
	  {
	  	  switch(num/(z/4))
	      {	
		    case 0:{Cube[i][7-j]|=Cube[i][7-i]>>1|cen[i];}break;
			case 1:{Cube[i][7-j]|=cen[7-i];j--;}break;
			case 2:{Cube[i][i]|=Cube[i][i]<<1|cen[7-i];}break;
		    case 3:{Cube[i][7-j]|=Cube[i][7-j]|cen[i];j++;}break;			
		  }
	  }
	  	
	    while(tim1<80)
		{
		  	for(y=0;y<8;y++)
			{
			  tim0=0;
			  for(x=0;x<8;x++)
			  {
			   hc595(Cube[y][x]);
			  }
			  hc595out();
			  while(tim0<2)
			  {
				  P2=cen[y];
				  delay(2);
				  P2=0x00;
			  }  
			}
		}
		tim1=0;
	  }
  }
  TR0=0;
  TR1=0;
}

void displaywater(u16 time)
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<8;z++)
  {
    while(tim1<time)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(water[0][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[y]<<(7-z);
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  for(z=1;z<6;z++)
  {
    while(tim1<time)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(water[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}

void displaywater_1()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
   for(z=0;z<8;z++)
  {
    while(tim1<110)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   //hc595(0xff);
		   hc595(water_1[0][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[y]<<(7-z);
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  for(z=1;z<6;z++)
  {
    while(tim1<80)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   //hc595(0xff);
		   hc595(water_1[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void displayIVU_1()
{
  unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<21;z++)
  {
    if((z+1)%7==0)
	{
	while(tim1<=300)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(IVU_1[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
	}
	else
	{
    while(tim1<=100)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(IVU_1[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
	}
  }
  TR0=0;
  TR1=0;
}
void display_LCX()
{
 unsigned char x,y,z;
  TR0=1;
  TR1=1;
  for(z=0;z<27;z++)
  {
    while(tim1<150)
	{
	  	for(y=0;y<8;y++)
		{
		  tim0=0;
		  for(x=0;x<8;x++)
		  {
		   hc595(LCX[z][y][x]);
		  }
		  hc595out();
		  while(tim0<2)
		  {
			  P2=cen[7-y];
			  delay(2);
			  P2=0x00;
		  }  
		}
	}
	tim1=0;
  }
  TR0=0;
  TR1=0;
}
void interinit()
{
  TMOD=0x11;
  TH0=(65536-2000)/256;
  TL0=(65536-2000)%256;
  TH1=(65536-2000)/256;
  TL1=(65536-2000)%256;
  ET0=1;
  ET1=1;
  TR0=0;
  TR1=0;
  IPH = PADCH;
  IP  = PADC;			  //中断优先级
  EA=1;
  P1ASF  = 0x03;          //0000,0010, 将 P1.1 置成模拟口
  AUXR1 &=0xFB;           //1111,1011, 令 ADRJ=0
  EADC   =1;				//AD中断打开
  ADC_CONTR = ADC_POWER | ADC_SPEEDHH | ADC_START | channel; //1110 1001   1打开 A/D （ADC_POWER）转换电源；11速度为90周期一次；
	    		                                               //0中断标志清零；1启动adc(ADC_START);001AD通道打开（这里为P1.1）;
}
void main()
{  
   unsigned char shu,i; 	  
   interinit();
//   P2M0 = 0xff;
//   P2M1 = 0x00;
//   P3M0 = 0x80;
//   P3M1 = 0x00;
//   P4M0 = 0xff;
//   P4M1 = 0x00;


   P2=0x00;
   gaodu(0x00);
   TR0=1; 
   while(tim0<10000)
   {
	   if(KEY1==0)
	   {
	     flag=1;
	     break;
	   }
	   if(KEY2==0)
	   {
	     flag=2;
	     TMOD = 0x12; //T0: 8位自动重装      T1: 16位模式
		 TH0  = 0x70; //ADC采样周期（80us或6.66us）  采样率 12.5 KHz                              				  
		 TL0  = 0x70; //
		 TH1  = 0xfd; //刷新显示周期（300us或25us） 	刷新率 										   
		 TL1  = 0Xa8; //
		 EADC = 1;	  //开启ADC 
		 TR1   = 1; //刷新显示
		 TR0   = 1; //控制采样速率
		 ADC_Count=0;
		 break;
	   }
	   if(KEY3==0)
	   {
	     flag=3;
	     break;
	   }
	   else
	   flag=1;
   }
   TR0=0;
   tim0=0;
   while(1)
   {
	   while(flag==3)
	   {	    
	   	//display(1000,0xff);
		displaywater_1();
	   }
	   while(flag==1)
	   {
	        displayking();
			displayloudou(200);
		    displaycube(200);
		    display(1000,0xff);
			displaycube2(200);
			display(300,0x00);
		    displayIVU_1();
			display_LCX();
		    displayshandian();
		    for(shu=0;shu<5;shu++)
		   {
		     displaysnow();
		   }
		   for(shu=20;shu>10;shu--)
		   {
		     displayhart_table(shu);
		   }
		   display_yanhua(100,2);
		   display_yanhua(100,1);
		   display_yanhua(100,0);
		   for(shu=0;shu<3;shu++)
		   {
		   displaywater_1();
		   }
		   displaywater(100);
		   displaywater(100);
		   for(shu=0;shu<5;shu++)
		   {
		   displayrain();
		   }
		    for(shu=5;shu>0;shu--)
		   { 
		   displaysin_cube_table();
		   }   
		    
		   displayxz_table();
		   displayyx_table(); 
			for(shu=2;shu>0;shu--)
		   { 
		   displayx_table();
		   displayy_table();
		   displayz_table(); 
		   } 
		   displaybianxing();
		   display(1000,0x00);
	   }
	   while(flag==2)
	   {
		    TR1  = 1;     //开启定时器中断1
			TR0  = 1;     //开启定时器中断0
			EADC = 1;	  //开启ADC 
			    ADC_Count=0;
			    while(ADC_Count<128); //转换128次
				for(i=0;i<128;i++)	  //FFT参数虚部赋值
				{
					Fft_Image[i]=0;	  //原始数据 虚部赋值为0
				}
				FFT();                //FFT运算并转换为各频段幅值
			
	   }
	}
}



void time1() interrupt 3
{
   if(flag==2)
   {
    TH1  = 0xfd; //刷新显示周期（300us或25us） 	刷新率 										   
	TL1  = 0Xa8; //
	G++;						  	
	if(G>=17) G=1;
   	switch(G)								     //往点阵屏填充一列的数据
	{		
		case 1: P2=tablew[(LED_TAB[0])%8];gaodu(0x80);break;	 //(LED_TAB[1] )%8取八的余数
		case 2: P2=tablew[(LED_TAB[1])%8];gaodu(0x80);break;
		case 3: P2=tablew[(LED_TAB[2])%8];gaodu(0x40);break;
		case 4: P2=tablew[(LED_TAB[3])%8];gaodu(0x40);break;
		case 5: P2=tablew[(LED_TAB[4])%8];gaodu(0x20);break;
		case 6: P2=tablew[(LED_TAB[5])%8];gaodu(0x20);break;
		case 7: P2=tablew[(LED_TAB[6])%8];gaodu(0x10);break;
		case 8: P2=tablew[(LED_TAB[7])%8];gaodu(0x10);break;
		case 9: P2=tablew[(LED_TAB[8])%8];gaodu(0x08);break;
		case 10:P2=tablew[(LED_TAB[9])%8];gaodu(0x08);break;
		case 11:P2=tablew[(LED_TAB[10])%8];gaodu(0x04);break;
		case 12:P2=tablew[(LED_TAB[11])%8];gaodu(0x04);break;
		case 13:P2=tablew[(LED_TAB[12])%8];gaodu(0x02);break;
		case 14:P2=tablew[(LED_TAB[13])%8];gaodu(0x02);break;
		case 15:P2=tablew[(LED_TAB[14])%8];gaodu(0x01);break;
		case 16:P2=tablew[(LED_TAB[15])%8];gaodu(0x01);break;
	}
	P2=0X00;	
   }
   else
   {
	   TH1=(65536-2000)/256;
	   TL1=(65536-2000)%256;
	   tim1++;
   }
}
void ADC_Finish() interrupt 5
{	   
	ADC_CONTR &= !ADC_FLAG; 
	Fft_Real[LIST_TAB[ADC_Count]] =(int)((ADC_RES)<<1)+(ADC_RESL>>1)*2;     //按LIST_TAB表里的顺序，进行存储采样值
	if(ADC_Count<=127)
	 { ADC_Count++;  }
	else              
	 { EADC=0;TR0=0; }	  													 
}
void Ad_Control() interrupt 1					 
{				
	//控制采样速率
	if(flag==2)
	{
		ADC_CONTR = ADC_POWER | ADC_SPEEDHH| ADC_START | channel; //开始AD采集
	}
	if(flag==1 || flag==3)
	{ 
     TH0=(65536-2000)/256;
     TL0=(65536-2000)%256;
     tim0++; 	
	}
	if(flag==0||flag==4);
} 
