#include <stdio.h>

#include "TestPin.h"

TestPin test;

int main(void) {
  test.exec();

  forever { test.update(); }

  return 0;
}
