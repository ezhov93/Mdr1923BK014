#pragma once

#include "1923VK014.h"

struct PortControlPhysic {
  Register KEY;
  Register RXTX;
  Register OE;
  Register FUNC[4];
  Register ANALOG;
  Register PULLUP;
  Register PULLDOWN;
  Register PD;
  Register PWR[2];
  Register CL;
  Register IE;
  Register IT;
  Register IR;
  Register HCUR;
};

struct PortControl {
  PortControl(PortControlPhysic& port)
      : KEY(port.KEY),
        RXTX(port.RXTX),
        SRXTX(&port.RXTX),
        CRXTX(&port.RXTX),
        SOE(&port.OE),
        COE(&port.OE),
        SANALOG(&port.ANALOG),
        CANALOG(&port.ANALOG),
        SPULLUP(&port.PULLUP),
        CPULLUP(&port.PULLUP),
        SPULLDOWN(&port.PULLDOWN),
        CPULLDOWN(&port.PULLDOWN),
        SPD(&port.PD),
        CPD(&port.PD),
        SCL(&port.CL),
        CCL(&port.CL),
        SIE(&port.IE),
        CIE(&port.IE),
        SIT(&port.IT),
        CIT(&port.IT),
        SIR(&port.IR),
        CIR(&port.IR),
        HCUR(port.HCUR) {
    for (int i = 0; i < 4; ++i) {
      SFUNC[i].setParent(&port.FUNC[i]);
      CFUNC[i].setParent(&port.FUNC[i]);
    }
    for (int i = 0; i < 2; ++i) {
      SPWR[i].setParent(&port.PWR[i]);
      CPWR[i].setParent(&port.PWR[i]);
    }
  }
  Register& KEY;
  Register& RXTX;
  SRegister SRXTX;
  CRegister CRXTX;
  SRegister SOE;
  CRegister COE;
  SRegister SFUNC[4];
  CRegister CFUNC[4];
  SRegister SANALOG;
  CRegister CANALOG;
  SRegister SPULLUP;
  CRegister CPULLUP;
  SRegister SPULLDOWN;
  CRegister CPULLDOWN;
  SRegister SPD;
  CRegister CPD;
  SRegister SPWR[2];
  CRegister CPWR[2];
  SRegister SCL;
  CRegister CCL;
  SRegister SIE;
  CRegister CIE;
  SRegister SIT;
  CRegister CIT;
  SRegister SIR;
  CRegister CIR;
  Register& HCUR;
};

namespace Private {
[[maybe_unused]] static PortControlPhysic physicA;
[[maybe_unused]] static PortControlPhysic physicB;
[[maybe_unused]] static PortControlPhysic physicC;
[[maybe_unused]] static PortControlPhysic physicD;
[[maybe_unused]] static PortControlPhysic physicE;
[[maybe_unused]] static PortControl portA(physicA);
[[maybe_unused]] static PortControl portB(physicB);
[[maybe_unused]] static PortControl portC(physicC);
[[maybe_unused]] static PortControl portD(physicD);
[[maybe_unused]] static PortControl portE(physicE);
}  // namespace Private

const static uint32_t PORTA_BASE = reinterpret_cast<uint32_t>(&Private::portA);
const static uint32_t PORTB_BASE = reinterpret_cast<uint32_t>(&Private::portB);
const static uint32_t PORTC_BASE = reinterpret_cast<uint32_t>(&Private::portC);
const static uint32_t PORTD_BASE = reinterpret_cast<uint32_t>(&Private::portD);
const static uint32_t PORTE_BASE = reinterpret_cast<uint32_t>(&Private::portE);

[[maybe_unused]] static PortControl* PORTA = &Private::portA;
[[maybe_unused]] static PortControl* PORTB = &Private::portB;
[[maybe_unused]] static PortControl* PORTC = &Private::portC;
[[maybe_unused]] static PortControl* PORTD = &Private::portD;
[[maybe_unused]] static PortControl* PORTE = &Private::portE;
