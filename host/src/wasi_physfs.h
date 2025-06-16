#include "wasm_export.h"

#include <stddef.h>
#include <stdint.h>

typedef uint32_t wasi_size_t;

typedef uint8_t wasi_advice_t;
#define WASI_ADVICE_NORMAL 0
#define WASI_ADVICE_SEQUENTIAL 1
#define WASI_ADVICE_RANDOM 2
#define WASI_ADVICE_WILLNEED 3
#define WASI_ADVICE_DONTNEED 4
#define WASI_ADVICE_NOREUSE 5

typedef struct wasi_ciovec_s {
  const void *buf;
  wasi_size_t buf_len;
} wasi_ciovec_t;

typedef uint32_t wasi_clockid_t;
#define WASI_CLOCK_REALTIME 0
#define WASI_CLOCK_MONOTONIC 1
#define WASI_CLOCK_PROCESS_CPUTIME_ID 2
#define WASI_CLOCK_THREAD_CPUTIME_ID 3

typedef uint64_t wasi_device_t;

typedef uint64_t wasi_dircookie_t;
#define WASI_DIRCOOKIE_START 0

typedef uint16_t wasi_errno_t;
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

typedef uint16_t wasi_eventrwflags_t; /* Bitfield */
#define WASI_EVENT_FD_READWRITE_HANGUP (1 << 0)

typedef uint8_t wasi_eventtype_t;
#define WASI_EVENTTYPE_CLOCK 0
#define WASI_EVENTTYPE_FD_READ 1
#define WASI_EVENTTYPE_FD_WRITE 2

typedef uint32_t wasi_exitcode_t;

typedef uint32_t wasi_fd_t;

typedef uint16_t wasi_fdflags_t; /* Bitfield */
#define WASI_FDFLAG_APPEND (1 << 0)
#define WASI_FDFLAG_DSYNC (1 << 1)
#define WASI_FDFLAG_NONBLOCK (1 << 2)
#define WASI_FDFLAG_RSYNC (1 << 3)
#define WASI_FDFLAG_SYNC (1 << 4)

typedef int64_t wasi_filedelta_t;

typedef uint64_t wasi_filesize_t;

typedef uint8_t wasi_filetype_t;
#define WASI_FILETYPE_UNKNOWN 0
#define WASI_FILETYPE_BLOCK_DEVICE 1
#define WASI_FILETYPE_CHARACTER_DEVICE 2
#define WASI_FILETYPE_DIRECTORY 3
#define WASI_FILETYPE_REGULAR_FILE 4
#define WASI_FILETYPE_SOCKET_DGRAM 5
#define WASI_FILETYPE_SOCKET_STREAM 6
#define WASI_FILETYPE_SYMBOLIC_LINK 7

typedef uint16_t wasi_fstflags_t; /* Bitfield */
#define WASI_FILESTAT_SET_ATIM (1 << 0)
#define WASI_FILESTAT_SET_ATIM_NOW (1 << 1)
#define WASI_FILESTAT_SET_MTIM (1 << 2)
#define WASI_FILESTAT_SET_MTIM_NOW (1 << 3)

typedef uint64_t wasi_inode_t;

typedef struct wasi_iovec_s {
  void *buf;
  wasi_size_t buf_len;
} wasi_iovec_t;

typedef uint64_t wasi_linkcount_t;

typedef uint32_t wasi_lookupflags_t; /* Bitfield */
#define WASI_LOOKUP_SYMLINK_FOLLOW (1 << 0)

typedef uint16_t wasi_oflags_t; /* Bitfield */
#define WASI_O_CREAT (1 << 0)
#define WASI_O_DIRECTORY (1 << 1)
#define WASI_O_EXCL (1 << 2)
#define WASI_O_TRUNC (1 << 3)

typedef uint8_t wasi_preopentype_t;
#define WASI_PREOPENTYPE_DIR 0

typedef struct wasi_prestat_s {
  wasi_preopentype_t pr_type;
  union wasi_prestat_u {
    struct wasi_prestat_dir_t {
      wasi_size_t pr_name_len;
    } dir;
  } u;
} wasi_prestat_t;

