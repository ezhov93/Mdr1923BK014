#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

#include "1923VK014.h"
#include "gdb_stub.h"

#define UART_FR_RXFE ((uint32_t)0x00000010)
#define UART_FR_TXFF ((uint32_t)0x00000020)
#define STDOUT 1
#define STDERR 2

int _write(int fd __attribute__((unused)), char *ptr, int len) {
  if (fd == STDERR) {
    gdb_console_write(ptr, len);
  } else if (fd == STDOUT) {
    for (int i = 0; i < len; ++i) {
      while (MDR_UART0->FR & UART_FR_TXFF) continue;
      MDR_UART0->DR = ptr[i] & 0xff;
    }
  }
  return len;
}

int _read(int fd __attribute__((unused)), char *ptr, int len) {
  for (int i = 0; i < len; ++i) {
    while (MDR_UART0->FR & UART_FR_RXFE) continue;
    ptr[i] = MDR_UART0->DR & 0xff;
  }
  return len;
}

void _ttywrch(int ch) {
  while (MDR_UART0->FR & UART_FR_TXFF) continue;
  MDR_UART0->DR = ch & 0xff;
}

int _fstat(int fd __attribute__((unused)), struct stat *pStat) {
  pStat->st_mode = S_IFCHR;
  return 0;
}

int _close(int fd __attribute__((unused))) { return -1; }

int _isatty(int fd __attribute__((unused))) { return 1; }

int _lseek(int a __attribute__((unused)), int b __attribute__((unused)),
           int c __attribute__((unused))) {
  return -1;
}
