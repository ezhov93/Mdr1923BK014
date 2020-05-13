#ifndef SYSTEM_1923VK014_H
#define SYSTEM_1923VK014_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SystemCoreClock;          // System Clock Frequency (Core Clock)

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_1923VK014_H

