#include <18F4550.h>
#fuses HSPLL,PLL5,CPUDIV1,NOWDT,NOLVP,NOPROTECT
#use delay(clock=48000000)

#include "keypad_sim.h"
#include "flex_lcd_sim.h"

const char operations[4][16] =
{
   "1.Addition",
   "2.Subtract",
   "3.Multiply",
   "4.Divide"
};

int8 menu = 0;

char msg_first[]  = "First digit:";
char msg_second[] = "Second digit:";

// ----------------------
// Edge-detect version!
// ----------------------
char get_key()
{
   static char last = 0;   // τελευταίο key
   char k = kbd_getc();    // τρέχουσα τιμή

   if(k != 0 && last == 0)
   {
      last = k;            // new press
      return k;
   }

   if(k == 0)
      last = 0;            // release

   return 0;               // ignore hold
}

// ---------------------------------------------------------
int8 get_digit(char *msg)
{
   char key;

   lcd_putc("\f");
   lcd_gotoxy(1,1);
   printf(lcd_putc, msg);
   lcd_gotoxy(1,2);
   lcd_putc("Press 0-9");

   while(TRUE)
   {
      key = get_key();   // ? χρήση edge-detect

      if(key >= '0' && key <= '9')
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, msg);
         lcd_gotoxy(1,2);
         printf(lcd_putc,"You: %c", key);

         delay_ms(200);
         return (key - '0');
      }
   }
}

// ---------------------------------------------------------
void show_menu()
{
   lcd_putc("\fSelect Op:");
   lcd_gotoxy(1,2);
   lcd_putc(operations[menu]);
}

// ---------------------------------------------------------
void main()
{
   kbd_init();
   lcd_init();

   lcd_putc("\fCalculator");
   lcd_gotoxy(1,2);
   lcd_putc("Ready...");
   delay_ms(300);

   show_menu();

   while(TRUE)
   {
      char key = get_key();  // ? edge-detect

      if(key == 0)
         continue;

      // -------- Πάνω (8) --------
      if(key == '8')
      {
         if(menu == 0) menu = 3;
         else menu--;
         show_menu();
      }

      // -------- Κάτω (2) --------
      else if(key == '2')
      {
         if(menu == 3) menu = 0;
         else menu++;
         show_menu();
      }

      // -------- Επιλογή (=) --------
      else if(key == '=')
      {
         int8 a, b;
         float result = 0;

         a = get_digit(msg_first);
         b = get_digit(msg_second);

         switch(menu)
         {
            case 0: result = a + b; break;
            case 1: result = a - b; break;
            case 2: result = a * b; break;
            case 3:
               if(b == 0) result = 0;
               else result = (float)a / b;
               break;
         }

         lcd_putc("\fResult:");
         lcd_gotoxy(1,2);

         switch(menu)
         {
            case 0: printf(lcd_putc,"%d+%d=%.1f",a,b,result); break;
            case 1: printf(lcd_putc,"%d-%d=%.1f",a,b,result); break;
            case 2: printf(lcd_putc,"%d*%d=%.1f",a,b,result); break;
            case 3:
               if(b == 0) lcd_putc("Error div 0");
               else printf(lcd_putc,"%d/%d=%.2f",a,b,result);
               break;
         }

         delay_ms(1200);
         show_menu();
      }
   }
}

