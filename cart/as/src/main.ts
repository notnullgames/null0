let x:u32 = 0
let y:u32 = 0

// called when the cart is loaded
export function load(): void {
  console.log("Hello from assemblyscript")
  const d = measure_text(0, "Hello from null0")
  console.log(`Text-size: ${d.width.toString()}x${d.height.toString()}`)
  x = 160 - (d.width/2)
  y = 120 - (d.height/2)
  
  const t = file_read("assets/cyber.txt")
  trace(`WASM ArrayBuffer size: ${t.byteLength.toString()}`)
  trace(String.UTF8.decode(t))
}

// called on every frame
export function update(): void {
  clear(BLACK)
  draw_text(0, "Hello from null0", x+1, y+1, BLUE)
  draw_text(0, "Hello from null0", x, y, RED)
}
