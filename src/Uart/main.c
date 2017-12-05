#include "msp430.h"
#include "../../lib/RxTx/RxTx.h"

#define Uart_isBusy() (UCA0STAT & UCBUSY)

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

	RxTx_init(CALBRR_9600, CALBRF_9600, CALBRS_9600);

	RxTx_puts("MSP430 ready!  :D\n\n");

	while (1) {
		RxTx_puts("ASDA\n");
		__delay_cycles(1000000);
	}
	return 0;
}
