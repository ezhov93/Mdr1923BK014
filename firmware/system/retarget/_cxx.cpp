// ----------------------------------------------------------------------------
// These functions are redefined locally, to avoid references to some
// heavy implementations in the standard C++ library.
// ----------------------------------------------------------------------------
#include <cstdlib>
#include <sys/types.h>
#include <stdio.h>

namespace __gnu_cxx {
void
__attribute__((noreturn))
__verbose_terminate_handler();

void __verbose_terminate_handler() {
  printf(__func__);
  abort();
}
}

extern "C" {
void
__attribute__((noreturn))
__cxa_pure_virtual();

void __cxa_pure_virtual() {
  printf(__func__);
  abort();
}
}