typedef uint16_t wasi_riflags_t; /* Bitfield */
#define WASI_SOCK_RECV_PEEK (1 << 0)
#define WASI_SOCK_RECV_WAITALL (1 << 1)

typedef uint64_t wasi_rights_t; /* Bitfield */
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

typedef uint16_t wasi_roflags_t; /* Bitfield */
#define WASI_SOCK_RECV_DATA_TRUNCATED (1 << 0)

typedef uint8_t wasi_sdflags_t; /* Bitfield */
#define WASI_SHUT_RD (1 << 0)
#define WASI_SHUT_WR (1 << 1)

typedef uint16_t wasi_siflags_t; /* Bitfield */

typedef uint8_t wasi_signal_t;
#define WASI_SIGHUP 1
#define WASI_SIGINT 2
#define WASI_SIGQUIT 3
#define WASI_SIGILL 4
#define WASI_SIGTRAP 5
#define WASI_SIGABRT 6
#define WASI_SIGBUS 7
#define WASI_SIGFPE 8
#define WASI_SIGKILL 9
#define WASI_SIGUSR1 10
#define WASI_SIGSEGV 11
#define WASI_SIGUSR2 12
#define WASI_SIGPIPE 13
#define WASI_SIGALRM 14
#define WASI_SIGTERM 15
#define WASI_SIGCHLD 16
#define WASI_SIGCONT 17
#define WASI_SIGSTOP 18
#define WASI_SIGTSTP 19
#define WASI_SIGTTIN 20
#define WASI_SIGTTOU 21
#define WASI_SIGURG 22
#define WASI_SIGXCPU 23
#define WASI_SIGXFSZ 24
#define WASI_SIGVTALRM 25
#define WASI_SIGPROF 26
#define WASI_SIGWINCH 27
#define WASI_SIGPOLL 28
#define WASI_SIGPWR 29
#define WASI_SIGSYS 30

typedef uint16_t wasi_subclockflags_t; /* Bitfield */
#define WASI_SUBSCRIPTION_CLOCK_ABSTIME (1 << 0)

typedef uint64_t wasi_timestamp_t;

typedef uint64_t wasi_userdata_t;

typedef struct wasi_subscription_s {
  wasi_userdata_t userdata;
  wasi_eventtype_t type;
  union {
    struct {
      wasi_clockid_t clock_id;
      wasi_timestamp_t timeout;
      wasi_timestamp_t precision;
      wasi_subclockflags_t flags;
    } clock;
    struct {
      wasi_fd_t fd;
    } fd_readwrite;
  } u;
} wasi_subscription_t;

typedef struct wasi_dirent_s {
  wasi_dircookie_t d_next;
  wasi_inode_t d_ino;
  uint32_t d_namlen;
  wasi_filetype_t d_type;
} wasi_dirent_t;

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

typedef struct wasi_event_s {
  wasi_userdata_t userdata;
  wasi_errno_t error;
  wasi_eventtype_t type;
  union {
    struct {
      wasi_filesize_t nbytes;
      wasi_eventrwflags_t flags;
    } fd_readwrite;
  } u;
} wasi_event_t;

typedef struct iovec_app {
  uint32_t buf_offset;
  uint32_t buf_len;
} iovec_app_t;

typedef struct wasi_prestat_app {
  wasi_preopentype_t pr_type;
  uint32_t pr_name_len;
} wasi_prestat_app_t;

typedef uint8_t wasi_whence_t;
#define WASI_WHENCE_SET 0
#define WASI_WHENCE_CUR 1
#define WASI_WHENCE_END 2

static wasi_errno_t wasi_args_get(wasm_exec_env_t exec_env, uint32_t *argv_offsets, char *argv_buf) {
  return 0;
}

static wasi_errno_t wasi_args_sizes_get(wasm_exec_env_t exec_env, uint32_t *argc_app, uint32_t *argv_buf_size_app) {
  return 0;
}

