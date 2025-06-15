import { writeFile } from 'node:fs/promises'
import { indent, createApiStream } from './utils.js'

const out = ['#include "host_header.h"']

// map of def-types into across-wasm types
const types = {
  i32: 'int32_t',
  u32: 'uint32_t',
  f32: 'float',
  u64: 'uint64_t',
  string: 'uint32_t',
  Vector: 'uint32_t',
  Rectangle: 'uint32_t',
  Dimensions: 'uint32_t',
  Image: 'uint32_t',
  Font: 'uint32_t',
  Sound: 'uint32_t',
  Color: 'uint32_t',
  ImageFilter: 'pntr_filter',
  Key: 'pntr_app_key',
  GamepadButton: 'pntr_app_gamepad_button',
  MouseButton: 'pntr_app_mouse_button',
  'Vector[]': 'uint32_t'
}

// map of cart function-names to host functions
// This also adds app/image for functions that need it
const functions = {
  current_time: 'null0_current_time(',
  delta_time: 'pntr_app_delta_time(null0_app',
  random_int: 'pntr_app_random(null0_app, ',
  random_seed_get: 'pntr_app_random_seed(null0_app',
  random_seed_set: 'pntr_app_random_set_seed(null0_app, ',
  load_sound: 'pntr_load_sound(',
  play_sound: 'pntr_play_sound(',
  stop_sound: 'pntr_stop_sound(',
  unload_sound: 'pntr_unload_sound(',
  key_pressed: 'pntr_app_key_pressed(null0_app, ',
  key_down: 'pntr_app_key_down(null0_app, ',
  key_released: 'pntr_app_key_released(null0_app, ',
  key_up: 'pntr_app_key_up(null0_app, ',
  gamepad_button_pressed: 'pntr_app_gamepad_button_pressed(null0_app, ',
  gamepad_button_down: 'pntr_app_gamepad_button_down(null0_app, ',
  gamepad_button_released: 'pntr_app_gamepad_button_released(null0_app, ',
  mouse_position: 'null0_mouse_position(',
  mouse_button_pressed: 'pntr_app_mouse_button_pressed(null0_app, ',
  mouse_button_down: 'pntr_app_mouse_button_down(null0_app, ',
  mouse_button_released: 'pntr_app_mouse_button_released(null0_app, ',
  mouse_button_up: 'pntr_app_mouse_button_up(null0_app, ',
  new_image: 'pntr_gen_image_color(',
  image_copy: 'pntr_image_copy(',
  image_subimage: 'pntr_image_subimage(',
  clear: 'pntr_clear_background(images[0], ',
  draw_point: 'pntr_draw_point(images[0], ',
  draw_line: 'pntr_draw_line(images[0], ',
  draw_rectangle: 'pntr_draw_rectangle_fill(images[0], ',
  draw_triangle: 'pntr_draw_triangle_fill(images[0], ',
  draw_ellipse: 'pntr_draw_ellipse_fill(images[0], ',
  draw_circle: 'pntr_draw_circle_fill(images[0], ',
  draw_polygon: 'pntr_draw_polygon_fill(images[0], ',
  draw_arc: 'pntr_draw_arc_fill(images[0], ',
  draw_rectangle_rounded: 'pntr_draw_rectangle_rounded_fill(images[0], ',
  draw_image: 'pntr_draw_image(images[0], ',
  draw_image_tint: 'pntr_draw_image_tint(images[0], ',
  draw_image_rotated: 'pntr_draw_image_rotated(images[0], ',
  draw_image_flipped: 'pntr_draw_image_flipped(images[0], ',
  draw_image_scaled: 'pntr_draw_image_scaled(images[0], ',
  draw_text: 'pntr_draw_text(images[0], ',
  save_image: 'pntr_save_image(',
  load_image: 'pntr_load_image(',
  image_resize: 'pntr_image_resize(',
  image_scale: 'pntr_image_scale(',
  image_color_replace: 'pntr_image_color_replace(',
  image_color_tint: 'pntr_image_color_tint(',
  image_color_fade: 'pntr_image_color_fade(',
  font_copy: 'pntr_font_copy(',
  font_scale: 'pntr_font_scale(',
  load_font_bmf: 'pntr_load_font_bmf(',
  load_font_bmf_from_image: 'pntr_load_font_bmf_from_image(',
  measure_text: 'pntr_measure_text_ex(',
  measure_image: 'null0_measure_image(',
  load_font_tty: 'pntr_load_font_tty(',
  load_font_tty_from_image: 'pntr_load_font_tty_from_image(',
  load_font_ttf: 'pntr_load_font_ttf(',
  image_color_invert: 'pntr_image_color_invert(',
  image_alpha_border: 'pntr_image_alpha_border(',
  image_crop: 'pntr_image_crop(',
  image_alpha_crop: 'pntr_image_alpha_crop(',
  image_color_brightness: 'pntr_image_color_brightness(',
  image_flip: 'pntr_image_flip(',
  image_color_contrast: 'pntr_image_color_contrast(',
  image_alpha_mask: 'pntr_image_alpha_mask(',
  image_rotate: 'pntr_image_rotate(',
  image_gradient: 'pntr_gen_image_gradient(',
  unload_image: 'pntr_unload_image(',
  unload_font: 'pntr_unload_font(',
  clear_image: 'pntr_clear_background(',
  draw_point_on_image: 'pntr_draw_point(',
  draw_line_on_image: 'pntr_draw_line(',
  draw_rectangle_on_image: 'pntr_draw_rectangle_fill(',
  draw_triangle_on_image: 'pntr_draw_triangle_fill(',
  draw_ellipse_on_image: 'pntr_draw_ellipse_fill(',
  draw_circle_on_image: 'pntr_draw_circle_fill(',
  draw_polygon_on_image: 'pntr_draw_polygon_fill(',
  draw_rectangle_rounded_on_image: 'pntr_draw_rectangle_rounded_fill(',
  draw_image_on_image: 'pntr_draw_image(',
  draw_image_tint_on_image: 'pntr_draw_image_tint(',
  draw_image_rotated_on_image: 'pntr_draw_image_rotated(',
  draw_image_flipped_on_image: 'pntr_draw_image_flipped(',
  draw_image_scaled_on_image: 'pntr_draw_image_scaled(',
  draw_text_on_image: 'pntr_draw_text(',
  draw_rectangle_outline: 'pntr_draw_rectangle_thick(images[0], ',
  draw_triangle_outline: 'pntr_draw_triangle_thick(images[0], ',
  draw_ellipse_outline: 'pntr_draw_ellipse_thick(images[0], ',
  draw_circle_outline: 'pntr_draw_circle_thick(images[0], ',
  draw_polygon_outline: 'pntr_draw_polygon_thick(images[0], ',
  draw_arc_outline: 'pntr_draw_arc_thick(images[0], ',
  draw_rectangle_rounded_outline: 'null0_draw_rectangle_thick_rounded(images[0], ',
  draw_rectangle_outline_on_image: 'pntr_draw_rectangle_thick(',
  draw_triangle_outline_on_image: 'pntr_draw_triangle_thick(',
  draw_ellipse_outline_on_image: 'pntr_draw_ellipse_thick(',
  draw_circle_outline_on_image: 'pntr_draw_circle_thick(',
  draw_polygon_outline_on_image: 'pntr_draw_polygon_thick(',
  draw_rectangle_rounded_outline_on_image: 'null0_draw_rectangle_thick_rounded(',
  file_read: 'fs_load_file(',
  file_write: 'fs_save_file(',
  file_append: 'fs_append_file(',
  get_write_dir: 'fs_get_write_dir(',
  color_tint: 'pntr_color_tint(',
  color_fade: 'pntr_color_fade(',
  color_brightness: 'pntr_color_brightness(',
  color_invert: 'pntr_color_invert(',
  color_alpha_blend: 'pntr_color_alpha_blend(',
  color_contrast: 'pntr_color_contrast(',
  color_bilinear_interpolate: 'pntr_color_bilinear_interpolate('
}

