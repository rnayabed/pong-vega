#include "timer.h"

void TIMER_setup_delay(unsigned char timer, unsigned long clocks)
{
    TIMER(timer).control = 0x0;             // Disable timer.
    TIMER(timer).load_count = clocks / 2;   // Load timer with no of clocks.
    TIMER(timer).control = 0x7;             // Enable timer with intr masked (0111)

    __asm__ __volatile__ ("fence");

    while(!TIMER_INTR_FLAG(timer));         // Wait till timer interrupts.
    TIMER(timer).control = 0x0;             // Disable timer.

    __asm__ __volatile__ ("fence");
}
