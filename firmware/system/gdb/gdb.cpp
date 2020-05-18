#include "gdb.h"

#include "config_gdb.h"
#include "gdb_stub.h"

void Gdb::begin() {
  StartGDB();
  gdb_bp();
}
