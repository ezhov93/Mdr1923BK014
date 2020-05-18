#include <stdint.h>

#include "1923VK014.h"
#include "1923VK014_conf.h"
#include "core_cm0.h"
#include "system_1923VK014_defs.h"

#define CLK_SEL_COUNT_PLL PLL_IN_HSE1div2 + 1
#define FERQ_FAULT_HZ __HSI

uint32_t SystemCoreClock = __SYSTEM_CLOCK;
uint32_t SystemCoreMaxClock = __SYSTEM_CLOCK;

void SystemCoreClockUpdate(void) {
  uint32_t freqHz;
  uint32_t selMaxClk = CLK_CNTR->MAX_CLK & CLK_CNTR_MAX_CLK_Select_Msk;
  if (selMaxClk < MAXCLK_PLL0) {
    freqHz = GenFreqsHz[selMaxClk];
  } else if (selMaxClk <= MAXCLK_PLL2) {
    uint32_t regCLK;
    switch (selMaxClk) {
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
    uint32_t selPll = _FLD2VAL(RST_PLL_SELECT, regCLK);
    if (selPll < CLK_SEL_COUNT_PLL) {
      uint32_t pllSource = GenFreqsHz[selPll];

      uint32_t pllQ = _FLD2VAL(RST_PLL_PLL_Q, regCLK);
      uint32_t pllDiv = _FLD2VAL(RST_PLL_DV, regCLK);
      uint32_t pllN = _FLD2VAL(RST_PLL_PLL_N, regCLK);
      if (pllN == 0) pllN = 2;

      freqHz = ((pllSource * pllN / (pllQ + 1)) / (pllDiv + 1));
    } else {
      freqHz = FERQ_FAULT_HZ;
    }
  } else {
    freqHz = FERQ_FAULT_HZ;
  }

  uint32_t freqDiv = (CLK_CNTR->CPU_CLK & RST_CLK_DIV_Msk) >> RST_CLK_DIV_Pos;

  SystemCoreMaxClock = freqHz;
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
  for (i = 0; i < FTCTRL_EVENT_COUNT; ++i) FT_CNTR->EVENT[i] = 0xFFFFFFFFUL;

  FT_CNTR->KEY = 0;
  FT_CNTR->KEY = 0;

  SystemCoreClock = __SYSTEM_CLOCK;
}
