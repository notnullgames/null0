// this uses physfs to create WASI functions for both hosts

#include "host_wasi.h"

#ifndef EMSCRIPTEN
cvector_vector_type(NativeSymbol) wasi_native_symbols = NULL;
#endif

// lil helpers to simplify working with passing data back/forth
static void set_cart_uint(uint32_t cart_ptr, uint32_t value) {
  copy_memory_to_cart_pointer(cart_ptr, &value, sizeof(uint32_t));
}
static uint32_t get_cart_uint(uint32_t cart_ptr) {
  uint32_t value = 0;
  copy_memory_from_cart_pointer(cart_ptr, &value, sizeof(uint32_t));
  return value;
}

WASI_FUNCTION(wasi_errno_t, args_get, (char **argv, char *argv_buf), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, args_sizes_get, (wasi_size_t * argc, wasi_size_t *argv_buf_size), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, clock_res_get, (wasi_clockid_t clock_id, wasi_timestamp_t *resolution), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, clock_time_get, (wasi_clockid_t clock_id, wasi_timestamp_t precision, wasi_timestamp_t *time), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, environ_get, (char **environment, char *environ_buf), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, environ_sizes_get, (wasi_size_t * environ_count, wasi_size_t *environ_buf_size), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_advise, (wasi_fd_t fd, wasi_filesize_t offset, wasi_filesize_t len, wasi_advice_t advice), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_allocate, (wasi_fd_t fd, wasi_filesize_t offset, wasi_filesize_t len), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_close, (wasi_fd_t fd), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_datasync, (wasi_fd_t fd), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_fdstat_get, (wasi_fd_t fd, wasi_fdstat_t *buf), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_fdstat_set_flags, (wasi_fd_t fd, wasi_fdflags_t flags), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_fdstat_set_rights, (wasi_fd_t fd, wasi_rights_t fs_rights_base, wasi_rights_t fs_rights_inheriting), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_filestat_get, (wasi_fd_t fd, wasi_filestat_t *buf), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_filestat_set_size, (wasi_fd_t fd, wasi_filesize_t st_size), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_filestat_set_times, (wasi_fd_t fd, wasi_timestamp_t st_atim, wasi_timestamp_t st_mtim, wasi_fstflags_t fst_flags), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_pread, (wasi_fd_t fd, const wasi_iovec_t *iovs, wasi_size_t iovs_len, wasi_filesize_t offset, wasi_size_t *nread), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_prestat_get, (wasi_fd_t fd, wasi_prestat_t *buf), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_prestat_dir_name, (wasi_fd_t fd, char *path, wasi_size_t path_len), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_pwrite, (wasi_fd_t fd, const wasi_ciovec_t *iovs, wasi_size_t iovs_len, wasi_filesize_t offset, wasi_size_t *nwritten), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_read, (wasi_fd_t fd, const wasi_iovec_t *iovs, wasi_size_t iovs_len, wasi_size_t *nread), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_readdir, (wasi_fd_t fd, void *buf, wasi_size_t buf_len, wasi_dircookie_t cookie, wasi_size_t *bufused), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_renumber, (wasi_fd_t from, wasi_fd_t to), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_seek, (wasi_fd_t fd, wasi_filedelta_t offset, wasi_whence_t whence, wasi_filesize_t *newoffset), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_sync, (wasi_fd_t fd), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, fd_tell, (wasi_fd_t fd, wasi_filesize_t *offset), {
  return WASI_ESUCCESS;
})

WASI_FUNCTION(wasi_errno_t, fd_write, (uint32_t fd, uint32_t iovs_cp, uint32_t iovs_len, uint32_t nwritten_cp), {
  uint32_t nwritten = 0;

  for (int i = 0; i < iovs_len; i++) {
    uint32_t ptr = iovs_cp + (i * sizeof(uint32_t) * 2);
    uint32_t buf = get_cart_uint(ptr);
    uint32_t buflen = get_cart_uint(ptr + sizeof(uint32_t));
    unsigned char *b = copy_memory_from_cart(buf, buflen);
    nwritten += buflen;
    if (fd == WASI_FD_STDOUT || fd == WASI_FD_STDERR) {
      write(fd, b, buflen);
    }
    free(b);
  }

  set_cart_uint(nwritten_cp, nwritten);
  return WASI_ESUCCESS;
})

WASI_FUNCTION(wasi_errno_t, path_create_directory, (wasi_fd_t fd, const char *path, wasi_size_t path_len), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, path_filestat_get, (wasi_fd_t fd, wasi_lookupflags_t flags, const char *path, wasi_size_t path_len, wasi_filestat_t *buf), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, path_filestat_set_times, (wasi_fd_t fd, wasi_lookupflags_t flags, const char *path, wasi_size_t path_len, wasi_timestamp_t st_atim, wasi_timestamp_t st_mtim, wasi_fstflags_t fst_flags), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, path_link, (wasi_fd_t old_fd, wasi_lookupflags_t old_flags, const char *old_path, wasi_size_t old_path_len, wasi_fd_t new_fd, const char *new_path, wasi_size_t new_path_len), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, path_open, (wasi_fd_t dirfd, wasi_lookupflags_t dirflags, const char *path, wasi_size_t path_len, wasi_oflags_t o_flags, wasi_rights_t fs_rights_base, wasi_rights_t fs_rights_inheriting, wasi_fdflags_t fs_flags, wasi_fd_t *fd), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, path_readlink, (wasi_fd_t fd, const char *path, wasi_size_t path_len, char *buf, wasi_size_t buf_len, wasi_size_t *bufused), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, path_remove_directory, (wasi_fd_t fd, const char *path, wasi_size_t path_len), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, path_rename, (wasi_fd_t old_fd, const char *old_path, wasi_size_t old_path_len, wasi_fd_t new_fd, const char *new_path, wasi_size_t new_path_len), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, path_symlink, (const char *old_path, wasi_size_t old_path_len, wasi_fd_t fd, const char *new_path, wasi_size_t new_path_len), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, path_unlink_file, (wasi_fd_t fd, const char *path, wasi_size_t path_len), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, poll_oneoff, (const wasi_subscription_t *in, wasi_event_t *out, wasi_size_t nsubscriptions, wasi_size_t *nevents), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, proc_exit, (wasi_exitcode_t rval), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, proc_raise, (wasi_signal_t sig), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, random_get, (void *buf, wasi_size_t buf_len), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, sched_yield, (), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, sock_accept, (wasi_fd_t sock, wasi_fdflags_t flags, wasi_fd_t *fd), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, sock_recv, (wasi_fd_t sock, const wasi_iovec_t *ri_data, wasi_size_t ri_data_len, wasi_riflags_t ri_flags, wasi_size_t *ro_datalen, wasi_roflags_t *ro_flags), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, sock_send, (wasi_fd_t sock, const wasi_ciovec_t *si_data, wasi_size_t si_data_len, wasi_siflags_t si_flags, wasi_size_t *so_datalen), {
  return WASI_ESUCCESS;
})
WASI_FUNCTION(wasi_errno_t, sock_shutdown, (wasi_fd_t sock, wasi_sdflags_t how), {
  return WASI_ESUCCESS;
})
