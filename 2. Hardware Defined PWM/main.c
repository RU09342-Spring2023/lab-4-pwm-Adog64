#include <msp430.h>
#include <stdbool.h>

#define COLOR_SPEED 2         // Speed to change color (1 slowest; 8 fastest)

char R_bright, G_bright, B_bright;
char R_decrementer, G_decrementer, B_decrementer;
char step;

void main (void)
{
  P6DIR |= 0x07;
  
  TB0CTL = TBSSEL__SMCLK, MC__UP, TBIE;
  TB0EX0 = 0x08 - COLOR_SPEED;
  
  TB0CCR0 = 0x0F;

  while (true) ;;
}


void __attribute__ ((interrupt(TIMER0_B1_VECTOR))) TIMER0_B1_ISR (void)
{
  if (step++ < 16)
  {
    if (!R_decrementer)
      P6OUT &= ~BIT0;
    if (!G_decrementer)
      P6OUT &= ~BIT1;
    if (!B_decrementer)
      P6OUT &= ~BIT2;
    
    R_decrementer--;
    G_decrementer--;
    B_decrementer--;
  }
  else
  {
    step = 0;
    R_decrementer = R_bright;
    G_decrementer = G_bright;
    B_decrementer = B_bright;

    P6OUT |= 0x07;
  }
}
