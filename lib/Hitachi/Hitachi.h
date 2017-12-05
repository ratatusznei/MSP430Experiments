#include "msp430.h"
#include <stdarg.h> // for variadic functions

#ifdef HITACHI_USE_PORT2

#define LCD_BUS P2OUT
#define LCD_DIR P2DIR
#define LCD_SEL P2SEL
#define LCD_SEL2 P2SEL2

#else

#define LCD_BUS P1OUT
#define LCD_DIR P1DIR
#define LCD_SEL P1SEL
#define LCD_SEL2 P1SEL2

#endif // HITACHI_USE_PORT2

#define RS	BIT0
#define RW  BIT1
#define E	BIT2

#define DB4 BIT4
#define DB5 BIT5
#define DB6 BIT6
#define DB7 BIT7

typedef enum {
	CURSOR_NONE,
	CURSOR_BLINK,
} CursorMode_t;

#define SBI(data, bit) data |= bit;
#define CBI(data, bit) data &= ~bit;

#define LCD_CLOCK() do {\
	SBI(LCD_BUS, E);\
	CBI(LCD_BUS, E); \
} while(0)

void LCD_put4 (char data);

void LCD_cmd (char cmd);

#define LCD_putc(data) LCD_data(data)
#define LCD_putchar(data) LCD_data(data)
void LCD_data (char data);

#define LCD_puts(data) LCD_string(data)
void LCD_string (char *data);

void LCD_printf(const char *format, ...);

void LCD_goto(char x, char y);

void LCD_makeChar (char bitmap[8], char code);

void LCD_progressBar (char size, char filled);

void LCD_init (int doBlink);