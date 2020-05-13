#include <stdlib.h>
#include <stdio.h>
#include "1923VK014.h"

// On Release, call the hardware reset procedure.
// On Debug we just enter an infinite loop, to be used as landmark when halting
// the debugger.
//
// It can be redefined in the application, if more functionality
// is required.

void exit(int code __attribute__((unused))) {
#if !defined(DEBUG)
  NVIC_SystemReset();
#endif

  printf("exited with code %d", code);
  while (1)
    continue;
}

void __attribute__((noreturn)) abort(void) {
  printf("abort(), exiting...");
  exit(1);
}
