#pragma once

#include "1923VK014/1923VK014.h"

// ToDo: methods

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

  enum Mode {
    Input,
    InputPullup,
    InputPulldown,
    AnalogInput,
    Output,
    OutputPullup,
    OutputPulldown,
    AnalogOutput
  };

  constexpr Pin(const uint portAddr, const uint number)
      : _portAddr(portAddr), _number(number) {}

  ~Pin() = default;

  void init(const Mode, const Function function = Function0) const;
  void set() const;
  void reset() const;
  void write(bool state) const { (state ? set() : reset()); }
  bool read() const;

 private:
  constexpr uint numberPos() const { return (1 << _number); }
  const uint _portAddr;
  const uint _number;
};
