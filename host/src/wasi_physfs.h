#pragma once

#include "wasm_export.h"
#include "fs.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

// WASI type definitions (must come first)
typedef uint32_t wasi_size_t;
typedef uint32_t wasi_fd_t;
typedef uint8_t wasi_advice_t;
typedef uint32_t wasi_clockid_t;
typedef uint64_t wasi_device_t;
typedef uint64_t wasi_dircookie_t;
typedef uint16_t wasi_errno_t;
typedef uint16_t wasi_eventrwflags_t;
typedef uint8_t wasi_eventtype_t;
typedef uint32_t wasi_exitcode_t;
typedef uint16_t wasi_fdflags_t;
typedef int64_t wasi_filedelta_t;
typedef uint64_t wasi_filesize_t;
typedef uint8_t wasi_filetype_t;
typedef uint16_t wasi_fstflags_t;
typedef uint64_t wasi_inode_t;
typedef uint64_t wasi_linkcount_t;
typedef uint32_t wasi_lookupflags_t;
typedef uint16_t wasi_oflags_t;
typedef uint8_t wasi_preopentype_t;
typedef uint16_t wasi_riflags_t;
typedef uint64_t wasi_rights_t;
typedef uint16_t wasi_roflags_t;
typedef uint8_t wasi_sdflags_t;
typedef uint16_t wasi_siflags_t;
typedef uint8_t wasi_signal_t;
typedef uint16_t wasi_subclockflags_t;
typedef uint64_t wasi_timestamp_t;
typedef uint64_t wasi_userdata_t;
typedef uint8_t wasi_whence_t;

// WASI constants
#define WASI_ESUCCESS 0
#define WASI_E2BIG 1
#define WASI_EACCES 2
#define WASI_EADDRINUSE 3
#define WASI_EADDRNOTAVAIL 4
#define WASI_EAFNOSUPPORT 5
#define WASI_EAGAIN 6
#define WASI_EALREADY 7
#define WASI_EBADF 8
#define WASI_EBADMSG 9
#define WASI_EBUSY 10
#define WASI_ECANCELED 11
#define WASI_ECHILD 12
#define WASI_ECONNABORTED 13
#define WASI_ECONNREFUSED 14
#define WASI_ECONNRESET 15
#define WASI_EDEADLK 16
#define WASI_EDESTADDRREQ 17
#define WASI_EDOM 18
#define WASI_EDQUOT 19
#define WASI_EEXIST 20
#define WASI_EFAULT 21
#define WASI_EFBIG 22
#define WASI_EHOSTUNREACH 23
#define WASI_EIDRM 24
#define WASI_EILSEQ 25
#define WASI_EINPROGRESS 26
#define WASI_EINTR 27
#define WASI_EINVAL 28
#define WASI_EIO 29
#define WASI_EISCONN 30
#define WASI_EISDIR 31
#define WASI_ELOOP 32
#define WASI_EMFILE 33
#define WASI_EMLINK 34
#define WASI_EMSGSIZE 35
#define WASI_EMULTIHOP 36
#define WASI_ENAMETOOLONG 37
#define WASI_ENETDOWN 38
#define WASI_ENETRESET 39
#define WASI_ENETUNREACH 40
#define WASI_ENFILE 41
#define WASI_ENOBUFS 42
#define WASI_ENODEV 43
#define WASI_ENOENT 44
#define WASI_ENOEXEC 45
#define WASI_ENOLCK 46
#define WASI_ENOLINK 47
#define WASI_ENOMEM 48
#define WASI_ENOMSG 49
#define WASI_ENOPROTOOPT 50
#define WASI_ENOSPC 51
#define WASI_ENOSYS 52
#define WASI_ENOTCONN 53
#define WASI_ENOTDIR 54
#define WASI_ENOTEMPTY 55
#define WASI_ENOTRECOVERABLE 56
#define WASI_ENOTSOCK 57
#define WASI_ENOTSUP 58
#define WASI_ENOTTY 59
#define WASI_ENXIO 60
#define WASI_EOVERFLOW 61
#define WASI_EOWNERDEAD 62
#define WASI_EPERM 63
#define WASI_EPIPE 64
#define WASI_EPROTO 65
#define WASI_EPROTONOSUPPORT 66
#define WASI_EPROTOTYPE 67
#define WASI_ERANGE 68
#define WASI_EROFS 69
#define WASI_ESPIPE 70
#define WASI_ESRCH 71
#define WASI_ESTALE 72
#define WASI_ETIMEDOUT 73
#define WASI_ETXTBSY 74
#define WASI_EXDEV 75
#define WASI_ENOTCAPABLE 76

#define WASI_CLOCK_REALTIME 0
#define WASI_CLOCK_MONOTONIC 1
#define WASI_CLOCK_PROCESS_CPUTIME_ID 2
#define WASI_CLOCK_THREAD_CPUTIME_ID 3

#define WASI_FILETYPE_UNKNOWN 0
#define WASI_FILETYPE_BLOCK_DEVICE 1
#define WASI_FILETYPE_CHARACTER_DEVICE 2
#define WASI_FILETYPE_DIRECTORY 3
#define WASI_FILETYPE_REGULAR_FILE 4
#define WASI_FILETYPE_SOCKET_DGRAM 5
#define WASI_FILETYPE_SOCKET_STREAM 6
#define WASI_FILETYPE_SYMBOLIC_LINK 7

