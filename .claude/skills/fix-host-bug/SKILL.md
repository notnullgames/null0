---
name: fix-host-bug
description: Debug or fix the null0 host/engine - crashes (SIGSEGV/SIGBUS), carts that stop after load, filesystem and save issues, WASI problems, input or rendering bugs in host/src. Use when a cart misbehaves in a way that is not the cart's fault, or when adding engine-side behavior.
---

# Fix a host bug

## Know which files you may edit

- **Generated, do not touch**: `host/src/host.c` (from `tools/gen_host.js`).
  Fix the generator or add a helper in `host_header.h` instead.
- **Hand-written**: `host_header.h` (helpers, cart-memory copying, handle
  vectors), `host.h` (the `HOST_FUNCTION` macro), `main.c` (pntr_app entry),
  `cart_wamr.c` (native cart loading/callbacks), `cart_emscripten.c` + `webroot/`
  (web equivalents), `fs.c` (physfs), `wasi_physfs.h` (the WASI subset).

Changes that affect cart lifecycle usually need the same edit in **both**
`cart_wamr.c` and the web path (`webroot/null0.js`).

## Reproduce with the smallest possible cart

Write a throwaway cart that calls only the suspect function, build it, and run
it under `timeout` (see the `run-cart` skill). Bisect by commenting calls out -
host crashes usually come from one specific host function, and the stack trace
printed by WAMR only covers the _cart_ side, not the host.

Then confirm whether the bug is language-specific: run the same call from a C
cart and from lua. If both crash, it's the host; if only one does, it's that
language's binding.

## The usual suspects

- **Unchecked pointer from physfs**: `PHYSFS_openRead/openWrite/openAppend`
  return NULL on failure. A missing NULL check crashes the host (this was the
  `save_image` bug: `si_addr: 0x8`).
- **Bad handle**: `Image`/`Font`/`Sound` handles are bounds-checked by
  `get_image`/`get_font`/`get_sound` - an out-of-range handle logs a warning
  and the call is skipped. If a cart still crashes the host with a handle, the
  handle came back from an `add_*` with a NULL pointer (a failed load) and the
  bug is there.
- **ABI mismatch**: a binding that declares a struct return by value instead of
  as a cart pointer will corrupt the argument list. Symptom: shifted/garbage
  field values, then a crash. Verify against the host signature in `host.c`,
  which is the truth.
- **Cart stops after `load`**: something called `proc_exit`; the host then skips
  every callback (`wasi_cart_has_exited`). Look at what the cart's runtime does
  when its `main` returns.
- **Cart never starts**: the host calls `_start`, else `_initialize` (wasi
  reactor), else `main`, then `load`. A module exporting none of those does
  nothing.
- **File not found from a cart**: physfs mounts the cart zip, and the write dir
  (a per-cart pref dir) is mounted last. Note WASI exposes one preopen `/` and
  **no working directory** - runtimes written in go must use absolute paths.

## Fix it, then prove it

1. Make the fix in the hand-written file (or the generator).
2. `cmake --build build --target host`.
3. Re-run the reproducer: it should now report a clear error instead of
   crashing, or work.
4. Test the failure path too - e.g. saving into a directory that doesn't exist
   should print an error and keep running.
5. Regression pass over one cart per family (`run-cart` skill), and rebuild the
   web host (`npm run host:web`) if you touched anything shared.
6. Remove every debug print before finishing.

## Style

Match the surrounding code: 2-space indent, braces on the same line, early
returns for error cases, and a short lowercase comment explaining _why_ when the
reason isn't obvious. Report failures with a real message
(`PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())`), not silence.
