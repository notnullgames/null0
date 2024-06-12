// this will eventually be generated

const MAX_STRING_LEN = 1024 * 20

export default function wireCartToHost (host, cart) {
  const copyBytesFromCart = (cartPtr, size, retPtr) => {
    const hostPtr = retPtr || host._malloc(size)
    const buf = cart.memory.buffer.slice(cartPtr, cartPtr + size)
    const pointerHeap = new Uint8Array(host.HEAPU8.buffer, hostPtr, size)
    pointerHeap.set(new Uint8Array(buf))
    return hostPtr
  }

  const copyBytesToCart = (hostPtr, size, retPtr) => {
    const cartPtr = retPtr || cart.malloc(size)
    const buf = host.HEAPU8.buffer.slice(hostPtr, hostPtr + size)
    const pointerHeap = new Uint8Array(cart.memory.buffer)
    pointerHeap.set(new Uint8Array(buf), cartPtr, size)
    return cartPtr
  }

  const cartStrlen = (pointer) => {
    let end = pointer
    const buf = new Uint8Array(cart.memory.buffer)
    while (end < (pointer + MAX_STRING_LEN)) {
      if (buf[end] === 0) {
        break
      }
      end++
    }
    return end - pointer
  }

  const hostStrlen = (pointer) => {
    let end = pointer
    const buf = new Uint8Array(host.HEAPU8.buffer)
    while (end < (pointer + MAX_STRING_LEN)) {
      if (buf[end] === 0) {
        break
      }
      end++
    }
    return end - pointer
  }

  return {
    trace (strPtr) {
      console.log(cart.getString(strPtr))
    },

    image_gradient (width, height, topLeftPtr, topRightPtr, bottomLeftPtr, bottomRightPtr) {
      const hostTopLeftPtr = copyBytesFromCart(topLeftPtr, 4)
      const hostTopRightPtr = copyBytesFromCart(topRightPtr, 4)
      const hostBottomLeftPtr = copyBytesFromCart(bottomLeftPtr, 4)
      const hostBottomRightPtr = copyBytesFromCart(bottomRightPtr, 4)
      const r = host._null0_image_gradient(width, height, hostTopLeftPtr, hostTopRightPtr, hostBottomLeftPtr, hostBottomRightPtr)
      host._free(hostTopLeftPtr)
      host._free(hostTopRightPtr)
      host._free(hostBottomLeftPtr)
      host._free(hostBottomRightPtr)
      return r
    },

    clear (colorPtr) {
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      host._null0_clear(hostColorPtr)
      host._free(hostColorPtr)
    },

    draw_ellipse (centerX, centerY, radiusX, radiusY, colorPtr) {
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      host._null0_draw_ellipse(centerX, centerY, radiusX, radiusY, hostColorPtr)
      host._free(hostColorPtr)
    },

    draw_triangle (x1, y1, x2, y2, x3, y3, colorPtr) {
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      host._null0_draw_triangle(x1, y1, x2, y2, x3, y3, hostColorPtr)
      host._free(hostColorPtr)
    },

    draw_circle (centerX, centerY, radius, colorPtr) {
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      host._null0_draw_circle(centerX, centerY, radius, hostColorPtr)
      host._free(hostColorPtr)
    },

    draw_rectangle (posX, posY, width, height, colorPtr) {
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      host._null0_draw_rectangle(posX, posY, width, height, hostColorPtr)
      host._free(hostColorPtr)
    },

    draw_rectangle_outline (posX, posY, width, height, colorPtr) {
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      host._null0_draw_rectangle_outline(posX, posY, width, height, hostColorPtr)
      host._free(hostColorPtr)
    },

    draw_circle_outline (centerX, centerY, radius, colorPtr) {
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      host._null0_draw_circle_outline(centerX, centerY, radius, hostColorPtr)
      host._free(hostColorPtr)
    },

    draw_point (x, y, colorPtr) {
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      host._null0_draw_point(x, y, hostColorPtr)
      host._free(hostColorPtr)
    },

    draw_line (startPosX, startPosY, endPosX, endPosY, colorPtr) {
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      host._null0_draw_line(startPosX, startPosY, endPosX, endPosY, hostColorPtr)
      host._free(hostColorPtr)
    },

    draw_image (src, posX, posy) {
      host._null0_draw_image(src, posX, posy)
    },

    color_tint (retPtr, colorPtr, tintPtr) {
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      const hostTintPtr = copyBytesFromCart(colorPtr, 4)
      const hostRetPtr = host._malloc(4)
      host._null0_color_tint(hostRetPtr, hostColorPtr, hostTintPtr)
      copyBytesToCart(hostRetPtr, 4, retPtr)
      host._free(hostColorPtr)
      host._free(hostTintPtr)
      host._free(hostRetPtr)
    },

    measure_text (retPtr, font, textPtr) {
      const len = cartStrlen(textPtr)
      const textHostPtr = copyBytesFromCart(textPtr, len)
      const retHostPtr = host._malloc(8)
      host._null0_measure_text(retHostPtr, font, textHostPtr)
      copyBytesToCart(retHostPtr, 8, retPtr)
      host._free(textHostPtr)
      host._free(retHostPtr)
    },

    load_image (filenamePtr) {
      const filenameHostPtr = copyBytesFromCart(filenamePtr, cartStrlen(filenamePtr) + 1)
      const index = host._null0_load_image(filenameHostPtr)
      host._free(filenameHostPtr)
      return index
    },

    draw_text (font, textPtr, posX, posY, colorPtr) {
      const textHostPtr = copyBytesFromCart(textPtr, cartStrlen(textPtr) + 1)
      const hostColorPtr = copyBytesFromCart(colorPtr, 4)
      host._null0_draw_text(font, textHostPtr, posX, posY, hostColorPtr)
      host._free(textHostPtr)
      host._free(hostColorPtr)
    },

    load_font_ttf (filenamePtr, fontSize) {
      const filenameHostPtr = copyBytesFromCart(filenamePtr, cartStrlen(filenamePtr) + 1)
      const index = host._null0_load_font_ttf(filenameHostPtr, fontSize)
      host._free(filenameHostPtr)
      return index
    },

    load_sound (filenamePtr) {
      const filenameHostPtr = copyBytesFromCart(filenamePtr, cartStrlen(filenamePtr) + 1)
      const index = host._null0_load_sound(filenameHostPtr)
      host._free(filenameHostPtr)
      return index
    },

    play_sound (sound, loop) {
      host._null0_play_sound(sound, loop)
    },

    unload_sound (sound) {
      host._null0_unload_sound(sound)
    },

    get_write_dir () {
      const hostRetPtr = host._null0_get_write_dir()
      const len = hostStrlen(hostRetPtr)
      return copyBytesToCart(hostRetPtr, len)
    },

    file_read (filenamePtr, bytesReadPtr) {
      const filenameHostPtr = copyBytesFromCart(filenamePtr, cartStrlen(filenamePtr) + 1)
      const bytesReadHostPtr = host._malloc(4)
      const hostRetPtr = host._null0_file_read(filenameHostPtr, bytesReadHostPtr)
      copyBytesToCart(bytesReadHostPtr, 4, bytesReadPtr)
      const len = host.HEAPU32[bytesReadHostPtr / 4]
      const ret = copyBytesToCart(hostRetPtr, len)
      host._free(filenameHostPtr)
      host._free(bytesReadHostPtr)
      host._free(hostRetPtr)
      return ret
    },

    file_info (retPtr, filenamePtr) {
      const retHostPtr = host._malloc(96)
      const filenameHostPtr = copyBytesFromCart(filenamePtr, cartStrlen(filenamePtr) + 1)
      host._null0_file_info(retHostPtr, filenameHostPtr)
      copyBytesToCart(retHostPtr, 96, retPtr)
      host._free(retHostPtr)
      host._free(filenameHostPtr)
    },

    file_write (filenamePtr, bytesPtr, byteSize) {
      const filenameHostPtr = copyBytesFromCart(filenamePtr, cartStrlen(filenamePtr) + 1)
      const bytesHostPtr = copyBytesFromCart(bytesPtr, byteSize)
      copyBytesFromCart(bytesHostPtr, byteSize, bytesPtr)
      const ret = host._null0_file_write(filenameHostPtr, bytesHostPtr, byteSize)
      host._free(filenameHostPtr)
      host._free(bytesHostPtr)
      return ret
    },

    new_sfx (paramsPtr) {
      // return id
    },

    preset_sfx (paramsPtr, type) {
    }
  }
}