#define WASI_FDFLAG_APPEND (1 << 0)
#define WASI_FDFLAG_DSYNC (1 << 1)
#define WASI_FDFLAG_NONBLOCK (1 << 2)
#define WASI_FDFLAG_RSYNC (1 << 3)
#define WASI_FDFLAG_SYNC (1 << 4)

#define WASI_O_CREAT (1 << 0)
#define WASI_O_DIRECTORY (1 << 1)
#define WASI_O_EXCL (1 << 2)
#define WASI_O_TRUNC (1 << 3)

#define WASI_WHENCE_SET 0
#define WASI_WHENCE_CUR 1
#define WASI_WHENCE_END 2

#define WASI_PREOPENTYPE_DIR 0

#define WASI_RIGHT_FD_DATASYNC (1 << 0)
#define WASI_RIGHT_FD_READ (1 << 1)
#define WASI_RIGHT_FD_SEEK (1 << 2)
#define WASI_RIGHT_FD_FDSTAT_SET_FLAGS (1 << 3)
#define WASI_RIGHT_FD_SYNC (1 << 4)
#define WASI_RIGHT_FD_TELL (1 << 5)
#define WASI_RIGHT_FD_WRITE (1 << 6)
#define WASI_RIGHT_FD_ADVISE (1 << 7)
#define WASI_RIGHT_FD_ALLOCATE (1 << 8)
#define WASI_RIGHT_PATH_CREATE_DIRECTORY (1 << 9)
#define WASI_RIGHT_PATH_CREATE_FILE (1 << 10)
#define WASI_RIGHT_PATH_LINK_SOURCE (1 << 11)
#define WASI_RIGHT_PATH_LINK_TARGET (1 << 12)
#define WASI_RIGHT_PATH_OPEN (1 << 13)
#define WASI_RIGHT_FD_READDIR (1 << 14)
#define WASI_RIGHT_PATH_READLINK (1 << 15)
#define WASI_RIGHT_PATH_RENAME_SOURCE (1 << 16)
#define WASI_RIGHT_PATH_RENAME_TARGET (1 << 17)
#define WASI_RIGHT_PATH_FILESTAT_GET (1 << 18)
#define WASI_RIGHT_PATH_FILESTAT_SET_SIZE (1 << 19)
#define WASI_RIGHT_PATH_FILESTAT_SET_TIMES (1 << 20)
#define WASI_RIGHT_FD_FILESTAT_GET (1 << 21)
#define WASI_RIGHT_FD_FILESTAT_SET_SIZE (1 << 22)
#define WASI_RIGHT_FD_FILESTAT_SET_TIMES (1 << 23)
#define WASI_RIGHT_PATH_SYMLINK (1 << 24)
#define WASI_RIGHT_PATH_REMOVE_DIRECTORY (1 << 25)
#define WASI_RIGHT_PATH_UNLINK_FILE (1 << 26)
#define WASI_RIGHT_POLL_FD_READWRITE (1 << 27)
#define WASI_RIGHT_SOCK_SHUTDOWN (1 << 28)
#define WASI_RIGHT_SOCK_ACCEPT (1 << 29)

// WASI structures
typedef struct wasi_ciovec_s {
  const void *buf;
  wasi_size_t buf_len;
} wasi_ciovec_t;

typedef struct wasi_iovec_s {
  void *buf;
  wasi_size_t buf_len;
} wasi_iovec_t;

typedef struct wasi_prestat_s {
  wasi_preopentype_t pr_type;
  union wasi_prestat_u {
    struct wasi_prestat_dir_t {
      wasi_size_t pr_name_len;
    } dir;
  } u;
} wasi_prestat_t;

typedef struct wasi_fdstat_s {
  wasi_filetype_t fs_filetype;
  wasi_fdflags_t fs_flags;
  wasi_rights_t fs_rights_base;
  wasi_rights_t fs_rights_inheriting;
} wasi_fdstat_t;

typedef struct wasi_filestat_s {
  wasi_device_t st_dev;
  wasi_inode_t st_ino;
  wasi_filetype_t st_filetype;
  wasi_linkcount_t st_nlink;
  wasi_filesize_t st_size;
  wasi_timestamp_t st_atim;
  wasi_timestamp_t st_mtim;
  wasi_timestamp_t st_ctim;
} wasi_filestat_t;

typedef struct iovec_app {
  uint32_t buf_offset;
  uint32_t buf_len;
} iovec_app_t;

typedef struct wasi_prestat_app {
  wasi_preopentype_t pr_type;
  uint32_t pr_name_len;
} wasi_prestat_app_t;

typedef struct wasi_dirent_s {
  wasi_dircookie_t d_next;
  wasi_inode_t d_ino;
  uint32_t d_namlen;
  wasi_filetype_t d_type;
} wasi_dirent_t;

// Maximum number of open file descriptors
#define MAX_FDS 256

// Global variables to store argc/argv
static int g_argc = 0;
static char **g_argv = NULL;

// File descriptor table
typedef struct {
  bool is_open;
  bool is_directory;
  PHYSFS_File *physfs_file;
  char *path;
  int flags;
  uint64_t position;
} wasi_fd_entry_t;

static wasi_fd_entry_t g_fds[MAX_FDS];
static bool g_fds_initialized = false;

