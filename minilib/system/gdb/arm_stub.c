/*
 * ARM GDB support
 * arch-specific portion of GDB stub
 */

#include <gdb_stub.h>
#include "1923VK014.h"

#define PS_N 0x80000000
#define PS_Z 0x40000000
#define PS_C 0x20000000
#define PS_V 0x10000000

#define IS_THUMB_ADDR(addr)     ((addr) & 1)
#define MAKE_THUMB_ADDR(addr) ((addr) | 1)
#define UNMAKE_THUMB_ADDR(addr) ((addr) & ~1)

static Gdb_SavedRegisters *regs;
static int compiled_break = 0;
static unsigned long step_addr = 0;
static int ins_will_execute(unsigned long ins);
static unsigned long target_ins(unsigned long *pc, unsigned long ins);

/*struct gdb_arch - Describe architecture specific values.*/
struct gdb_arch arch_gdb_ops = { { 0xfe, 0xde, 0xff, 0xe7 }  //Little-Endian
    , 0, 0, 0, 0 };

/**
 * gdb_breakpoint - generate a compiled_breadk
 * It is used to sync up with a debugger and stop progarm
 */
void gdb_breakpointt() {
  //asm("0xe7ffdeff");
}

void gdb_set_register(void *hw_regs) {
  regs = hw_regs;
}
void gdb_get_register(unsigned long *gdb_regs) {
  int regno;
  /* Initialize all to zero. */
  for (regno = 0; regno < GDB_MAX_REGS; regno++)
    gdb_regs[regno] = 0;

  gdb_regs[GDB_R0] = regs->r0;
  gdb_regs[GDB_R1] = regs->r1;
  gdb_regs[GDB_R2] = regs->r2;
  gdb_regs[GDB_R3] = regs->r3;
  gdb_regs[GDB_R4] = regs->r4;
  gdb_regs[GDB_R5] = regs->r5;
  gdb_regs[GDB_R6] = regs->r6;
  gdb_regs[GDB_R7] = regs->r7;
  gdb_regs[GDB_R8] = regs->r8;
  gdb_regs[GDB_R9] = regs->r9;
  gdb_regs[GDB_R10] = regs->r10;
  gdb_regs[GDB_FP] = regs->r11;
  gdb_regs[GDB_IP] = regs->r12;
  gdb_regs[GDB_SPT] = regs->sp;
  gdb_regs[GDB_LR] = regs->lr;
  gdb_regs[GDB_PC] = regs->pc;
  gdb_regs[GDB_CPSR] = regs->psr;

}
;

void gdb_put_register(unsigned long *gdb_regs) {
  regs->r0 = gdb_regs[GDB_R0];
  regs->r1 = gdb_regs[GDB_R1];
  regs->r2 = gdb_regs[GDB_R2];
  regs->r3 = gdb_regs[GDB_R3];

  regs->r4 = gdb_regs[GDB_R4];
  regs->r5 = gdb_regs[GDB_R5];
  regs->r6 = gdb_regs[GDB_R6];
  regs->r7 = gdb_regs[GDB_R7];
  regs->r8 = gdb_regs[GDB_R8];
  regs->r9 = gdb_regs[GDB_R9];
  regs->r10 = gdb_regs[GDB_R10];
  regs->r11 = gdb_regs[GDB_FP];
  regs->r12 = gdb_regs[GDB_IP];
  regs->sp = gdb_regs[GDB_SPT];
  regs->lr = gdb_regs[GDB_LR];
  regs->pc = gdb_regs[GDB_PC];
  regs->psr = gdb_regs[GDB_CPSR];

}