static wasi_errno_t wasi_clock_res_get(wasm_exec_env_t exec_env, wasi_clockid_t clock_id, wasi_timestamp_t *resolution) {
  return 0;
}

static wasi_errno_t wasi_clock_time_get(wasm_exec_env_t exec_env, wasi_clockid_t clock_id, wasi_timestamp_t precision, wasi_timestamp_t *time) {
  return 0;
}

static wasi_errno_t wasi_environ_get(wasm_exec_env_t exec_env, uint32_t *environ_offsets, char *environ_buf) {
  return 0;
}

static wasi_errno_t wasi_environ_sizes_get(wasm_exec_env_t exec_env, uint32_t *environ_count_app, uint32_t *environ_buf_size_app) {
  return 0;
}

static wasi_errno_t wasi_fd_prestat_get(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_prestat_app_t *prestat_app) {
  return 0;
}

static wasi_errno_t wasi_fd_prestat_dir_name(wasm_exec_env_t exec_env, wasi_fd_t fd, char *path, uint32_t path_len) {
  return 0;
}

static wasi_errno_t wasi_fd_close(wasm_exec_env_t exec_env, wasi_fd_t fd) {
  return 0;
}

static wasi_errno_t wasi_fd_datasync(wasm_exec_env_t exec_env, wasi_fd_t fd) {
  return 0;
}

static wasi_errno_t wasi_fd_pread(wasm_exec_env_t exec_env, wasi_fd_t fd, iovec_app_t *iovec_app, uint32_t iovs_len, wasi_filesize_t offset, uint32_t *nread_app) {
  return 0;
}

static wasi_errno_t wasi_fd_pwrite(wasm_exec_env_t exec_env, wasi_fd_t fd, const iovec_app_t *iovec_app, uint32_t iovs_len, wasi_filesize_t offset, uint32_t *nwritten_app) {
  return 0;
}

static wasi_errno_t wasi_fd_read(wasm_exec_env_t exec_env, wasi_fd_t fd, const iovec_app_t *iovec_app, uint32_t iovs_len, uint32_t *nread_app) {
  return 0;
}

static wasi_errno_t wasi_fd_renumber(wasm_exec_env_t exec_env, wasi_fd_t from, wasi_fd_t to) {
  return 0;
}

static wasi_errno_t wasi_fd_seek(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filedelta_t offset, wasi_whence_t whence, wasi_filesize_t *newoffset) {
  return 0;
}

static wasi_errno_t wasi_fd_tell(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filesize_t *newoffset) {
  return 0;
}

static wasi_errno_t wasi_fd_fdstat_get(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_fdstat_t *fdstat_app) {
  return 0;
}

static wasi_errno_t wasi_fd_fdstat_set_flags(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_fdflags_t flags) {
  return 0;
}

static wasi_errno_t wasi_fd_fdstat_set_rights(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_rights_t fs_rights_base, wasi_rights_t fs_rights_inheriting) {
  return 0;
}

static wasi_errno_t wasi_fd_sync(wasm_exec_env_t exec_env, wasi_fd_t fd) {
  return 0;
}

static wasi_errno_t wasi_fd_write(wasm_exec_env_t exec_env, wasi_fd_t fd, const iovec_app_t *iovec_app, uint32_t iovs_len, uint32_t *nwritten_app) {
  return 0;
}

static wasi_errno_t wasi_fd_advise(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filesize_t offset, wasi_filesize_t len, wasi_advice_t advice) {
  return 0;
}

static wasi_errno_t wasi_fd_allocate(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filesize_t offset, wasi_filesize_t len) {
  return 0;
}

static wasi_errno_t wasi_path_create_directory(wasm_exec_env_t exec_env, wasi_fd_t fd, const char *path, uint32_t path_len) {
  return 0;
}

static wasi_errno_t wasi_path_link(wasm_exec_env_t exec_env, wasi_fd_t old_fd, wasi_lookupflags_t old_flags, const char *old_path, uint32_t old_path_len, wasi_fd_t new_fd, const char *new_path, uint32_t new_path_len) {
  return 0;
}