// map args to host-types
const argsMap = (args) =>
  Object.entries(args)
    .map(([name, type]) => `${types[type] || type} ${name}`)
    .join(', ')

// generate input/output mappers for args/return
function buildBody(name, args, returns) {
  const body = []
  const cleanup = []
  const callArgs = []
  const allArgs = Object.entries(args)
  let i = 0
  for (const [name, type] of allArgs) {
    if (type === 'Color') {
      body.push(`pntr_color ${name}Host = copy_color_from_cart(${name});`)
      callArgs.push(`${name}Host`)
    } else if (type === 'Image') {
      callArgs.push(`images[${name}]`)
    } else if (type === 'Sound') {
      callArgs.push(`sounds[${name}]`)
    } else if (type === 'Font') {
      callArgs.push(`fonts[${name}]`)
    } else if (type === 'string') {
      body.push(`char* ${name}Host = copy_string_from_cart(${name});`)
      cleanup.push(`free(${name}Host);`)
      callArgs.push(`${name}Host`)
    } else if (type === 'bytes') {
      body.push(`unsigned char* ${name}Host = copy_memory_from_cart(${name}, ${allArgs[i + 1][0]});`)
      cleanup.push(`free(${name}Host);`)
      callArgs.push(`${name}Host`)
    } else if (type === 'Vector[]') {
      body.push(`pntr_vector* ${name}Host = copy_memory_from_cart(${name}, ${allArgs[i + 1][0]} * sizeof(pntr_vector));`)
      cleanup.push(`free(${name}Host);`)
      callArgs.push(`${name}Host`)
    } else {
      callArgs.push(name)
    }
    i++
  }
  if (returns && returns !== 'void') {
    if (['i32', 'u32', 'f32'].includes(returns)) {
      body.push(`${types[returns]} retHost = ${functions[name]}${callArgs.join(', ')});`)
    } else {
      if (returns === 'Font') {
        body.push(`uint32_t retHost = add_font(${functions[name]}${callArgs.join(', ')}));`)
      } else if (returns === 'Image') {
        body.push(`uint32_t retHost = add_image(${functions[name]}${callArgs.join(', ')}));`)
      } else if (returns === 'Sound') {
        body.push(`uint32_t retHost = add_sound(${functions[name]}${callArgs.join(', ')}));`)
      } else if (returns === 'Color') {
        body.push(`uint32_t retHost = copy_color_to_cart(${functions[name]}${callArgs.join(', ')}));`)
      } else if (returns === 'Vector') {
        body.push(`pntr_vector retHostVal = ${functions[name]}${callArgs.join(', ')});`)
        body.push(`uint32_t retHost = copy_memory_to_cart(&retHostVal, sizeof(pntr_vector));`)
      } else if (returns === 'Rectangle') {
        body.push(`pntr_rectangle retHostVal = ${functions[name]}${callArgs.join(', ')});`)
        body.push(`uint32_t retHost = copy_memory_to_cart(&retHostVal, sizeof(pntr_rectangle));`)
      } else if (returns === 'Dimensions') {
        body.push(`pntr_vector retHostVal = ${functions[name]}${callArgs.join(', ')});`)
        body.push(`uint32_t retHost = copy_memory_to_cart(&retHostVal, sizeof(pntr_vector));`)
      } else {
        body.push(`${types[returns] || returns} retHost = ${functions[name]}${callArgs.join(', ')});`)
      }
    }
  } else {
    body.push(`${functions[name]}${callArgs.join(', ')});`)
  }
  body.push(...cleanup)
  if (returns && returns !== 'void') {
    body.push(`return retHost;`)
  }
  return body.join('\n')
}

const api = createApiStream()

api.on('api', (apiName) => {
  out.push('', `// ${apiName.toUpperCase()}`, '')
})

api.on('function', ({ apiName, funcName, args = {}, returns = 'void', description = '' }) => {
  out.push(`// ${description}`)
  out.push(`HOST_FUNCTION(${types[returns] || returns}, ${funcName}, (${argsMap(args)}), {`)
  out.push(indent(buildBody(funcName, args, returns)))
  out.push('})', '')
})

api.on('end', async () => {
  await writeFile('host/src/host.c', out.join('\n'))
})

api.on('error', (e) => {
  console.error(e)
})
