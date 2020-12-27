#ifndef _delay_h_
#define _delay_h_

#include "msp430.h"

#define CPU_F ((double)25000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#endif