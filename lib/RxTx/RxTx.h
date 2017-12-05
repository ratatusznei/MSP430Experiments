#ifndef RXTX_H
#define RXTX_H

#include "msp430.h"
#include <stdarg.h>

/*
	Baudrate callibration consts at 1 MHz
*/
#define CALBRR_9600 104
#define CALBRS_9600 1
#define CALBRF_9600 0

#define CALBRR_19200 52
#define CALBRS_19200 0
#define CALBRF_19200 0

#define CALBRR_38400 26
#define CALBRS_38400 0
#define CALBRF_38400 0

#define CALBRR_56000 17
#define CALBRS_56000 7
#define CALBRF_56000 0

#define CALBRR_115200 8
#define CALBRS_115200 6
#define CALBRF_115200 0

#define CALBRR_128000 7
#define CALBRS_128000 7
#define CALBRF_128000 0

#define CALBRR_256000 3
#define CALBRS_256000 7
#define CALBRF_256000 0

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

#endif // RXTX_H