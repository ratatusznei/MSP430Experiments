#include <msp430.h>

#define __interrupt_vec(vec) __attribute__((interrupt(vec)))

#define PERIOD 0x0100
#define PWM(x) PERIOD * (x / 100.0)

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW | WDTHOLD;

	// Timmer 0 com clock interno, divisao de clock por 1 e modo up
	TA0CTL = TASSEL_2 | ID_0 | MC_1;

	// Contagem maxima do clock em 100% do pwm
	TA0CCR0 = PERIOD;

	// Inicio da contagem em zero, modo reset/set
	TA0CCR1 = PWM(0);
	TA0CCTL1 = OUTMOD_7;

	// P1.6 ligado na saida do TA0.1 do timer 0
	P1DIR = BIT6;
	P1SEL = BIT6;

	int i;
	for (i = 0;; i++){
		TA0CCR1 = i % PERIOD;
		__delay_cycles(10000);
	}
	return 0;
}