#include<lpc214x.h>
#include"TIMER.h"
#include"ULTRASONIC.h"
#include"LCD.h"
#define EN (1<<16)|(1<<17)
int cent = 100;
#define delay for(i=0;i<65000;i++);
unsigned int range,i;
unsigned int value;
int main()
{		
		VPBDIV=0x01;                // PCLK = 60MHz
    IO0DIR |= 0x00FF3400; 			//10 12 13 16-23
																//0000000111111110011010000000000
		IO1DIR = EN;
    ultrasonic_init();
    lcd_init();
    //show("Distance :");
		IOSET1 = EN;
    while(1) 
		{
			cmd(0x8A);
			range = 30;		//range=get_range();
			dat((range/100)%10+48);
      dat((range/10)%10+48);
      dat((range%10)+48);
      //show("cm");
			
			if (range<50)
			{
				IOCLR1 = IOCLR1|EN;
				cmd(0xc0);
				//show("EMERGENCY BRAKE ");
			}
			else if (range<=100&range>=50)
			{
				if(IOSET1&&EN == EN)
				{
					cmd(0xc0);
					//show("CRASH WARNING  ");
					cent=range;
					while(cent!=0)
					{
						//range = get_range();
						if(range<=100 & range>=50)
						{
							IOSET1 = IOSET1|EN;
							timer1delay(cent*200);
							IOCLR1 = IOCLR1|EN;
							timer1delay((100-cent)*200);
							cent=cent-(1);
						}
						else if (range<50)
						{
							IOCLR1 = IOCLR1|EN;
							cmd(0xc0);
							//show("EMERGENCY BRAKE ");
						}
						else
						{
							break;
						}
					}
				}
			}
			//range=get_range();
			else if (range>100)
			{
				IOSET1 = IOSET1|EN;
				cmd(0xC0);
				//show("You are safe :) ");
			}			
		}
		return 0;
}