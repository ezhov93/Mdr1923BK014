/*
 * I/O and interface portion of GDB stub
 */

#include "gdb_stub.h"
#include "1923VK014.h"

#define UART_FR_RXFE                            ((uint32_t)0x00000010)
#define UART_FR_TXFF                            ((uint32_t)0x00000020)

//rt_device_t gdb_dev = RT_NULL;
//static struct rt_serial_device *gdb_serial;
char gdb_io_set;

void gdb_uart_putc(char);
int gdb_uart_getc();
void gdb_uart_flush();

/*if you want to use something instead of the serial,change it */
struct gdb_io gdb_io_ops = { gdb_uart_getc, gdb_uart_putc, gdb_uart_flush, 0 };

void gdb_uart_putc(char ch) {
  while (MDR_UART0->FR & UART_FR_TXFF)
    continue;
  MDR_UART0->DR = ch;
}

int gdb_uart_getc() {
//  int ch;
//  ch = -1;
//  do {
//    ch = -1;
//    while (MDR_UART0->FR & UART_FR_RXFE)
//      continue;
//    ch = MDR_UART0->DR & 0xff;
//    MDR_UART0->DR = ch;
//  } while (ch == -1);
//  return ch;

  while (MDR_UART0->FR & UART_FR_RXFE)
    continue;
  return (char) (MDR_UART0->DR & 0xff);
}

void gdb_uart_flush() {
  while (MDR_UART0->FR & UART_FR_TXFF)
    continue;
}
