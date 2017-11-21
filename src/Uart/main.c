#include "msp430.h"
#include <stdarg.h> // for variadic functions
#include "../../lib/SambaTopKeys/SambaTopKeys.h"

#define Uart_isBusy() (UCA0STAT & UCBUSY)

/* 
	Initializes the uart:
		- 8 data bits
		- No parity
		- 1 stop bit
		- baud = baud
		- LSB first

	It also changes the DCO frequency to 1 MHz
*/
void Uart_init(int brr, int brf, int brs) {
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

char Uart_getchar () {
	while (!(IFG2 & UCA0RXIFG)) {
		// wait
	}

	return UCA0RXBUF;
}

void Uart_putchar (char c) {
	while (!(IFG2 & UCA0TXIFG)) {
		// wait
	}

	UCA0TXBUF = c;
}

void Uart_puts (char *str) {
	char *p = str;
	while (*p) {
		Uart_putchar(*(p++));
	}
}

void Uart_printf (char *format, ...) {
	// 80 chars tá bom
	char str[81];

	// Inicia os argumentos "variadicos"
	va_list args;
	va_start(args, format);
	// Printf redirecionado para str
	vsprintf(str, format, args);
	// Finaliza essa coisa
	va_end(args);

	// Manda para o Uart
	Uart_puts(str);
}

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

	Samba_init();
	Uart_init(104, 1, 0);

	Uart_puts("MSP430 ready!  :D\n\n");

	char new = '\0';
	char old = '\0';

	for(;;) {
		new = Samba_getc();

		if (new == old) {
			new = '\0';
		}
		else {
			old = new;
		}

		if (new) {
			Uart_printf("Samba pressed key: %c \n", new);
		}
	}
	return 0;
}