static wasi_errno_t wasi_path_open(wasm_exec_env_t exec_env, wasi_fd_t dirfd, wasi_lookupflags_t dirflags, const char *path, uint32_t path_len, wasi_oflags_t oflags, wasi_rights_t fs_rights_base, wasi_rights_t fs_rights_inheriting, wasi_fdflags_t fs_flags, wasi_fd_t *fd_app) {
  return 0;
}

static wasi_errno_t wasi_fd_readdir(wasm_exec_env_t exec_env, wasi_fd_t fd, void *buf, uint32_t buf_len, wasi_dircookie_t cookie, uint32_t *bufused_app) {
  return 0;
}

static wasi_errno_t wasi_path_readlink(wasm_exec_env_t exec_env, wasi_fd_t fd, const char *path, uint32_t path_len, char *buf, uint32_t buf_len, uint32_t *bufused_app) {
  return 0;
}

static wasi_errno_t wasi_path_rename(wasm_exec_env_t exec_env, wasi_fd_t old_fd, const char *old_path, uint32_t old_path_len, wasi_fd_t new_fd, const char *new_path, uint32_t new_path_len) {
  return 0;
}

static wasi_errno_t wasi_fd_filestat_get(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filestat_t *filestat) {
  return 0;
}

static wasi_errno_t wasi_fd_filestat_set_times(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_timestamp_t st_atim, wasi_timestamp_t st_mtim, wasi_fstflags_t fstflags) {
  return 0;
}

static wasi_errno_t wasi_fd_filestat_set_size(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_filesize_t st_size) {
  return 0;
}

static wasi_errno_t wasi_path_filestat_get(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_lookupflags_t flags, const char *path, uint32_t path_len, wasi_filestat_t *filestat) {
  return 0;
}

static wasi_errno_t wasi_path_filestat_set_times(wasm_exec_env_t exec_env, wasi_fd_t fd, wasi_lookupflags_t flags, const char *path, uint32_t path_len, wasi_timestamp_t st_atim, wasi_timestamp_t st_mtim, wasi_fstflags_t fstflags) {
  return 0;
}

static wasi_errno_t wasi_path_symlink(wasm_exec_env_t exec_env, const char *old_path, uint32_t old_path_len, wasi_fd_t fd, const char *new_path, uint32_t new_path_len) {
  return 0;
}

static wasi_errno_t wasi_path_unlink_file(wasm_exec_env_t exec_env, wasi_fd_t fd, const char *path, uint32_t path_len) {
  return 0;
}

static wasi_errno_t wasi_path_remove_directory(wasm_exec_env_t exec_env, wasi_fd_t fd, const char *path, uint32_t path_len) {
  return 0;
}

static wasi_errno_t wasi_poll_oneoff(wasm_exec_env_t exec_env, const wasi_subscription_t *in, wasi_event_t *out, uint32_t nsubscriptions, uint32_t *nevents_app) {
  return 0;
}

static void wasi_proc_exit(wasm_exec_env_t exec_env, wasi_exitcode_t rval) {
}

static wasi_errno_t wasi_proc_raise(wasm_exec_env_t exec_env, wasi_signal_t sig) {
  return 0;
}

static wasi_errno_t wasi_random_get(wasm_exec_env_t exec_env, void *buf, uint32_t buf_len) {
  return 0;
}

