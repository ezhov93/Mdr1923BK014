#ifndef SYSTEM_1923VK014_DEFS_H
#define SYSTEM_1923VK014_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "1923VK014.h"

//RST_CLK

#define RST_CLK_DIV_Pos                        (0UL)
#define RST_CLK_DIV_Msk                   (0xffffUL)
#define CLK_CNTR_MAX_CLK_Select_Msk          (0xfUL)
#define RST_PLL_SELECT_Pos                    (29UL)
#define RST_PLL_SELECT_Msk            (0xe0000000UL)
#define RST_PLL_PLL_Q_Pos                      (0UL)
#define RST_PLL_PLL_Q_Msk                    (0xfUL)
#define RST_PLL_DV_Pos                         (4UL)
#define RST_PLL_DV_Msk                      (0x10UL)
#define RST_PLL_PLL_N_Pos                      (8UL)
#define RST_PLL_PLL_N_Msk                 (0x7f00UL)
#define RST_PER0_FTCNTR_CLK_EN_Msk           (0x8UL)

typedef enum {
  MAXCLK_HSI = 0,
  MAXCLK_HSIdiv2 = 1,
  MAXCLK_HSE0 = 2,
  MAXCLK_HSE0div2 = 3,
  MAXCLK_HSE1 = 4,
  MAXCLK_HSE1div2 = 5,
  MAXCLK_LSI = 6,
  MAXCLK_LSE = 7,
  MAXCLK_PLL0 = 8,
  MAXCLK_PLL1 = 9,
  MAXCLK_PLL2 = 10,
  MAXCLK_ERR = 11,   //  Error Value - reserved
} CLK_CNTR_MAXCLK_SEL;

typedef enum {
  PLL_IN_HSI = 0,
  PLL_IN_HSIdiv2 = 1,
  PLL_IN_HSE0 = 2,
  PLL_IN_HSE0div2 = 3,
  PLL_IN_HSE1 = 4,
  PLL_IN_HSE1div2 = 5,
} PLL_IN_SEL;

#define CLK_SEL_COUNT MAXCLK_PLL0
static const uint32_t GenFreqsHz[CLK_SEL_COUNT] = {
    __HSI,          //  MAXCLK_HSI      = 0,
    __HSI / 2,      //  MAXCLK_HSIdiv2  = 1,
    __HSE0,         //  MAXCLK_HSE0     = 2,
    __HSE0 / 2,     //  MAXCLK_HSE0div2 = 3,
    __HSE1,         //  MAXCLK_HSE1     = 4,
    __HSE1 / 2,     //  MAXCLK_HSE1div2 = 5,
    __LSI,          //  MAXCLK_LSI      = 6,
    __LSE           //  MAXCLK_LSE      = 7
    };

// BKP

#define BKP_REG60_PORSTn_Dis_Msk      (0x10000000UL)

// FT Control
#define FTCTRL_EVENT_COUNT  13

#ifdef __cplusplus
}
#endif

#endif SYSTEM_1923VK014_DEFS_H
