#include <iostream>
#include "1923VK014/1923VK014.h"
#include "pin.h"

static const Pin pin(PORTA_BASE, 7);

int main() {
  pin.init(Pin::Output);
  pin.set();
  return 0;
  std::cout << 7 % 16;
}
