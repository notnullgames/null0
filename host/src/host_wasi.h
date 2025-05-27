#ifndef HOST_WASI_H_
#define HOST_WASI_H_

#include "host.h"

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

/* API: https://github.com/WebAssembly/WASI/blob/main/phases/snapshot/docs.md */

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
#define WASI_FD_STDIN 0
#define WASI_FD_STDOUT 1
#define WASI_FD_STDERR 2

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

typedef uint8_t wasi_whence_t;
#define WASI_WHENCE_SET 0
#define WASI_WHENCE_CUR 1
#define WASI_WHENCE_END 2

struct wasi_fd_table_t;

typedef struct wasi_preopen_s {
  const char *mapped_path;
  const char *real_path;
} wasi_preopen_t;

typedef struct wasi_preopen_socket_s {
  const char *address;
  int port;
} wasi_preopen_socket_t;

#endif // HOST_WASI_H_
