#include "gdb.h"
#include "config_gdb.h"
#include "gdb_stub.h"

void Gdb::init() {
  StartGDB();
}

void Gdb::start() {
  gdb_bp();
}

void Gdb::print(unsigned char ch) {
  (void)ch;
//  const char *ptr = (char*)&ch;
//  gdb_console_write("hello",unsigned(1));
}

