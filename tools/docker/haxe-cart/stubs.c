// Stubs for libc/POSIX bits wasi-libc lacks, needed to link the hashlink
// runtime (gc.c + std/*). None of these should ever be called by a cart.

#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <execinfo.h>
#include <pthread.h>

// WAMR's fast interpreter has no wasm exception-handling proposal, so there
// is no real setjmp/longjmp. The hl GC uses setjmp only to snapshot callee
// registers before scanning the C stack - on wasm all locals live in linear
// memory and get scanned anyway, so a zeroed buffer is fine. hl_trap (haxe
// try/catch) relies on longjmp, which is why haxe carts cannot throw.
int setjmp(jmp_buf env) {
  memset(env, 0, sizeof(jmp_buf));
  return 0;
}
void longjmp(jmp_buf env, int val) {
  (void)env;
  (void)val;
  abort();
}
int sigsetjmp(sigjmp_buf env, int savemask) {
  (void)savemask;
  return setjmp(env);
}
void siglongjmp(sigjmp_buf env, int val) { longjmp(env, val); }

// terminal control (Sys.getChar etc) - no TTY in a cart
int tcgetattr(int fd, struct termios *t) {
  (void)fd;
  (void)t;
  return -1;
}
int tcsetattr(int fd, int a, const struct termios *t) {
  (void)fd;
  (void)a;
  (void)t;
  return -1;
}
void cfmakeraw(struct termios *t) { (void)t; }

// misc POSIX used by libhl std
int pthread_setname_np(pthread_t t, const char *n) {
  (void)t;
  (void)n;
  return 0;
}
int backtrace(void **buffer, int size) {
  (void)buffer;
  (void)size;
  return 0;
}
char **backtrace_symbols(void *const *buffer, int size) {
  (void)buffer;
  (void)size;
  return 0;
}
int getpid(void) { return 1; }
int system(const char *cmd) {
  (void)cmd;
  return -1;
}
long sysconf(int name) {
  (void)name;
  return -1;
}