/* It will be called during process_packet */
int gdb_arch_handle_exception(char *remcom_in_buffer, char *remcom_out_buffer) {
  (void) remcom_out_buffer;

  unsigned long addr, curins;
  char *ptr;

  /*clear single step*/
  if (step_addr) {
    gdb_remove_sw_break(step_addr);
    step_addr = 0;
  }

  switch (remcom_in_buffer[0]) {
  case 'D':
  case 'k':
  case 'c':
    /*
     * If this was a compiled breakpoint, we need to move
     * to the next instruction or we will breakpoint
     * over and over again
     */
    ptr = &remcom_in_buffer[1];
    if (gdb_hex2long(&ptr, &addr))
      regs->pc = addr;
    else if (compiled_break == 1)
      regs->pc += 4;
    compiled_break = 0;
    return 0;

  case 's':
    ptr = &remcom_in_buffer[1];
    if (gdb_hex2long(&ptr, &addr))
      regs->pc = addr;

    curins = (unsigned long) *(unsigned short*) (regs->pc);
    curins |= (unsigned long) *((unsigned short*) (regs->pc) + 1) << 16;

    //curins = *(unsigned long*)(regs->pc);
    if (ins_will_execute(curins))
      //Decode instruction to decide what the next pc will be
      step_addr = target_ins((unsigned long*) regs->pc, curins);
    else
      step_addr = regs->pc + 4;

#ifdef RT_GDB_DEBUG
            rt_kprintf("\n next will be %x \n",step_addr);
#endif
    gdb_set_sw_break(step_addr);

    if (compiled_break == 1)
      regs->pc += 4;
    compiled_break = 0;
    return 0;
  }

  return -1;

}

/* flush icache to let the sw breakpoint working */
void gdb_flush_icache_range(unsigned long start, unsigned long end) {
  (void) start;
  (void) end;
#ifdef RT_GDB_ICACHE
    extern void mmu_invalidate_icache();
    mmu_invalidate_icache();  //for arm,wo can only invalidate it
#endif
}

/* register a hook in undef*/
int gdb_undef_hook(void *regs) {
  unsigned long val_pc;
  Gdb_SavedRegisters *tmp_reg = (Gdb_SavedRegisters*) regs;
  unsigned short *tmp_pc = (unsigned short*) tmp_reg->pc;

  val_pc = (unsigned long) *tmp_pc;
  val_pc |= (unsigned long) *++tmp_pc << 16;

  /* it is a compiled break */
  if (val_pc == GDB_COMPILED_BREAK) {
    compiled_break = 1;
    gdb_handle_exception(SIGTRAP, regs);
    return 1;

  }
  /* it is a sw break */
  else if (val_pc == GDB_BREAKINST) {
    gdb_handle_exception(SIGTRAP, regs);
    return 1;
  }
  /*or we just go */
  return 0;
}

static unsigned long gdb_arch_regs[GDB_MAX_REGS];
static int ins_will_execute(unsigned long ins) {
  unsigned long psr = regs->psr;  // condition codes
  int res = 0;
  switch ((ins & 0xF0000000) >> 28) {
  case 0x0: // EQ
    res = (psr & PS_Z) != 0;
    break;
  case 0x1: // NE
    res = (psr & PS_Z) == 0;
    break;
  case 0x2: // CS
    res = (psr & PS_C) != 0;
    break;
  case 0x3: // CC
    res = (psr & PS_C) == 0;
    break;
  case 0x4: // MI
    res = (psr & PS_N) != 0;
    break;
  case 0x5: // PL
    res = (psr & PS_N) == 0;
    break;
  case 0x6: // VS
    res = (psr & PS_V) != 0;
    break;
  case 0x7: // VC
    res = (psr & PS_V) == 0;
    break;
  case 0x8: // HI
    res = ((psr & PS_C) != 0) && ((psr & PS_Z) == 0);
    break;
  case 0x9: // LS
    res = ((psr & PS_C) == 0) || ((psr & PS_Z) != 0);
    break;
  case 0xA: // GE
    res = ((psr & (PS_N | PS_V)) == (PS_N | PS_V))
        || ((psr & (PS_N | PS_V)) == 0);
    break;
  case 0xB: // LT
    res = ((psr & (PS_N | PS_V)) == PS_N) || ((psr & (PS_N | PS_V)) == PS_V);
    break;
  case 0xC: // GT
    res = ((psr & (PS_N | PS_V)) == (PS_N | PS_V))
        || ((psr & (PS_N | PS_V)) == 0);
    res = ((psr & PS_Z) == 0) && res;
    break;
  case 0xD: // LE
    res = ((psr & (PS_N | PS_V)) == PS_N) || ((psr & (PS_N | PS_V)) == PS_V);
    res = ((psr & PS_Z) == PS_Z) || res;
    break;
  case 0xE: // AL
    res = 1;
    break;
  case 0xF: // NV
    if (((ins & 0x0E000000) >> 24) == 0xA)
      res = 1;
    else
      res = 0;
    break;
  }
  return res;
}

