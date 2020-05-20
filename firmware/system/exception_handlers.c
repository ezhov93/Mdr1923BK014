#include "system/exception_handlers.h"

#include <stdio.h>
#include <string.h>

#include "system/cmsis_device.h"

extern void __attribute__((noreturn, weak)) _start(void);

// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.

extern unsigned int _estackprocess;
extern unsigned int _estack;

#if defined(DEBUG)

// The DEBUG version is not naked, but has a proper stack frame,
// to allow setting breakpoints at Reset_Handler.
void __attribute__((section(".after_vectors"), noreturn)) Reset_Handler(void) {
  asm volatile(
      "LDR      R0, =_estack \n"
      "MSR      PSP, R0 \n"
      "LDR      R0, =_estackprocess \n"
      "MSR      MSP, R0 \n"
      "MOVS     R0, #2 \n"
      "MSR      CONTROL, R0 \n");
  _start();
}

#else

// The Release version is optimised to a quick branch to _start.
void __attribute__((section(".after_vectors"), naked)) Reset_Handler(void) {
  asm volatile(
      " ldr     r0,=_start \n"
      " bx      r0"
      :
      :
      :);
}

#endif

void __attribute__((section(".after_vectors"), weak)) NMI_Handler(void) {
#if defined(DEBUG)
  __DEBUG_BKPT();
#endif
  while (1) {
  }
}

// ----------------------------------------------------------------------------

#if defined(TRACE)
void dumpExceptionStack(ExceptionStackFrame *frame, uint32_t lr) {
  fprintf(stderr, "Stack frame:\n");
  fprintf(stderr, " R0 =  %08X\n", frame->r0);
  fprintf(stderr, " R1 =  %08X\n", frame->r1);
  fprintf(stderr, " R2 =  %08X\n", frame->r2);
  fprintf(stderr, " R3 =  %08X\n", frame->r3);
  fprintf(stderr, " R12 = %08X\n", frame->r12);
  fprintf(stderr, " LR =  %08X\n", frame->lr);
  fprintf(stderr, " PC =  %08X\n", frame->pc);
  fprintf(stderr, " PSR = %08X\n", frame->psr);
  fprintf(stderr, "Misc\n");
  fprintf(stderr, " LR/EXC_RETURN= %08X\n", lr);
}
#endif  // defined(TRACE)

// Hard Fault handler wrapper in assembly.
// It extracts the location of stack frame and passes it to handler
// in C as a pointer. We also pass the LR value as second
// parameter.
// (Based on Joseph Yiu's, The Definitive Guide to ARM Cortex-M0
// First Edition, Chap. 12.8, page 402).
#ifndef GDB
void __attribute__((section(".after_vectors"), weak, naked))
HardFault_Handler(void) {
  asm volatile(
      " movs r0,#4      \n"
      " mov r1,lr       \n"
      " tst r0,r1       \n"
      " beq 1f          \n"
      " mrs r0,psp      \n"
      " b   2f          \n"
      "1:               \n"
      " mrs r0,msp      \n"
      "2:"
      " mov r1,lr       \n"
      " ldr r2,=HardFault_Handler_C \n"
      " bx r2"

      : /* Outputs */
      : /* Inputs */
      : /* Clobbers */
  );
}

#endif

void __attribute__((section(".after_vectors"), weak, used))
HardFault_Handler_C(ExceptionStackFrame *frame __attribute__((unused)),
                    uint32_t lr __attribute__((unused))) {
  // There is no semihosting support for Cortex-M0, since on ARMv6-M
  // faults are fatal and it is not possible to return from the handler.
#if defined(TRACE)
  fprintf(stderr, "[HardFault]\n");
  dumpExceptionStack(frame, lr);

#endif  // defined(TRACE)

#if defined(DEBUG)
  __DEBUG_BKPT();
#endif
  while (1) {
  }
}

void __attribute__((section(".after_vectors"), weak)) SVC_Handler(void) {
#if defined(DEBUG)
  __DEBUG_BKPT();
#endif
  while (1) {
  }
}

void __attribute__((section(".after_vectors"), weak)) PendSV_Handler(void) {
#if defined(DEBUG)
  __DEBUG_BKPT();
#endif
  while (1) {
  }
}

void __attribute__((section(".after_vectors"), weak)) SysTick_Handler(void) {
  // DO NOT loop, just return.
  // Useful in case someone (like STM HAL) inadvertently enables SysTick.
  ;
}
