#ifndef _STUB_SETJMP_H
#define _STUB_SETJMP_H
// wasi-libc's setjmp.h hard-errors without the wasm EH proposal; shadow it.
// See stubs.c for why this is safe here.
typedef struct { void *__regs[8]; } __stub_jmp_buf[1];
typedef __stub_jmp_buf jmp_buf;
typedef __stub_jmp_buf sigjmp_buf;
int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);
int sigsetjmp(sigjmp_buf env, int savemask);
void siglongjmp(sigjmp_buf env, int val);
#endif
