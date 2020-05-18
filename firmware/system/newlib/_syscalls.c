int errno;
void *__dso_handle __attribute__((weak));

#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>
//#include <sys/types.h>
#include <limits.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>

void __initialize_args(int *p_argc, char ***p_argv);

// This is the standard default implementation for the routine to
// process args. It returns a single empty arg.
// For semihosting applications, this is redefined to get the real
// args from the debugger. You can also use it if you decide to keep
// some args in a non-volatile memory.

void __attribute__((weak)) __initialize_args(int *p_argc, char ***p_argv) {
  // By the time we reach this, the data and bss should have been initialised.

  // The strings pointed to by the argv array shall be modifiable by the
  // program, and retain their last-stored values between program startup
  // and program termination. (static, no const)
  static char name[] = "";

  // The string pointed to by argv[0] represents the program name;
  // argv[0][0] shall be the null character if the program name is not
  // available from the host environment. argv[argc] shall be a null pointer.
  // (static, no const)
  static char *argv[2] = {name, NULL};

  *p_argc = 1;
  *p_argv = &argv[0];
  return;
}

// These functions are defined here to avoid linker errors in freestanding
// applications. They might be called in some error cases from library
// code.
//
// If you detect other functions to be needed, just let us know
// and we'll add them.

__attribute__((weak)) int raise(int sig __attribute__((unused))) {
  errno = ENOSYS;
  return -1;
}

int kill(pid_t pid, int sig);

__attribute__((weak)) int kill(pid_t pid __attribute__((unused)),
                               int sig __attribute__((unused))) {
  errno = ENOSYS;
  return -1;
}
