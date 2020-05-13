/*
 * CORTEXM GDB support
 * arch-specific portion of GDB stub
 */

#include <gdb_stub.h>

static Gdb_SavedRegisters *regs;
unsigned long single_step_basepri = 0;

void gdb_remove_all_hw_break();
//void gdb_enable_hw_debug();
//void gdb_disable_hw_debug();
int gdb_set_hw_break(unsigned long, int, enum gdb_bptype);
int gdb_remove_hw_break(unsigned long, int, enum gdb_bptype);

static struct hw_breakpoint {
  int enabled;
  unsigned long addr;
} breakinfo[HBP_NUM];

static struct hw_watchpoint {
  int enabled;
  unsigned long addr;
  int len;
  enum gdb_bptype type;
} watchinfo[HWP_NUM];

//The following table defines the memory areas that GDB is allow to touch
static const struct {
  unsigned long start;
  unsigned long end;
} data_access[] = { { 0x20000000, 0x40000000 - 1 }, // On-chip ram
    { 0x60000000, 0xa0000000 - 1 }, // External ram
    { 0x00000000, 0x20000000 - 1 }, // On-chip flash
    { 0x60000000, 0xa0000000 - 1 }, // External flash
    { 0xE0000000, 0x00000000 - 1 }, // cortex-M peripheral
    { 0x40000000, 0x60000000 - 1 }, // mcu peripheral
    };

int gdb_permit_data_access(unsigned long addr, unsigned long count) {
  unsigned char i;

  for (i = 0; i < sizeof(data_access) / sizeof(data_access[0]); i++) {
    if ((addr >= data_access[i].start)
        && (addr + count) <= data_access[i].end) {
      return 0;
    }
  }

  return -1;
}

/*we need to block all pending interrupts by swtting basepri
 * before doing the steo
 */
void gdb_single_step() {
  volatile unsigned long *base;

  //mask all interrupts
  single_step_basepri = regs->basepri;
  regs->basepri = GDB_CORTEXM_PRIORITY_MAX;

  //When MON_EN = 1, this steps the core
  base = (unsigned long*) (GDB_DEBUG_REG_BASE + GDB_DEBUG_REG_DEMCR);
  *base |= GDB_DEBUG_REG_DEMCR_MON_STEP;

  /* Clear any bits set in DFSR*/
  base = (unsigned long*) (GDB_NVIC_REG_BASE + GDB_NVIC_REG_DFSR);
  *base = 0xffffffff;

}

void gdb_clear_single_step() {
  volatile unsigned long *base;

  regs->basepri = single_step_basepri;

  /*clear single step*/
  base = (unsigned long*) (GDB_DEBUG_REG_BASE + GDB_DEBUG_REG_DEMCR);
  *base &= ~GDB_DEBUG_REG_DEMCR_MON_STEP;

  // Clear any bits set in DFSR
  base = (unsigned long*) (GDB_NVIC_REG_BASE + GDB_NVIC_REG_DFSR);
  *base = 0xffffffff;

}

int gdb_set_hw_break(unsigned long addr, int len, enum gdb_bptype bptype) {
  int i;

  if (bptype == BP_HARDWARE_BREAKPOINT) {
    for (i = 0; i < HBP_NUM; i++)
      if (!breakinfo[i].enabled)
        break;
    if (i == HBP_NUM)
      return -1;
    breakinfo[i].addr = addr;
    breakinfo[i].enabled = 1;
  } else if (bptype == BP_WRITE_WATCHPOINT) {
    for (i = 0; i < HWP_NUM; i++)
      if (!watchinfo[i].enabled)
        break;
    if (i == HWP_NUM)
      return -1;
    watchinfo[i].addr = addr;
    watchinfo[i].len = len;
    watchinfo[i].type = BP_WRITE_WATCHPOINT;
    watchinfo[i].enabled = 1;
  } else if (bptype == BP_READ_WATCHPOINT) {
    for (i = 0; i < HWP_NUM; i++)
      if (!watchinfo[i].enabled)
        break;
    if (i == HWP_NUM)
      return -1;
    watchinfo[i].addr = addr;
    watchinfo[i].len = len;
    watchinfo[i].type = BP_READ_WATCHPOINT;
    watchinfo[i].enabled = 1;
  } else if (bptype == BP_ACCESS_WATCHPOINT) {
    for (i = 0; i < HWP_NUM; i++)
      if (!watchinfo[i].enabled)
        break;
    if (i == HWP_NUM)
      return -1;
    watchinfo[i].addr = addr;
    watchinfo[i].len = len;
    watchinfo[i].type = BP_ACCESS_WATCHPOINT;
    watchinfo[i].enabled = 1;
  }

  return 0;
}

