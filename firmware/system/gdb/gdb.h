/*
 * gdb.h
 *
 *  Created on: 16 апр. 2020 г.
 *      Author: ezhov
 */

#ifndef GDB_GDB_H_
#define GDB_GDB_H_

#include <stdio.h>
#include "1923VK014.h"

class Gdb {
public:
  Gdb() = default;
  static void init();
  static void start();
  static void print(unsigned char ch);
  static void print(char ch) {
    print((unsigned char) (ch));
  }
  static void print(const char *str) {
    while (*str != '\0')
      print(*str++);
  }

  static void print(int c) {
    char buffer[sizeof("-9223372036854775807-1")] = { };
    sprintf(buffer, "%d", c);
    print(buffer);
  }

  static void println() {
    print('\r');
    print('\n');
  }

  static void println(unsigned char ch) {
    print(ch);
    println();
  }

  static void println(char ch) {
    println((unsigned char) (ch));
  }

  static void println(const char *str) {
    while (*str != '\0')
      print(*str++);
    println();
  }

  static void println(int c) {
    char buffer[sizeof("-9223372036854775807-1")] = { };
    sprintf(buffer, "%d", c);
    print(buffer);
    println();
  }

};


#endif /* GDB_GDB_H_ */
