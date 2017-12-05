#include "Hitachi.h"

//Envia 4 bits para o bus de dados do display, é a função de nível mais baixo
void LCD_put4 (char data) {
  	__delay_cycles(110);
	
  	// Limpa os DBx
	CBI(LCD_BUS, ~(RS | RW | E));
	
	if (data & 0x01) {
		SBI(LCD_BUS, DB4);	
	}
	
	if (data & 0x02) {
		SBI(LCD_BUS, DB5);
	}
	
	if (data & 0x04) {
		SBI(LCD_BUS, DB6);
	}
	
	if (data & 0x08) {
		SBI(LCD_BUS, DB7);
	}
	
	LCD_CLOCK();
}

// Envia um comando de 8 bits, atraves de dois de 4 bits
void LCD_cmd (char cmd) {
	CBI(LCD_BUS, RS);
  
  	LCD_put4(cmd >> 4);
	LCD_put4(cmd);
}

// Envia um char de dados
#define LCD_putc(data) LCD_data(data)
#define LCD_putchar(data) LCD_data(data)
void LCD_data (char data) {
	SBI(LCD_BUS, RS);
  
  	LCD_put4(data >> 4);
	LCD_put4(data);
}

// Envia uma string
#define LCD_puts(data) LCD_string(data)
void LCD_string (char *data) {
	while (*data) {
		LCD_data(*(data++));
	}
}

// Funcao equivalente a printf
// Obs.: O que acontece aqui fica aqui
void LCD_printf(const char *format, ...) {
	// Maximo de 80 chars no display controlado pelo hitachi
	char str[81];

	// Inicia os argumentos "variadicos"
	va_list args;
	va_start(args, format);
	// Printf redirecionado para str
	vsprintf(str, format, args);
	// Finaliza essa coisa
	va_end(args);

	// Manda para o display
	LCD_puts(str);
}


// Move o cursor para uma posição no display
/*
	x ->
y	+----------------+
|	|00...         F0|
V	|01...         F1|
	+----------------+
*/
void LCD_goto(char x, char y) {
	char cmd = 0x80;
	
	cmd += x;
	cmd += y * 0x40;
  
	LCD_cmd(cmd);
}

void LCD_makeChar (char bitmap[8], char code) {
	int i = 0;

	// Set cgram address
	CBI(LCD_BUS, ~(RS | RW));
	LCD_cmd(0x40 | (code * 8));

	for (i = 0; i < 8; i++) {
		LCD_data(bitmap[i]);
	}
}

// Displays a progress bar in the cursor position, 0x00 <= filled <= 0xFF
// Ex: [------      ]
void LCD_progressBar (char size, char filled) {
	LCD_putc('[');
	char i = 0;

	// Percentage of 1 char in display
	float step = (float) (0xFF) / (size - 2);

	// Number of char to be printed
	// Round it
	char charCount = (char) ((filled / step) + 0.5);

	for (i = 0; i < charCount; i++) {
		// 0xFF is a full block char
		LCD_putc(0xFF);
	}

	for (i = 0; i < (size - charCount - 1 - 1); i++) {
		LCD_putc('-');
	}

	LCD_putc(']');
}

// Inicializa o display
void LCD_init (int doBlink) { 
	// 15 ms
	__delay_cycles(15000);
	
	LCD_DIR = 0xFF;
	LCD_BUS = 0x00;
	LCD_SEL = 0x00;
	LCD_SEL2 = 0x00;
	
	// UM TRES
	LCD_put4(0x3);
	// 4.1 ms min
	__delay_cycles(42000);
	
	// DOIS TRES
	LCD_put4(0x3);
	// 100 us min
	__delay_cycles(42000);
	
	// TRES TRES
	LCD_put4(0x3);
	// 100 us min
	__delay_cycles(110);
	
	/*
		Inicio das instruçoes de 4 bits
	*/
	
	// Ativa o modo de 4 bits
	LCD_put4(0x2);
	
	// 2 linhas
	LCD_cmd(0x28);
	
	// Cursor
	if (doBlink) {
		LCD_cmd(0x0F);
	}
	else {
		LCD_cmd(0x0C);
	}
	
	// Clear
	LCD_cmd(0x01);
	__delay_cycles(5000);
	
	// Auto incremento do cursor
	LCD_cmd(0x16);
	
	// Return home
	LCD_cmd(0x02);
}