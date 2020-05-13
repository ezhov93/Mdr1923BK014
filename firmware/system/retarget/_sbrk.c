#include <sys/types.h>
#include <errno.h>

caddr_t _sbrk(int incr);

// The definitions used here should be kept in sync with the
// stack definitions in the linker script.

caddr_t _sbrk(int incr) {
  extern char __HeapBase; // Defined by the linker.
  extern char __HeapLimit; // Defined by the linker.

  static char *current_heap_end;
  char *current_block_address;

  if (current_heap_end == 0) {
    current_heap_end = &__HeapBase;
  }

  current_block_address = current_heap_end;

  incr = (incr + 3) & (~3); // align value to 4
  if (current_heap_end + incr > &__HeapLimit) {
#if 0
      extern void abort (void);
      _write (1, "_sbrk: Heap and stack collision\n", 32);
      abort ();
#else
    // Heap has overflowed
    errno = ENOMEM;
    return (caddr_t) -1;
#endif
  }

  current_heap_end += incr;

  return (caddr_t) current_block_address;
}

// ----------------------------------------------------------------------------

