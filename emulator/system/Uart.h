#ifndef UART_H
#define UART_H

#include "1923VK014.h"

typedef struct {
  Register DR;
  Register RSR_ECR;
  Register Reserved1[4];
  Register FR;
  Register Reserved2;
  Register ILPR;
  Register IBRD;
  Register FBRD;
  Register LCR_H;
  Register CR;
  Register IFLS;
  Register IMSC;
  Register RIS;
  Register MIS;
  Register ICR;
  Register DMACR;
} MDR_UART_TypeDef;

namespace Private {
[[maybe_unused]] static MDR_UART_TypeDef uart0;
[[maybe_unused]] static MDR_UART_TypeDef uart1;
}  // namespace Private

const uint32_t MDR_UART0_BASE = reinterpret_cast<uint32_t>(&Private::uart0);
const uint32_t MDR_UART1_BASE = reinterpret_cast<uint32_t>(&Private::uart1);

[[maybe_unused]] static MDR_UART_TypeDef* MDR_UART0 = &Private::uart0;
[[maybe_unused]] static MDR_UART_TypeDef* MDR_UART1 = &Private::uart1;

#endif  // UART_H
