#include "msp430.h"
#include "../../lib/SambaTopKeys/SambaTopKeys.h"

#define __interrupt_vec(vec) __attribute__((interrupt(vec)))

int main () {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

	Samba_init();

	P1DIR = BIT0;
	P1OUT = 0;

	_EINT();

	for(;;);
	return 0;
}

void blink (char n) {
	while (n--) {
		P1OUT |= BIT0;
		__delay_cycles(100000);
		P1OUT &= ~BIT0;
		__delay_cycles(100000);
	}
}

void __interrupt_vec(PORT2_VECTOR) MatrixInterrupt () {
	char smb = Samba_getc();

	if (smb >= '1' && smb <= '9') {
		blink(smb - '0');
	}
	else if (smb == 'C') {
		P1OUT &= ~BIT0;
	}
	else if (smb == 'E') {
		P1OUT |= BIT0;
	}
	else if (smb == '0') {
		P1OUT ^= BIT0;
	}

	MatrixIFG = 0;
	return;
}