static NativeSymbol wasi_native_symbols[] = {
  {"args_get", wasi_args_get, "(**)i"},
  {"args_sizes_get", wasi_args_sizes_get, "(**)i"},
  {"clock_res_get", wasi_clock_res_get, "(i*)i"},
  {"clock_time_get", wasi_clock_time_get, "(iI*)i"},
  {"environ_get", wasi_environ_get, "(**)i"},
  {"environ_sizes_get", wasi_environ_sizes_get, "(**)i"},
  {"fd_prestat_get", wasi_fd_prestat_get, "(i*)i"},
  {"fd_prestat_dir_name", wasi_fd_prestat_dir_name, "(i*~)i"},
  {"fd_close", wasi_fd_close, "(i)i"},
  {"fd_datasync", wasi_fd_datasync, "(i)i"},
  {"fd_pread", wasi_fd_pread, "(i*iI*)i"},
  {"fd_pwrite", wasi_fd_pwrite, "(i*iI*)i"},
  {"fd_read", wasi_fd_read, "(i*i*)i"},
  {"fd_renumber", wasi_fd_renumber, "(ii)i"},
  {"fd_seek", wasi_fd_seek, "(iIi*)i"},
  {"fd_tell", wasi_fd_tell, "(i*)i"},
  {"fd_fdstat_get", wasi_fd_fdstat_get, "(i*)i"},
  {"fd_fdstat_set_flags", wasi_fd_fdstat_set_flags, "(ii)i"},
  {"fd_fdstat_set_rights", wasi_fd_fdstat_set_rights, "(iII)i"},
  {"fd_sync", wasi_fd_sync, "(i)i"},
  {"fd_write", wasi_fd_write, "(i*i*)i"},
  {"fd_advise", wasi_fd_advise, "(iIIi)i"},
  {"fd_allocate", wasi_fd_allocate, "(iII)i"},
  {"path_create_directory", wasi_path_create_directory, "(i*~)i"},
  {"path_link", wasi_path_link, "(ii*~i*~)i"},
  {"path_open", wasi_path_open, "(ii*~iIIi*)i"},
  {"fd_readdir", wasi_fd_readdir, "(i*~I*)i"},
  {"path_readlink", wasi_path_readlink, "(i*~*~*)i"},
  {"path_rename", wasi_path_rename, "(i*~i*~)i"},
  {"fd_filestat_get", wasi_fd_filestat_get, "(i*)i"},
  {"fd_filestat_set_times", wasi_fd_filestat_set_times, "(iIIi)i"},
  {"fd_filestat_set_size", wasi_fd_filestat_set_size, "(iI)i"},
  {"path_filestat_get", wasi_path_filestat_get, "(ii*~*)i"},
  {"path_filestat_set_times", wasi_path_filestat_set_times, "(ii*~IIi)i"},
  {"path_symlink", wasi_path_symlink, "(*~i*~)i"},
  {"path_unlink_file", wasi_path_unlink_file, "(i*~)i"},
  {"path_remove_directory", wasi_path_remove_directory, "(i*~)i"},
  {"poll_oneoff", wasi_poll_oneoff, "(**i*)i"},
  {"proc_exit", wasi_proc_exit, "(i)"},
  {"proc_raise", wasi_proc_raise, "(i)i"},
  {"random_get", wasi_random_get, "(*~)i"},

  // These are not needed
  // {"sock_accept", wasi_sock_accept, "(ii*)i"},
  // {"sock_addr_local", wasi_sock_addr_local, "(i*)i"},
  // {"sock_addr_remote", wasi_sock_addr_remote, "(i*)i"},
  // {"sock_addr_resolve", wasi_sock_addr_resolve, "($$**i*)i"},
  // {"sock_bind", wasi_sock_bind, "(i*)i"},
  // {"sock_close", wasi_sock_close, "(i)i"},
  // {"sock_connect", wasi_sock_connect, "(i*)i"},
  // {"sock_get_broadcast", wasi_sock_get_broadcast, "(i*)i"},
  // {"sock_get_keep_alive", wasi_sock_get_keep_alive, "(i*)i"},
  // {"sock_get_linger", wasi_sock_get_linger, "(i**)i"},
  // {"sock_get_recv_buf_size", wasi_sock_get_recv_buf_size, "(i*)i"},
  // {"sock_get_recv_timeout", wasi_sock_get_recv_timeout, "(i*)i"},
  // {"sock_get_reuse_addr", wasi_sock_get_reuse_addr, "(i*)i"},
  // {"sock_get_reuse_port", wasi_sock_get_reuse_port, "(i*)i"},
  // {"sock_get_send_buf_size", wasi_sock_get_send_buf_size, "(i*)i"},
  // {"sock_get_send_timeout", wasi_sock_get_send_timeout, "(i*)i"},
  // {"sock_get_tcp_fastopen_connect", wasi_sock_get_tcp_fastopen_connect, "(i*)i"},
  // {"sock_get_tcp_keep_idle", wasi_sock_get_tcp_keep_idle, "(i*)i"},
  // {"sock_get_tcp_keep_intvl", wasi_sock_get_tcp_keep_intvl, "(i*)i"},
  // {"sock_get_tcp_no_delay", wasi_sock_get_tcp_no_delay, "(i*)i"},
  // {"sock_get_tcp_quick_ack", wasi_sock_get_tcp_quick_ack, "(i*)i"},
  // {"sock_get_ip_multicast_loop", wasi_sock_get_ip_multicast_loop, "(ii*)i"},
  // {"sock_get_ip_multicast_ttl", wasi_sock_get_ip_multicast_ttl, "(i*)i"},
  // {"sock_get_ip_ttl", wasi_sock_get_ip_ttl, "(i*)i"},
  // {"sock_get_ipv6_only", wasi_sock_get_ipv6_only, "(i*)i"},
  // {"sock_listen", wasi_sock_listen, "(ii)i"},
  // {"sock_open", wasi_sock_open, "(iii*)i"},
  // {"sock_recv", wasi_sock_recv, "(i*ii**)i"},
  // {"sock_recv_from", wasi_sock_recv_from, "(i*ii**)i"},
  // {"sock_send", wasi_sock_send, "(i*ii*)i"},
  // {"sock_send_to", wasi_sock_send_to, "(i*ii**)i"},
  // {"sock_set_broadcast", wasi_sock_set_broadcast, "(ii)i"},
  // {"sock_set_keep_alive", wasi_sock_set_keep_alive, "(ii)i"},
  // {"sock_set_linger", wasi_sock_set_linger, "(iii)i"},
  // {"sock_set_recv_buf_size", wasi_sock_set_recv_buf_size, "(ii)i"},
  // {"sock_set_recv_timeout", wasi_sock_set_recv_timeout, "(iI)i"},
  // {"sock_set_reuse_addr", wasi_sock_set_reuse_addr, "(ii)i"},
  // {"sock_set_reuse_port", wasi_sock_set_reuse_port, "(ii)i"},
  // {"sock_set_send_buf_size", wasi_sock_set_send_buf_size, "(ii)i"},
  // {"sock_set_send_timeout", wasi_sock_set_send_timeout, "(iI)i"},
  // {"sock_set_tcp_fastopen_connect", wasi_sock_set_tcp_fastopen_connect, "(ii)i"},
  // {"sock_set_tcp_keep_idle", wasi_sock_set_tcp_keep_idle, "(ii)i"},
  // {"sock_set_tcp_keep_intvl", wasi_sock_set_tcp_keep_intvl, "(ii)i"},
  // {"sock_set_tcp_no_delay", wasi_sock_set_tcp_no_delay, "(ii)i"},
  // {"sock_set_tcp_quick_ack", wasi_sock_set_tcp_quick_ack, "(ii)i"},
  // {"sock_set_ip_multicast_loop", wasi_sock_set_ip_multicast_loop, "(iii)i"},
  // {"sock_set_ip_multicast_ttl", wasi_sock_set_ip_multicast_ttl, "(ii)i"},
  // {"sock_set_ip_add_membership", wasi_sock_set_ip_add_membership, "(i*i)i"},
  // {"sock_set_ip_drop_membership", wasi_sock_set_ip_drop_membership, "(i*i)i"},
  // {"sock_set_ip_ttl", wasi_sock_set_ip_ttl, "(ii)i"},
  // {"sock_set_ipv6_only", wasi_sock_set_ipv6_only, "(ii)i"},
  // {"sock_shutdown", wasi_sock_shutdown, "(ii)i"},
  // {"sched_yield", wasi_sched_yield, "()i"},
};
