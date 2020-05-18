#include <stdio.h>
#include <sys/types.h>

#include <cstdlib>

namespace __gnu_cxx {
void __attribute__((noreturn)) __verbose_terminate_handler();

void __verbose_terminate_handler() {
  fprintf(stderr, __func__);
  abort();
}
}  // namespace __gnu_cxx

extern "C" {
void __attribute__((noreturn)) __cxa_pure_virtual();

void __cxa_pure_virtual() {
  fprintf(stderr, __func__);
  abort();
}
}
