#include "main.h"

extern long int duty , period;
void __interrupt() isr(void)
{
    static unsigned int count = 0;
    
    if (TMR0IF == 1)
    {
        /* TMR0 Register valur + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 8;
        
        if (++count <= duty)
        {
        RB3 = 1;
        }
        else if(count <= period)
        {
            RB3= 0;
        }
        if(count == period)
            count = 0;
        
        TMR0IF = 0;
    }
}
