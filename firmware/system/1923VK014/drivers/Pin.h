#ifndef SYSTEM_1923VK014_DRIVERS_PIN_H_
#define SYSTEM_1923VK014_DRIVERS_PIN_H_

#include "Global.h"

class Pin {
 public:
  enum Function {
    Function0,
    Function1,
    Function2,
    Function3,
    Function4,
    Function5,
    Function6,
    Function7,
    Function8,
    Function9,
    Function10,
    Function11,
    Function12,
    Function13,
    Function14,
    Function15,
  };

  constexpr Pin(uint portAddr, uint number) :
      _portAddr(portAddr), _number(number), _function(Function0) {
  }

  ~Pin() = default;

  void write() const;
  void read() const;
  void set() const;
  void reset() const;
  void setFunction();
  void function();
 private:
  const uint _portAddr;
  const uint _number;
  int _function;
};

#endif /* SYSTEM_1923VK014_DRIVERS_PIN_H_ */
