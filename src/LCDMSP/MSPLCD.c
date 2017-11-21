#include "msp430.h"

#include <stdlib.h> // for rand
#include "../../lib/Hitachi/Hitachi.h"

void ConfigureAdc () {
	ADC10CTL1 = INCH_3;
	ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON;
	ADC10AE0 |= BIT3;

	P1SEL |= BIT3;
}

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

	LCD_init(CURSOR_NONE);

	ConfigureAdc ();

	char i = 0;
	char adc_data = 0;

	while (1) {
		ADC10CTL0 &= ~ENC;				// Disable Conversion
    	while (ADC10CTL1 & BUSY);		// Wait if ADC10 busy
    	adc_data = ADC10MEM / 4;
  		ADC10CTL0 |= ENC + ADC10SC;		// Enable Conversion and conversion start

  		LCD_goto(0, 0);
		LCD_progressBar(16, adc_data);
		LCD_goto(0, 1);
		LCD_progressBar(6, adc_data);
		LCD_goto(6, 1);
		LCD_progressBar(10, adc_data);
	}

	return 0;
}
