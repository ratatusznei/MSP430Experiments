# Documentação - Hitachi

## Montagem física
Por padrão é utilizado o PORT1, porém é possível configurar o PORT2 também. As ligações seguem a tabela:

| Pino do MSP | Pino do LCD |
|:-----------:|:-----------:|
|Px.0         |RS           |
|Px.1         |R/W          |
|Px.2         |E            |
|Px.3         |Nenhum       |
|Px.4         |DB4          |
|Px.5         |DB5          |
|Px.6         |DB6          |
|Px.7         |DB7          |


Para utilizar o PORT2 basta definir a constante HITACHI_USE_PORT2 antes de incluir o arquivo .h no projeto, conforme o exemplo:

```c
#include "msp430.h"

#define HITACHI_USE_PORT2
#include "your_path/Hitachi.h"

int main () {
	[...]
}
```

## LCD_init (int doBlink)

Configura o port selecionado e inicializa o lcd no modo de 4 bits, com 2 linhas, com o estilo do cursor seguin a doBlink e auto incremento de cursor.

O parâmetro doBlink pode ser CURSOR_NONE, sem cursor, ou CURSOR_BLINK, o cursor piscando.

Exemplo:

```c
#include "msp430.h"

// Configura no PORT1
#include "your_path/Hitachi.h"

int main () {
	// Inicia o display com o cursor piscando
	LCD_init(CURSOR_BLINK);
	[...]
}
```

## LCD_cmd (char cmd)

Envia o código de um comando no barramento do LCD. Ver datasheet do controlador de display Hitachi HD44780U para códigos.

## LCD_putc (char data), LCD_puts (char *data), LCD_printf(const char *format, ...)

Funções para imprimir dados no display, a partir da posição atual do cursor. Funcionam de forma semelhante as suas equivalentes da biblioteca padrão.

## LCD_goto (char x, char y)

Move o cursor para a posição (x, y) do display. O canto superior esquerdo possui a posição (0, 0), com x incrementando para a direita e y incrementando para baixo

### Exemplo de mapeamento:

|       |       |       |       |       |
|-------|-------|-------|-------|-------|
| (0,0) | (1,0) | (2,0) |  ...  |(15, 0)|
| (0,1) | (1,1) | (2,1) |  ...  |(15, 1)|

## void LCD_progressBar (char size, char filled)

Imprimi no display uma barra de progresso. O tamanho da barra em caracteres é dado pelo argumento size. O quanto da barra está preenchido é proporcional ao argumento filled, sendo 0% = 0x00 e 100% = 0xFF.

## void LCD_makeChar (char bitmap[8], char code)

Cria um novo caractere para ser utilizado no display. Os caracteres aceitos possuem o formato 5x8 e os bytes individuais são alinhados à direita, ou seja, em um byte 1100 0011, os 3 primeiros caracteres (110) são ignorados.


```c
#include "msp430.h"

// Configura no PORT1
#include "your_path/Hitachi.h"

int main () {
	[...]
	
	#define CODE_CADEADO 0
        char bitmap_cadeado[8] = {
		0x0E, /* _ 1 1 1 _ */
		0x11, /* 1 _ _ _ 1 */
		0x11, /* 1 _ _ _ 1 */
		0x11, /* 1 _ _ _ 1 */
		0x1F, /* 1 1 1 1 1 */
		0x1B, /* 1 1 _ 1 1 */
		0x1B, /* 1 1 _ 1 1 */
		0x1F, /* 1 1 1 1 1 */
	};

	// Define o código e bitmap do cadeado
	LDC_makeChar(bitmap_cadeado, CODE_CADEADO);
	
	// Imprime o cadeado na posição do cursor
	LCD_putc(CODE_CADEADO);
	
	[...]
}
```
