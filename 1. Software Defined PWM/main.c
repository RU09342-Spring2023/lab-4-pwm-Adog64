#include <msp430.h>
#include <stdbool.h>

#include "embedded_utils.h"

int main(void)
{
    killWatchdogTimer();
    unlockGPIO();
    initGPIO();

    TB0CCR0 = 12000;
    TB0CTL |= TBSSEL_2 | MC_1 | TBCLR | TBIE;
    while(1);
}

void initGPIO()
{
    setAsInput(2,1);        // button at P2.1
    setAsInput(4,3);        // button at P4.3

    setAsOutput(1,0);       // Red LED at P1.0
    setAsOutput(6,6);       // Green LED at P6.6

    clearPinValue(6,6);
    clearPinValue(1,0);
}

// void tb0SignalLow()
// {
//     // clearPinValue(1,0);
// }

// void tb0SignalHigh()
// {
//     setPinValue(1,0);
// }

void __attribute__ ((interrupt(TIMER0_B1_VECTOR))) TIMER0_B1_ISR (void)
{
    switch(__even_in_range(TB0IV,TB0IV_TBIFG))
    {
        case TB0IV_NONE:
            break;                               // No interrupt
        case TB0IV_TBCCR1:
            clearPinValue(1,0);
            break;                               // CCR1 Set the pin to a 0
        case TB0IV_TBCCR2:
            break;                               // CCR2 not used
        case TB0IV_TBIFG:
            setPinValue(1,0);
            break;
        default:
            break;
    }
}