#include <exception_handlers.h>

void __attribute__((weak)) Default_Handler(void);

//  MDR1923VK014 Specific Interrupts
void FT_ERR_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CLK_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void POWER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void BKP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EBC_ERROR_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CCSDS_TX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CCSDS_RX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPIO_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPW1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPW2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMER1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMER2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMER3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMER4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void MIL1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void MIL2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void MIL3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void MIL4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SSP1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SSP2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SSP3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SSP4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SSP5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SSP6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CRC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ECC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

extern unsigned int _estack;

typedef void (*const pHandler)(void);

// The vector table.
// This relies on the linker script to place at correct location in memory.

__attribute__ ((section(".isr_vector"),used))
pHandler __isr_vectors[] = {  //
    (pHandler) &_estack,                          // The initial stack pointer
        Reset_Handler,                            // The reset handler
        NMI_Handler,                              // The NMI handler
        HardFault_Handler,                        // The hard fault handler
        0,                                        // Reserved
        0,                                        // Reserved
        0,				                                // Reserved
        0,                                        // Reserved
        0,                                        // Reserved
        0,                                        // Reserved
        0,                                        // Reserved
        SVC_Handler,                              // SVCall handler
        0,					                              // Reserved
        0,                                        // Reserved
        PendSV_Handler,                           // The PendSV handler
        SysTick_Handler,                          // The SysTick handler

        // External Interrupts - MDR1923VK014 Specific
        FT_ERR_IRQHandler,                        // 0: FT_IF0_Handler
        CLK_IRQHandler,                           // 1: CLK_IF_Handler
        POWER_IRQHandler,                         // 2: PVD_IF_Handler
        RTC_IRQHandler,                           // 3: RTC_IF_Handler
        BKP_IRQHandler,                           // 4: BKP_IF_Handler
        EBC_ERROR_IRQHandler,                     // 5: EXT_INTERROR0_Handler
        DMA_IRQHandler,                           // 6: DMA_ERR_Handler
        CCSDS_TX_IRQHandler,                      // 7: INT_ETH0_Handler
        CCSDS_RX_IRQHandler,                      // 8: INT_ETH0_Handler
        GPIO_IRQHandler,                          // 9: IRQ_PORTA_Handler
        SPW1_IRQHandler,                          // 10: INT_SPW0_Handler
        SPW2_IRQHandler,                          // 11: INT_SPW1_Handler
        TIMER1_IRQHandler,                        // 12: INT_TMR0_Handler
        TIMER2_IRQHandler,                        // 13: INT_TMR1_Handler
        TIMER3_IRQHandler,                        // 14: INT_TMR2_Handler
        TIMER4_IRQHandler,                        // 15: INT_TMR3_Handler
        CAN1_IRQHandler,                          // 16: INT_CAN0_Handler
        CAN2_IRQHandler,                          // 17: INT_CAN1_Handler
        UART1_IRQHandler,                         // 18: INT_UART0_Handler
        UART2_IRQHandler,                         // 19: INT_UART1_Handler
        MIL1_IRQHandler,                          // 20: INT_MIL0_Handler
        MIL2_IRQHandler,                          // 21: INT_MIL1_Handler
        MIL3_IRQHandler,                          // 22: INT_MIL2_Handler
        MIL4_IRQHandler,                          // 23: INT_MIL3_Handler
        SSP1_IRQHandler,                          // 24: INT_SSP0_Handler
        SSP2_IRQHandler,                          // 25: INT_SSP1_Handler
        SSP3_IRQHandler,                          // 26: INT_SSP2_Handler
        SSP4_IRQHandler,                          // 27: INT_SSP3_Handler
        SSP5_IRQHandler,                          // 28: INT_SSP4_Handler
        SSP6_IRQHandler,                          // 29: INT_SSP5_Handler
        CRC_IRQHandler,                           // 30: CRC_Handler
        ECC_IRQHandler                           // 31: ECC_Handlere
    };

// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.

void __attribute__ ((section(".after_vectors"))) Default_Handler(void) {
  while (1) {
  }
}
