#include "msp430.h"

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

	P1DIR = BIT0;

	for(;;) {
		P1OUT ^= BIT0;
		__delay_cycles(500000);
	}
	return 0;
}
