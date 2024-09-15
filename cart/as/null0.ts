// include this in your null0 cart
// asc src/index.ts  --target release --use trace=_null0_trace --use abort=_null0_abort --use seed=_null0_seed --lib ./null0.ts

// log a string
@external("null0", "trace")
declare function _null0_real_trace(text: ArrayBuffer): void

// these are called by language
// https://www.assemblyscript.org/concepts.html#special-imports
// TODO: would WASI help with these?

export function _null0_trace(message: String): void {
  _null0_real_trace(String.UTF8.encode(message, true));
}

export function _null0_abort(message: String, fileName: String, line: u32, column: u32): void {
  _null0_real_trace(String.UTF8.encode("ABORT: " + message, true));
}

export function _null0_seed(): f64 {
  return 1.0;
}
