#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <physfs.h>

// WASI Error Codes
#define WASI_ERRNO_SUCCESS 0
#define WASI_ERRNO_2BIG 1
#define WASI_ERRNO_ACCES 2
#define WASI_ERRNO_ADDRINUSE 3
#define WASI_ERRNO_ADDRNOTAVAIL 4
#define WASI_ERRNO_AFNOSUPPORT 5
#define WASI_ERRNO_AGAIN 6
#define WASI_ERRNO_ALREADY 7
#define WASI_ERRNO_BADF 8
#define WASI_ERRNO_BADMSG 9
#define WASI_ERRNO_BUSY 10
#define WASI_ERRNO_CANCELED 11
#define WASI_ERRNO_CHILD 12
#define WASI_ERRNO_CONNABORTED 13
#define WASI_ERRNO_CONNREFUSED 14
#define WASI_ERRNO_CONNRESET 15
#define WASI_ERRNO_DEADLK 16
#define WASI_ERRNO_DESTADDRREQ 17
#define WASI_ERRNO_DOM 18
#define WASI_ERRNO_DQUOT 19
#define WASI_ERRNO_EXIST 20
#define WASI_ERRNO_FAULT 21
#define WASI_ERRNO_FBIG 22
#define WASI_ERRNO_HOSTUNREACH 23
#define WASI_ERRNO_IDRM 24
#define WASI_ERRNO_ILSEQ 25
#define WASI_ERRNO_INPROGRESS 26
#define WASI_ERRNO_INTR 27
#define WASI_ERRNO_INVAL 28
#define WASI_ERRNO_IO 29
#define WASI_ERRNO_ISCONN 30
#define WASI_ERRNO_ISDIR 31
#define WASI_ERRNO_LOOP 32
#define WASI_ERRNO_MFILE 33
#define WASI_ERRNO_MLINK 34
#define WASI_ERRNO_MSGSIZE 35
#define WASI_ERRNO_MULTIHOP 36
#define WASI_ERRNO_NAMETOOLONG 37
#define WASI_ERRNO_NETDOWN 38
#define WASI_ERRNO_NETRESET 39
#define WASI_ERRNO_NETUNREACH 40
#define WASI_ERRNO_NFILE 41
#define WASI_ERRNO_NOBUFS 42
#define WASI_ERRNO_NODEV 43
#define WASI_ERRNO_NOENT 44
#define WASI_ERRNO_NOEXEC 45
#define WASI_ERRNO_NOLCK 46
#define WASI_ERRNO_NOLINK 47
#define WASI_ERRNO_NOMEM 48
#define WASI_ERRNO_NOMSG 49
#define WASI_ERRNO_NOPROTOOPT 50
#define WASI_ERRNO_NOSPC 51
#define WASI_ERRNO_NOSYS 52
#define WASI_ERRNO_NOTCONN 53
#define WASI_ERRNO_NOTDIR 54
#define WASI_ERRNO_NOTEMPTY 55
#define WASI_ERRNO_NOTRECOVERABLE 56
#define WASI_ERRNO_NOTSOCK 57
#define WASI_ERRNO_NOTSUP 58
#define WASI_ERRNO_NOTTY 59
#define WASI_ERRNO_NXIO 60
#define WASI_ERRNO_OVERFLOW 61
#define WASI_ERRNO_OWNERDEAD 62
#define WASI_ERRNO_PERM 63
#define WASI_ERRNO_PIPE 64
#define WASI_ERRNO_PROTO 65
#define WASI_ERRNO_PROTONOSUPPORT 66
#define WASI_ERRNO_PROTOTYPE 67
#define WASI_ERRNO_RANGE 68
#define WASI_ERRNO_ROFS 69
#define WASI_ERRNO_SPIPE 70
#define WASI_ERRNO_SRCH 71
#define WASI_ERRNO_STALE 72
#define WASI_ERRNO_TIMEDOUT 73
#define WASI_ERRNO_TXTBSY 74
#define WASI_ERRNO_XDEV 75

// WASI Clock IDs
#define WASI_CLOCKID_REALTIME 0
#define WASI_CLOCKID_MONOTONIC 1
#define WASI_CLOCKID_PROCESS_CPUTIME_ID 2
#define WASI_CLOCKID_THREAD_CPUTIME_ID 3