int gdb_remove_hw_break(unsigned long addr, int len, enum gdb_bptype bptype) {
  (void) len;

  int i;

  if (bptype == BP_HARDWARE_BREAKPOINT) {
    for (i = 0; i < HBP_NUM; i++)
      if (breakinfo[i].addr == addr && breakinfo[i].enabled)
        break;
    if (i == HBP_NUM)
      return -1;
    breakinfo[i].enabled = 0;

  } else if (bptype == BP_WRITE_WATCHPOINT) {
    for (i = 0; i < HWP_NUM; i++)
      if (watchinfo[i].addr == addr && watchinfo[i].enabled
          && watchinfo[i].type == bptype)
        break;
    if (i == HWP_NUM)
      return -1;
    watchinfo[i].enabled = 0;

  } else if (bptype == BP_READ_WATCHPOINT) {
    for (i = 0; i < HWP_NUM; i++)
      if (watchinfo[i].addr == addr && watchinfo[i].enabled
          && watchinfo[i].type == bptype)
        break;
    if (i == HWP_NUM)
      return -1;
    watchinfo[i].enabled = 0;

  } else if (bptype == BP_ACCESS_WATCHPOINT) {
    for (i = 0; i < HWP_NUM; i++)
      if (watchinfo[i].addr == addr && watchinfo[i].enabled
          && watchinfo[i].type == bptype)
        break;
    if (i == HWP_NUM)
      return -1;
    watchinfo[i].enabled = 0;

  }

  return 0;
}

void gdb_remove_all_hw_break() {
  int i;
  volatile unsigned long *base;

  // Disable hardware break
  for (i = 0; i < HBP_NUM; i++) {
    if (!breakinfo[i].enabled)
      break;
    base = (unsigned long*) (GDB_FPB_REG_BASE + GDB_FPB_REG_COMP + i * 4);
    *base &= ~GDB_FPB_REG_COMP_ENABLE;
  }

  // Disable watchpoint
  for (i = 0; i < HWP_NUM; i++) {
    if (!watchinfo[i].enabled)
      break;
    base = (unsigned long*) (GDB_DWT_REG_BASE + GDB_DWT_REG_FUNCTION + i * 12);
    *base &= ~GDB_DWT_REG_FUNCTION_FUC;
  }

}

void gdb_arch_late() {
  gdb_remove_all_hw_break();
}

void gdb_arch_exit() {
  volatile unsigned long *base;
  char num = 1;
  int i;

  // Install the hardware break
  for (i = 0; i < HBP_NUM; i++) {
    if (breakinfo[i].enabled) {
      base = (unsigned long*) (GDB_FPB_REG_BASE + GDB_FPB_REG_COMP + i * 4);

      *base = GDB_FPB_REG_COMP_ADDR & ((unsigned long) (breakinfo[i].addr));

      if (breakinfo[i].addr & 2)
        *base |= (1UL << 31); //set BKPT on upper halfword
      else
        *base |= (1UL << 30); //set BKPT on lower halfword,

      *base |= GDB_FPB_REG_COMP_ENABLE;
    }
  }

  // Install the watchpoint
  for (i = 0; i < HWP_NUM; i++) {
    if (watchinfo[i].enabled) {
      base = (unsigned long*) (GDB_DWT_REG_BASE + GDB_DWT_REG_COMP + i * 12);
      *base = watchinfo[i].addr;

      base = (unsigned long*) (GDB_DWT_REG_BASE + GDB_DWT_REG_MASK + i * 12);
      while (watchinfo[i].len >> num) {
        num++;
      }
      *base = num - 1; //DWT matching is performed as:(ADDR & (~0 << MASK)) == COMP

      base =
          (unsigned long*) (GDB_DWT_REG_BASE + GDB_DWT_REG_FUNCTION + i * 12);

      if (watchinfo[i].type == BP_WRITE_WATCHPOINT)
        *base = (*base & ~GDB_DWT_REG_FUNCTION_FUC) + 0x05;
      else if (watchinfo[i].type == BP_READ_WATCHPOINT)
        *base = (*base & ~GDB_DWT_REG_FUNCTION_FUC) + 0x06;
      else if (watchinfo[i].type == BP_ACCESS_WATCHPOINT)
        *base = (*base & ~GDB_DWT_REG_FUNCTION_FUC) + 0x07;

    }
  }
}

