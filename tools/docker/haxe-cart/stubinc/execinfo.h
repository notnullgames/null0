#ifndef _STUB_EXECINFO_H
#define _STUB_EXECINFO_H
int backtrace(void **buffer, int size);
char **backtrace_symbols(void *const *buffer, int size);
#endif
