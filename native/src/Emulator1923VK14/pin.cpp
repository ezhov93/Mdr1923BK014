#include "pin.h"
#include <cassert>
#include <iostream>
#include "1923VK014/1923VK014.h"

constexpr uint PortClkEnable(const uint portAddr) {
  return (1 << (13 + ((portAddr & 0xFFFF) >> 12)));
}

typedef enum { PowerDiverOff, Power300ns, Power100ns, Power10ns } Power;

void Pin::init(const Mode mode, const Function function) const {
  // Clock enable

  assert(PortClkEnable(0x40082000) == (1 << 15));
  CLK_CNTR->PER0_CLK |= PortClkEnable(_portAddr);

  PortControl* port = reinterpret_cast<PortControl*>(_portAddr);

  // Default
  port->KEY = _KEY_;

  // Function
  const uint cntOfFunction = _number / 8;
  const uint func = (function << ((_number % 8) * 4));
  port->CFUNC[cntOfFunction] = func;

  // Input / Output
  (mode < Output) ? port->SOE : port->COE = numberPos();

  // Digital / Analog
  if (mode == AnalogInput || mode == AnalogOutput)
    port->CANALOG = numberPos();
  else
    port->SANALOG = numberPos();

  // Pullup / Pulldown
  if (mode == InputPullup || mode == OutputPullup) {
    port->SPULLUP = numberPos();
  } else if (mode == InputPulldown || mode == OutputPulldown) {
    port->SPULLDOWN = numberPos();
  } else {
    port->CPULLDOWN = numberPos();
    port->CPULLUP = numberPos();
  }
  // Power
  const uint cntOfPwr = _number / 16;
  const uint pwr = (Power10ns << ((_number % 16) * 2));
  port->CPWR[cntOfPwr] = pwr;
  port->SPWR[cntOfPwr] = pwr;
}

bool Pin::read() const {
  return reinterpret_cast<PortControl*>(_portAddr)->RXTX;
}

void Pin::set() const {
  reinterpret_cast<PortControl*>(_portAddr)->SRXTX |= numberPos();
}

void Pin::reset() const {
  reinterpret_cast<PortControl*>(_portAddr)->CRXTX |= numberPos();
}
