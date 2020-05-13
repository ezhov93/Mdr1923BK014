#include "led.h"
#include "gdb.h"

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

    printf("%d\r\n",cnt);
    cnt++;
  }

  return 0;
}

//void HardFault_Handler() {
//  led.on(1);
//}
