#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    printf("=== WASI File System Test ===\n");

    // Test 1: Using fopen/fread
    printf("\nTest 1: fopen/fread\n");
    FILE *file = fopen("assets/test.txt", "r");
    if (file) {
        printf("  SUCCESS: fopen succeeded\n");

        // Get file descriptor from FILE*
        int file_fd = fileno(file);
        printf("  File descriptor from fileno: %d\n", file_fd);

        // Try fgetc first
        int c = fgetc(file);
        if (c != EOF) {
            printf("  fgetc returned: '%c' (0x%02x)\n", c, c);
            ungetc(c, file);
        } else {
            printf("  fgetc returned EOF\n");
        }

        char buffer[256];
        size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, file);
        buffer[bytes_read] = '\0';

        printf("  Read %zu bytes: %s\n", bytes_read, buffer);

        // Check if we're at EOF
        if (feof(file)) {
            printf("  At EOF\n");
        }
        if (ferror(file)) {
            printf("  File error occurred\n");
        }

        fclose(file);
    } else {
        printf("  FAILED: fopen failed with errno=%d (%s)\n", errno, strerror(errno));
    }

    // Test 2: Using open/read (POSIX)
    printf("\nTest 2: open/read\n");
    int fd = open("assets/test.txt", O_RDONLY);
    if (fd >= 0) {
        printf("  SUCCESS: open succeeded, fd=%d\n", fd);

        // Get file size
        off_t file_size = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);
        printf("  File size via lseek: %lld bytes\n", (long long)file_size);

        char buffer[256];
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read >= 0) {
            buffer[bytes_read] = '\0';
            printf("  Read %zd bytes: %s\n", bytes_read, buffer);

            // Try reading again to see if position advanced
            ssize_t bytes_read2 = read(fd, buffer, sizeof(buffer) - 1);
            printf("  Second read returned %zd bytes\n", bytes_read2);
        } else {
            printf("  FAILED: read failed with errno=%d (%s)\n", errno, strerror(errno));
        }

        close(fd);
    } else {
        printf("  FAILED: open failed with errno=%d (%s)\n", errno, strerror(errno));
    }

    // Test 3: Check file existence with stat
    printf("\nTest 3: stat\n");
    struct stat st;
    if (stat("assets/test.txt", &st) == 0) {
        printf("  SUCCESS: stat succeeded\n");
        printf("  File size: %lld bytes\n", (long long)st.st_size);
        printf("  File mode: 0%o\n", st.st_mode);
        printf("  Is regular file: %s\n", S_ISREG(st.st_mode) ? "yes" : "no");
    } else {
        printf("  FAILED: stat failed with errno=%d (%s)\n", errno, strerror(errno));
    }

    // Test 4: Try different path variations
    printf("\nTest 4: Path variations\n");
    const char *paths[] = {
        "assets/test.txt",
        "./assets/test.txt",
        "/assets/test.txt",
        "test.txt",
        NULL
    };

    for (int i = 0; paths[i] != NULL; i++) {
        FILE *f = fopen(paths[i], "r");
        printf("  Path '%s': %s\n", paths[i], f ? "SUCCESS" : "FAILED");
        if (f) fclose(f);
    }

    printf("\n=== Test Complete ===\n");

    return 0;
}
