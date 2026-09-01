#include"header.h"

 #include<lpc21xx.h>


 void wifi(){

 	uart0_tx_string("AT\r\n");

	delay_ms(100);

	uart0_tx_string("AT+CWMODE=1\r\n");

	delay_ms(100);

	
	uart0_tx_string("AT+CWJAP=\"sai\",\"123456789\"\r\n");

	delay_ms(100);

	uart0_tx_string("AT+CIFRS\r\n");

	delay_ms(100);

	

	uart0_tx_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

	delay_ms(100);

	

	uart0_tx_string("\r\nAT+CIPSEND=122");

	delay_ms(100);

	

	//uart0_str("GET /update?api_key=\r\n=I7CAZU9NW9XSZDNG&field1=30&field2=45 HTTP/1.1\r\n");

	uart0_tx_string("GET /update?api_key=\r\n=P3NMKR3M8JKHDZFJ&field1=30&field2=45 HTTP/1.1\r\n");

	delay_ms(100);

	

	uart0_tx_string("Host:api.thingspeak.com\r\n\r\n");

	delay_ms(100);

	uart0_tx_string("connection:close\r\n\r\n");

	delay_ms(100);	

 }


 void esp_read(void){

 	unsigned char ch;

	while(1){

		ch=uart0_rx();

		uart0_tx(ch);

	}

}

