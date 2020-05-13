#ifndef SYSTEM_1923VK014_H
#define SYSTEM_1923VK014_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// < System Clock Frequency (Core Clock)
extern uint32_t SystemCoreClock;

// Initialize the System and update the SystemCoreClock variable.
extern void SystemInit(void);

// Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_1923VK014_H */
