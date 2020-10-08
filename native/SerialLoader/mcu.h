#ifndef MCU_H
#define MCU_H

#include <QtGlobal>

struct Mcu {
  const struct Type {
    const quint32 adr;
    const quint32 size;
  } flash, ram, xram;
  const char* name;
};

const Mcu NoMcu = {.flash = {0x00000000, 0},
                   .ram = {0x00000000, 0},
                   .xram = {0x00000000, 0},
                   .name = ""};

const Mcu Mdr1923VK014 = {.flash = {0x00000000, 128 * 1024},
                          .ram = {0x20000000, 32 * 1024},
                          .xram = {0x02000000, 32 * 1024},
                          .name = "1923VK014"};

#endif  // MCU_H
