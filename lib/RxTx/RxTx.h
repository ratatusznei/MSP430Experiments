#include "msp430.h"
#include <stdarg.h>

/* 
	Initializes the uart:
		- 8 data bits
		- No parity
		- 1 stop bit
		- baud configured via brr, brf and brs
			- See tables in pages 424-425 of slau144.pdf
		- LSB first

	It also changes the DCO frequency to 1 MHz
*/
void RxTx_init (int brr, int brf, int brs);

// Wait a char to be available and return it
#define RxTx_getc() RxTx_getchar()
char RxTx_getchar ();

// Writes a char to out buffer if not busy
#define RxTx_putc(data) Rx_Tx_putchar(data)
void Rx_Tx_putchar (char data); 

// Sends a string via the uart
void RxTx_puts (char *str);

// Sends a formatted string via the uart
void RxTx_printf (char *format, ...);

