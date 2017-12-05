#include "msp430.h"

#include <string.h>

#include "../../lib/Hitachi/Hitachi.h"

#define USE_PORT2
#include "../../lib/SambaTopKeys/SambaTopKeys.h"

#define PASS_LENGTH 10

typedef enum {
  SPLASH,
  LOGIN,
  PASS,
  AUTHORIZED,
  UNAUTHORIZED,
} States;

int main() {
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

        char passTable[][PASS_LENGTH] = {
          "1111",
          "91939",
          "666",
          "12345",
        };
        
        #define LOCKED 0
        char cadeadoFechado[8] = {
          0x0E,
          0x11,
          0x11,
          0x11,
          0x1F,
          0x1B,
          0x1B,
          0x1F,
        };
        
        #define UNLOCKED 1
        char cadeadoAberto[8] = {
          0x0E,
          0x11,
          0x10,
          0x10,
          0x1F,
          0x1B,
          0x1B,
          0x1F,
        };
        
	LCD_init(CURSOR_NONE);
        
        LCD_makeChar(cadeadoFechado, LOCKED);
        LCD_makeChar(cadeadoAberto, UNLOCKED);
        
        Samba_init();

        States state = SPLASH;
        
        char choice = 0;
        char user = -1;
        int i = 0;
        char pass[PASS_LENGTH] = "";
        
        while(1) {
          switch(state) {
          case SPLASH:
            LCD_goto(0, 0);
            LCD_puts("  BEM VINDO AO  ");
            LCD_goto(0, 1);
            LCD_putc(LOCKED);
            LCD_puts(" CADEADO-TRON ");
            LCD_putc(LOCKED);
            __delay_cycles(4000000);
            
            state = LOGIN;
            break;
            
          case LOGIN:
            LCD_goto(0, 0);
            LCD_puts("Digite o numero ");
            LCD_goto(0, 1);
            LCD_puts("de usuario     ");
            LCD_putc(LOCKED);
            
            do {
              choice = Samba_getc();
            } while (!(choice >= '1' && choice <= '4'));
            
            user = choice;
            state = PASS;
            break;
            
          case PASS:
            if (user == -1) {
              state = LOGIN;
              break;
            }
            
            LCD_goto(0, 0);
            LCD_puts("Digite a senha: ");
            LCD_goto(0, 1);
            LCD_puts("               ");
            LCD_putc(LOCKED);

            for (i = 0; i < PASS_LENGTH; i++) {
              pass[i] = '\0';
            }
            i = 0;
            do {
              if (choice == '\0') {
                choice = Samba_getc();
                
                if (choice == '\0') {
                  continue;
                }
                
                if (choice == 'E') {
                  break;
                }
                
                if (choice == 'C') {
                  LCD_goto(0, 1);
                  LCD_puts("               ");
                  i = 0;
                  strcpy(pass, "");
                  continue;
                }
              }
              else {
                choice = Samba_getc();
                continue;
              }
              
              LCD_goto(i, 1);
              LCD_putc('*');
              pass[i] = choice;
              i++;
            } while (i < PASS_LENGTH);
            
            if (strcmp(pass, passTable[user - '0' - 1]) == 0) {
              state = AUTHORIZED;
            }
            else {
              state = UNAUTHORIZED;
            }
                                       
            user = -1;
            break;
            
          case AUTHORIZED:
              LCD_goto(0, 0);
              LCD_puts("Acesso livre    ");
              LCD_goto(0, 1);
              LCD_puts("     :D        ");
              LCD_putc(UNLOCKED);
              
              __delay_cycles(3000000);
              
              state = LOGIN;
              break;
          
          case UNAUTHORIZED:
              LCD_goto(0, 0);
              LCD_puts("Acesso negado   ");
              LCD_goto(0, 1);
              LCD_puts("     >:(       ");
              LCD_putc(LOCKED);
              
              __delay_cycles(3000000);
              
              state = LOGIN;
              break;
              
          default:
              state = SPLASH;
          } // switch (state)
        } // while (1)
	return 0;
}