// WASI File Types
#define WASI_FILETYPE_UNKNOWN 0
#define WASI_FILETYPE_BLOCK_DEVICE 1
#define WASI_FILETYPE_CHARACTER_DEVICE 2
#define WASI_FILETYPE_DIRECTORY 3
#define WASI_FILETYPE_REGULAR_FILE 4
#define WASI_FILETYPE_SOCKET_DGRAM 5
#define WASI_FILETYPE_SOCKET_STREAM 6
#define WASI_FILETYPE_SYMBOLIC_LINK 7

// WASI Whence values
#define WASI_WHENCE_SET 0
#define WASI_WHENCE_CUR 1
#define WASI_WHENCE_END 2

// WASI Open Flags
#define WASI_OFLAGS_CREAT 0x0001
#define WASI_OFLAGS_DIRECTORY 0x0002
#define WASI_OFLAGS_EXCL 0x0004
#define WASI_OFLAGS_TRUNC 0x0008

// WASI FD Flags
#define WASI_FDFLAGS_APPEND 0x0001
#define WASI_FDFLAGS_DSYNC 0x0002
#define WASI_FDFLAGS_NONBLOCK 0x0004
#define WASI_FDFLAGS_RSYNC 0x0008
#define WASI_FDFLAGS_SYNC 0x0010

// WASI IOVec structure
typedef struct {
    uint32_t buf_ptr;
    uint32_t buf_len;
} wasi_iovec_t;

// WASI FDStat structure
typedef struct {
    uint8_t fs_filetype;
    uint16_t fs_flags;
    uint64_t fs_rights_base;
    uint64_t fs_rights_inheriting;
} wasi_fdstat_t;

// WASI Prestat structure
typedef struct {
    uint8_t pr_type;
    uint32_t pr_name_len;
} wasi_prestat_t;

// WASI Filestat structure
typedef struct {
    uint64_t dev;
    uint64_t ino;
    uint8_t filetype;
    uint64_t nlink;
    uint64_t size;
    uint64_t atim;
    uint64_t mtim;
    uint64_t ctim;
} wasi_filestat_t;

// File descriptor to PhysicsFS handle mapping
typedef struct {
    PHYSFS_File* handle;
    char* path;
    int flags;
    int is_directory;
} physfs_fd_mapping_t;

#define MAX_FDS 1024
static physfs_fd_mapping_t fd_table[MAX_FDS] = {0};
static int next_fd = 10;

// Pre-opened directories
static const char* preopen_dirs[] = { "/" };
static const int num_preopen_dirs = 1;

// Initialize FD table
static void init_fd_table() {
    memset(fd_table, 0, sizeof(fd_table));

    // Pre-opened directory
    fd_table[3].path = strdup("/");
    fd_table[3].is_directory = 1;
}

// Allocate a new file descriptor
static int allocate_fd(PHYSFS_File* handle, const char* path, int flags) {
    for (int fd = next_fd; fd < MAX_FDS; fd++) {
        if (!fd_table[fd].handle && !fd_table[fd].is_directory) {
            fd_table[fd].handle = handle;
            fd_table[fd].path = strdup(path);
            fd_table[fd].flags = flags;
            fd_table[fd].is_directory = 0;
            return fd;
        }
    }
    return -1;
}

// Free a file descriptor
static void free_fd(int fd) {
    if (fd >= 0 && fd < MAX_FDS) {
        if (fd_table[fd].path) {
            free(fd_table[fd].path);
            fd_table[fd].path = NULL;
        }
        fd_table[fd].handle = NULL;
        fd_table[fd].flags = 0;
        fd_table[fd].is_directory = 0;
    }
}

// Convert PhysicsFS error to WASI errno
static int physfs_to_wasi_errno() {
    PHYSFS_ErrorCode err = PHYSFS_getLastErrorCode();
    switch (err) {
        case PHYSFS_ERR_OK: return WASI_ERRNO_SUCCESS;
        case PHYSFS_ERR_NOT_FOUND: return WASI_ERRNO_NOENT;
        case PHYSFS_ERR_NOT_A_FILE: return WASI_ERRNO_ISDIR;
        case PHYSFS_ERR_READ_ONLY: return WASI_ERRNO_ROFS;
        case PHYSFS_ERR_PERMISSION: return WASI_ERRNO_ACCES;
        case PHYSFS_ERR_NO_SPACE: return WASI_ERRNO_NOSPC;
        case PHYSFS_ERR_OUT_OF_MEMORY: return WASI_ERRNO_NOMEM;
        case PHYSFS_ERR_BAD_FILENAME: return WASI_ERRNO_INVAL;
        default: return WASI_ERRNO_IO;
    }
}

