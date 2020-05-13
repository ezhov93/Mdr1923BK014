/*
 * gdb.h
 *
 *  Created on: 16 ���. 2020 �.
 *      Author: ezhov
 */

#ifndef GDB_GDB_H_
#define GDB_GDB_H_

#include <stdio.h>
#include "1923VK014.h"

class Gdb {
 public:
  Gdb() = default;
  static void begin();

  static void print(const char *str) {
    fprintf(stderr, str);
  }

  static void print(int c) {
    fprintf(stderr, "%d", c);
  }

  static void println() {
    fprintf(stderr, "\r\n");
  }

  static void println(const char *str) {
    print(str);
    println();
  }

  static void println(int c) {
    print(c);
    println();
  }
//  TODO �������� ����������

};

#endif /* GDB_GDB_H_ */
