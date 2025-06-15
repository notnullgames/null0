#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
    printf("=== Simple WASI FD Test ===\n");

    // Test 1: Simple fopen/fgetc
    printf("\nTest 1: fopen + fgetc\n");
    FILE *f = fopen("assets/hello.txt", "r");
    if (f) {
        printf("  fopen SUCCESS\n");

        int c = fgetc(f);
        if (c != EOF) {
            printf("  First char: '%c' (0x%02x)\n", c, c);
        } else {
            printf("  fgetc returned EOF, errno=%d\n", errno);
        }

        fclose(f);
    } else {
        printf("  fopen FAILED: errno=%d (%s)\n", errno, strerror(errno));
    }

    // Test 2: Direct open/read with small buffer
    printf("\nTest 2: open + read (small buffer)\n");
    int fd = open("assets/hello.txt", O_RDONLY);
    if (fd >= 0) {
        printf("  open SUCCESS, fd=%d\n", fd);

        char buf[10];
        ssize_t n = read(fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("  Read %zd bytes: '%s'\n", n, buf);
        } else if (n == 0) {
            printf("  read returned 0 (EOF)\n");
        } else {
            printf("  read FAILED: errno=%d (%s)\n", errno, strerror(errno));
        }

        close(fd);
    } else {
        printf("  open FAILED: errno=%d (%s)\n", errno, strerror(errno));
    }

    // Test 3: Check if we can read from fd 3 (should be prestat)
    printf("\nTest 3: Check fd 3 (prestat)\n");
    char buf[256];
    ssize_t n = read(3, buf, sizeof(buf));
    printf("  read(3, buf, %zu) returned %zd\n", sizeof(buf), n);
    if (n < 0) {
        printf("  errno=%d (%s)\n", errno, strerror(errno));
    }

    printf("\n=== Test Complete ===\n");
    return 0;
}
