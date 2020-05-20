
#include <stdio.h>

#include <iostream>
#include <string>

#include "system/test/TestPin.h"

TestPin test;

int main(void) {
  std::cout << "Hello" << std::endl;

  test.exec();
  while (1) {
    test.update();
  }
  return 0;
}
