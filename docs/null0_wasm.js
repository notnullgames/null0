// Null0 host interface for web

const MAX_STRING_LEN = 1024 * 20

const td = new TextDecoder()

export default function wireCartToHost (host, cart) {
  const copyBytesFromCart = (cartPtr, size, retPtr) => {
    const cartMem = new DataView(cart.memory.buffer)
    const hostPtr = retPtr || host._malloc(size)
    for (let b = 0; b < size; b++) {
      host.HEAPU8[hostPtr + b] = cartMem.getUint8(cartPtr + b)
    }
    return hostPtr
  }

  const copyBytesToCart = (hostPtr, size, retPtr) => {
    const cartMem = new DataView(cart.memory.buffer)
    const cartPtr = retPtr || cart.malloc(size)
    for (let b = 0; b < size; b++) {
      cartMem.setUint8(cartPtr + b, host.HEAPU8[hostPtr + b])
    }
    return cartPtr
  }

  const cartStrlen = (pointer) => {
    const cartMem = new DataView(cart.memory.buffer)
    let end = pointer
    while (end < pointer + MAX_STRING_LEN) {
      if (cartMem.getUint8(end) === 0) {
        break
      }
      end++
    }
    return end - pointer
  }

  const hostStrlen = (pointer) => {
    let end = pointer
    while (end < pointer + MAX_STRING_LEN) {
      if (host.HEAPU8[end] === 0) {
        break
      }
      end++
    }
    return end - pointer
  }

  const cartStr = (pointer) => cart.getString(pointer, cartStrlen(pointer))

  return {
    trace (str) {
      console.log(cartStr(str))
    },
    current_time () {
      return BigInt(Date.now())
    },
    delta_time () {
      return host._null0_delta_time()
    },
    random_int (min, max) {
      return host._null0_random_int()
    },
    load_sound (filename) {
      const filenameHostPtr = copyBytesFromCart(
        filename,
        cartStrlen(filename) + 1
      )
      const r = host._null0_load_sound(filenameHostPtr)
      host._free(filenameHostPtr)
      return r
    },
    play_sound (sound, loop) {
      host._null0_play_sound(sound, loop)
    },
    stop_sound (sound) {
      host._null0_stop_sound(sound)
    },
    new_sfx (params) {
      const paramsHostPtr = copyBytesFromCart(params, 96)
      const r = host._null0_new_sfx(paramsHostPtr)
      host._free(paramsHostPtr)
      return r
    },
    preset_sfx (params, type) {
      const paramsHostPtr = copyBytesFromCart(params, 96)
      host._null0_preset_sfx(paramsHostPtr, type)
      copyBytesToCart(paramsHostPtr, 96, params)
      host._free(paramsHostPtr)
    },
    randomize_sfx (params, waveType) {
      const paramsHostPtr = copyBytesFromCart(params, 96)
      host._null0_randomize_sfx(paramsHostPtr, waveType)
      copyBytesToCart(params, 96, paramsHostPtr)
      host._free(paramsHostPtr)
    },
    mutate_sfx (params, range, mask) {
      const paramsHostPtr = copyBytesFromCart(params, 96)
      host._null0_mutate_sfx(paramsHostPtr, range, mask)
      host._free(paramsHostPtr)
    },
    load_sfx (retPtr, filename) {
      const filenameHostPtr = copyBytesFromCart(
        filename,
        cartStrlen(filename) + 1
      )
      const retHostPtr = host._malloc(96)
      host._null0_load_sfx(retHostPtr, filenameHostPtr)
      copyBytesToCart(retHostPtr, 96, retPtr)
      host._free(retHostPtr)
      host._free(filenameHostPtr)
    },
    unload_sound (sound) {
      host._null0_unload_sound(sound)
    },
    key_pressed (key) {
      return host._null0_key_pressed(key)
    },
    key_down (key) {
      return host._null0_key_down(key)
    },
    key_released (key) {
      return host._null0_key_released(key)
    },
    key_up (key) {
      return host._null0_key_up(key)
    },
    gamepad_button_pressed (gamepad, button) {
      return host._null0_gamepad_button_pressed(gamepad, button)
    },
    gamepad_button_down (gamepad, button) {
      return host._null0_gamepad_button_down(gamepad, button)
    },
    gamepad_button_released (gamepad, button) {
      return host._null0_gamepad_button_released(gamepad, button)
    },
    mouse_position (retPtr) {
      const hostRetPtr = host._malloc(8)
      host._null0_mouse_position(hostRetPtr)
      copyBytesToCart(hostRetPtr, 8, retPtr)
      host._free(hostRetPtr)
    },
    mouse_button_pressed (button) {
      return host._null0_mouse_button_pressed(button)
    },
    mouse_button_down (button) {
      return host._null0_mouse_button_down(button)
    },
    mouse_button_released (button) {
      return host._null0_mouse_button_released(button)
    },
    mouse_button_up (button) {
      return host._null0_mouse_button_up(button)
    },
    new_image (width, height, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const r = host._null0_clear(width, height, hostColorPtr)
      host._free(hostColorPtr)
      return r
    },
    image_copy (image) {
      return host._null0_image_copy(image)
    },
    image_subimage (image, x, y, width, height) {
      return host._null0_image_subimage(image, x, y, width, height)
    },
    clear (color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_clear(hostColorPtr)
      host._free(hostColorPtr)
    },
    draw_point (x, y, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_point(x, y, hostColorPtr)
      host._free(hostColorPtr)
    },
    draw_line (startPosX, startPosY, endPosX, endPosY, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_line(
        startPosX,
        startPosY,
        endPosX,
        endPosY,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_rectangle (posX, posY, width, height, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_rectangle(posX, posY, width, height, hostColorPtr)
      host._free(hostColorPtr)
    },
    draw_triangle (x1, y1, x2, y2, x3, y3, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_triangle(x1, y1, x2, y2, x3, y3, hostColorPtr)
      host._free(hostColorPtr)
    },
    draw_ellipse (centerX, centerY, radiusX, radiusY, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_ellipse(
        centerX,
        centerY,
        radiusX,
        radiusY,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_circle (centerX, centerY, radius, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_circle(centerX, centerY, radius, hostColorPtr)
      host._free(hostColorPtr)
    },
    draw_polygon (points, numPoints, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const size = numPoints * 8
      const hostPointsPtr = copyBytesFromCart(points, size)
      host._null0_draw_polygon(hostPointsPtr, numPoints, hostColorPtr)
      host._free(hostColorPtr)
      host._free(hostPointsPtr)
    },
    draw_polyline (points, numPoints, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const size = numPoints * 8
      const hostPointsPtr = copyBytesFromCart(points, size)
      host._null0_draw_polyline(hostPointsPtr, numPoints, hostColorPtr)
      host._free(hostColorPtr)
      host._free(hostPointsPtr)
    },
    draw_arc (centerX, centerY, radius, startAngle, endAngle, segments, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_arc(
        centerX,
        centerY,
        radius,
        startAngle,
        endAngle,
        segments,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_rectangle_rounded (x, y, width, height, cornerRadius, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_rectangle_rounded(
        x,
        y,
        width,
        height,
        cornerRadius,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_image (src, posX, posY) {
      host._null0_draw_image(src, posX, posY)
    },
    draw_image_tint (src, posX, posY, tint) {
      const tintPntr = copyBytesFromCart(tint, 4)
      host._null0_draw_image_tint(src, posX, posY, tintPntr)
      host._free(tintPntr)
    },
    draw_image_rotated (src, posX, posY, degrees, offsetX, offsetY, filter) {
      host._null0_draw_image_rotated(
        src,
        posX,
        posY,
        degrees,
        offsetX,
        offsetY,
        filter
      )
    },
    draw_image_flipped (
      src,
      posX,
      posY,
      flipHorizontal,
      flipVertical,
      flipDiagonal
    ) {
      host._null0_draw_image_flipped(
        src,
        posX,
        posY,
        flipHorizontal,
        flipVertical,
        flipDiagonal
      )
    },
    draw_image_scaled (
      src,
      posX,
      posY,
      scaleX,
      scaleY,
      offsetX,
      offsetY,
      filter
    ) {
      host._null0_draw_image_scaled(
        src,
        posX,
        posY,
        scaleX,
        scaleY,
        offsetX,
        offsetY,
        filter
      )
    },
    draw_text (font, text, posX, posY, color) {
      const textHostPtr = copyBytesFromCart(text, cartStrlen(text) + 1)
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_text(font, textHostPtr, posX, posY, hostColorPtr)
      host._free(textHostPtr)
      host._free(hostColorPtr)
    },
    save_image (image, filename) {
      const filenameHostPtr = copyBytesFromCart(
        filename,
        cartStrlen(filename) + 1
      )
      host._null0_save_image(image, filenameHostPtr)
      host._free(filenameHostPtr)
    },
    load_image (filename) {
      const filenameHostPtr = copyBytesFromCart(
        filename,
        cartStrlen(filename) + 1
      )
      const r = host._null0_load_image(filenameHostPtr)
      host._free(filenameHostPtr)
      return r
    },
    image_resize (image, newWidth, newHeight, offsetX, offsetY, fill) {
      const fillPtr = copyBytesFromCart(fill, 4)
      host._null0_image_resize(
        image,
        newWidth,
        newHeight,
        offsetX,
        offsetY,
        fillPtr
      )
      host._free(fillPtr)
    },
    image_scale (image, scaleX, scaleY, filter) {
      host._null0_image_scale(image, scaleX, scaleY, filter)
    },
    image_color_replace (image, color, replace) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const hostReplacePtr = copyBytesFromCart(replace, 4)
      host._null0_image_color_replace(image, hostColorPtr, hostReplacePtr)
      host._free(hostColorPtr)
      host._free(hostReplacePtr)
    },
    image_color_tint (image, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_image_color_tint(image, hostColorPtr)
      host._free(hostColorPtr)
    },
    image_color_fade (image, alpha) {
      host._null0_image_color_fade(image, alpha)
    },
    font_copy (font) {
      return host._null0_font_copy(font)
    },
    font_scale (font, scaleX, scaleY, filter) {
      return host._null0_font_scale(font, scaleX, scaleY, filter)
    },
    load_font_bmf (filename, characters) {
      const filenameHostPtr = copyBytesFromCart(
        filename,
        cartStrlen(filename) + 1
      )
      const charactersHostPtr = copyBytesFromCart(
        characters,
        cartStrlen(characters) + 1
      )
      const r = host._null0_load_font_bmf(filenameHostPtr, charactersHostPtr)
      host._free(filenameHostPtr)
      host._free(charactersHostPtr)
      return r
    },
    load_font_bmf_from_image (image, characters) {
      const charactersHostPtr = copyBytesFromCart(
        characters,
        cartStrlen(characters) + 1
      )
      const r = host._null0_load_font_bmf_from_image(image, charactersHostPtr)
      host._free(charactersHostPtr)
      return r
    },
    measure_text (retPtr, font, text) {
      const textHostPtr = copyBytesFromCart(text, cartStrlen(text))
      const retHostPtr = host._malloc(8)
      host._null0_measure_text(retHostPtr, font, textHostPtr)
      copyBytesToCart(retHostPtr, 8, retPtr)
      host._free(textHostPtr)
      host._free(retHostPtr)
    },
    measure_image (retPtr, image) {
      const retHostPtr = host._malloc(8)
      host._null0_measure_image(retHostPtr, image)
      copyBytesToCart(retHostPtr, 8, retPtr)
      host._free(retHostPtr)
    },
    load_font_tty (filename, glyphWidth, glyphHeight, characters) {
      const filenameHostPtr = copyBytesFromCart(
        filename,
        cartStrlen(filename) + 1
      )
      const charactersHostPtr = copyBytesFromCart(
        characters,
        cartStrlen(characters) + 1
      )
      const r = host._null0_load_font_tty(
        filenameHostPtr,
        glyphWidth,
        glyphHeight,
        charactersHostPtr
      )
      host._free(filenameHostPtr)
      host._free(charactersHostPtr)
      return r
    },
    load_font_tty_from_image (image, glyphWidth, glyphHeight, characters) {
      const charactersHostPtr = copyBytesFromCart(
        characters,
        cartStrlen(characters) + 1
      )
      const r = host._null0_load_font_tty_from_image(
        image,
        glyphWidth,
        glyphHeight,
        charactersHostPtr
      )
      host._free(charactersHostPtr)
      return r
    },
    load_font_ttf (filename, fontSize) {
      const filenameHostPtr = copyBytesFromCart(
        filename,
        cartStrlen(filename) + 1
      )
      const r = host._null0_load_font_ttf(filenameHostPtr, fontSize)
      host._free(filenameHostPtr)
      return r
    },
    image_color_invert (image) {
      host._null0_image_color_invert(image)
    },
    image_alpha_border (retPtr, image, threshold) {
      const retHostPtr = host._malloc(16)
      host._null0_image_alpha_border(retHostPtr, image, threshold)
      copyBytesToCart(retPtr, 16, retHostPtr)
      host._free(retHostPtr)
    },
    image_crop (image, x, y, width, height) {
      host._null0_image_crop(image, x, y, width, height)
    },
    image_alpha_crop (image, threshold) {
      host._null0_image_alpha_crop(image, threshold)
    },
    image_color_brightness (image, factor) {
      host._null0_image_color_brightness(image, factor)
    },
    image_flip (image, horizontal, vertical) {
      host._null0_image_flip(image, horizontal, vertical)
    },
    image_color_contrast (image, contrast) {
      host._null0_image_color_contrast(image, contrast)
    },
    image_alpha_mask (image, alphaMask, posX, posY) {
      host._null0_image_alpha_mask(image, alphaMask, posX, posY)
    },
    image_rotate (image, degrees, filter) {
      host._null0_image_rotate(image, degrees, filter)
    },
    image_gradient (width, height, topLeft, topRight, bottomLeft, bottomRight) {
      const hostTopLeftPtr = copyBytesFromCart(topLeft, 4)
      const hostTopRightPtr = copyBytesFromCart(topRight, 4)
      const hostBottomLeftPtr = copyBytesFromCart(bottomLeft, 4)
      const hostBottomRightPtr = copyBytesFromCart(bottomRight, 4)
      const r = host._null0_image_gradient(
        width,
        height,
        hostTopLeftPtr,
        hostTopRightPtr,
        hostBottomLeftPtr,
        hostBottomRightPtr
      )
      host._free(hostTopLeftPtr)
      host._free(hostTopRightPtr)
      host._free(hostBottomLeftPtr)
      host._free(hostBottomRightPtr)
      return r
    },
    unload_image (image) {
      host._null0_unload_image(image)
    },
    unload_font (font) {
      host._null0_unload_font(font)
    },
    clear_on_image (destination, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_clear_on_image(destination, hostColorPtr)
      host._free(hostColorPtr)
    },
    draw_point_on_image (destination, x, y, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_point_on_image(destination, x, y, hostColorPtr)
      host._free(hostColorPtr)
    },
    draw_line_on_image (
      destination,
      startPosX,
      startPosY,
      endPosX,
      endPosY,
      color
    ) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_line_on_image(
        destination,
        startPosX,
        startPosY,
        endPosX,
        endPosY,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_rectangle_on_image (destination, posX, posY, width, height, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_rectangle_on_image(
        destination,
        posX,
        posY,
        width,
        height,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_triangle_on_image (destination, x1, y1, x2, y2, x3, y3, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_triangle_on_image(
        destination,
        x1,
        y1,
        x2,
        y2,
        x3,
        y3,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_ellipse_on_image (
      destination,
      centerX,
      centerY,
      radiusX,
      radiusY,
      color
    ) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_ellipse_on_image(
        destination,
        centerX,
        centerY,
        radiusX,
        radiusY,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_circle_on_image (destination, centerX, centerY, radius, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_circle_on_image(
        destination,
        centerX,
        centerY,
        radius,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_polygon_on_image (destination, points, numPoints, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const size = numPoints * 8
      const hostPointsPtr = copyBytesFromCart(points, size)
      host._null0_draw_polygon_on_image(
        destination,
        hostPointsPtr,
        numPoints,
        hostColorPtr
      )
      host._free(hostColorPtr)
      host._free(hostPointsPtr)
    },
    draw_polyline_on_image (destination, points, numPoints, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const size = numPoints * 8
      const hostPointsPtr = copyBytesFromCart(points, size)
      host._null0_draw_polyline_on_image(
        destination,
        hostPointsPtr,
        numPoints,
        hostColorPtr
      )
      host._free(hostColorPtr)
      host._free(hostPointsPtr)
    },
    draw_rectangle_rounded_on_image (
      destination,
      x,
      y,
      width,
      height,
      cornerRadius,
      color
    ) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_rectangle_rounded_on_image(
        destination,
        x,
        y,
        width,
        height,
        cornerRadius,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_image_on_image (destination, src, posX, posY) {
      host._null0_draw_image_on_image(destination, src, posX, posY)
    },
    draw_image_tint_on_image (destination, src, posX, posY, tint) {
      const hostTintPtr = copyBytesFromCart(tint, 4)
      host._null0_draw_image_tint_on_image(
        destination,
        src,
        posX,
        posY,
        hostTintPtr
      )
    },
    draw_image_rotated_on_image (
      destination,
      src,
      posX,
      posY,
      degrees,
      offsetX,
      offsetY,
      filter
    ) {
      host._null0_draw_image_rotated_on_image(
        destination,
        src,
        posX,
        posY,
        degrees,
        offsetX,
        offsetY,
        filter
      )
    },
    draw_image_flipped_on_image (
      destination,
      src,
      posX,
      posY,
      flipHorizontal,
      flipVertical,
      flipDiagonal
    ) {
      host._null0_draw_image_flipped_on_image(
        destination,
        src,
        posX,
        posY,
        flipHorizontal,
        flipVertical,
        flipDiagonal
      )
    },
    draw_image_scaled_on_image (
      destination,
      src,
      posX,
      posY,
      scaleX,
      scaleY,
      offsetX,
      offsetY,
      filter
    ) {
      host._null0_draw_image_scaled_on_image(
        destination,
        src,
        posX,
        posY,
        scaleX,
        scaleY,
        offsetX,
        offsetY,
        filter
      )
    },
    draw_text_on_image (destination, font, text, posX, posY, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const textHostPtr = copyBytesFromCart(text, cartStrlen(text) + 1)
      host._null0_draw_text_on_image(
        destination,
        font,
        textHostPtr,
        posX,
        posY,
        hostColorPtr
      )
      host._free(hostColorPtr)
      host._free(textHostPtr)
    },
    draw_rectangle_outline (posX, posY, width, height, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_rectangle_outline(
        posX,
        posY,
        width,
        height,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_triangle_outline (x1, y1, x2, y2, x3, y3, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_triangle_outline(x1, y1, x2, y2, x3, y3, hostColorPtr)
      host._free(hostColorPtr)
    },
    draw_ellipse_outline (centerX, centerY, radiusX, radiusY, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_ellipse_outline(
        centerX,
        centerY,
        radiusX,
        radiusY,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    draw_circle_outline (centerX, centerY, radius, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_circle_outline(centerX, centerY, radius, hostColorPtr)
      host._free(hostColorPtr)
    },
    draw_polygon_outline (points, numPoints, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_polygon_outline(points, numPoints, color)
      host._free(hostColorPtr)
    },
    draw_arc_outline (
      centerX,
      centerY,
      radius,
      startAngle,
      endAngle,
      segments,
      color
    ) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_arc_outline(
        centerX,
        centerY,
        radius,
        startAngle,
        endAngle,
        segments,
        hostColorPtr
      )
    },
    draw_rectangle_rounded_outline (x, y, width, height, cornerRadius, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_rectangle_rounded_outline(
        x,
        y,
        width,
        height,
        cornerRadius,
        hostColorPtr
      )
    },
    draw_rectangle_outline_on_image (
      destination,
      posX,
      posY,
      width,
      height,
      color
    ) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_rectangle_outline_on_image(
        destination,
        posX,
        posY,
        width,
        height,
        hostColorPtr
      )
    },
    draw_triangle_outline_on_image (destination, x1, y1, x2, y2, x3, y3, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_triangle_outline_on_image(
        destination,
        x1,
        y1,
        x2,
        y2,
        x3,
        y3,
        hostColorPtr
      )
    },
    draw_ellipse_outline_on_image (
      destination,
      centerX,
      centerY,
      radiusX,
      radiusY,
      color
    ) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_ellipse_outline_on_image(
        destination,
        centerX,
        centerY,
        radiusX,
        radiusY,
        hostColorPtr
      )
    },
    draw_circle_outline_on_image (destination, centerX, centerY, radius, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_circle_outline_on_image(
        destination,
        centerX,
        centerY,
        radius,
        hostColorPtr
      )
    },
    draw_polygon_outline_on_image (destination, points, numPoints, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const size = numPoints * 8
      const hostPointsPtr = copyBytesFromCart(points, size)
      host._null0_draw_polygon_outline_on_image(
        destination,
        hostPointsPtr,
        numPoints,
        hostColorPtr
      )
      host._free(hostColorPtr)
      host._free(hostPointsPtr)
    },
    draw_rectangle_rounded_outline_on_image (
      destination,
      x,
      y,
      width,
      height,
      cornerRadius,
      color
    ) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      host._null0_draw_rectangle_rounded_outline_on_image(
        destination,
        x,
        y,
        width,
        height,
        cornerRadius,
        hostColorPtr
      )
      host._free(hostColorPtr)
    },
    file_read (filename, wasmBytesReadPtr, wasmRetPtr) {
      // copy filename from cart to host
      const filenameHostPtr = copyBytesFromCart(filename, cartStrlen(filename) + 1)

      // get size of file
      const fileInfoHostPtr = host._malloc(40)
      host._null0_file_info(fileInfoHostPtr, filenameHostPtr)
      const filesize = host.HEAPU32[fileInfoHostPtr / 4]

      // setup cart-pointer for bytesRead/ret
      const bytesReadHostPtr = host._malloc(4)
      const retPtr = host._malloc(filesize)

      host._null0_file_read(filenameHostPtr, bytesReadHostPtr, retPtr)
      copyBytesToCart(retPtr, wasmRetPtr, filesize)
    },
    file_write (filename, data, byteSize) {
      const filenameHostPtr = copyBytesFromCart(
        filename,
        cartStrlen(filename) + 1
      )
      const bytesHostPtr = copyBytesFromCart(data, byteSize)
      copyBytesFromCart(bytesHostPtr, byteSize, data)
      const r = host._null0_file_write(filenameHostPtr, bytesHostPtr, byteSize)
      host._free(filenameHostPtr)
      host._free(bytesHostPtr)
      return r
    },
    file_append (filename, data, byteSize) {
      const filenameHostPtr = copyBytesFromCart(
        filename,
        cartStrlen(filename) + 1
      )
      const bytesHostPtr = copyBytesFromCart(data, byteSize)
      copyBytesFromCart(bytesHostPtr, byteSize, data)
      const r = host._null0_file_append(
        filenameHostPtr,
        bytesHostPtr,
        byteSize
      )
      host._free(filenameHostPtr)
      host._free(bytesHostPtr)
      return r
    },
    file_info (retPtr, filename) {
      const retHostPtr = host._malloc(40)
      const filenameHostPtr = copyBytesFromCart(
        filename,
        cartStrlen(filename) + 1
      )
      host._null0_file_info(retHostPtr, filenameHostPtr)
      copyBytesToCart(retHostPtr, 40, retPtr)
      host._free(retHostPtr)
      host._free(filenameHostPtr)
    },
    get_write_dir () {
      const hostRetPtr = host._null0_get_write_dir()
      return copyBytesToCart(hostRetPtr, hostStrlen(hostRetPtr))
    },
    color_tint (retPtr, color, tint) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const hostTintPtr = copyBytesFromCart(tint, 4)
      const hostRetPtr = host._malloc(4)
      host._null0_color_tint(hostRetPtr, hostColorPtr, hostTintPtr)
      copyBytesToCart(hostRetPtr, 4, retPtr)
      host._free(hostColorPtr)
      host._free(hostTintPtr)
      host._free(hostRetPtr)
    },
    color_fade (retPtr, color, alpha) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const hostRetPtr = host.malloc(4)
      host._null0_color_fade(hostRetPtr, hostColorPtr, alpha)
      copyBytesToCart(hostRetPtr, 4, retPtr)
      host._free(hostColorPtr)
      host._free(hostRetPtr)
    },
    color_brightness (retPtr, color, factor) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const hostRetPtr = host.malloc(4)
      host._null0_color_brightness(hostRetPtr, hostColorPtr, factor)
      copyBytesToCart(hostRetPtr, 4, retPtr)
      host._free(hostColorPtr)
      host._free(hostRetPtr)
    },
    color_invert (retPtr, color) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const hostRetPtr = host.malloc(4)
      host._null0_color_invert(hostRetPtr, hostColorPtr)
      copyBytesToCart(hostRetPtr, 4, retPtr)
      host._free(hostColorPtr)
      host._free(hostRetPtr)
    },
    color_alpha_blend (retPtr, dst, src) {
      const hostDstPtr = copyBytesFromCart(dst, 4)
      const hostSrcPtr = copyBytesFromCart(src, 4)
      const hostRetPtr = host.malloc(4)
      host._null0_color_alpha_blend(hostRetPtr, hostDstPtr, hostSrcPtr)
      copyBytesToCart(hostRetPtr, 4, retPtr)
      host._free(hostDstPtr)
      host._free(hostSrcPtr)
      host._free(hostRetPtr)
    },
    color_contrast (retPtr, color, contrast) {
      const hostColorPtr = copyBytesFromCart(color, 4)
      const hostRetPtr = host.malloc(4)
      host._null0_color_contrast(hostRetPtr, hostColorPtr, contrast)
      copyBytesToCart(hostRetPtr, 4, retPtr)
      host._free(hostColorPtr)
      host._free(hostRetPtr)
    },
    color_bilinear_interpolate (
      retPtr,
      color00,
      color01,
      color10,
      color11,
      coordinateX,
      coordinateY
    ) {
      const hostColor00Ptr = copyBytesFromCart(color00, 4)
      const hostColor01Ptr = copyBytesFromCart(color01, 4)
      const hostColor10Ptr = copyBytesFromCart(color10, 4)
      const hostColor11Ptr = copyBytesFromCart(color11, 4)
      const hostRetPtr = host.malloc(4)
      host._null0_color_bilinear_interpolate(
        hostRetPtr,
        hostColor00Ptr,
        hostColor01Ptr,
        hostColor10Ptr,
        hostColor11Ptr,
        coordinateX,
        coordinateY
      )
      copyBytesToCart(hostRetPtr, 4, retPtr)
      host._free(hostRetPtr)
    }
  }
}