// Initialize file descriptor table
static void init_fds() {
  if (g_fds_initialized) return;
  
  for (int i = 0; i < MAX_FDS; i++) {
    g_fds[i].is_open = false;
    g_fds[i].is_directory = false;
    g_fds[i].physfs_file = NULL;
    g_fds[i].path = NULL;
    g_fds[i].flags = 0;
    g_fds[i].position = 0;
  }
  
  // Reserve standard file descriptors
  g_fds[0].is_open = true; // stdin
  g_fds[1].is_open = true; // stdout
  g_fds[2].is_open = true; // stderr
  
  // Set up the preopen directory fd 3 as root "/"
  g_fds[3].is_open = true;
  g_fds[3].is_directory = true;
  g_fds[3].physfs_file = NULL;
  g_fds[3].path = strdup("/"); // Root directory
  g_fds[3].flags = 0;
  g_fds[3].position = 0;
  
  g_fds_initialized = true;
}

// Allocate a new file descriptor
static wasi_fd_t alloc_fd() {
  init_fds();
  for (wasi_fd_t fd = 4; fd < MAX_FDS; fd++) { // Start from 4, skip preopen dir fd 3
    if (!g_fds[fd].is_open) {
      g_fds[fd].is_open = true;
      return fd;
    }
  }
  return (wasi_fd_t)-1; // No available descriptors
}

// Free a file descriptor
static void free_fd(wasi_fd_t fd) {
  if (fd >= MAX_FDS || !g_fds[fd].is_open) return;
  
  // Don't free reserved fds (stdin/stdout/stderr/preopen_dir)
  if (fd <= 3) return;
  
  if (g_fds[fd].physfs_file) {
    PHYSFS_close(g_fds[fd].physfs_file);
  }
  if (g_fds[fd].path) {
    free(g_fds[fd].path);
  }
  
  g_fds[fd].is_open = false;
  g_fds[fd].is_directory = false;
  g_fds[fd].physfs_file = NULL;
  g_fds[fd].path = NULL;
  g_fds[fd].flags = 0;
  g_fds[fd].position = 0;
}

// Function to initialize arguments (call this before running WASM)
void wasi_set_args(int argc, char **argv) {
  g_argc = argc;
  g_argv = argv;
}

// Helper functions
static wasi_errno_t errno_to_wasi(int err) {
  switch (err) {
    case 0: return WASI_ESUCCESS;
    case ENOENT: return WASI_ENOENT;
    case EACCES: return WASI_EACCES;
    case EEXIST: return WASI_EEXIST;
    case ENOTDIR: return WASI_ENOTDIR;
    case EISDIR: return WASI_EISDIR;
    case EINVAL: return WASI_EINVAL;
    case ENOMEM: return WASI_ENOMEM;
    case EIO: return WASI_EIO;
    case EBADF: return WASI_EBADF;
    default: return WASI_EIO;
  }
}

static char *wasm_string_to_cstring(wasm_exec_env_t exec_env, const char *str, uint32_t len) {
  wasm_module_inst_t module_inst = wasm_runtime_get_module_inst(exec_env);
  const char *native_str = wasm_runtime_addr_app_to_native(module_inst, (uint32_t)str);
  if (!native_str) return NULL;
  
  char *result = malloc(len + 1);
  if (!result) return NULL;
  
  memcpy(result, native_str, len);
  result[len] = '\0';
  return result;
}