// Convert errno to WASI errno
static int errno_to_wasi(int err) {
    switch (err) {
        case 0: return WASI_ERRNO_SUCCESS;
        case EACCES: return WASI_ERRNO_ACCES;
        case EBADF: return WASI_ERRNO_BADF;
        case EEXIST: return WASI_ERRNO_EXIST;
        case EINVAL: return WASI_ERRNO_INVAL;
        case EIO: return WASI_ERRNO_IO;
        case EISDIR: return WASI_ERRNO_ISDIR;
        case ENOENT: return WASI_ERRNO_NOENT;
        case ENOTDIR: return WASI_ERRNO_NOTDIR;
        case ENOMEM: return WASI_ERRNO_NOMEM;
        case ENOSPC: return WASI_ERRNO_NOSPC;
        case ENOSYS: return WASI_ERRNO_NOSYS;
        case EPERM: return WASI_ERRNO_PERM;
        default: return WASI_ERRNO_IO;
    }
}

// Get memory pointer from WASM instance
static void* get_wasm_memory_ptr(uint32_t offset) {
    return wasm_runtime_addr_app_to_native(module_inst, offset);
}

// ========== FILE DESCRIPTOR OPERATIONS ==========

WASI_FUNCTION(int, fd_close, (int fd), {
    if (fd < 0 || fd >= MAX_FDS) {
        return WASI_ERRNO_BADF;
    }

    // Don't close stdin/stdout/stderr or pre-opened directories
    if (fd <= 2 || (fd >= 3 && fd < 3 + num_preopen_dirs && fd_table[fd].is_directory)) {
        return WASI_ERRNO_SUCCESS;
    }

    if (fd_table[fd].handle) {
        if (!PHYSFS_close(fd_table[fd].handle)) {
            return physfs_to_wasi_errno();
        }
    }

    free_fd(fd);
    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, fd_fdstat_get, (int fd, uint32_t statPtr), {
    if (fd < 0 || fd >= MAX_FDS) {
        return WASI_ERRNO_BADF;
    }

    wasi_fdstat_t* stat = (wasi_fdstat_t*)get_wasm_memory_ptr(statPtr);
    if (!stat) {
        return WASI_ERRNO_FAULT;
    }

    // Standard I/O
    if (fd <= 2) {
        stat->fs_filetype = WASI_FILETYPE_CHARACTER_DEVICE;
        stat->fs_flags = 0;
        stat->fs_rights_base = 0xFFFFFFFFFFFFFFFF;
        stat->fs_rights_inheriting = 0;
        return WASI_ERRNO_SUCCESS;
    }

    // Directories
    if (fd_table[fd].is_directory) {
        stat->fs_filetype = WASI_FILETYPE_DIRECTORY;
        stat->fs_flags = 0;
        stat->fs_rights_base = 0xFFFFFFFFFFFFFFFF;
        stat->fs_rights_inheriting = 0xFFFFFFFFFFFFFFFF;
        return WASI_ERRNO_SUCCESS;
    }

    // Regular files
    if (fd_table[fd].handle) {
        stat->fs_filetype = WASI_FILETYPE_REGULAR_FILE;
        stat->fs_flags = fd_table[fd].flags;
        stat->fs_rights_base = 0xFFFFFFFFFFFFFFFF;
        stat->fs_rights_inheriting = 0xFFFFFFFFFFFFFFFF;
        return WASI_ERRNO_SUCCESS;
    }

    return WASI_ERRNO_BADF;
})

WASI_FUNCTION(int, fd_fdstat_set_flags, (int fd, int fdflags), {
    if (fd < 0 || fd >= MAX_FDS) {
        return WASI_ERRNO_BADF;
    }

    if (fd_table[fd].handle || fd_table[fd].is_directory) {
        fd_table[fd].flags = fdflags;
        return WASI_ERRNO_SUCCESS;
    }

    return WASI_ERRNO_BADF;
})

WASI_FUNCTION(int, fd_prestat_get, (int fd, uint32_t prestatPtr), {
    if (fd < 3 || fd >= 3 + num_preopen_dirs) {
        return WASI_ERRNO_BADF;
    }

    wasi_prestat_t* prestat = (wasi_prestat_t*)get_wasm_memory_ptr(prestatPtr);
    if (!prestat) {
        return WASI_ERRNO_FAULT;
    }

    prestat->pr_type = 0;
    prestat->pr_name_len = strlen(preopen_dirs[fd - 3]);
    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, fd_prestat_dir_name, (int fd, uint32_t namePtr, int nameLen), {
    if (fd < 3 || fd >= 3 + num_preopen_dirs) {
        return WASI_ERRNO_BADF;
    }

    char* name = (char*)get_wasm_memory_ptr(namePtr);
    if (!name) {
        return WASI_ERRNO_FAULT;
    }

    const char* dir_name = preopen_dirs[fd - 3];
    int actual_len = strlen(dir_name);

    if (nameLen < actual_len) {
        return WASI_ERRNO_NAMETOOLONG;
    }

    memcpy(name, dir_name, actual_len);
    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, fd_read, (int fd, uint32_t iovsPtr, int iovsLen, uint32_t nreadPtr), {
    if (fd < 0 || fd >= MAX_FDS) {
        return WASI_ERRNO_BADF;
    }

    wasi_iovec_t* iovs = (wasi_iovec_t*)get_wasm_memory_ptr(iovsPtr);
    uint32_t* nread = (uint32_t*)get_wasm_memory_ptr(nreadPtr);

    if (!iovs || !nread) {
        return WASI_ERRNO_FAULT;
    }

    *nread = 0;

    // stdin
    if (fd == 0) {
        for (int i = 0; i < iovsLen; i++) {
            char* buf = (char*)get_wasm_memory_ptr(iovs[i].buf_ptr);
            if (!buf) return WASI_ERRNO_FAULT;

            ssize_t bytes_read = read(0, buf, iovs[i].buf_len);
            if (bytes_read < 0) return errno_to_wasi(errno);

            *nread += bytes_read;
            if (bytes_read < iovs[i].buf_len) break;
        }
        return WASI_ERRNO_SUCCESS;
    }

    // PhysicsFS files
    if (!fd_table[fd].handle) {
        return WASI_ERRNO_BADF;
    }

    for (int i = 0; i < iovsLen; i++) {
        char* buf = (char*)get_wasm_memory_ptr(iovs[i].buf_ptr);
        if (!buf) return WASI_ERRNO_FAULT;

        PHYSFS_sint64 bytes_read = PHYSFS_readBytes(fd_table[fd].handle, buf, iovs[i].buf_len);
        if (bytes_read < 0) {
            return physfs_to_wasi_errno();
        }

        *nread += bytes_read;
        if (bytes_read < iovs[i].buf_len) break;
    }

    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, fd_seek, (int fd, int64_t offset, int whence, uint32_t newoffsetPtr), {
    if (fd < 0 || fd >= MAX_FDS || !fd_table[fd].handle) {
        return WASI_ERRNO_BADF;
    }

    uint64_t* newoffset = (uint64_t*)get_wasm_memory_ptr(newoffsetPtr);
    if (!newoffset) {
        return WASI_ERRNO_FAULT;
    }

    PHYSFS_sint64 file_size = PHYSFS_fileLength(fd_table[fd].handle);
    PHYSFS_sint64 new_pos;

    switch (whence) {
        case WASI_WHENCE_SET:
            new_pos = offset;
            break;
        case WASI_WHENCE_CUR:
            new_pos = PHYSFS_tell(fd_table[fd].handle) + offset;
            break;
        case WASI_WHENCE_END:
            new_pos = file_size + offset;
            break;
        default:
            return WASI_ERRNO_INVAL;
    }

    if (!PHYSFS_seek(fd_table[fd].handle, new_pos)) {
        return physfs_to_wasi_errno();
    }

    *newoffset = PHYSFS_tell(fd_table[fd].handle);
    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, fd_write, (int fd, uint32_t iovsPtr, int iovsLen, uint32_t nwrittenPtr), {
    if (fd < 0 || fd >= MAX_FDS) {
        return WASI_ERRNO_BADF;
    }

    wasi_iovec_t* iovs = (wasi_iovec_t*)get_wasm_memory_ptr(iovsPtr);
    uint32_t* nwritten = (uint32_t*)get_wasm_memory_ptr(nwrittenPtr);

    if (!iovs || !nwritten) {
        return WASI_ERRNO_FAULT;
    }

    *nwritten = 0;

    // stdout/stderr
    if (fd == 1 || fd == 2) {
        for (int i = 0; i < iovsLen; i++) {
            char* buf = (char*)get_wasm_memory_ptr(iovs[i].buf_ptr);
            if (!buf) return WASI_ERRNO_FAULT;

            ssize_t bytes_written = write(fd, buf, iovs[i].buf_len);
            if (bytes_written < 0) return errno_to_wasi(errno);

            *nwritten += bytes_written;
            if (bytes_written < iovs[i].buf_len) break;
        }
        return WASI_ERRNO_SUCCESS;
    }

    // PhysicsFS files
    if (!fd_table[fd].handle) {
        return WASI_ERRNO_BADF;
    }

    for (int i = 0; i < iovsLen; i++) {
        char* buf = (char*)get_wasm_memory_ptr(iovs[i].buf_ptr);
        if (!buf) return WASI_ERRNO_FAULT;

        PHYSFS_sint64 bytes_written = PHYSFS_writeBytes(fd_table[fd].handle, buf, iovs[i].buf_len);
        if (bytes_written < 0) {
            return physfs_to_wasi_errno();
        }

        *nwritten += bytes_written;
        if (bytes_written < iovs[i].buf_len) break;
    }

    return WASI_ERRNO_SUCCESS;
})

// ========== PATH OPERATIONS ==========

WASI_FUNCTION(int, path_open, (int dirfd, int dirflags, uint32_t pathPtr, int pathLen, int oflags, uint64_t fs_rights_base, uint64_t fs_rights_inheriting, int fdflags, uint32_t newfdPtr), {
    char* path = (char*)get_wasm_memory_ptr(pathPtr);
    uint32_t* newfd = (uint32_t*)get_wasm_memory_ptr(newfdPtr);

    if (!path || !newfd) {
        return WASI_ERRNO_FAULT;
    }

    char path_buf[pathLen + 1];
    memcpy(path_buf, path, pathLen);
    path_buf[pathLen] = '\0';

    // Check if directory
    PHYSFS_Stat stat;
    if (PHYSFS_stat(path_buf, &stat) && stat.filetype == PHYSFS_FILETYPE_DIRECTORY) {
        if (oflags & WASI_OFLAGS_DIRECTORY) {
            for (int fd = next_fd; fd < MAX_FDS; fd++) {
                if (!fd_table[fd].handle && !fd_table[fd].is_directory) {
                    fd_table[fd].path = strdup(path_buf);
                    fd_table[fd].is_directory = 1;
                    *newfd = fd;
                    return WASI_ERRNO_SUCCESS;
                }
            }
            return WASI_ERRNO_MFILE;
        }
        return WASI_ERRNO_ISDIR;
    }

    // Open file
    PHYSFS_File* handle = NULL;

    if (oflags & WASI_OFLAGS_CREAT) {
        handle = PHYSFS_openWrite(path_buf);
        if (handle && !(oflags & WASI_OFLAGS_EXCL)) {
            PHYSFS_close(handle);
            handle = PHYSFS_openAppend(path_buf);
        }
    } else {
        if (fs_rights_base & 0x1) {
            handle = (fdflags & WASI_FDFLAGS_APPEND) ?
                     PHYSFS_openAppend(path_buf) : PHYSFS_openWrite(path_buf);
        } else {
            handle = PHYSFS_openRead(path_buf);
        }
    }

    if (!handle) {
        return physfs_to_wasi_errno();
    }

    if (oflags & WASI_OFLAGS_TRUNC) {
        PHYSFS_close(handle);
        handle = PHYSFS_openWrite(path_buf);
        if (!handle) {
            return physfs_to_wasi_errno();
        }
    }

    int fd = allocate_fd(handle, path_buf, fdflags);
    if (fd < 0) {
        PHYSFS_close(handle);
        return WASI_ERRNO_MFILE;
    }

    *newfd = fd;
    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, path_filestat_get, (int fd, int flags, uint32_t pathPtr, int pathLen, uint32_t filestatPtr), {
    char* path = (char*)get_wasm_memory_ptr(pathPtr);
    wasi_filestat_t* filestat = (wasi_filestat_t*)get_wasm_memory_ptr(filestatPtr);

    if (!path || !filestat) {
        return WASI_ERRNO_FAULT;
    }

    char path_buf[pathLen + 1];
    memcpy(path_buf, path, pathLen);
    path_buf[pathLen] = '\0';

    PHYSFS_Stat stat;
    if (!PHYSFS_stat(path_buf, &stat)) {
        return physfs_to_wasi_errno();
    }

    memset(filestat, 0, sizeof(wasi_filestat_t));
    filestat->dev = 0;
    filestat->ino = 0;

    switch (stat.filetype) {
        case PHYSFS_FILETYPE_REGULAR:
            filestat->filetype = WASI_FILETYPE_REGULAR_FILE;
            break;
        case PHYSFS_FILETYPE_DIRECTORY:
            filestat->filetype = WASI_FILETYPE_DIRECTORY;
            break;
        case PHYSFS_FILETYPE_SYMLINK:
            filestat->filetype = WASI_FILETYPE_SYMBOLIC_LINK;
            break;
        default:
            filestat->filetype = WASI_FILETYPE_UNKNOWN;
    }

    filestat->nlink = 1;
    filestat->size = stat.filesize;
    filestat->atim = stat.accesstime * 1000000000ULL;
    filestat->mtim = stat.modtime * 1000000000ULL;
    filestat->ctim = stat.createtime * 1000000000ULL;

    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, path_create_directory, (int fd, uint32_t pathPtr, int pathLen), {
    char* path = (char*)get_wasm_memory_ptr(pathPtr);
    if (!path) {
        return WASI_ERRNO_FAULT;
    }

    char path_buf[pathLen + 1];
    memcpy(path_buf, path, pathLen);
    path_buf[pathLen] = '\0';

    if (!PHYSFS_mkdir(path_buf)) {
        return physfs_to_wasi_errno();
    }

    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, path_remove_directory, (int fd, uint32_t pathPtr, int pathLen), {
    char* path = (char*)get_wasm_memory_ptr(pathPtr);
    if (!path) {
        return WASI_ERRNO_FAULT;
    }

    char path_buf[pathLen + 1];
    memcpy(path_buf, path, pathLen);
    path_buf[pathLen] = '\0';

    if (!PHYSFS_delete(path_buf)) {
        return physfs_to_wasi_errno();
    }

    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, path_unlink_file, (int fd, uint32_t pathPtr, int pathLen), {
    char* path = (char*)get_wasm_memory_ptr(pathPtr);
    if (!path) {
        return WASI_ERRNO_FAULT;
    }

    char path_buf[pathLen + 1];
    memcpy(path_buf, path, pathLen);
    path_buf[pathLen] = '\0';

    if (!PHYSFS_delete(path_buf)) {
        return physfs_to_wasi_errno();
    }

    return WASI_ERRNO_SUCCESS;
})

// ========== CLOCK OPERATIONS ==========

WASI_FUNCTION(int, clock_res_get, (int clockid, uint32_t resolutionPtr), {
    uint64_t* resolution = (uint64_t*)get_wasm_memory_ptr(resolutionPtr);
    if (!resolution) {
        return WASI_ERRNO_FAULT;
    }

    struct timespec ts;
    clockid_t native_clockid;

    switch (clockid) {
        case WASI_CLOCKID_REALTIME:
            native_clockid = CLOCK_REALTIME;
            break;
        case WASI_CLOCKID_MONOTONIC:
            native_clockid = CLOCK_MONOTONIC;
            break;
        case WASI_CLOCKID_PROCESS_CPUTIME_ID:
            native_clockid = CLOCK_PROCESS_CPUTIME_ID;
            break;
        case WASI_CLOCKID_THREAD_CPUTIME_ID:
            native_clockid = CLOCK_THREAD_CPUTIME_ID;
            break;
        default:
            return WASI_ERRNO_INVAL;
    }

    if (clock_getres(native_clockid, &ts) == -1) {
        return errno_to_wasi(errno);
    }

    *resolution = ts.tv_sec * 1000000000ULL + ts.tv_nsec;
    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, clock_time_get, (int clockid, uint64_t precision, uint32_t timePtr), {
    uint64_t* time = (uint64_t*)get_wasm_memory_ptr(timePtr);
    if (!time) {
        return WASI_ERRNO_FAULT;
    }

    struct timespec ts;
    clockid_t native_clockid;

    switch (clockid) {
        case WASI_CLOCKID_REALTIME:
            native_clockid = CLOCK_REALTIME;
            break;
        case WASI_CLOCKID_MONOTONIC:
            native_clockid = CLOCK_MONOTONIC;
            break;
        case WASI_CLOCKID_PROCESS_CPUTIME_ID:
            native_clockid = CLOCK_PROCESS_CPUTIME_ID;
            break;
        case WASI_CLOCKID_THREAD_CPUTIME_ID:
            native_clockid = CLOCK_THREAD_CPUTIME_ID;
            break;
        default:
            return WASI_ERRNO_INVAL;
    }

    if (clock_gettime(native_clockid, &ts) == -1) {
        return errno_to_wasi(errno);
    }

    *time = ts.tv_sec * 1000000000ULL + ts.tv_nsec;
    return WASI_ERRNO_SUCCESS;
})

// ========== RANDOM OPERATIONS ==========

WASI_FUNCTION(int, random_get, (uint32_t bufPtr, uint32_t bufLen), {
    uint8_t* buf = (uint8_t*)get_wasm_memory_ptr(bufPtr);
    if (!buf) {
        return WASI_ERRNO_FAULT;
    }

    FILE* urandom = fopen("/dev/urandom", "rb");
    if (!urandom) {
        srand(time(NULL));
        for (uint32_t i = 0; i < bufLen; i++) {
            buf[i] = rand() & 0xFF;
        }
        return WASI_ERRNO_SUCCESS;
    }

    size_t bytes_read = fread(buf, 1, bufLen, urandom);
    fclose(urandom);

    if (bytes_read != bufLen) {
        return WASI_ERRNO_IO;
    }

    return WASI_ERRNO_SUCCESS;
})

// ========== PROCESS OPERATIONS ==========

WASI_FUNCTION(void, proc_exit, (int rval), {
    exit(rval);
})

WASI_FUNCTION(int, args_get, (uint32_t argvPtr, uint32_t argvBufPtr), {
    uint32_t* argv = (uint32_t*)get_wasm_memory_ptr(argvPtr);
    if (!argv) {
        return WASI_ERRNO_FAULT;
    }

    argv[0] = 0;
    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, args_sizes_get, (uint32_t argcPtr, uint32_t argvBufSizePtr), {
    uint32_t* argc = (uint32_t*)get_wasm_memory_ptr(argcPtr);
    uint32_t* argvBufSize = (uint32_t*)get_wasm_memory_ptr(argvBufSizePtr);

    if (!argc || !argvBufSize) {
        return WASI_ERRNO_FAULT;
    }

    *argc = 0;
    *argvBufSize = 0;
    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, environ_get, (uint32_t environPtr, uint32_t environBufPtr), {
    uint32_t* environ = (uint32_t*)get_wasm_memory_ptr(environPtr);
    if (!environ) {
        return WASI_ERRNO_FAULT;
    }

    environ[0] = 0;
    return WASI_ERRNO_SUCCESS;
})

WASI_FUNCTION(int, environ_sizes_get, (uint32_t environCountPtr, uint32_t environBufSizePtr), {
    uint32_t* environCount = (uint32_t*)get_wasm_memory_ptr(environCountPtr);
    uint32_t* environBufSize = (uint32_t*)get_wasm_memory_ptr(environBufSizePtr);

    if (!environCount || !environBufSize) {
        return WASI_ERRNO_FAULT;
    }

    *environCount = 0;
    *environBufSize = 0;
    return WASI_ERRNO_SUCCESS;
})

// ========== POLL OPERATIONS ==========

WASI_FUNCTION(int, poll_oneoff, (uint32_t inPtr, uint32_t outPtr, uint32_t nsubscriptions, uint32_t neventsPtr), {
    uint32_t* nevents = (uint32_t*)get_wasm_memory_ptr(neventsPtr);
    if (!nevents) {
        return WASI_ERRNO_FAULT;
    }

    *nevents = 0;
    return WASI_ERRNO_SUCCESS;
})

// ========== SOCKET OPERATIONS (Stubs) ==========

WASI_FUNCTION(int, sock_recv, (int fd, uint32_t riDataPtr, uint32_t riDataLen, int riFlags, uint32_t roDatalenPtr, uint32_t roFlagsPtr), {
    return WASI_ERRNO_NOSYS;
})

WASI_FUNCTION(int, sock_send, (int fd, uint32_t siDataPtr, uint32_t siDataLen, int siFlags, uint32_t soDatalenPtr), {
    return WASI_ERRNO_NOSYS;
})

WASI_FUNCTION(int, sock_shutdown, (int fd, int how), {
    return WASI_ERRNO_NOSYS;
})

// ========== INITIALIZATION ==========

void wasi_physfs_init() {
    init_fd_table();
}
