#include "led.h"
#include "gdb.h"
#include "stdio.h"

Led led;

int main(void) {
  Gdb::init();
  Gdb::start();
  led.init();

  while (true) {
    static int cnt = 0;
    led.on(0);
    for (int cnt = 0; cnt < 120000; cnt++)
      continue;

    led.off(0);
    for (int cnt = 0; cnt < 120000; cnt++)
      continue;

    fprintf(stderr, "Hello\n");
    fprintf(stderr, "%d\n", cnt);
    cnt++;
  }

  return 0;
}
