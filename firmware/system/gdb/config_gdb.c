#include "1923VK014.h"
#include "config_gdb.h"

void ClockConfig(void) {
  CLK_CNTR->HSE1_CLK = (1 << 27) | (1 << 29);               // Enable HSE1 osc
  while ((CLK_CNTR->HSE1_STAT & (1 << 20)) == 0) {
  } //wait while HSE1 not ready

  CLK_CNTR->MAX_CLK = 4;    //MAX_CLOCK = HSE1 = 8 MHz
//  CLK_CNTR->CPU_CLK = 0;  //Core clock <-> MAX_CLOCK

//  CLK_CNTR->PLL0_CLK = (2 << 29)|(8 << 8)|(0 << 0);   // PLL_FREQ = (10 MHz * 8) / 1 = 80 MHz
//  CLK_CNTR->PLL0_CLK |= (1 << 27);    //PLL ON
//  while((CLK_CNTR->PLL0_STAT & (1 << 20)) == 0){} //wait while PLL0 not ready
//  CLK_CNTR->MAX_CLK = 8;  //MAX_CLOK <-- PLL0 cpu freq = 80 MHz

}

void PorDisable(void) {
  BKP->KEY = _KEY_; // Key to access battery domain control

  BKP->REG_60_TMR0 |= 1 << 28; // disable POR
  BKP->REG_60_TMR1 |= 1 << 28; // disable POR
  BKP->REG_60_TMR2 |= 1 << 28; // disable POR

  CLK_CNTR->KEY = _KEY_; // Key to access clock control
  FT_CNTR->KEY = _KEY_; // Key to access fault control

  FT_CNTR->RESET_EVENT0 = 0x0; // hide all errors
  FT_CNTR->RESET_EVENT1 = 0x0; // hide all errors
  FT_CNTR->RESET_EVENT2 = 0x0; // hide all errors
  FT_CNTR->RESET_EVENT3 = 0x0; // hide all errors
  FT_CNTR->RESET_EVENT4 = 0x0; // hide all errors
}

void UartConfig(void) {
  CLK_CNTR->UART0_CLK = (2 << 28) | (1 << 16); //Frequency UART0 -> 8 MHz (HSE1)
  CLK_CNTR->PER1_CLK = (1 << 6);                //UART0 Clock Enable

  /* for ref. clock of UART0 16 MHz*/
  //MDR_UART0->IBRD = 8;
  //MDR_UART0->FBRD = 43;   //speed 115200 bit/s
  /* for ref. clock of UART0 8 MHz*/
//  MDR_UART0->IBRD = 4;
//  MDR_UART0->FBRD = 22; //speed 115200 bit/s
  /* for ref. clock of UART0 8 MHz*/
  MDR_UART0->IBRD = 52;
  MDR_UART0->FBRD = 5; //speed 9600 bit/s

  MDR_UART0->LCR_H = (3 << 5);  //8 bit in word, 1-stop bit
  MDR_UART0->IMSC = (1 << 4);       //RXIM (Rx interrupt enable)
  MDR_UART0->CR = (1 << 9) | (1 << 8) | (1 << 0); //Tx enable, Rx enable, Uart0 enable.
}

void UartPortsConfig(void) {
  CLK_CNTR->PER0_CLK |= (1 << 17); //Enable clock of PortE

  PORTE->KEY = _KEY_;

  PORTE->SFUNC[1] = (5 << 28);  //5 function of PortE[15] - UART0_TX
  PORTE->SFUNC[2] = (5 << 0);       //5 function of PortE[16] - UART0_RX

  PORTE->SANALOG = (1 << 15) | (1 << 16);   //PortE[15], PortE[16] - digital

  PORTE->SPWR[0] = (2U << 30);  //PortE[15] - middle edge
  PORTE->SPWR[1] = (2 << 0);    //PortE[16] - middle edge

  PORTE->KEY = 0;
}

void StartGDB(void) {
  ClockConfig();     // HSE configuration
  UartPortsConfig(); // GPIO configuration for UART0
  UartConfig();      // UART0 configuration
}

void gdb_bp(void) {
# ifdef DEBUG
  asm volatile(
      ".word     0xe7ffdeff \n"
      "bx      lr \n"
      "NOP\n"
  );
#endif
}

void gdb_led(int enable) {
  if (enable)
    PORTC->RXTX |= (1 << 7);
  else
    PORTC->RXTX &= ~(1 << 7);
}