// WASI function implementations
static wasi_errno_t wasi_args_sizes_get(wasm_exec_env_t exec_env, uint32_t *argc_app, uint32_t *argv_buf_size_app) {
  uint32_t buf_size = 0;
  for (int i = 0; i < g_argc; i++) {
    buf_size += strlen(g_argv[i]) + 1;
  }
  *argc_app = g_argc;
  *argv_buf_size_app = buf_size;
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_args_get(wasm_exec_env_t exec_env, uint32_t *argv_offsets, char *argv_buf) {
  wasm_module_inst_t module_inst = wasm_runtime_get_module_inst(exec_env);
  uint32_t *offsets = (uint32_t *)wasm_runtime_addr_app_to_native(module_inst, (uint32_t)argv_offsets);
  char *buf = wasm_runtime_addr_app_to_native(module_inst, (uint32_t)argv_buf);
  uint32_t buf_offset = 0;

  if (!offsets || !buf) {
    return WASI_EFAULT;
  }

  for (int i = 0; i < g_argc; i++) {
    size_t len = strlen(g_argv[i]) + 1;
    offsets[i] = (uint32_t)argv_buf + buf_offset;
    memcpy(buf + buf_offset, g_argv[i], len);
    buf_offset += len;
  }

  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_clock_time_get(wasm_exec_env_t exec_env, wasi_clockid_t clock_id, wasi_timestamp_t precision, wasi_timestamp_t *time) {
  struct timespec ts;
  int result;

  switch (clock_id) {
  case WASI_CLOCK_REALTIME:
    result = clock_gettime(CLOCK_REALTIME, &ts);
    break;
  case WASI_CLOCK_MONOTONIC:
    result = clock_gettime(CLOCK_MONOTONIC, &ts);
    break;
  case WASI_CLOCK_PROCESS_CPUTIME_ID:
    result = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    break;
  case WASI_CLOCK_THREAD_CPUTIME_ID:
    result = clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
    break;
  default:
    return WASI_EINVAL;
  }

  if (result != 0) {
    return WASI_EIO;
  }

  *time = (wasi_timestamp_t)ts.tv_sec * 1000000000ULL + (wasi_timestamp_t)ts.tv_nsec;
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_clock_res_get(wasm_exec_env_t exec_env, wasi_clockid_t clock_id, wasi_timestamp_t *resolution) {
  struct timespec ts;
  int result;

  switch (clock_id) {
  case WASI_CLOCK_REALTIME:
    result = clock_getres(CLOCK_REALTIME, &ts);
    break;
  case WASI_CLOCK_MONOTONIC:
    result = clock_getres(CLOCK_MONOTONIC, &ts);
    break;
  case WASI_CLOCK_PROCESS_CPUTIME_ID:
    result = clock_getres(CLOCK_PROCESS_CPUTIME_ID, &ts);
    break;
  case WASI_CLOCK_THREAD_CPUTIME_ID:
    result = clock_getres(CLOCK_THREAD_CPUTIME_ID, &ts);
    break;
  default:
    return WASI_EINVAL;
  }

  if (result != 0) {
    return WASI_EIO;
  }

  *resolution = (wasi_timestamp_t)ts.tv_sec * 1000000000ULL + (wasi_timestamp_t)ts.tv_nsec;
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_environ_sizes_get(wasm_exec_env_t exec_env, uint32_t *environ_count_app, uint32_t *environ_buf_size_app) {
  extern char **environ;
  uint32_t count = 0;
  uint32_t buf_size = 0;
  char **env_ptr = environ;

  while (*env_ptr) {
    count++;
    buf_size += strlen(*env_ptr) + 1;
    env_ptr++;
  }

  *environ_count_app = count;
  *environ_buf_size_app = buf_size;
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_environ_get(wasm_exec_env_t exec_env, uint32_t *environ_offsets, char *environ_buf) {
  wasm_module_inst_t module_inst = wasm_runtime_get_module_inst(exec_env);
  extern char **environ;
  char **env_ptr = environ;
  uint32_t *offsets = (uint32_t *)wasm_runtime_addr_app_to_native(module_inst, (uint32_t)environ_offsets);
  char *buf = wasm_runtime_addr_app_to_native(module_inst, (uint32_t)environ_buf);
  uint32_t buf_offset = 0;
  uint32_t i = 0;

  if (!offsets || !buf) {
    return WASI_EFAULT;
  }

  while (*env_ptr) {
    size_t len = strlen(*env_ptr) + 1;
    offsets[i] = (uint32_t)environ_buf + buf_offset;
    memcpy(buf + buf_offset, *env_ptr, len);
    buf_offset += len;
    env_ptr++;
    i++;
  }

  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_fd_prestat_get(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_prestat_app_t *prestat_app) {
  // For now, we'll support one preopen directory "/"
  if (fd == 3) { // First available fd after stdin/stdout/stderr
    prestat_app->pr_type = WASI_PREOPENTYPE_DIR;
    prestat_app->pr_name_len = 1; // "/"
    return WASI_ESUCCESS;
  }
  return WASI_EBADF;
}

static wasi_errno_t wasi_fd_prestat_dir_name(wasm_exec_env_t exec_env, wasi_fd_t fd, char *path, uint32_t path_len) {
  wasm_module_inst_t module_inst = wasm_runtime_get_module_inst(exec_env);
  char *native_path = wasm_runtime_addr_app_to_native(module_inst, (uint32_t)path);
  
  if (!native_path) {
    return WASI_EFAULT;
  }
  
  if (fd == 3 && path_len >= 1) {
    native_path[0] = '/';
    return WASI_ESUCCESS;
  }
  return WASI_EBADF;
}

static void wasi_proc_exit(wasm_exec_env_t exec_env, wasi_exitcode_t rval) {
  exit(rval);
}

static wasi_errno_t wasi_random_get(wasm_exec_env_t exec_env, void *buf, uint32_t buf_len) {
  wasm_module_inst_t module_inst = wasm_runtime_get_module_inst(exec_env);
  char *native_buf = wasm_runtime_addr_app_to_native(module_inst, (uint32_t)buf);

  if (!native_buf) {
    return WASI_EFAULT;
  }

  // Use /dev/urandom for random data
  int fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0) {
    return WASI_EIO;
  }

  ssize_t bytes_read = read(fd, native_buf, buf_len);
  close(fd);

  if (bytes_read < 0 || (uint32_t)bytes_read != buf_len) {
    return WASI_EIO;
  }

  return WASI_ESUCCESS;
}

// Filesystem functions using PhysFS
static wasi_errno_t wasi_fd_close(wasm_exec_env_t exec_env, wasi_fd_t fd) {
  init_fds();
  
  if (fd >= MAX_FDS || !g_fds[fd].is_open) {
    return WASI_EBADF;
  }
  
  // Don't close stdin/stdout/stderr/preopen_dir
  if (fd <= 3) {
    return WASI_ESUCCESS;
  }
  
  free_fd(fd);
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_fd_read(wasm_exec_env_t exec_env, wasi_fd_t fd, const iovec_app_t *iovec_app, uint32_t iovs_len, uint32_t *nread_app) {
  wasm_module_inst_t module_inst = wasm_runtime_get_module_inst(exec_env);
  uint32_t total_read = 0;
  
  init_fds();
  
  if (fd >= MAX_FDS || !g_fds[fd].is_open) {
    return WASI_EBADF;
  }
  
  // Handle stdin specially
  if (fd == 0) {
    for (uint32_t i = 0; i < iovs_len; i++) {
      char *buf = wasm_runtime_addr_app_to_native(module_inst, iovec_app[i].buf_offset);
      uint32_t buf_len = iovec_app[i].buf_len;
      
      if (!buf) {
        return WASI_EFAULT;
      }
      
      size_t bytes_read = fread(buf, 1, buf_len, stdin);
      total_read += bytes_read;
      
      if (bytes_read < buf_len) {
        break;
      }
    }
    
    if (nread_app) {
      *nread_app = total_read;
    }
    return WASI_ESUCCESS;
  }
  
  // Handle regular files
  if (!g_fds[fd].physfs_file) {
    return WASI_EBADF;
  }
  
  for (uint32_t i = 0; i < iovs_len; i++) {
    char *buf = wasm_runtime_addr_app_to_native(module_inst, iovec_app[i].buf_offset);
    uint32_t buf_len = iovec_app[i].buf_len;
    
    if (!buf) {
      return WASI_EFAULT;
    }
    
    PHYSFS_sint64 bytes_read = PHYSFS_readBytes(g_fds[fd].physfs_file, buf, buf_len);
    if (bytes_read < 0) {
      return WASI_EIO;
    }
    
    total_read += bytes_read;
    g_fds[fd].position += bytes_read;
    
    if (bytes_read < buf_len) {
      break;
    }
  }
  
  if (nread_app) {
    *nread_app = total_read;
  }
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_fd_write(wasm_exec_env_t exec_env, wasi_fd_t fd, const iovec_app_t *iovec_app, uint32_t iovs_len, uint32_t *nwritten_app) {
  wasm_module_inst_t module_inst = wasm_runtime_get_module_inst(exec_env);
  uint32_t total_written = 0;
  
  init_fds();
  
  if (fd >= MAX_FDS || !g_fds[fd].is_open) {
    return WASI_EBADF;
  }
  
  // Handle stdout/stderr specially
  if (fd == 1 || fd == 2) {
    for (uint32_t i = 0; i < iovs_len; i++) {
      char *buf = wasm_runtime_addr_app_to_native(module_inst, iovec_app[i].buf_offset);
      uint32_t buf_len = iovec_app[i].buf_len;
      
      if (!buf) {
        return WASI_EFAULT;
      }
      
      if (fd == 1) {
        fwrite(buf, 1, buf_len, stdout);
        fflush(stdout);
      } else {
        fwrite(buf, 1, buf_len, stderr);
        fflush(stderr);
      }
      
      total_written += buf_len;
    }
    
    if (nwritten_app) {
      *nwritten_app = total_written;
    }
    return WASI_ESUCCESS;
  }
  
  // Handle regular files
  if (!g_fds[fd].physfs_file) {
    return WASI_EBADF;
  }
  
  for (uint32_t i = 0; i < iovs_len; i++) {
    char *buf = wasm_runtime_addr_app_to_native(module_inst, iovec_app[i].buf_offset);
    uint32_t buf_len = iovec_app[i].buf_len;
    
    if (!buf) {
      return WASI_EFAULT;
    }
    
    PHYSFS_sint64 bytes_written = PHYSFS_writeBytes(g_fds[fd].physfs_file, buf, buf_len);
    if (bytes_written < 0) {
      return WASI_EIO;
    }
    
    total_written += bytes_written;
    g_fds[fd].position += bytes_written;
    
    if (bytes_written < buf_len) {
      break;
    }
  }
  
  if (nwritten_app) {
    *nwritten_app = total_written;
  }
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_fd_seek(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filedelta_t offset, wasi_whence_t whence, wasi_filesize_t *newoffset) {
  init_fds();
  
  if (fd >= MAX_FDS || !g_fds[fd].is_open || !g_fds[fd].physfs_file) {
    return WASI_EBADF;
  }
  
  PHYSFS_sint64 new_pos;
  
  switch (whence) {
    case WASI_WHENCE_SET:
      new_pos = offset;
      break;
    case WASI_WHENCE_CUR:
      new_pos = g_fds[fd].position + offset;
      break;
    case WASI_WHENCE_END:
      new_pos = PHYSFS_fileLength(g_fds[fd].physfs_file) + offset;
      break;
    default:
      return WASI_EINVAL;
  }
  
  if (new_pos < 0) {
    return WASI_EINVAL;
  }
  
  if (!PHYSFS_seek(g_fds[fd].physfs_file, new_pos)) {
    return WASI_EIO;
  }
  
  g_fds[fd].position = new_pos;
  
  if (newoffset) {
    *newoffset = new_pos;
  }
  
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_fd_tell(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filesize_t *offset) {
  init_fds();
  
  if (fd >= MAX_FDS || !g_fds[fd].is_open) {
    return WASI_EBADF;
  }
  
  if (fd <= 3) {
    // stdin/stdout/stderr/preopen_dir don't support tell
    return WASI_ESPIPE;
  }
  
  if (!g_fds[fd].physfs_file) {
    return WASI_EBADF;
  }
  
  PHYSFS_sint64 pos = PHYSFS_tell(g_fds[fd].physfs_file);
  if (pos < 0) {
    return WASI_EIO;
  }
  
  *offset = pos;
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_path_open(wasm_exec_env_t exec_env, wasi_fd_t dirfd, wasi_lookupflags_t dirflags, 
                                  const char *path, uint32_t path_len, wasi_oflags_t oflags, 
                                  wasi_rights_t fs_rights_base, wasi_rights_t fs_rights_inheriting, 
                                  wasi_fdflags_t fs_flags, wasi_fd_t *fd_app) {
  init_fds();
  
  // Validate the directory fd
  if (dirfd >= MAX_FDS || !g_fds[dirfd].is_open || !g_fds[dirfd].is_directory) {
    return WASI_EBADF;
  }
  
  char *path_str = wasm_string_to_cstring(exec_env, path, path_len);
  if (!path_str) {
    return WASI_EFAULT;
  }
  
  wasi_fd_t new_fd = alloc_fd();
  if (new_fd == (wasi_fd_t)-1) {
    free(path_str);
    return WASI_EMFILE;
  }
  
  // Check if the file exists
  PHYSFS_Stat stat;
  bool exists = PHYSFS_stat(path_str, &stat) != 0;
  
  // Handle creation flags
  if (oflags & WASI_O_CREAT) {
    if (exists && (oflags & WASI_O_EXCL)) {
      free(path_str);
      free_fd(new_fd);
      return WASI_EEXIST;
    }
  } else if (!exists) {
    free(path_str);
    free_fd(new_fd);
    return WASI_ENOENT;
  }
  
  // Handle directory vs file
  if (exists && stat.filetype == PHYSFS_FILETYPE_DIRECTORY) {
    if (!(oflags & WASI_O_DIRECTORY)) {
      free(path_str);
      free_fd(new_fd);
      return WASI_EISDIR;
    }
    
    g_fds[new_fd].is_directory = true;
    g_fds[new_fd].physfs_file = NULL;
  } else {
    if (oflags & WASI_O_DIRECTORY) {
      free(path_str);
      free_fd(new_fd);
      return WASI_ENOTDIR;
    }
    
    // Determine open mode
    PHYSFS_File *file = NULL;
    
    if (fs_rights_base & WASI_RIGHT_FD_WRITE) {
      if (oflags & WASI_O_TRUNC) {
        file = PHYSFS_openWrite(path_str);
      } else if (fs_flags & WASI_FDFLAG_APPEND) {
        file = PHYSFS_openAppend(path_str);
      } else {
        // PhysFS doesn't support read+write mode directly
        // For now, prefer write mode if write permission is requested
        file = PHYSFS_openWrite(path_str);
      }
    } else {
      file = PHYSFS_openRead(path_str);
    }
    
    if (!file) {
      free(path_str);
      free_fd(new_fd);
      return WASI_EIO;
    }
    
    g_fds[new_fd].physfs_file = file;
    g_fds[new_fd].is_directory = false;
  }
  
  g_fds[new_fd].path = path_str;
  g_fds[new_fd].flags = fs_flags;
  g_fds[new_fd].position = 0;
  
  *fd_app = new_fd;
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_fd_filestat_get(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filestat_t *filestat) {
  init_fds();
  
  if (fd >= MAX_FDS || !g_fds[fd].is_open) {
    return WASI_EBADF;
  }
  
  if (fd <= 2) {
    // stdin/stdout/stderr
    filestat->st_dev = 0;
    filestat->st_ino = fd;
    filestat->st_filetype = WASI_FILETYPE_CHARACTER_DEVICE;
    filestat->st_nlink = 1;
    filestat->st_size = 0;
    filestat->st_atim = 0;
    filestat->st_mtim = 0;
    filestat->st_ctim = 0;
    return WASI_ESUCCESS;
  }
  
  if (fd == 3) {
    // Preopen directory "/"
    filestat->st_dev = 0;
    filestat->st_ino = 3;
    filestat->st_filetype = WASI_FILETYPE_DIRECTORY;
    filestat->st_nlink = 1;
    filestat->st_size = 0;
    filestat->st_atim = 0;
    filestat->st_mtim = 0;
    filestat->st_ctim = 0;
    return WASI_ESUCCESS;
  }
  
  if (!g_fds[fd].path) {
    return WASI_EBADF;
  }
  
  PHYSFS_Stat stat;
  if (!PHYSFS_stat(g_fds[fd].path, &stat)) {
    return WASI_EIO;
  }
  
  filestat->st_dev = 0;
  filestat->st_ino = 0; // PhysFS doesn't provide inode numbers
  filestat->st_nlink = 1;
  filestat->st_size = stat.filesize;
  filestat->st_atim = stat.accesstime * 1000000000ULL; // Convert to nanoseconds
  filestat->st_mtim = stat.modtime * 1000000000ULL;
  filestat->st_ctim = stat.createtime * 1000000000ULL;
  
  switch (stat.filetype) {
    case PHYSFS_FILETYPE_REGULAR:
      filestat->st_filetype = WASI_FILETYPE_REGULAR_FILE;
      break;
    case PHYSFS_FILETYPE_DIRECTORY:
      filestat->st_filetype = WASI_FILETYPE_DIRECTORY;
      break;
    case PHYSFS_FILETYPE_SYMLINK:
      filestat->st_filetype = WASI_FILETYPE_SYMBOLIC_LINK;
      break;
    default:
      filestat->st_filetype = WASI_FILETYPE_UNKNOWN;
      break;
  }
  
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_path_filestat_get(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_lookupflags_t flags, 
                                          const char *path, uint32_t path_len, wasi_filestat_t *filestat) {
  char *path_str = wasm_string_to_cstring(exec_env, path, path_len);
  if (!path_str) {
    return WASI_EFAULT;
  }
  
  PHYSFS_Stat stat;
  if (!PHYSFS_stat(path_str, &stat)) {
    free(path_str);
    return WASI_ENOENT;
  }
  
  filestat->st_dev = 0;
  filestat->st_ino = 0;
  filestat->st_nlink = 1;
  filestat->st_size = stat.filesize;
  filestat->st_atim = stat.accesstime * 1000000000ULL;
  filestat->st_mtim = stat.modtime * 1000000000ULL;
  filestat->st_ctim = stat.createtime * 1000000000ULL;
  
  switch (stat.filetype) {
    case PHYSFS_FILETYPE_REGULAR:
      filestat->st_filetype = WASI_FILETYPE_REGULAR_FILE;
      break;
    case PHYSFS_FILETYPE_DIRECTORY:
      filestat->st_filetype = WASI_FILETYPE_DIRECTORY;
      break;
    case PHYSFS_FILETYPE_SYMLINK:
      filestat->st_filetype = WASI_FILETYPE_SYMBOLIC_LINK;
      break;
    default:
      filestat->st_filetype = WASI_FILETYPE_UNKNOWN;
      break;
  }
  
  free(path_str);
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_path_create_directory(wasm_exec_env_t exec_env, wasi_fd_t fd, const char *path, uint32_t path_len) {
  char *path_str = wasm_string_to_cstring(exec_env, path, path_len);
  if (!path_str) {
    return WASI_EFAULT;
  }
  
  if (!PHYSFS_mkdir(path_str)) {
    free(path_str);
    return WASI_EIO;
  }
  
  free(path_str);
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_path_remove_directory(wasm_exec_env_t exec_env, wasi_fd_t fd, const char *path, uint32_t path_len) {
  char *path_str = wasm_string_to_cstring(exec_env, path, path_len);
  if (!path_str) {
    return WASI_EFAULT;
  }
  
  if (!PHYSFS_delete(path_str)) {
    free(path_str);
    return WASI_EIO;
  }
  
  free(path_str);
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_path_unlink_file(wasm_exec_env_t exec_env, wasi_fd_t fd, const char *path, uint32_t path_len) {
  char *path_str = wasm_string_to_cstring(exec_env, path, path_len);
  if (!path_str) {
    return WASI_EFAULT;
  }
  
  if (!PHYSFS_delete(path_str)) {
    free(path_str);
    return WASI_EIO;
  }
  
  free(path_str);
  return WASI_ESUCCESS;
}

// Stub implementations for unsupported functions
static wasi_errno_t wasi_fd_datasync(wasm_exec_env_t exec_env, wasi_fd_t fd) {
  return WASI_ESUCCESS; // PhysFS handles sync automatically
}

static wasi_errno_t wasi_fd_sync(wasm_exec_env_t exec_env, wasi_fd_t fd) {
  return WASI_ESUCCESS; // PhysFS handles sync automatically
}

static wasi_errno_t wasi_fd_fdstat_get(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_fdstat_t *fdstat_app) {
  init_fds();
  
  if (fd >= MAX_FDS || !g_fds[fd].is_open) {
    return WASI_EBADF;
  }
  
  fdstat_app->fs_flags = g_fds[fd].flags;
  fdstat_app->fs_rights_base = (wasi_rights_t)-1; // All rights for simplicity
  fdstat_app->fs_rights_inheriting = (wasi_rights_t)-1;
  
  if (fd <= 2) {
    fdstat_app->fs_filetype = WASI_FILETYPE_CHARACTER_DEVICE;
  } else if (g_fds[fd].is_directory) {
    fdstat_app->fs_filetype = WASI_FILETYPE_DIRECTORY;
  } else {
    fdstat_app->fs_filetype = WASI_FILETYPE_REGULAR_FILE;
  }
  
  return WASI_ESUCCESS;
}

// Additional stub functions
static wasi_errno_t wasi_fd_renumber(wasm_exec_env_t exec_env, wasi_fd_t from, wasi_fd_t to) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_fd_advise(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filesize_t offset, wasi_filesize_t len, wasi_advice_t advice) {
  return WASI_ESUCCESS;
}

static wasi_errno_t wasi_fd_allocate(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filesize_t offset, wasi_filesize_t len) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_fd_fdstat_set_flags(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_fdflags_t flags) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_fd_fdstat_set_rights(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_rights_t fs_rights_base, wasi_rights_t fs_rights_inheriting) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_fd_filestat_set_size(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filesize_t st_size) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_fd_filestat_set_times(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_timestamp_t st_atim, wasi_timestamp_t st_mtim, wasi_fstflags_t fstflags) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_fd_pread(wasm_exec_env_t exec_env, wasi_fd_t fd, iovec_app_t *iovec_app, uint32_t iovs_len, wasi_filesize_t offset, uint32_t *nread_app) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_fd_pwrite(wasm_exec_env_t exec_env, wasi_fd_t fd, const iovec_app_t *iovec_app, uint32_t iovs_len, wasi_filesize_t offset, uint32_t *nwritten_app) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_fd_readdir(wasm_exec_env_t exec_env, wasi_fd_t fd, void *buf, uint32_t buf_len, wasi_dircookie_t cookie, uint32_t *bufused_app) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_path_filestat_set_times(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_lookupflags_t flags, const char *path, uint32_t path_len, wasi_timestamp_t st_atim, wasi_timestamp_t st_mtim, wasi_fstflags_t fstflags) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_path_link(wasm_exec_env_t exec_env, wasi_fd_t old_fd, wasi_lookupflags_t old_flags, const char *old_path, uint32_t old_path_len, wasi_fd_t new_fd, const char *new_path, uint32_t new_path_len) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_path_readlink(wasm_exec_env_t exec_env, wasi_fd_t fd, const char *path, uint32_t path_len, char *buf, uint32_t buf_len, uint32_t *bufused_app) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_path_rename(wasm_exec_env_t exec_env, wasi_fd_t old_fd, const char *old_path, uint32_t old_path_len, wasi_fd_t new_fd, const char *new_path, uint32_t new_path_len) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_path_symlink(wasm_exec_env_t exec_env, const char *old_path, uint32_t old_path_len, wasi_fd_t fd, const char *new_path, uint32_t new_path_len) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_poll_oneoff(wasm_exec_env_t exec_env, const void *in, void *out, uint32_t nsubscriptions, uint32_t *nevents_app) {
  return WASI_ENOSYS;
}

static wasi_errno_t wasi_proc_raise(wasm_exec_env_t exec_env, wasi_signal_t sig) {
  return WASI_ENOSYS;
}

// WASI native symbols array for WAMR
static NativeSymbol wasi_native_symbols[] = {
  {"args_get", wasi_args_get, "(**)i"},
  {"args_sizes_get", wasi_args_sizes_get, "(**)i"},
  {"clock_res_get", wasi_clock_res_get, "(i*)i"},
  {"clock_time_get", wasi_clock_time_get, "(iI*)i"},
  {"environ_get", wasi_environ_get, "(**)i"},
  {"environ_sizes_get", wasi_environ_sizes_get, "(**)i"},
  {"fd_advise", wasi_fd_advise, "(iIIi)i"},
  {"fd_allocate", wasi_fd_allocate, "(iII)i"},
  {"fd_close", wasi_fd_close, "(i)i"},
  {"fd_datasync", wasi_fd_datasync, "(i)i"},
  {"fd_fdstat_get", wasi_fd_fdstat_get, "(i*)i"},
  {"fd_fdstat_set_flags", wasi_fd_fdstat_set_flags, "(ii)i"},
  {"fd_fdstat_set_rights", wasi_fd_fdstat_set_rights, "(iII)i"},
  {"fd_filestat_get", wasi_fd_filestat_get, "(i*)i"},
  {"fd_filestat_set_size", wasi_fd_filestat_set_size, "(iI)i"},
  {"fd_filestat_set_times", wasi_fd_filestat_set_times, "(iIIi)i"},
  {"fd_pread", wasi_fd_pread, "(i*iI*)i"},
  {"fd_pwrite", wasi_fd_pwrite, "(i*iI*)i"},
  {"fd_prestat_dir_name", wasi_fd_prestat_dir_name, "(i*~)i"},
  {"fd_prestat_get", wasi_fd_prestat_get, "(i*)i"},
  {"fd_read", wasi_fd_read, "(i*i*)i"},
  {"fd_readdir", wasi_fd_readdir, "(i*~I*)i"},
  {"fd_renumber", wasi_fd_renumber, "(ii)i"},
  {"fd_seek", wasi_fd_seek, "(iIi*)i"},
  {"fd_sync", wasi_fd_sync, "(i)i"},
  {"fd_tell", wasi_fd_tell, "(i*)i"},
  {"fd_write", wasi_fd_write, "(i*i*)i"},
  {"path_create_directory", wasi_path_create_directory, "(i*~)i"},
  {"path_filestat_get", wasi_path_filestat_get, "(ii*~*)i"},
  {"path_filestat_set_times", wasi_path_filestat_set_times, "(ii*~IIi)i"},
  {"path_link", wasi_path_link, "(ii*~i*~)i"},
  {"path_open", wasi_path_open, "(ii*~iIIi*)i"},
  {"path_readlink", wasi_path_readlink, "(i*~*~*)i"},
  {"path_remove_directory", wasi_path_remove_directory, "(i*~)i"},
  {"path_rename", wasi_path_rename, "(i*~i*~)i"},
  {"path_symlink", wasi_path_symlink, "(*~i*~)i"},
  {"path_unlink_file", wasi_path_unlink_file, "(i*~)i"},
  {"poll_oneoff", wasi_poll_oneoff, "(**i*)i"},
  {"proc_exit", wasi_proc_exit, "(i)"},
  {"proc_raise", wasi_proc_raise, "(i)i"},
  {"random_get", wasi_random_get, "(*~)i"},
};

// Function to get the number of WASI symbols
static size_t wasi_native_symbols_count() {
  return sizeof(wasi_native_symbols) / sizeof(NativeSymbol);
} 