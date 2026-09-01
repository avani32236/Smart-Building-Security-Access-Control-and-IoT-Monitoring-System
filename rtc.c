#include<lpc21xx.h>
#include"header.h"
extern u8 hrs,mins,secs,date,month,year;
void rtc_write()
{
i2c_init();
i2c_write(0xD0,0x2,0x23);
i2c_write(0xD0,0x1,0x59);
i2c_write(0xD0,0x0,0x55);
i2c_write(0xD0,0x4,0x14);
i2c_write(0xD0,0x5,0x08);
i2c_write(0xD0,0x6,0x26);
}
void read(int a[])
{
a[0]=i2c_read(0xD1,0x2);
a[1]=i2c_read(0xD1,0x1);
a[2]=i2c_read(0xD1,0x0);
a[3]=i2c_read(0xD1,0x4);
a[4]=i2c_read(0xD1,0x5);
a[5]=i2c_read(0xD1,0x6);

uart0_tx((a[0]/16)+48);
uart0_tx((a[0]%16)+48);
uart0_tx(':');
uart0_tx((a[1]/16)+48);
uart0_tx((a[1]%16)+48);
uart0_tx(':');
uart0_tx((a[2]/16)+48);
uart0_tx((a[2]%16)+48);

uart0_tx('\r');

uart0_tx((a[3]/16)+48);
uart0_tx((a[3]%16)+48);
uart0_tx('/');
uart0_tx((a[4]/16)+48);
uart0_tx((a[4]%16)+48);
uart0_tx('/');
uart0_tx((a[5]/16)+48);
uart0_tx((a[5]%16)+48);

uart0_tx('\r');
}





