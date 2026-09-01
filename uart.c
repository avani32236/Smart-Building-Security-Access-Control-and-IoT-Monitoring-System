#include<lpc21xx.h>
#include"header.h"
void uart0_init(unsigned int baud)
{
	int pclk,result=0;
	if(VPBDIV==0x0)
		pclk=15000000;
	else if(VPBDIV==0x01)
		pclk=60000000;
	else if(VPBDIV==0x02)
		pclk=30000000;
	result=pclk/(16*baud);
	PINSEL0|=0x00000005;
	U0LCR=0x83;
	U0DLL=(result&0xff);
	U0DLM=((result>>8)&0xff);
	U0LCR=0x03;
}
#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}

void uart0_tx_string(const char *p)
{
	while(*p!=0)
	{
		uart0_tx(*p);
	p++;
	}
}

#define RDR (U0LSR&1)
unsigned char uart0_rx()
{
	while(RDR==0);
	return U0RBR;
}


void uart0_rx_string(unsigned char *p,u32 a)
{
	int i;
	for(i=0;i<a;i++)
	{
		while(RDR==0);
		p[i]=U0RBR;
		if(p[i]=='\r')
			break;
	}
	p[i]='\0';
}
void uart0_tx_integer(int num)
{
char a[10];
int i;
if(num<0)
{
uart0_tx('-');
num=-num;
}
if(num==0)
{
uart0_tx('0');
return;
}
for(i=0;num;num=num/10,i++)
a[i]=num%10+48;
for(--i;i>=0;i--)
uart0_tx(a[i]);
}

