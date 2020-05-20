/*
 * I/O and interface portion of GDB stub
 *
 * File      : hal_stub.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-04     Wzyy2      first version
 */
//#include <rtthread.h>
//#include <rthw.h>
#include "system/1923VK014.h"
#include "system/gdb/gdb_stub.h"

// #ifdef RT_USING_SERIAL
// #include <rtdevice.h>
// #endif

#define UART_FR_RXFE ((uint32_t)0x00000010)
#define UART_FR_TXFF ((uint32_t)0x00000020)

// rt_device_t gdb_dev = RT_NULL;
static struct rt_serial_device *gdb_serial;
char gdb_io_set;

void gdb_uart_putc(char c);
int gdb_uart_getc();

/*if you want to use something instead of the serial,change it */
struct gdb_io gdb_io_ops = {
    gdb_uart_getc,
    gdb_uart_putc,
    0,
};

/**
 * @ingroup gdb_stub
 *
 * This function will get GDB stubs started, with a proper environment
 */
// void gdb_start()
// {
//     if (gdb_dev == RT_NULL)
//         rt_kprintf("GDB: no gdb_dev found,please set it first\n");
//     else
//         gdb_breakpointt();
// }
/**
 * @ingroup gdb_stub
 *
 * This function sets the input device of gdb_stub.
 *
 * @param device_name the name of new input device.
 */
// void gdb_set_device(const char* device_name)
// {
//     rt_device_t dev = RT_NULL;
//     dev = rt_device_find(device_name);
//     if(dev == RT_NULL){
//         rt_kprintf("GDB: can not find device: %s\n", device_name);
//         return;
//     }
//     /* open this device and set the new device  */
//     if (rt_device_open(dev, RT_DEVICE_OFLAG_RDWR) == RT_EOK)
//     {
//         gdb_dev = dev;
//         gdb_serial = (struct rt_serial_device *)gdb_dev;
//     }
// }
void gdb_uart_putc(char c) {
  // #ifdef RT_GDB_DEBUG
  //     rt_kprintf("%c",c);
  // #endif
  // rt_device_write(gdb_dev, 0, &c, 1);
  while (MDR_UART0->FR & UART_FR_TXFF) continue;
  MDR_UART0->DR = c;
}

/*  polling  */
int gdb_uart_getc() {
  while (MDR_UART0->FR & UART_FR_RXFE) continue;
  return (char)MDR_UART0->DR & 0xff;

  //#else
  //    rt_device_read(gdb_dev, 0, &ch, 1);
  //#endif

  // #ifdef RT_GDB_DEBUG
  //     rt_kprintf("%c",ch);
  // #endif
}
