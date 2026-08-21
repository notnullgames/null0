// null0 cart entry for haxe HL/C carts.
// This shadows hashlink's hlc_main.c (via include path) so the module boots
// the haxe runtime at _start and then lets the null0 host drive the
// load/update/... callbacks (exported from null0_shim.c).
#include <hlc.h>

int main(int argc, char *argv[]) {
  (void)argv;
  hl_global_init();
  hl_register_thread(&argc);
  hl_setup_callbacks(hlc_static_call, hlc_get_wrapper);
  hl_sys_init(NULL, 0, NULL);
  hl_entry_point();
  // do not hl_global_free() or proc_exit() here: the host keeps calling
  // into the cart (load/update/...) after main() returns.
  return 0;
}
