#include "msp430.h"

void init_SPI () {
    P1SEL = BIT1 | BIT2 | BIT4;
    P1SEL2 = BIT1 | BIT2 | BIT4;

    UCA0CTL1 = UCSWRST;
    UCA0CTL0 |= UCCKPH | UCMSB | UCMST | UCSYNC;
    UCA0CTL1 |= UCSSEL_2;
	
    UCA0CTL1 &= ~UCSWRST;
}

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

	P1DIR |= BIT0;
	P1OUT &= ~BIT0;		

	char received_ch = 0;
	char i = 1;

	init_SPI();
	
	for (i = 1;;i <<= 1) {
		if (i == 0) {
			i = 1;
		}

		while (!(IFG2 & UCA0TXIFG));
		UCA0TXBUF = i;

		while (!(IFG2 & UCA0RXIFG));
		received_ch = UCA0RXBUF;

		if (received_ch & BIT0) {
			P1OUT |= BIT0;
		}
		else {
			P1OUT &= ~BIT0;
		}

		__delay_cycles(50000);
	}

	return 0;
}
