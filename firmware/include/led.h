#ifndef LED_H
#define LED_H

#include "1923VK014.h"

class Led {
 public:
  Led() {}
  ~Led() {}

  void init() {
    CLK_CNTR->PER0_CLK |= 1 << 15;  // Enable clock of PortC
    PORTC->KEY = _KEY_;

    PORTC->CFUNC[0] = 0xFFFFFFFF;
    PORTC->CFUNC[1] = 0xFFFFFFFF;
    PORTC->CFUNC[2] = 0xFFFFFFFF;
    PORTC->CFUNC[3] = 0xFFFFFFFF;

    PORTC->SOE = (0xFF << 0);
    PORTC->SANALOG = (0xFF << 0);
    PORTC->SPWR[0] = 0x5555;

    PORTC->RXTX = 0;
  }

  void on(int num) { PORTC->RXTX |= (1 << num); }

  void off(int num) {
    PORTC->RXTX &= ~(1 << num);
  }
};

#endif  // LED_H

