#include "led.h"
#include "gdb.h"

Led led;

int main(void) {
  Gdb::begin();
  led.init();

  while (true) {
    static int cnt = 0;
    led.on(0);
    for (int cnt = 0; cnt < 120000; cnt++)
      continue;

    led.off(0);
    for (int cnt = 0; cnt < 120000; cnt++)
      continue;

    Gdb::println("Hello\n");
    Gdb::println(cnt);
    cnt++;
  }

  return 0;
}