static unsigned long RmShifted(int shift) {
  unsigned long Rm = gdb_arch_regs[shift & 0x00F];
  int shift_count;
  if ((shift & 0x010) == 0) {
    shift_count = (shift & 0xF80) >> 7;
  } else {
    shift_count = gdb_arch_regs[(shift & 0xF00) >> 8];
  }
  switch ((shift & 0x060) >> 5) {
  case 0x0: // Logical left
    Rm <<= shift_count;
    break;
  case 0x1: // Logical right
    Rm >>= shift_count;
    break;
  case 0x2: // Arithmetic right
    Rm = (unsigned long) ((long) Rm >> shift_count);
    break;
  case 0x3: // Rotate right
    if (shift_count == 0) {
      // Special case, RORx
      Rm >>= 1;
      if (gdb_arch_regs[GDB_CPSR] & PS_C)
        Rm |= 0x80000000;
    } else {
      Rm = (Rm >> shift_count) | (Rm << (32 - shift_count));
    }
    break;
  }
  return Rm;
}

// Decide the next instruction to be executed for a given instruction
static unsigned long target_ins(unsigned long *pc, unsigned long ins) {
  unsigned long new_pc, offset, op2;
  unsigned long Rn;
  unsigned long val_Rn;
  int i, reg_count, c;

  gdb_get_register(gdb_arch_regs);

  switch ((ins & 0x0C000000) >> 26) {
  case 0x0:
    // BX or BLX
    if ((ins & 0x0FFFFFD0) == 0x012FFF10) {
      new_pc = (unsigned long) gdb_arch_regs[ins & 0x0000000F];
      return new_pc;
    }
    // Data processing
    new_pc = (unsigned long) (pc + 1);
    if ((ins & 0x0000F000) == 0x0000F000) {
      // Destination register is PC
      if ((ins & 0x0FBF0000) != 0x010F0000) {
        Rn = (unsigned long) gdb_arch_regs[(ins & 0x000F0000) >> 16];
        if ((ins & 0x000F0000) == 0x000F0000)
          Rn += 8;  // PC prefetch!
        if ((ins & 0x02000000) == 0) {
          op2 = RmShifted(ins & 0x00000FFF);
        } else {
          op2 = ins & 0x000000FF;
          i = (ins & 0x00000F00) >> 8;  // Rotate count
          op2 = (op2 >> (i * 2)) | (op2 << (32 - (i * 2)));
        }
        switch ((ins & 0x01E00000) >> 21) {
        case 0x0: // AND
          new_pc = Rn & op2;
          break;
        case 0x1: // EOR
          new_pc = Rn ^ op2;
          break;
        case 0x2: // SUB
          new_pc = Rn - op2;
          break;
        case 0x3: // RSB
          new_pc = op2 - Rn;
          break;
        case 0x4: // ADD
          new_pc = Rn + op2;
          break;
        case 0x5: // ADC
          c = (gdb_arch_regs[GDB_CPSR] & PS_C) != 0;
          new_pc = Rn + op2 + c;
          break;
        case 0x6: // SBC
          c = (gdb_arch_regs[GDB_CPSR] & PS_C) != 0;
          new_pc = Rn - op2 + c - 1;
          break;
        case 0x7: // RSC
          c = (gdb_arch_regs[GDB_CPSR] & PS_C) != 0;
          new_pc = op2 - Rn + c - 1;
          break;
        case 0x8: // TST
        case 0x9: // TEQ
        case 0xA: // CMP
        case 0xB: // CMN
          break; // PC doesn't change
        case 0xC: // ORR
          new_pc = Rn | op2;
          break;
        case 0xD: // MOV
          new_pc = op2;
          break;
        case 0xE: // BIC
          new_pc = Rn & ~op2;
          break;
        case 0xF: // MVN
          new_pc = ~op2;
          break;
        }
      }
    }
    return new_pc;
  case 0x1:
    if ((ins & 0x02000010) == 0x02000010) {
      // Undefined!
      return (unsigned long) (pc + 1);
    } else {
      if ((ins & 0x00100000) == 0) {
        // STR
        return (unsigned long) (pc + 1);
      } else {
        // LDR
        if ((ins & 0x0000F000) != 0x0000F000) {
          // Rd not PC
          return (unsigned long) (pc + 1);
        } else {
          Rn = (unsigned long) gdb_arch_regs[(ins & 0x000F0000) >> 16];
          if ((ins & 0x000F0000) == 0x000F0000)
            Rn += 8;  // PC prefetch!
          if (ins & 0x01000000) {
            // Add/subtract offset before
            if ((ins & 0x02000000) == 0) {
              // Immediate offset
              if (ins & 0x00800000) {
                // Add offset
                Rn += (ins & 0x00000FFF);
              } else {
                // Subtract offset
                Rn -= (ins & 0x00000FFF);
              }
            } else {
              // Offset is in a register
              if (ins & 0x00800000) {
                // Add offset
                Rn += RmShifted(ins & 0x00000FFF);
              } else {
                // Subtract offset
                Rn -= RmShifted(ins & 0x00000FFF);
              }
            }
          }
          val_Rn = (unsigned long) *(unsigned short*) Rn;
          val_Rn |= (unsigned long) *((unsigned short*) Rn + 1) << 16;

          return val_Rn;
        }
      }
    }
    return (unsigned long) (pc + 1);
  case 0x2:  // Branch, LDM/STM
    if ((ins & 0x02000000) == 0) {
      // LDM/STM
      if ((ins & 0x00100000) == 0) {
        // STM
        return (unsigned long) (pc + 1);
      } else {
        // LDM
        if ((ins & 0x00008000) == 0) {
          // PC not in list
          return (unsigned long) (pc + 1);
        } else {
          Rn = (unsigned long) gdb_arch_regs[(ins & 0x000F0000) >> 16];
          if ((ins & 0x000F0000) == 0x000F0000)
            Rn += 8;  // PC prefetch!
          offset = ins & 0x0000FFFF;
          reg_count = 0;
          for (i = 0; i < 15; i++) {
            if (offset & (1 << i))
              reg_count++;
          }
          if (ins & 0x00800000) {
            // Add offset
            Rn += reg_count * 4;
          } else {
            // Subtract offset
            Rn -= 4;
          }
          val_Rn = (unsigned long) *(unsigned short*) Rn;
          val_Rn |= (unsigned long) *((unsigned short*) Rn + 1) << 16;

          return val_Rn;
        }
      }
    } else {
      // Branch
      if (ins_will_execute(ins)) {
        offset = (ins & 0x00FFFFFF) << 2;
        if (ins & 0x00800000)
          offset |= 0xFC000000;  // sign extend
        new_pc = (unsigned long) (pc + 2) + offset;
        // If its BLX, make new_pc a thumb address.
        if ((ins & 0xFE000000) == 0xFA000000) {
          if ((ins & 0x01000000) == 0x01000000)
            new_pc |= 2;
          new_pc = MAKE_THUMB_ADDR(new_pc);
        }

        return new_pc;
      } else {
        // Falls through
        return (unsigned long) (pc + 1);
      }
    }
  case 0x3:  // Coprocessor & SWI
    if (((ins & 0x03000000) == 0x03000000) && ins_will_execute(ins))
      (void) 0;
    // SWI
    // TO DO(wzyy2) some problems.
    // extern unsigned long vector_swi;
    // return vector_swi;
    else
      return (unsigned long) (pc + 1);
    // no break
  default:
    // Never reached - but fixes compiler warning.
    return 0;
  }
}

void rt_hw_debugmon_exception(Gdb_SavedRegisters *regs) {
  gdb_undef_hook(regs);
}