#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void __attribute__((noreturn)) __assert_func(const char *file, int line,
                                             const char *func,
                                             const char *failedexpr) {
  fprintf(stderr, "assertion \"%s\" failed: file \"%s\", line %d%s%s\n",
          failedexpr, file, line, func ? ", function: " : "", func ? func : "");
  abort();
  /* NOTREACHED */
}

#ifdef  USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t *file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif // USE_FULL_ASSERT

#if defined(USE_FULL_ASSERT)
void assert_failed(uint8_t *file, uint32_t line);

// Called from the assert_param() macro, usually defined in the stm32f*_conf.h
void __attribute__((noreturn, weak)) assert_failed(uint8_t *file, uint32_t line) {
  fprintf(stderr, "assert_param() failed: file \"%s\", line %d\n", file, line);
  abort();
  /* NOTREACHED */
}
#endif // defined(USE_FULL_ASSERT)

