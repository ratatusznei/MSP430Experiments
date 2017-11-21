#include "msp430.h"
#include "../../lib/SambaTopKeys/SambaTopKeys.h"
#include "../../lib/RxTx/RxTx.h"

#define Uart_isBusy() (UCA0STAT & UCBUSY)

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

	Samba_init();
	RxTx_init(104, 1, 0);

	RxTx_puts("MSP430 ready!  :D\n\n");

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
			RxTx_printf("Samba pressed key: %c \n", new);
		}
	}
	return 0;
}
