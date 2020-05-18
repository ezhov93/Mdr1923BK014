#ifndef TEST_TESTPIN_H_
#define TEST_TESTPIN_H_

#include <assert.h>

#include "Pin.h"
#include "TestInterface.h"

class TestPin : public TestInterface {
 public:
  constexpr TestPin() : led0(PC0), led7(PC7) {}

  virtual void exec() final {
    printf("*** TEST PIN ***\r\n");
    led0.init(Pin::Output);
    led7.init(Pin::Output);
  }

  virtual void update() final {
    led0.set();
    assert(led0.read() == true);
    delay();

    led0.reset();
    assert(led0.read() == false);
    delay();

    led7.write(true);
    assert(led7.read() == true);
    delay();

    led7.write(false);
    assert(led7.read() == false);
    delay();
  }

 private:
  void delay() {
    volatile int cnt = 0;
    while (cnt < 120000) ++cnt;
  }

  const Pin &led0;
  const Pin &led7;
};

#endif  // TEST_TESTPIN_H_
