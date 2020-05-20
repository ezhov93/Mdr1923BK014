#include "Pin.h"

#include "system/1923VK014.h"

void Pin::init(const Mode mode, const Function function) const {
  enum Power { PowerDiverOff, Power300ns, Power100ns, Power10ns };

  // Clock enable
  const uint portClkEnable = (1 << (13 + ((_portAddr & 0xFFFF) >> 12)));
  CLK_CNTR->PER0_CLK |= portClkEnable;

  PortControl *port = reinterpret_cast<PortControl *>(_portAddr);
  port->KEY = _KEY_;
  // Function
  const uint cntOfFunction = _number / 8;
  const uint func = (function << ((_number % 8) * 4));
  port->CFUNC[cntOfFunction] = func;
  // Input / Output
  if (mode < Output)
    port->COE = numberPos();
  else
    port->SOE = numberPos();
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
  return reinterpret_cast<PortControl *>(_portAddr)->RXTX & numberPos();
}

void Pin::set() const {
  reinterpret_cast<PortControl *>(_portAddr)->SRXTX = numberPos();
}

void Pin::reset() const {
  reinterpret_cast<PortControl *>(_portAddr)->CRXTX = numberPos();
}
