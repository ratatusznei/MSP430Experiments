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

## TODO
- O resto