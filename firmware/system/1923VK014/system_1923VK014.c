#include <stdint.h>
#include "1923VK014.h"

#define __HSI             ( 6000000UL)
#define __XTAL            (12000000UL)    /* Oscillator frequency             */
#define __SYS_OSC_CLK     (    ___HSI)    /* Main oscillator frequency        */

#define __SYSTEM_CLOCK    (8000000UL)

uint32_t SystemCoreClock = __SYSTEM_CLOCK; /*!< System Clock Frequency (Core Clock)*/

void SystemCoreClockUpdate(void) /* Get Core Clock Frequency      */
{
  int pll = (CLK_CNTR->PLL0_CLK & (0x3F << 8)) >> 8;
  SystemCoreClock = __SYSTEM_CLOCK*pll;
}

void SystemInit(void) {
  SystemCoreClock = __SYSTEM_CLOCK;
}
