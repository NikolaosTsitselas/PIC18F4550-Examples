#include <18F4550.h>

#use delay(clock=48000000)

#include "keypad_sim.h"
#include "flex_lcd_sim.h"

// ------------------------------------------------
// Περιμένει μέχρι να πατηθεί πλήκτρο
// ------------------------------------------------
char wait_key(void)
{
   char k;
   do {
      k = kbd_getc();
   } while(k == 0);
   return k;
}

// ------------------------------------------------
void main(void)
{
   char key;
   int8 menu = 0;
   int8 a, b;
   float result;

   kbd_init();
   lcd_init();

   lcd_putc("\fCalculator");
   lcd_gotoxy(1,2);
   lcd_putc("8=Up 2=Down");
   delay_ms(1000);

   while(TRUE)
   {
      // -------- Εμφάνιση menu --------
      lcd_putc("\f");
      lcd_gotoxy(1,1);

      switch(menu)
      {
         case 0: lcd_putc("1.Addition");   break;
         case 1: lcd_putc("2.Subtract");   break;
         case 2: lcd_putc("3.Multiply");   break;
         case 3: lcd_putc("4.Divide");     break;
      }

      

      key = wait_key();

      // -------- Πάνω --------
      if(key == '8')
      {
         if(menu == 0) menu = 3;
         else menu--;
      }

      // -------- Κάτω --------
      else if(key == '2')
      {
         if(menu == 3) menu = 0;
         else menu++;
      }

      // -------- Επιλογή --------
      else if(key == '=')
      {
         // ---- Πρώτο ψηφίο ----
         lcd_putc("\fFirst digit:");
         a = wait_key() - '0'; //to kanei se ascii morfi alla mporeis
                               // na peis kai k&0b00001111

         lcd_gotoxy(1,2);
         printf(lcd_putc,"You: %d", a);
         delay_ms(500);

         // ---- Δεύτερο ψηφίο ----
         lcd_putc("\fSecond digit:");
         b = wait_key() - '0';

         lcd_gotoxy(1,2);
         printf(lcd_putc,"You: %d", b);
         delay_ms(500);

         // ---- Υπολογισμός ----
         switch(menu)
         {
            case 0: result = a + b; break;
            case 1: 
            if(b>a){
               result= (a-b)*(-1);
            }
            else
               result = a - b; break;
            case 2: result = a * b; break;
            case 3:
               if(b == 0) result = 0;
               else result = (float)a / b;
               break;
         }

         // ---- Αποτέλεσμα ----
         lcd_putc("\fResult:");
         lcd_gotoxy(1,2);

         switch(menu)
         {
            case 0: printf(lcd_putc,"%d+%d=%.1f",a,b,result); break;
            case 1: printf(lcd_putc,"%d-%d= - %.1f",a,b,result); break;
            case 2: printf(lcd_putc,"%d*%d=%.1f",a,b,result); break;
            case 3:
               if(b == 0) lcd_putc("Error div 0");
               else printf(lcd_putc,"%d/%d=%.2f",a,b,result);
               break;
         }

         delay_ms(1500);
      }
   }
}

