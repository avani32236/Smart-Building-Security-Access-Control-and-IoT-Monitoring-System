/*header.h*/
#ifndef __HEADER_H_
#define __HEADER_H_

#define PORT0 0
#define PORT1 1
#define SET   1
#define CLEAR 0
typedef unsigned int u32;
typedef 	signed int s32;
typedef unsigned char u8;
typedef 	signed char s8;
typedef unsigned short int u16;
typedef   signed short int s16;


void delay_sec(u32 sec);
void delay_ms(unsigned int ms);


unsigned char uart0_rx(void);
void uart0_tx(unsigned char data);
void uart0_init(unsigned int baud);
void uart0_tx_string(char *ptr);
void uart0_tx_integer(int num);
void uart0_tx_float(float num);
void uart0_tx_hex(int num);


extern void config_vic_for_eint0(void);
extern void config_eint0(void);
extern void config_vic_for_uart0(void);

extern u32 mcp3204_read(u8 ch_num);
extern void spi0_init(void);
extern u8 spi0(u8 data);

extern void i2c_init(void);
extern void i2c_send(u8 sa,u8 mr,u8 data);
extern u8 i2c_read(u8 sa,u8 mr);

extern void lcd_init(void);
extern void lcd_cmd(u8 cmd);
extern void lcd_data(u8 data);
extern void lcd_string(s8 *ptr);
extern void delay_ms(u32 ms);

extern void config_vic_for_eint0(void);

typedef struct CAN1_MSG{
	u32 id;
	u32 byteA;
	u32 byteB;
	u8 rtr;
	u8 dlc;
	u8 ff;
}CAN1;

extern void can1_tx(CAN1 v);
extern void can1_init(void);






#endif


