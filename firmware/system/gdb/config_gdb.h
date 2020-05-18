#ifndef __CONFIG_GDP_H
#define __CONFIG_GDP_H

#include <stdint.h>

#define _KEY_ 0x8555AAA1

#ifdef __cplusplus
extern "C" {
#endif

void StartGDB(void);
void gdb_bp(void);
void gdb_led(int);

#ifdef __cplusplus
}
#endif

#endif  // __CONFIG_GDP_H
