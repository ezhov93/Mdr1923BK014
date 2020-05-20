#ifndef LED_H
#define LED_H

#include "Pin.h"

class Led {
 public:
  constexpr explicit Led(const Pin &pin) : _pin(pin) {}
  ~Led() = default;

  void init() const { _pin.init(Pin::Output); }
  void on() const { _pin.reset(); }
  void off() const { _pin.reset(); }

 private:
  Pin &_pin;
};

static const Led Led0(PC0);
static const Led Led1(PC1);
static const Led Led2(PC2);
static const Led Led3(PC3);
static const Led Led4(PC4);
static const Led Led5(PC5);
static const Led Led6(PC6);
static const Led Led7(PC7);

#endif  // LED_H
