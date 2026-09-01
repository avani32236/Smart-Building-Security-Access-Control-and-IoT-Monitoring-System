#include<lpc21xx.h>
#include"header.h"
#include<string.h>
#define GREENLED (1<<25)
#define REDLED (1<<26)
#define YELLOWLED (1<<27)
  

   #define R1 (1<<10)
   #define R2 (1<<11)
   #define R3 (1<<12)
   #define R4 (1<<13)
  
   #define C1 (1<<4)
  #define C2 (1<<5)
  #define C3 (1<<6)
  #define C4 (1<<24)


void keypad_init(void)

{

    IO0DIR |= (R1|R2|R3|R4);      

    IO0DIR &= ~(C1|C2|C3|C4);    

}


char keypad_read(void)

{

    while(1)

    {

        IO0SET = R2|R3|R4;

        IO0CLR = R1;


        if((IO0PIN & C1)==0){

		delay_ms(20); 

		while((IO0PIN&C1)==0); 

		return '1';

		}

        if((IO0PIN & C2)==0){

		delay_ms(20); 

		while((IO0PIN&C2)==0);

		return '2';

		}

        if((IO0PIN & C3)==0){

		delay_ms(20); 

		while((IO0PIN&C3)==0);

		return '3';

		}

        if((IO0PIN & C4)==0){

		delay_ms(20); 

		while((IO0PIN&C4)==0); 

		return 'A';

		}




        IO0SET = R1|R3|R4;

        IO0CLR = R2;


        if((IO0PIN & C1)==0){

		delay_ms(20);

		while((IO0PIN&C1)==0);

		return '4';

		}

        if((IO0PIN & C2)==0){

		delay_ms(20); 

		while((IO0PIN&C2)==0);

		return '5';

		}

        if((IO0PIN & C3)==0){

		delay_ms(20); 

		while((IO0PIN&C3)==0); 

		return '6';

		}

        if((IO0PIN & C4)==0){

		delay_ms(20); 

		while((IO0PIN&C4)==0); 

		return 'B';

		}




		IO0SET = R1|R2|R4;

        IO0CLR = R3;


        if((IO0PIN & C1)==0){

		delay_ms(20); 

		while((IO0PIN&C1)==0);

		return '7';

		}

        if((IO0PIN & C2)==0){

		delay_ms(20); 

		while((IO0PIN&C2)==0);

		return '8';

		}

        if((IO0PIN & C3)==0){

		delay_ms(20); 

		while((IO0PIN&C3)==0); 

		return '9';

		}

        if((IO0PIN & C4)==0){

		delay_ms(20); 

		while((IO0PIN&C4)==0); 

		return 'C';

		}


        

        IO0SET = R1|R2|R3;

        IO0CLR = R4;


        if((IO0PIN & C1)==0){

		delay_ms(20); 

		while((IO0PIN&C1)==0); 

		return '*';

		}

        if((IO0PIN & C2)==0){

		delay_ms(20); 

		while((IO0PIN&C2)==0);

		return '0';

		}

        if((IO0PIN & C3)==0){

		delay_ms(20); 

		while((IO0PIN&C3)==0);

		return '#';

		}

        if((IO0PIN & C4)==0){

		delay_ms(20); 

		while((IO0PIN&C4)==0); 

		return 'D';

		}

    }

}

void key()
{
char password[5];
char *valid_password="1234";
int i;

IODIR0|= GREENLED|REDLED;
IOSET0 = GREENLED|REDLED;
	
uart0_init(9600);
lcd_init();

lcd_cmd(0x01);
lcd_string("ENTER PASS");
uart0_tx_string("\r\n 4*4 Keypad Initialised");
uart0_tx_string("\r\n Waiting for password");
uart0_tx_string("enter password\n");

for(i=0;i<4;i++)
{
    password[i]=keypad_read();

    lcd_data('*');  
    uart0_tx(password[i]);
}

password[4]='\0';

if(strcmp(password,valid_password)==0)
{
    lcd_cmd(0x01);
	  IOCLR0 = GREENLED;
    IOSET0 = REDLED;
	uart0_tx_string("\r\n Password verified");
    lcd_string("ACCESS GRANTED");
				uart0_tx_string("Access Granted\n");

			servo_180deg();
			uart0_tx_string("door open \r\n");
}
else
{
    lcd_cmd(0x01);
	          IOCLR0= REDLED;
            IOSET0 = GREENLED;
	  lcd_string("WRONG PASSWORD");
			uart0_tx_string ("wrong password");
			servo_0deg();
			uart0_tx_string("not open\r\n");
}
}

