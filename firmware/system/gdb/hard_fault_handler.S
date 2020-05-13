    .syntax unified
    .arch armv7-m
    .cpu cortex-m0
    .thumb
    .align 4

	.globl rt_hw_debugmon_exception
	.globl HardFault_Handler

.thumb_func
HardFault_Handler:
				mrs     r0,psp                  ;// Get process stack
				movs	r1,r0
				subs    r1,#(4*13)           ;// Make space for saved state
				msr     psp,r1                  ;// Ensure PSP is up to date

				mov     r12,r0                  ;// R12 = stack
				movs     r1,#1                   ;// R1 = exception state type
				mrs     r2,ipsr                 ;// R2 = vector number

				subs 	r0,#(4*13)
				stm 	r0!,{r1-r7}

				mov     r1, r8
				mov		r2, r9
				mov		r3, r10
				mov		r4, r11
				mov		r5, r12
				mov		r6, lr
				stm 	r0!,{r1-r6}
				subs 	r0,#(4*13)

				mov     r4,r0                   ;// R4 = saved state pointer
				bl      rt_hw_debugmon_exception

				mov     r0,r4                   ;// R4 = saved state pointer

				adds 	r0,#(4*7)
				ldm 	r0!,{r1-r6}
				mov     r8, r1
				mov		r9, r2
				mov		r10, r3
				mov		r11, r4
				mov		r12, r5
				mov		lr, r6
				subs 	r0,#(4*13)
				ldm 	r0!,{r1-r7}
				adds 	r0,#(4*6)

				msr     psp,r0                  ;// Restore PSP

				bx      lr
	.end
