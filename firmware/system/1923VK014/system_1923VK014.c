#include <stdint.h>
#include "1923VK014_conf.h"
#include "1923VK014.h"
#include "system_1923VK014_defs.h"
#include "core_cm0.h"

#define CLK_SEL_COUNT_PLL   PLL_IN_HSE1div2 + 1
#define FERQ_FAULT_HZ       __HSI

uint32_t SystemCoreClock = __SYSTEM_CLOCK;
uint32_t MaxClock = __SYSTEM_CLOCK;

void SystemCoreClockUpdate(void)
{
  uint32_t regCLK;
  uint32_t pll_source, pll_N, pll_Q, pll_DIV;
  uint32_t sel_max_clk, sel_pll;
  uint32_t freqHz;

  sel_max_clk = CLK_CNTR->MAX_CLK & CLK_CNTR_MAX_CLK_Select_Msk;

  if (sel_max_clk < MAXCLK_PLL0)
    freqHz = GenFreqsHz[sel_max_clk];
  else if (sel_max_clk <= MAXCLK_PLL2) {
    switch (sel_max_clk) {
      case MAXCLK_PLL1:
        regCLK = CLK_CNTR->PLL1_CLK;
        break;
      case MAXCLK_PLL2:
        regCLK = CLK_CNTR->PLL2_CLK;
        break;
      default:
        regCLK = CLK_CNTR->PLL0_CLK;
        break;
    }
    sel_pll = _FLD2VAL(CLK_CNTR_PLL_SELECT_Pos, regCLK);
    if (sel_pll < CLK_SEL_COUNT_PLL) {
      pll_source = GenFreqsHz[sel_pll];

      pll_Q = _FLD2VAL(RST_PLL_PLL_Q_Pos, regCLK);
      pll_DIV = _FLD2VAL(RST_PLL_DV_Pos, regCLK);
      pll_N = _FLD2VAL(RST_PLL_PLL_N_Pos, regCLK);
      if (pll_N == 0)
        pll_N = 2;

      freqHz = ((pll_source * pll_N / (pll_Q + 1)) / (pll_DIV + 1));
    } else
      freqHz = FERQ_FAULT_HZ;
  } else
    freqHz = FERQ_FAULT_HZ;

  uint32_t freqDiv = (CLK_CNTR->CPU_CLK & RST_CLK_DIV_Msk) >> RST_CLK_DIV_Pos;

  MaxClock = freqHz;
  SystemCoreClock = freqHz / (freqDiv + 1);
}

void SystemInit(void) {
//  TODO: add code to initialize the system do not use global variable

//  Disable Reset by Upor
  BKP->KEY = _KEY_;
  BKP->REG_60_TMR0 |= BKP_REG60_PORSTn_Dis_Msk;
  BKP->REG_60_TMR1 |= BKP_REG60_PORSTn_Dis_Msk;
  BKP->REG_60_TMR1 |= BKP_REG60_PORSTn_Dis_Msk;

  //  Clear EVENTs in FTCNTR
  CLK_CNTR->KEY = _KEY_;
  CLK_CNTR->PER0_CLK |= RST_PER0_FTCNTR_CLK_EN_Msk;

  FT_CNTR->KEY = _KEY_;

  // Disable reset by EVENT0-EVENT4
  FT_CNTR->RESET_EVENT0 = 0x0;
  FT_CNTR->RESET_EVENT1 = 0x0;
  FT_CNTR->RESET_EVENT2 = 0x0;
  FT_CNTR->RESET_EVENT3 = 0x0;
  FT_CNTR->RESET_EVENT4 = 0x0;

  //  Clear EVENTS
  uint32_t i;
  for (i = 0; i < FTCTRL_EVENT_COUNT; ++i)
    FT_CNTR->EVENT[i] = 0xFFFFFFFFUL;

  FT_CNTR->KEY = 0;
  FT_CNTR->KEY = 0;

  SystemCoreClock = __SYSTEM_CLOCK;
}
