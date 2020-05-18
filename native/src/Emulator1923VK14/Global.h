#ifndef DEFENITION_H
#define DEFENITION_H

#include <stdint.h>

// Macroses
#define __IO volatile
#define __I volatile constf
#define forever for (;;)
#define UNUSED(arg) (void)(arg)

// Typedefs
typedef void (*func_ptr)();
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;

#define _KEY_ 0x8555AAA1

#endif  // DEFENITION_H
