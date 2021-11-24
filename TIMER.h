#include<lpc214x.h>
void timer0delay(unsigned int a);
void timer1delay(unsigned int b);

void timer0delay(unsigned int a)
{
		T0TCR=0X02;
    T0CTCR=0X00;
    T0PR=0X1D;
    T0MR0=a;              
    T0MCR=0X0004;
    T0TCR=0X01;
    while(T0TC!=T0MR0);
    T0TC=0;
}


void timer1delay(unsigned int b)
{
		T1TCR=0X02;
    T1CTCR=0X00;
    T1PR=0X1D;
    T1MR0=b;              
    T1MCR=0X0004;
    T1TCR=0X01;
    while(T1TC!=T1MR0);
    T1TC=0;
}
