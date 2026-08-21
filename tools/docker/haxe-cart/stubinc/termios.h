#ifndef _STUB_TERMIOS_H
#define _STUB_TERMIOS_H
struct termios { unsigned int c_lflag; };
#define ICANON 1
#define ECHO 2
#define TCSANOW 0
int tcgetattr(int fd, struct termios *t);
int tcsetattr(int fd, int a, const struct termios *t);
void cfmakeraw(struct termios *t);
#endif
