/******************************************************************************/
/* Controle de servo motor                                          08/11/2017*/
/* Fernando Henrique Ratusznei Caetano, Vinicios Pereira Possagno             */
/******************************************************************************/

#include "msp430.h"

void ConfigureAdc () {
  	// Canal 3
	ADC10CTL1 = INCH_3;
	// Configura referencia
	ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON;
	// Pino p1.3
	ADC10AE0 |= BIT3;

	// Pino p1.3 como entrada do adc
	P1SEL |= BIT3;
}

char ReadAdc () {
  	char adc_data = 0;
  
	// Para o adc
	ADC10CTL0 &= ~ENC;
	while (ADC10CTL1 & BUSY) {
		// Espera se ocupado
	}
	adc_data = ADC10MEM / 4;
	// Reinicia a conversão
	ADC10CTL0 |= ENC + ADC10SC;
	
	return adc_data;
}

void ConfigureServo () {
  	// Modo up
	TA0CTL = TASSEL_2 | MC_1;
	
	// Periodo de 20 ms
	TA0CCR0 = 22000;
	
	// Duty cycle 1ms
	TA0CCR1 = 1100;
	TA0CCTL1 = OUTMOD_7;
	
	// P1.2 saída do timer
	P1DIR = BIT2;
	P1SEL = BIT2;
}

void SetServo (char duty) {
  	// Map do duty cycle entre 1 ms e 2ms
	TA0CCR1 = (int)(duty * (2200.0 - 1100.0)) + 1100;
}

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;
	
	ConfigureAdc();
	ConfigureServo();
	
	while(1) {
		SetServo(ReadAdc());
	}

	return 0;
}

