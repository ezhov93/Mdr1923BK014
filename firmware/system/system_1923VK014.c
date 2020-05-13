#include "1923VK014.h"

uint32_t SystemCoreClock = (uint32_t) 8000000; //  System Clock Frequency (Core Clock)

void SystemCoreClockUpdate(void) {
//  SystemCoreClock = SystemCoreClock;

}

void SystemInit(void) {
  retarget_init();
  SystemCoreClockUpdate();
}
