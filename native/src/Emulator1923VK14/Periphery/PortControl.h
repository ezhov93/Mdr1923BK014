#pragma once

#include "Global.h"

// Ports
typedef struct {
  __IO uint32_t KEY;
  __IO uint32_t RXTX;
  __IO uint32_t SRXTX;
  __IO uint32_t CRXTX;
  __IO uint32_t SOE;
  __IO uint32_t COE;
  __IO uint32_t SFUNC[4];
  __IO uint32_t CFUNC[4];
  __IO uint32_t SANALOG;
  __IO uint32_t CANALOG;
  __IO uint32_t SPULLUP;
  __IO uint32_t CPULLUP;
  __IO uint32_t SPULLDOWN;
  __IO uint32_t CPULLDOWN;
  __IO uint32_t SPD;
  __IO uint32_t CPD;
  __IO uint32_t SPWR[2];
  __IO uint32_t CPWR[2];
  __IO uint32_t SCL;
  __IO uint32_t CCL;
  __IO uint32_t SIE;
  __IO uint32_t CIE;
  __IO uint32_t SIT;
  __IO uint32_t CIT;
  __IO uint32_t SIR;
  __IO uint32_t CIR;
  __IO uint32_t HCUR;
} PortControl;

namespace Private {
[[maybe_unused]] static PortControl portA = {};
[[maybe_unused]] static PortControl portB = {};
[[maybe_unused]] static PortControl portC = {};
[[maybe_unused]] static PortControl portD = {};
[[maybe_unused]] static PortControl portE = {};
}  // namespace Private

const static uint PORTA_BASE = reinterpret_cast<int>(&Private::portA);
const static uint PORTB_BASE = reinterpret_cast<int>(&Private::portB);
const static uint PORTC_BASE = reinterpret_cast<int>(&Private::portC);
const static uint PORTD_BASE = reinterpret_cast<int>(&Private::portD);
const static uint PORTE_BASE = reinterpret_cast<int>(&Private::portE);

[[maybe_unused]] static PortControl* PORTA = &Private::portA;
[[maybe_unused]] static PortControl* PORTB = &Private::portB;
[[maybe_unused]] static PortControl* PORTC = &Private::portC;
[[maybe_unused]] static PortControl* PORTD = &Private::portD;
[[maybe_unused]] static PortControl* PORTE = &Private::portE;
