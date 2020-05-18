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
  enum { HEX, DEC };

  Gdb() = default;
  static void begin();

  static void print(char ch) { fprintf(stderr, "%c", ch); }

  static void print(const char *str) { fprintf(stderr, str); }

  static void print(uint8_t n, int base = DEC) {
    print(static_cast<unsigned int>(n), base);
  }

  static void print(int n, int base = DEC) {
    fprintf(stderr, base == HEX ? "%X" : "%d", n);
  }

  static void print(unsigned int n, int base = DEC) {
    fprintf(stderr, base == HEX ? "%x" : "%du", n);
  }

  static void print(long n, int base = DEC) {
    print(static_cast<int>(n), base);
  }

  static void print(unsigned long n, int base = DEC) {
    print(static_cast<unsigned int>(n), base);
  }

  static void print(double n, int base = 2) {
    char format[] = "%.2f";
    format[2] = (base < 10) ? (48 + base) : (48 + 9);
    fprintf(stderr, format, n);
  }

  static void println() { fprintf(stderr, "\r\n"); }

  static void println(char ch) {
    print(ch);
    println();
  }

  static void println(const char *str) {
    print(str);
    println();
  }

  static void println(uint8_t n, int base = DEC) {
    print(n, base);
    println();
  }

  static void println(int n, int base = DEC) {
    print(n, base);
    println();
  }

  static void println(unsigned int n, int base = DEC) {
    print(n, base);
    println();
  }

  static void println(long n, int base = DEC) {
    print(n, base);
    println();
  }

  static void println(unsigned long n, int base = DEC) {
    print(n, base);
    println();
  }

  static void println(double n, int base = 2) {
    print(n, base);
    println();
  }
};

#endif /* GDB_GDB_H_ */
