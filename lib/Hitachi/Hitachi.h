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

//Envia 4 bits para o bus de dados do display, é a função de nível mais baixo
void LCD_put4 (char data);

// Envia um comando de 8 bits, atraves de dois de 4 bits
void LCD_cmd (char cmd);

// Envia um char de dados
#define LCD_putc(data) LCD_data(data)
#define LCD_putchar(data) LCD_data(data)
void LCD_data (char data);

// Envia uma string
#define LCD_puts(data) LCD_string(data)
void LCD_string (char *data);

// Funcao equivalente a printf
void LCD_printf(const char *format, ...);

// Move o cursor para uma posição no display
/*
	x ->
y	+----------------+
|	|00...         F0|
V	|01...         F1|
	+----------------+
*/
void LCD_goto(char x, char y);

// Cria um caracter com base no bitmap 5x8
// Ele é imprimido na tela chamando a função LCD_data(code)
void LCD_makeChar (char bitmap[8], char code);

// Desenha uma barra de progresso na posição do cursor, 0x00 <= filled <= 0xFF
// Ex: [------      ]
void LCD_progressBar (char size, char filled);

// Configura os pinos e inicializa o display
void LCD_init (int doBlink);