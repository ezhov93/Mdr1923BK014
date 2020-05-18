#ifndef UART_H
#define UART_H

#include "Global.h"

typedef struct {
  __IO uint32_t DR;
  __IO uint32_t RSR_ECR;
  __IO uint32_t Reserved1[4];
  __IO uint32_t FR;
  __IO uint32_t Reserved2;
  __IO uint32_t ILPR;
  __IO uint32_t IBRD;
  __IO uint32_t FBRD;
  __IO uint32_t LCR_H;
  __IO uint32_t CR;
  __IO uint32_t IFLS;
  __IO uint32_t IMSC;
  __IO uint32_t RIS;
  __IO uint32_t MIS;
  __IO uint32_t ICR;
  __IO uint32_t DMACR;
} MDR_UART_TypeDef;

namespace Private {
[[maybe_unused]] static MDR_UART_TypeDef uart0 = {};
[[maybe_unused]] static MDR_UART_TypeDef uart1 = {};
}  // namespace Private

const uint MDR_UART0_BASE = reinterpret_cast<uint>(&Private::uart0);
const uint MDR_UART1_BASE = reinterpret_cast<uint>(&Private::uart1);

[[maybe_unused]] static MDR_UART_TypeDef* MDR_UART0 = &Private::uart0;
[[maybe_unused]] static MDR_UART_TypeDef* MDR_UART1 = &Private::uart1;

#endif  // UART_H
