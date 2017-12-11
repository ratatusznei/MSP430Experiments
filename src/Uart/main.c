#include "msp430.h"
#include "../../lib/RxTx/RxTx.h"

#define __interrupt_vec(vec) __attribute__((interrupt(vec)))

#define RED_LED BIT0
#define GREEN_LED BIT6
#define BTN BIT3

void init_PORT1 ();
void init_adc ();
int read_adc ();
int read_temperature ();

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

	RxTx_init(CALBRR_9600, CALBRF_9600, CALBRS_9600);
	init_adc();
	init_PORT1();

	_EINT();

	char choice = 0;
	while (1) {
		choice = RxTx_getc();

		switch (choice) {
		case 'V':
			P1OUT |= RED_LED;
			break;

		case 'v':
			P1OUT &= ~RED_LED;
			break;

		case 'C':
			P1OUT |= GREEN_LED;
			break;

		case 'c':
			P1OUT &= ~GREEN_LED;
			break;

		case 'T':
		case 't':
			RxTx_printf("Temperatura = %d graus C\n", read_temperature() / 1000);
			break;

		default:
			RxTx_puts("Comando invalido!\n");
		}
	}

	return 0;
}

void init_PORT1 () {
	// Leds verde e vermelho
	P1DIR = RED_LED | GREEN_LED;
	
	// Pull up no botão
	P1OUT = BTN;
	P1REN = BTN;

	// Interrupção no btn
	P1IE = BTN;
	P1IFG = 0;
}

void init_adc () {
  	// Canal 10
	ADC10CTL1 = INCH_10;
	// Configura referencia
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + ADC10ON + REFON;
	ADC10CTL0 |= ENC + ADC10SC;
}

int read_adc () {
  	int adc_data = 0;
  
	// Para o adc
	ADC10CTL0 &= ~ENC;
	while (ADC10CTL1 & BUSY) {
		// Espera se ocupado
	}
	adc_data = ADC10MEM;
	// Reinicia a conversão
	ADC10CTL0 |= ENC + ADC10SC;
	
	return adc_data;
}

int read_temperature () {
	int raw_adc = read_adc();

	return (raw_adc - CAL_ADC_15T30) * ((85 - 30) / (CAL_ADC_15T85 - CAL_ADC_15T30)) + 30;
}

void __interrupt_vec(PORT1_VECTOR) alert () {
	RxTx_puts("ALERTA!\n");
	P1IFG = 0;
}