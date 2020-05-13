#ifndef EXCEPTION_HANDLERS_H
#define EXCEPTION_HANDLERS_H

#include <stdint.h>

#if defined(DEBUG)
#define __DEBUG_BKPT()  asm volatile ("bkpt 0")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

// External references to cortexm_handlers.c

extern void Reset_Handler(void);
extern void NMI_Handler(void);
extern void HardFault_Handler(void);

extern void SVC_Handler(void);

extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

// Exception Stack Frame of the Cortex-M3 or Cortex-M4 processor.
typedef struct {
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r12;
  uint32_t lr;
  uint32_t pc;
  uint32_t psr;
} ExceptionStackFrame;

#if defined(TRACE)
void dumpExceptionStack(ExceptionStackFrame *frame, uint32_t lr);
#endif // defined(TRACE)

void HardFault_Handler_C(ExceptionStackFrame *frame, uint32_t lr);

#if defined(__cplusplus)
}
#endif

#endif // EXCEPTION_HANDLERS_H
