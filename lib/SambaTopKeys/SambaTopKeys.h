#include "msp430.h"

#ifdef SAMBA_USE_PORT2

#define MatrixDIR P2DIR
#define MatrixOUT P2OUT
#define MatrixIN P2IN
#define MatrixREN P2REN
#define MatrixIE P2IE
#define MatrixIES P2IES
#define MatrixIFG P2IFG
#define MatrixSEL P2SEL
#define MatrixSEL2 P2SEL2

#else

#define MatrixDIR P1DIR
#define MatrixOUT P1OUT
#define MatrixIN P1IN
#define MatrixREN P1REN
#define MatrixIE P1IE
#define MatrixIES P1IES
#define MatrixIFG P1IFG
#define MatrixSEL P1SEL
#define MatrixSEL2 P1SEL2

#endif // SAMBA_USE_PORT2

#define DEBOUNCE_DELAY 64

enum MatrixPins {
	Keys1470 = BIT0,
	Keys258E = BIT1,
	Keys369C = BIT2,

	Keys123 = BIT3,
	Keys456 = BIT4,
	Keys789 = BIT5,
	Keys0EC = BIT6,
};

#define WRITE_KEYS (Keys1470 | Keys258E | Keys369C)
#define READ_KEYS (Keys123 | Keys456 | Keys789 | Keys0EC)

#define setBits(REG, B) (REG |= (B))
#define clearBits(REG, B) (REG &= ~(B))

#define isHIGH(X) (MatrixIN & X)
#define isLOW(X) (!isHIGH(X))

// Initialize the pins
void Samba_init ();

// Scan for que pressed collumn
char Samba_getPressedCollumn (char rowPin);

// Debounce a going to Low input
char Samba_debounceLOW (char pin);

// Reads a char from the key pad
#define Samba_getc() Samba_getchar()
char Samba_getchar ();