#include "RxTx.h"

void RxTx_init(int brr, int brf, int brs) {
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	// Configure Rx and Tx pins
	P1SEL |= BIT1 | BIT2;
	P1SEL2 |= BIT1 | BIT2;

	// USCI in reset state
	UCA0CTL1 = UCSWRST;

	// UCA0CTL0 = UCPEN_0 | UCMSB_0 | UC7BIT_0 | UCSPB_0 | UCMODE_0 | UC_SYNC0;
	// É o mesmo que:
	UCA0CTL0 = 0;

	// Clock = SMCLK
	UCA0CTL1 = UCSSEL_2;

	/*
		Baud rate config
			See tables in pages 424-425 of slau144.pdf
	*/
	UCA0BR0 = brr & 0x00FF;
	UCA0BR1 = brr >> 8;

	UCA0MCTL = brf << 4;
	UCA0MCTL |= brs << 1;

	// USCI reenabled
	UCA0CTL1 &= ~UCSWRST;
}

char RxTx_getchar () {
	while (!(IFG2 & UCA0RXIFG)) {
		// wait
	}

	return UCA0RXBUF;
}

void RxTx_putchar (char c) {
	while (!(IFG2 & UCA0TXIFG)) {
		// wait
	}

	UCA0TXBUF = c;
}

void RxTx_puts (char *str) {
	char *p = str;
	while (*p) {
		RxTx_putchar(*(p++));
	}
}

void RxTx_printf (char *format, ...) {
	// 80 chars tá bom
	char str[81];

	// Inicia os argumentos "variadicos"
	va_list args;
	va_start(args, format);
	// Printf redirecionado para str
	vsprintf(str, format, args);
	// Finaliza essa coisa
	va_end(args);

	// Manda para o uart
	RxTx_puts(str);
}