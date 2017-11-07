#include <msp430.h>

#define __interrupt_vec(vec) __attribute__((interrupt(vec)))

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW | WDTHOLD;

	// Timer com o clock externo, com interrupção, modo continuo
	TA0CTL = TASSEL_1 | TAIE | MC_1;
	TACCR0 = 0xF0;

	P1DIR = BIT6 | BIT0;
	P1OUT = BIT0;

	_EINT();

	for (;;);
	return 0;
}


void __interrupt_vec(TIMER0_A1_VECTOR) fixedUpdate () {
	P1OUT ^= BIT6 | BIT0;
	TA0CTL &= ~TAIFG;
	return;
}