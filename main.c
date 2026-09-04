#include<lpc21xx.h>
#include"header.h"
#include<string.h>
#define LED_PIN (1 << 11)  
#define PIR_PIN (1<<23)
#define GREENLED (1<<25)
#define REDLED (1<<26)
#define YELLOWLED (1<<27)
char *password[5];   
main() 
 {
 static int i;
 u8 am_pm;
 int t[6];
   unsigned char a[13],c[13];
   unsigned char b[]="4900C8FDDCA0";
 
 IO0DIR|=LED_PIN;
 IO0SET=LED_PIN;
 uart0_init(9600);
 i2c_init();
 servo_init();
 keypad_init(); 
can1_init(); // Enabled CAN initialization
 uart0_tx_string("\r\n===SMART BUILDING SECURITY SYSTEM===");
 uart0_tx_string("\r\n system initialising.....");
 lcd_string("system initialising");
 uart0_tx_string("\r\n uart initialised");
 lcd_string(" uart initialised");

 while(1)
 {
//PIR Sensor initialised
 if(((IO0PIN>>23)&1)==1)
 {
 IO0CLR=GREENLED;
 uart0_tx_string("\r\n PIR Motion Sensor initialised");
 uart0_tx_string("\r\n Monitoring for Motion\n");
 delay_ms(2000);
 uart0_tx_string("\r\nmotion detected\n");
 lcd_string("motion detected\r\n");
 //RFID CARD Initialised
uart0_tx_string("\r\n===RFID CARD INITIALISATION===");
uart0_tx_string("\r\n scan your rfid card:");
lcd_string("\r\n scan your rfid card");
uart0_rx_string(a,12);
uart0_tx_string("\r\n data received");
lcd_string("\r\n data recived\n");
uart0_tx_string(a);
lcd_string(a);
for(;a[i]!='\0';i++)
{
if(a[i]=='\r' || a[i]=='\n')
{
a[i]='\0';
break;
}
}
if(strcmp(a,b)==0)
{
uart0_tx_string("\r\n RFID CARD AUTHENTICATION SUCCESSFUL");
lcd_string("\r\n match");

// --- CAN MESSAGE TRANSMISSION START ---
                msg.id = 0x101;       // Node ID for Door 1
                msg.dlc = 8;          // 8 Data Bytes
                 msg.rtr = 0;          // Data Frame
                msg.ff = 0;           // Standard Frame Format
                msg.byteA = (a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3]; // Send RFID tag first 4 bytes
                msg.byteB = (a[4] << 24) | (a[5] << 16) | (a[6] << 8) | a[7]; // Send RFID tag next 4 bytes
                can1_tx(msg);         // Transmit over CAN
                uart0_tx_string("\r\n CAN Log Message Transmitted");
                // --- CAN MESSAGE TRANSMISSION END ---

uart0_tx_string("\r\n SERVO MOTOR INTIALISED");
lcd_string("servo motor ready");
uart0_tx_string("\r\n Door Control Ready");
servo_90deg();
uart0_tx_string("\r\nDoor opened");
lcd_string("\r\n Door open");
delay_ms(100);
servo_0deg();
uart0_tx_string("\r\nDoor Closed");
lcd_string("door closed");
//RTC Initialised
rtc_write();
read(t);
if(t[2]<12)
am_pm='A';
else
am_pm='P';
//EEPROM Initialised
eeprom_store_pass(a);
eeprom_store_datetime(t[0],t[1],t[2],am_pm,t[3],t[4],t[5]);
for(i=0;i<13;i++)
{
c[i]=i2c_read(0xA1,i);
}
uart0_tx_string(c);
uart0_tx_string("data is stored\r\n");
uart0_tx_string("\r\n");

}
else
{ uart0_tx_string("\r\n RFID CARD AUTHENTICATION FAILED");
lcd_string("\r\nnot match");
servo_0deg();
uart0_tx_string("\r\nNot Open");
lcd_string("\r\n" );
//KEYPAD Initialised
uart0_tx_string("\r\n===KEYPAD INITIALISED===");
uart0_tx_string("\r\nEnter Password");
key();
rtc_write();
read(t);
if(t[2]<12)
am_pm='A';
else
am_pm='P';

eeprom_store_pass(a);
eeprom_store_datetime(t[0],t[1],t[2],am_pm,t[3],t[4],t[5]);
uart0_tx_string("data is stored\r\n");
 }
 }
 IO0SET=LED_PIN;
 uart0_tx_string("no motion\r\n");
uart0_tx_string("\r\n not open");
}			   
}




