// GENERATED FILE - do not edit by hand. See tools/gen_cart_python.js
#![allow(non_snake_case, non_upper_case_globals, unused_unsafe, dead_code)]

use rustpython_vm as vm;
use std::cell::OnceCell;
use std::ffi::CString;
use vm::function::FuncArgs;
use vm::scope::Scope;
use vm::{Interpreter, PyObjectRef, PyResult, VirtualMachine};

/// Sfx parameters.
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct SfxParams {
    pub randSeed: u32,
    pub waveType: i32,
    pub attackTime: f32,
    pub sustainTime: f32,
    pub sustainPunch: f32,
    pub decayTime: f32,
    pub startFrequency: f32,
    pub minFrequency: f32,
    pub slide: f32,
    pub deltaSlide: f32,
    pub vibratoDepth: f32,
    pub vibratoSpeed: f32,
    pub changeAmount: f32,
    pub changeSpeed: f32,
    pub squareDuty: f32,
    pub dutySweep: f32,
    pub repeatSpeed: f32,
    pub phaserOffset: f32,
    pub phaserSweep: f32,
    pub lpfCutoff: f32,
    pub lpfCutoffSweep: f32,
    pub lpfResonance: f32,
    pub hpfCutoff: f32,
    pub hpfCutoffSweep: f32,
}

/// The 2D size of something (width/height.)
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Dimensions {
    pub width: i32,
    pub height: i32,
}

/// The 2D position of something (x/y.)
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Vector {
    pub x: i32,
    pub y: i32,
}

/// The 2D position + size of something (x/y/w/h.)
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Rectangle {
    pub x: i32,
    pub y: i32,
    pub width: i32,
    pub height: i32,
}

/// An RGBA color.
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Color {
    pub r: u8,
    pub g: u8,
    pub b: u8,
    pub a: u8,
}

/// A custom property on a tilemap, layer, object, or tile. Only the member named by `type` is meaningful - a PROP_BOOL is 0/1 in `integer`, and a PROP_COLOR is RGBA bytes in `integer`.
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct TilemapProp {
    pub name: *const u8,
    pub r#type: i32,
    pub integer: i32,
    pub number: f32,
    pub text: *const u8,
}

/// An object from an object-layer of a tilemap. This is the map's initial state - carts own whatever they spawn from it.
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct TilemapObject {
    pub id: i32,
    pub name: *const u8,
    pub r#type: *const u8,
    pub gid: i32,
    pub x: f32,
    pub y: f32,
    pub width: f32,
    pub height: f32,
    pub rotation: f32,
    pub visible: i32,
}

#[link(wasm_import_module = "null0")]
extern "C" {
    pub fn color_tint(color: Color, tint: Color) -> u32;
    pub fn color_fade(color: Color, alpha: f32) -> u32;
    pub fn color_brightness(color: Color, factor: f32) -> u32;
    pub fn color_invert(color: Color) -> u32;
    pub fn color_alpha_blend(dst: Color, src: Color) -> u32;
    pub fn color_contrast(color: Color, contrast: f32) -> u32;
    pub fn color_bilinear_interpolate(color00: Color, color01: Color, color10: Color, color11: Color, coordinateX: f32, coordinateY: f32) -> u32;
    pub fn new_image(width: i32, height: i32, color: Color) -> u32;
    pub fn image_copy(image: u32) -> u32;
    pub fn image_subimage(image: u32, x: i32, y: i32, width: i32, height: i32) -> u32;
    pub fn clear(color: Color);
    pub fn draw_point(x: i32, y: i32, color: Color);
    pub fn draw_line(startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color);
    pub fn draw_rectangle(posX: i32, posY: i32, width: i32, height: i32, color: Color);
    pub fn draw_triangle(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color);
    pub fn draw_ellipse(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color);
    pub fn draw_circle(centerX: i32, centerY: i32, radius: i32, color: Color);
    pub fn draw_polygon(points: *const Vector, numPoints: i32, color: Color);
    pub fn draw_arc(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, color: Color);
    pub fn draw_rectangle_rounded(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color);
    pub fn draw_image(src: u32, posX: i32, posY: i32);
    pub fn draw_image_tint(src: u32, posX: i32, posY: i32, tint: Color);
    pub fn draw_image_rotated(src: u32, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: i32);
    pub fn draw_image_flipped(src: u32, posX: i32, posY: i32, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool);
    pub fn draw_image_scaled(src: u32, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: i32);
    pub fn draw_text(font: u32, text: *const u8, posX: i32, posY: i32, color: Color);
    pub fn save_image(image: u32, filename: *const u8);
    pub fn load_image(filename: *const u8) -> u32;
    pub fn image_resize(image: u32, newWidth: i32, newHeight: i32, filter: i32) -> u32;
    pub fn image_scale(image: u32, scaleX: f32, scaleY: f32, filter: i32) -> u32;
    pub fn image_color_replace(image: u32, color: Color, replace: Color);
    pub fn image_color_tint(image: u32, color: Color);
    pub fn image_color_fade(image: u32, alpha: f32);
    pub fn font_copy(font: u32) -> u32;
    pub fn font_scale(font: u32, scaleX: f32, scaleY: f32, filter: i32) -> u32;
    pub fn load_font_bmf(filename: *const u8, characters: *const u8) -> u32;
    pub fn load_font_bmf_from_image(image: u32, characters: *const u8) -> u32;
    pub fn measure_text(font: u32, text: *const u8, textLength: i32) -> u32;
    pub fn measure_image(image: u32) -> u32;
    pub fn load_font_tty(filename: *const u8, glyphWidth: i32, glyphHeight: i32, characters: *const u8) -> u32;
    pub fn load_font_tty_from_image(image: u32, glyphWidth: i32, glyphHeight: i32, characters: *const u8) -> u32;
    pub fn load_font_ttf(filename: *const u8, fontSize: i32) -> u32;
    pub fn image_color_invert(image: u32);
    pub fn image_alpha_border(image: u32, threshold: f32) -> u32;
    pub fn image_crop(image: u32, x: i32, y: i32, width: i32, height: i32);
    pub fn image_alpha_crop(image: u32, threshold: f32);
    pub fn image_color_brightness(image: u32, factor: f32);
    pub fn image_flip(image: u32, horizontal: bool, vertical: bool);
    pub fn image_color_contrast(image: u32, contrast: f32);
    pub fn image_alpha_mask(image: u32, alphaMask: u32, posX: i32, posY: i32);
    pub fn image_rotate(image: u32, degrees: f32, filter: i32) -> u32;
    pub fn image_gradient(width: i32, height: i32, topLeft: Color, topRight: Color, bottomLeft: Color, bottomRight: Color) -> u32;
    pub fn unload_image(image: u32);
    pub fn unload_font(font: u32);
    pub fn clear_image(destination: u32, color: Color);
    pub fn draw_point_on_image(destination: u32, x: i32, y: i32, color: Color);
    pub fn draw_line_on_image(destination: u32, startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color);
    pub fn draw_rectangle_on_image(destination: u32, posX: i32, posY: i32, width: i32, height: i32, color: Color);
    pub fn draw_triangle_on_image(destination: u32, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color);
    pub fn draw_ellipse_on_image(destination: u32, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color);
    pub fn draw_circle_on_image(destination: u32, centerX: i32, centerY: i32, radius: i32, color: Color);
    pub fn draw_polygon_on_image(destination: u32, points: *const Vector, numPoints: i32, color: Color);
    pub fn draw_rectangle_rounded_on_image(destination: u32, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color);
    pub fn draw_image_on_image(destination: u32, src: u32, posX: i32, posY: i32);
    pub fn draw_image_tint_on_image(destination: u32, src: u32, posX: i32, posY: i32, tint: Color);
    pub fn draw_image_rotated_on_image(destination: u32, src: u32, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: i32);
    pub fn draw_image_flipped_on_image(destination: u32, src: u32, posX: i32, posY: i32, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool);
    pub fn draw_image_scaled_on_image(destination: u32, src: u32, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: i32);
    pub fn draw_text_on_image(destination: u32, font: u32, text: *const u8, posX: i32, posY: i32, color: Color);
    pub fn draw_rectangle_outline(posX: i32, posY: i32, width: i32, height: i32, thickness: i32, color: Color);
    pub fn draw_triangle_outline(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, thickness: i32, color: Color);
    pub fn draw_ellipse_outline(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, thickness: i32, color: Color);
    pub fn draw_circle_outline(centerX: i32, centerY: i32, radius: i32, thickness: i32, color: Color);
    pub fn draw_polygon_outline(points: *const Vector, numPoints: i32, thickness: i32, color: Color);
    pub fn draw_arc_outline(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, thickness: i32, color: Color);
    pub fn draw_rectangle_rounded_outline(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, thickness: i32, color: Color);
    pub fn draw_rectangle_outline_on_image(destination: u32, posX: i32, posY: i32, width: i32, height: i32, thickness: i32, color: Color);
    pub fn draw_triangle_outline_on_image(destination: u32, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, thickness: i32, color: Color);
    pub fn draw_ellipse_outline_on_image(destination: u32, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, thickness: i32, color: Color);
    pub fn draw_circle_outline_on_image(destination: u32, centerX: i32, centerY: i32, radius: i32, thickness: i32, color: Color);
    pub fn draw_polygon_outline_on_image(destination: u32, points: *const Vector, numPoints: i32, thickness: i32, color: Color);
    pub fn draw_rectangle_rounded_outline_on_image(destination: u32, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, thickness: i32, color: Color);
    pub fn gui_begin_window(title: *const u8, rect: Rectangle) -> bool;
    pub fn gui_end_window();
    pub fn gui_button(label: *const u8) -> bool;
    pub fn gui_label(text: *const u8);
    pub fn gui_text(text: *const u8);
    pub fn gui_checkbox(label: *const u8, state: bool) -> bool;
    pub fn gui_slider(value: f32, low: f32, high: f32) -> f32;
    pub fn gui_layout_row(widths: *const i32, numWidths: i32, height: i32);
    pub fn gui_end();
    pub fn gui_draw(dst: u32);
    pub fn key_pressed(key: i32) -> bool;
    pub fn key_down(key: i32) -> bool;
    pub fn key_released(key: i32) -> bool;
    pub fn key_up(key: i32) -> bool;
    pub fn gamepad_button_pressed(gamepad: i32, button: i32) -> bool;
    pub fn gamepad_button_down(gamepad: i32, button: i32) -> bool;
    pub fn gamepad_button_released(gamepad: i32, button: i32) -> bool;
    pub fn mouse_position() -> u32;
    pub fn mouse_button_pressed(button: i32) -> bool;
    pub fn mouse_button_down(button: i32) -> bool;
    pub fn mouse_button_released(button: i32) -> bool;
    pub fn mouse_button_up(button: i32) -> bool;
    pub fn load_sound(filename: *const u8) -> u32;
    pub fn play_sound(sound: u32, r#loop: bool);
    pub fn stop_sound(sound: u32);
    pub fn unload_sound(sound: u32);
    pub fn tts_sound(text: *const u8, phonetic: bool, pitch: i32, speed: i32, throat: i32, mouth: i32, sing: bool) -> u32;
    pub fn sfx_sound(params: SfxParams) -> u32;
    pub fn sfx_generate(r#type: i32) -> u32;
    pub fn load_tilemap(filename: *const u8) -> u32;
    pub fn unload_tilemap(tilemap: u32);
    pub fn tile_update(tilemap: u32, deltaTime: f32);
    pub fn tile_map_size(tilemap: u32) -> u32;
    pub fn tile_tile_size(tilemap: u32) -> u32;
    pub fn tile_map_prop(tilemap: u32, name: *const u8) -> u32;
    pub fn tile_map_prop_count(tilemap: u32) -> i32;
    pub fn tile_map_prop_at(tilemap: u32, index: i32) -> u32;
    pub fn tile_draw(tilemap: u32, posX: i32, posY: i32);
    pub fn tile_draw_tint(tilemap: u32, posX: i32, posY: i32, tint: Color);
    pub fn tile_draw_on_image(dst: u32, tilemap: u32, posX: i32, posY: i32);
    pub fn tilemap_image(tilemap: u32) -> u32;
    pub fn tile_layer_count(tilemap: u32) -> i32;
    pub fn tile_layer_index(tilemap: u32, name: *const u8) -> i32;
    pub fn tile_layer_name(tilemap: u32, layer: i32) -> *const u8;
    pub fn tile_layer_type(tilemap: u32, layer: i32) -> i32;
    pub fn tile_layer_size(tilemap: u32, layer: i32) -> u32;
    pub fn tile_layer_visible(tilemap: u32, layer: i32) -> bool;
    pub fn tile_layer_prop(tilemap: u32, layer: i32, name: *const u8) -> u32;
    pub fn tile_layer_prop_count(tilemap: u32, layer: i32) -> i32;
    pub fn tile_layer_prop_at(tilemap: u32, layer: i32, index: i32) -> u32;
    pub fn tile_draw_layer(tilemap: u32, layer: i32, posX: i32, posY: i32);
    pub fn tile_draw_layer_tint(tilemap: u32, layer: i32, posX: i32, posY: i32, tint: Color);
    pub fn tile_draw_layer_on_image(dst: u32, tilemap: u32, layer: i32, posX: i32, posY: i32);
    pub fn tile_layer_image(tilemap: u32, layer: i32) -> u32;
    pub fn tile_get_tile(tilemap: u32, layer: i32, column: i32, row: i32) -> i32;
    pub fn tile_set_tile(tilemap: u32, layer: i32, column: i32, row: i32, gid: i32);
    pub fn tile_draw_tile(tilemap: u32, gid: i32, posX: i32, posY: i32);
    pub fn tile_image(tilemap: u32, gid: i32) -> u32;
    pub fn tile_gid_prop(tilemap: u32, gid: i32, name: *const u8) -> u32;
    pub fn tile_gid_prop_count(tilemap: u32, gid: i32) -> i32;
    pub fn tile_gid_prop_at(tilemap: u32, gid: i32, index: i32) -> u32;
    pub fn tile_object_count(tilemap: u32, layer: i32) -> i32;
    pub fn tile_object(tilemap: u32, layer: i32, index: i32) -> u32;
    pub fn tile_object_index(tilemap: u32, layer: i32, name: *const u8) -> i32;
    pub fn tile_object_prop(tilemap: u32, layer: i32, index: i32, name: *const u8) -> u32;
    pub fn tile_object_prop_count(tilemap: u32, layer: i32, index: i32) -> i32;
    pub fn tile_object_prop_at(tilemap: u32, layer: i32, index: i32, propIndex: i32) -> u32;
    pub fn current_time() -> u64;
    pub fn delta_time() -> f32;
    pub fn random_int(min: i32, max: i32) -> i32;
    pub fn random_seed_get() -> u64;
    pub fn random_seed_set(seed: u64);
}

// a host string (bytes in our own memory, valid until this callback returns)
fn cstr_to_py(p: *const u8, vm: &VirtualMachine) -> PyObjectRef {
    if p.is_null() {
        return vm.ctx.new_str("").into();
    }
    let mut len = 0usize;
    unsafe {
        while *p.add(len) != 0 {
            len += 1;
        }
        let bytes = core::slice::from_raw_parts(p, len);
        vm.ctx.new_str(String::from_utf8_lossy(bytes).into_owned()).into()
    }
}


fn sfxparams_from_py(obj: &PyObjectRef, vm: &VirtualMachine) -> PyResult<SfxParams> {
    Ok(SfxParams {
        randSeed: obj.get_item("randSeed", vm)?.try_into_value::<u32>(vm)?,
        waveType: obj.get_item("waveType", vm)?.try_into_value::<i32>(vm)?,
        attackTime: obj.get_item("attackTime", vm)?.try_into_value::<f32>(vm)?,
        sustainTime: obj.get_item("sustainTime", vm)?.try_into_value::<f32>(vm)?,
        sustainPunch: obj.get_item("sustainPunch", vm)?.try_into_value::<f32>(vm)?,
        decayTime: obj.get_item("decayTime", vm)?.try_into_value::<f32>(vm)?,
        startFrequency: obj.get_item("startFrequency", vm)?.try_into_value::<f32>(vm)?,
        minFrequency: obj.get_item("minFrequency", vm)?.try_into_value::<f32>(vm)?,
        slide: obj.get_item("slide", vm)?.try_into_value::<f32>(vm)?,
        deltaSlide: obj.get_item("deltaSlide", vm)?.try_into_value::<f32>(vm)?,
        vibratoDepth: obj.get_item("vibratoDepth", vm)?.try_into_value::<f32>(vm)?,
        vibratoSpeed: obj.get_item("vibratoSpeed", vm)?.try_into_value::<f32>(vm)?,
        changeAmount: obj.get_item("changeAmount", vm)?.try_into_value::<f32>(vm)?,
        changeSpeed: obj.get_item("changeSpeed", vm)?.try_into_value::<f32>(vm)?,
        squareDuty: obj.get_item("squareDuty", vm)?.try_into_value::<f32>(vm)?,
        dutySweep: obj.get_item("dutySweep", vm)?.try_into_value::<f32>(vm)?,
        repeatSpeed: obj.get_item("repeatSpeed", vm)?.try_into_value::<f32>(vm)?,
        phaserOffset: obj.get_item("phaserOffset", vm)?.try_into_value::<f32>(vm)?,
        phaserSweep: obj.get_item("phaserSweep", vm)?.try_into_value::<f32>(vm)?,
        lpfCutoff: obj.get_item("lpfCutoff", vm)?.try_into_value::<f32>(vm)?,
        lpfCutoffSweep: obj.get_item("lpfCutoffSweep", vm)?.try_into_value::<f32>(vm)?,
        lpfResonance: obj.get_item("lpfResonance", vm)?.try_into_value::<f32>(vm)?,
        hpfCutoff: obj.get_item("hpfCutoff", vm)?.try_into_value::<f32>(vm)?,
        hpfCutoffSweep: obj.get_item("hpfCutoffSweep", vm)?.try_into_value::<f32>(vm)?,
    })
}

fn sfxparams_to_py(v: SfxParams, vm: &VirtualMachine) -> PyObjectRef {
    let d = vm.ctx.new_dict();
    d.set_item("randSeed", vm.ctx.new_int(v.randSeed).into(), vm).unwrap();
    d.set_item("waveType", vm.ctx.new_int(v.waveType).into(), vm).unwrap();
    d.set_item("attackTime", vm.ctx.new_float(v.attackTime as f64).into(), vm).unwrap();
    d.set_item("sustainTime", vm.ctx.new_float(v.sustainTime as f64).into(), vm).unwrap();
    d.set_item("sustainPunch", vm.ctx.new_float(v.sustainPunch as f64).into(), vm).unwrap();
    d.set_item("decayTime", vm.ctx.new_float(v.decayTime as f64).into(), vm).unwrap();
    d.set_item("startFrequency", vm.ctx.new_float(v.startFrequency as f64).into(), vm).unwrap();
    d.set_item("minFrequency", vm.ctx.new_float(v.minFrequency as f64).into(), vm).unwrap();
    d.set_item("slide", vm.ctx.new_float(v.slide as f64).into(), vm).unwrap();
    d.set_item("deltaSlide", vm.ctx.new_float(v.deltaSlide as f64).into(), vm).unwrap();
    d.set_item("vibratoDepth", vm.ctx.new_float(v.vibratoDepth as f64).into(), vm).unwrap();
    d.set_item("vibratoSpeed", vm.ctx.new_float(v.vibratoSpeed as f64).into(), vm).unwrap();
    d.set_item("changeAmount", vm.ctx.new_float(v.changeAmount as f64).into(), vm).unwrap();
    d.set_item("changeSpeed", vm.ctx.new_float(v.changeSpeed as f64).into(), vm).unwrap();
    d.set_item("squareDuty", vm.ctx.new_float(v.squareDuty as f64).into(), vm).unwrap();
    d.set_item("dutySweep", vm.ctx.new_float(v.dutySweep as f64).into(), vm).unwrap();
    d.set_item("repeatSpeed", vm.ctx.new_float(v.repeatSpeed as f64).into(), vm).unwrap();
    d.set_item("phaserOffset", vm.ctx.new_float(v.phaserOffset as f64).into(), vm).unwrap();
    d.set_item("phaserSweep", vm.ctx.new_float(v.phaserSweep as f64).into(), vm).unwrap();
    d.set_item("lpfCutoff", vm.ctx.new_float(v.lpfCutoff as f64).into(), vm).unwrap();
    d.set_item("lpfCutoffSweep", vm.ctx.new_float(v.lpfCutoffSweep as f64).into(), vm).unwrap();
    d.set_item("lpfResonance", vm.ctx.new_float(v.lpfResonance as f64).into(), vm).unwrap();
    d.set_item("hpfCutoff", vm.ctx.new_float(v.hpfCutoff as f64).into(), vm).unwrap();
    d.set_item("hpfCutoffSweep", vm.ctx.new_float(v.hpfCutoffSweep as f64).into(), vm).unwrap();
    d.into()
}

fn dimensions_from_py(obj: &PyObjectRef, vm: &VirtualMachine) -> PyResult<Dimensions> {
    Ok(Dimensions {
        width: obj.get_item("width", vm)?.try_into_value::<i32>(vm)?,
        height: obj.get_item("height", vm)?.try_into_value::<i32>(vm)?,
    })
}

fn dimensions_to_py(v: Dimensions, vm: &VirtualMachine) -> PyObjectRef {
    let d = vm.ctx.new_dict();
    d.set_item("width", vm.ctx.new_int(v.width).into(), vm).unwrap();
    d.set_item("height", vm.ctx.new_int(v.height).into(), vm).unwrap();
    d.into()
}

fn vector_from_py(obj: &PyObjectRef, vm: &VirtualMachine) -> PyResult<Vector> {
    Ok(Vector {
        x: obj.get_item("x", vm)?.try_into_value::<i32>(vm)?,
        y: obj.get_item("y", vm)?.try_into_value::<i32>(vm)?,
    })
}

fn vector_to_py(v: Vector, vm: &VirtualMachine) -> PyObjectRef {
    let d = vm.ctx.new_dict();
    d.set_item("x", vm.ctx.new_int(v.x).into(), vm).unwrap();
    d.set_item("y", vm.ctx.new_int(v.y).into(), vm).unwrap();
    d.into()
}

fn rectangle_from_py(obj: &PyObjectRef, vm: &VirtualMachine) -> PyResult<Rectangle> {
    Ok(Rectangle {
        x: obj.get_item("x", vm)?.try_into_value::<i32>(vm)?,
        y: obj.get_item("y", vm)?.try_into_value::<i32>(vm)?,
        width: obj.get_item("width", vm)?.try_into_value::<i32>(vm)?,
        height: obj.get_item("height", vm)?.try_into_value::<i32>(vm)?,
    })
}

fn rectangle_to_py(v: Rectangle, vm: &VirtualMachine) -> PyObjectRef {
    let d = vm.ctx.new_dict();
    d.set_item("x", vm.ctx.new_int(v.x).into(), vm).unwrap();
    d.set_item("y", vm.ctx.new_int(v.y).into(), vm).unwrap();
    d.set_item("width", vm.ctx.new_int(v.width).into(), vm).unwrap();
    d.set_item("height", vm.ctx.new_int(v.height).into(), vm).unwrap();
    d.into()
}

fn color_from_py(obj: &PyObjectRef, vm: &VirtualMachine) -> PyResult<Color> {
    Ok(Color {
        r: obj.get_item("r", vm)?.try_into_value::<u8>(vm)?,
        g: obj.get_item("g", vm)?.try_into_value::<u8>(vm)?,
        b: obj.get_item("b", vm)?.try_into_value::<u8>(vm)?,
        a: obj.get_item("a", vm)?.try_into_value::<u8>(vm)?,
    })
}

fn color_to_py(v: Color, vm: &VirtualMachine) -> PyObjectRef {
    let d = vm.ctx.new_dict();
    d.set_item("r", vm.ctx.new_int(v.r).into(), vm).unwrap();
    d.set_item("g", vm.ctx.new_int(v.g).into(), vm).unwrap();
    d.set_item("b", vm.ctx.new_int(v.b).into(), vm).unwrap();
    d.set_item("a", vm.ctx.new_int(v.a).into(), vm).unwrap();
    d.into()
}

fn tilemapprop_to_py(v: TilemapProp, vm: &VirtualMachine) -> PyObjectRef {
    let d = vm.ctx.new_dict();
    d.set_item("name", cstr_to_py(v.name, vm), vm).unwrap();
    d.set_item("type", vm.ctx.new_int(v.r#type).into(), vm).unwrap();
    d.set_item("integer", vm.ctx.new_int(v.integer).into(), vm).unwrap();
    d.set_item("number", vm.ctx.new_float(v.number as f64).into(), vm).unwrap();
    d.set_item("text", cstr_to_py(v.text, vm), vm).unwrap();
    d.into()
}

fn tilemapobject_to_py(v: TilemapObject, vm: &VirtualMachine) -> PyObjectRef {
    let d = vm.ctx.new_dict();
    d.set_item("id", vm.ctx.new_int(v.id).into(), vm).unwrap();
    d.set_item("name", cstr_to_py(v.name, vm), vm).unwrap();
    d.set_item("type", cstr_to_py(v.r#type, vm), vm).unwrap();
    d.set_item("gid", vm.ctx.new_int(v.gid).into(), vm).unwrap();
    d.set_item("x", vm.ctx.new_float(v.x as f64).into(), vm).unwrap();
    d.set_item("y", vm.ctx.new_float(v.y as f64).into(), vm).unwrap();
    d.set_item("width", vm.ctx.new_float(v.width as f64).into(), vm).unwrap();
    d.set_item("height", vm.ctx.new_float(v.height as f64).into(), vm).unwrap();
    d.set_item("rotation", vm.ctx.new_float(v.rotation as f64).into(), vm).unwrap();
    d.set_item("visible", vm.ctx.new_int(v.visible).into(), vm).unwrap();
    d.into()
}

// COLORS

/// Tint a color with another color.
fn nf_color_tint(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let color = color_from_py(&args.args[0], vm)?;
    let tint = color_from_py(&args.args[1], vm)?;
    let ret = unsafe { color_tint(color, tint) } as *const Color;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(color_to_py(unsafe { *ret }, vm))
}

/// Fade a color.
fn nf_color_fade(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let color = color_from_py(&args.args[0], vm)?;
    let alpha = args.args[1].clone().try_into_value::<f32>(vm)?;
    let ret = unsafe { color_fade(color, alpha) } as *const Color;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(color_to_py(unsafe { *ret }, vm))
}

/// Change the brightness of a color.
fn nf_color_brightness(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let color = color_from_py(&args.args[0], vm)?;
    let factor = args.args[1].clone().try_into_value::<f32>(vm)?;
    let ret = unsafe { color_brightness(color, factor) } as *const Color;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(color_to_py(unsafe { *ret }, vm))
}

/// Invert a color.
fn nf_color_invert(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let color = color_from_py(&args.args[0], vm)?;
    let ret = unsafe { color_invert(color) } as *const Color;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(color_to_py(unsafe { *ret }, vm))
}

/// Blend 2 colors together.
fn nf_color_alpha_blend(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let dst = color_from_py(&args.args[0], vm)?;
    let src = color_from_py(&args.args[1], vm)?;
    let ret = unsafe { color_alpha_blend(dst, src) } as *const Color;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(color_to_py(unsafe { *ret }, vm))
}

/// Change contrast of a color.
fn nf_color_contrast(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let color = color_from_py(&args.args[0], vm)?;
    let contrast = args.args[1].clone().try_into_value::<f32>(vm)?;
    let ret = unsafe { color_contrast(color, contrast) } as *const Color;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(color_to_py(unsafe { *ret }, vm))
}

/// Interpolate colors.
fn nf_color_bilinear_interpolate(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let color00 = color_from_py(&args.args[0], vm)?;
    let color01 = color_from_py(&args.args[1], vm)?;
    let color10 = color_from_py(&args.args[2], vm)?;
    let color11 = color_from_py(&args.args[3], vm)?;
    let coordinateX = args.args[4].clone().try_into_value::<f32>(vm)?;
    let coordinateY = args.args[5].clone().try_into_value::<f32>(vm)?;
    let ret = unsafe { color_bilinear_interpolate(color00, color01, color10, color11, coordinateX, coordinateY) } as *const Color;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(color_to_py(unsafe { *ret }, vm))
}

// GRAPHICS

/// Create a new blank image.
fn nf_new_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let width = args.args[0].clone().try_into_value::<i32>(vm)?;
    let height = args.args[1].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[2], vm)?;
    let ret = unsafe { new_image(width, height, color) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Copy an image to a new image.
fn nf_image_copy(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let ret = unsafe { image_copy(image) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Create an image from a region of another image.
fn nf_image_subimage(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let x = args.args[1].clone().try_into_value::<i32>(vm)?;
    let y = args.args[2].clone().try_into_value::<i32>(vm)?;
    let width = args.args[3].clone().try_into_value::<i32>(vm)?;
    let height = args.args[4].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { image_subimage(image, x, y, width, height) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Clear the screen.
fn nf_clear(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let color = color_from_py(&args.args[0], vm)?;
    unsafe { clear(color) };
    Ok(vm.ctx.none())
}

/// Draw a single pixel on the screen.
fn nf_draw_point(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let x = args.args[0].clone().try_into_value::<i32>(vm)?;
    let y = args.args[1].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[2], vm)?;
    unsafe { draw_point(x, y, color) };
    Ok(vm.ctx.none())
}

/// Draw a line on the screen.
fn nf_draw_line(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let startPosX = args.args[0].clone().try_into_value::<i32>(vm)?;
    let startPosY = args.args[1].clone().try_into_value::<i32>(vm)?;
    let endPosX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let endPosY = args.args[3].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[4], vm)?;
    unsafe { draw_line(startPosX, startPosY, endPosX, endPosY, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled rectangle on the screen.
fn nf_draw_rectangle(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let posX = args.args[0].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[1].clone().try_into_value::<i32>(vm)?;
    let width = args.args[2].clone().try_into_value::<i32>(vm)?;
    let height = args.args[3].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[4], vm)?;
    unsafe { draw_rectangle(posX, posY, width, height, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled triangle on the screen.
fn nf_draw_triangle(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let x1 = args.args[0].clone().try_into_value::<i32>(vm)?;
    let y1 = args.args[1].clone().try_into_value::<i32>(vm)?;
    let x2 = args.args[2].clone().try_into_value::<i32>(vm)?;
    let y2 = args.args[3].clone().try_into_value::<i32>(vm)?;
    let x3 = args.args[4].clone().try_into_value::<i32>(vm)?;
    let y3 = args.args[5].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[6], vm)?;
    unsafe { draw_triangle(x1, y1, x2, y2, x3, y3, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled ellipse on the screen.
fn nf_draw_ellipse(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let centerX = args.args[0].clone().try_into_value::<i32>(vm)?;
    let centerY = args.args[1].clone().try_into_value::<i32>(vm)?;
    let radiusX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let radiusY = args.args[3].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[4], vm)?;
    unsafe { draw_ellipse(centerX, centerY, radiusX, radiusY, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled circle on the screen.
fn nf_draw_circle(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let centerX = args.args[0].clone().try_into_value::<i32>(vm)?;
    let centerY = args.args[1].clone().try_into_value::<i32>(vm)?;
    let radius = args.args[2].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[3], vm)?;
    unsafe { draw_circle(centerX, centerY, radius, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled polygon on the screen.
fn nf_draw_polygon(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let points_vec: Vec<Vector> = { let list = args.args[0].clone().try_into_value::<vm::builtins::PyListRef>(vm)?; let mut v = Vec::with_capacity(list.borrow_vec().len()); for item in list.borrow_vec().iter() { v.push(vector_from_py(item, vm)?); } v };
    let points = points_vec.as_ptr();
    let points_len = points_vec.len() as i32;
    let color = color_from_py(&args.args[1], vm)?;
    unsafe { draw_polygon(points, points_len, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled arc on the screen.
fn nf_draw_arc(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let centerX = args.args[0].clone().try_into_value::<i32>(vm)?;
    let centerY = args.args[1].clone().try_into_value::<i32>(vm)?;
    let radius = args.args[2].clone().try_into_value::<f32>(vm)?;
    let startAngle = args.args[3].clone().try_into_value::<f32>(vm)?;
    let endAngle = args.args[4].clone().try_into_value::<f32>(vm)?;
    let segments = args.args[5].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[6], vm)?;
    unsafe { draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled round-rectangle on the screen.
fn nf_draw_rectangle_rounded(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let x = args.args[0].clone().try_into_value::<i32>(vm)?;
    let y = args.args[1].clone().try_into_value::<i32>(vm)?;
    let width = args.args[2].clone().try_into_value::<i32>(vm)?;
    let height = args.args[3].clone().try_into_value::<i32>(vm)?;
    let cornerRadius = args.args[4].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[5], vm)?;
    unsafe { draw_rectangle_rounded(x, y, width, height, cornerRadius, color) };
    Ok(vm.ctx.none())
}

/// Draw an image on the screen.
fn nf_draw_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let src = args.args[0].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[2].clone().try_into_value::<i32>(vm)?;
    unsafe { draw_image(src, posX, posY) };
    Ok(vm.ctx.none())
}

/// Draw a tinted image on the screen.
fn nf_draw_image_tint(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let src = args.args[0].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let tint = color_from_py(&args.args[3], vm)?;
    unsafe { draw_image_tint(src, posX, posY, tint) };
    Ok(vm.ctx.none())
}

/// Draw an image, rotated, on the screen.
fn nf_draw_image_rotated(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let src = args.args[0].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let degrees = args.args[3].clone().try_into_value::<f32>(vm)?;
    let offsetX = args.args[4].clone().try_into_value::<f32>(vm)?;
    let offsetY = args.args[5].clone().try_into_value::<f32>(vm)?;
    let filter = args.args[6].clone().try_into_value::<i32>(vm)?;
    unsafe { draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter) };
    Ok(vm.ctx.none())
}

/// Draw an image, flipped, on the screen.
fn nf_draw_image_flipped(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let src = args.args[0].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let flipHorizontal = args.args[3].clone().try_into_value::<bool>(vm)?;
    let flipVertical = args.args[4].clone().try_into_value::<bool>(vm)?;
    let flipDiagonal = args.args[5].clone().try_into_value::<bool>(vm)?;
    unsafe { draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) };
    Ok(vm.ctx.none())
}

/// Draw an image, scaled, on the screen.
fn nf_draw_image_scaled(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let src = args.args[0].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let scaleX = args.args[3].clone().try_into_value::<f32>(vm)?;
    let scaleY = args.args[4].clone().try_into_value::<f32>(vm)?;
    let offsetX = args.args[5].clone().try_into_value::<f32>(vm)?;
    let offsetY = args.args[6].clone().try_into_value::<f32>(vm)?;
    let filter = args.args[7].clone().try_into_value::<i32>(vm)?;
    unsafe { draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) };
    Ok(vm.ctx.none())
}

/// Draw some text on the screen.
fn nf_draw_text(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let font = args.args[0].clone().try_into_value::<u32>(vm)?;
    let text_cs = CString::new(args.args[1].clone().try_into_value::<String>(vm)?).unwrap();
    let text = text_cs.as_ptr() as *const u8;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[4], vm)?;
    unsafe { draw_text(font, text, posX, posY, color) };
    Ok(vm.ctx.none())
}

/// Save an image to persistant storage.
fn nf_save_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let filename_cs = CString::new(args.args[1].clone().try_into_value::<String>(vm)?).unwrap();
    let filename = filename_cs.as_ptr() as *const u8;
    unsafe { save_image(image, filename) };
    Ok(vm.ctx.none())
}

/// Load an image from a file in cart.
fn nf_load_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let filename_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let filename = filename_cs.as_ptr() as *const u8;
    let ret = unsafe { load_image(filename) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Resize an image, return copy.
fn nf_image_resize(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let newWidth = args.args[1].clone().try_into_value::<i32>(vm)?;
    let newHeight = args.args[2].clone().try_into_value::<i32>(vm)?;
    let filter = args.args[3].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { image_resize(image, newWidth, newHeight, filter) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Scale an image, return copy.
fn nf_image_scale(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let scaleX = args.args[1].clone().try_into_value::<f32>(vm)?;
    let scaleY = args.args[2].clone().try_into_value::<f32>(vm)?;
    let filter = args.args[3].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { image_scale(image, scaleX, scaleY, filter) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Replace a color in an image, in-place.
fn nf_image_color_replace(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let color = color_from_py(&args.args[1], vm)?;
    let replace = color_from_py(&args.args[2], vm)?;
    unsafe { image_color_replace(image, color, replace) };
    Ok(vm.ctx.none())
}

/// Tint a color in an image, in-place.
fn nf_image_color_tint(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let color = color_from_py(&args.args[1], vm)?;
    unsafe { image_color_tint(image, color) };
    Ok(vm.ctx.none())
}

/// Fade a color in an image, in-place.
fn nf_image_color_fade(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let alpha = args.args[1].clone().try_into_value::<f32>(vm)?;
    unsafe { image_color_fade(image, alpha) };
    Ok(vm.ctx.none())
}

/// Copy a font to a new font.
fn nf_font_copy(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let font = args.args[0].clone().try_into_value::<u32>(vm)?;
    let ret = unsafe { font_copy(font) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Scale a font, return a new font.
fn nf_font_scale(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let font = args.args[0].clone().try_into_value::<u32>(vm)?;
    let scaleX = args.args[1].clone().try_into_value::<f32>(vm)?;
    let scaleY = args.args[2].clone().try_into_value::<f32>(vm)?;
    let filter = args.args[3].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { font_scale(font, scaleX, scaleY, filter) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Load a BMF font from a file in cart.
fn nf_load_font_bmf(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let filename_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let filename = filename_cs.as_ptr() as *const u8;
    let characters_cs = CString::new(args.args[1].clone().try_into_value::<String>(vm)?).unwrap();
    let characters = characters_cs.as_ptr() as *const u8;
    let ret = unsafe { load_font_bmf(filename, characters) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Load a BMF font from an image.
fn nf_load_font_bmf_from_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let characters_cs = CString::new(args.args[1].clone().try_into_value::<String>(vm)?).unwrap();
    let characters = characters_cs.as_ptr() as *const u8;
    let ret = unsafe { load_font_bmf_from_image(image, characters) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Measure the size of some text.
fn nf_measure_text(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let font = args.args[0].clone().try_into_value::<u32>(vm)?;
    let text_cs = CString::new(args.args[1].clone().try_into_value::<String>(vm)?).unwrap();
    let text = text_cs.as_ptr() as *const u8;
    let textLength = args.args[2].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { measure_text(font, text, textLength) } as *const Dimensions;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(dimensions_to_py(unsafe { *ret }, vm))
}

/// Meaure an image (use 0 for screen).
fn nf_measure_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let ret = unsafe { measure_image(image) } as *const Dimensions;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(dimensions_to_py(unsafe { *ret }, vm))
}

/// Load a TTY font from a file in cart.
fn nf_load_font_tty(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let filename_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let filename = filename_cs.as_ptr() as *const u8;
    let glyphWidth = args.args[1].clone().try_into_value::<i32>(vm)?;
    let glyphHeight = args.args[2].clone().try_into_value::<i32>(vm)?;
    let characters_cs = CString::new(args.args[3].clone().try_into_value::<String>(vm)?).unwrap();
    let characters = characters_cs.as_ptr() as *const u8;
    let ret = unsafe { load_font_tty(filename, glyphWidth, glyphHeight, characters) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Load a TTY font from an image.
fn nf_load_font_tty_from_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let glyphWidth = args.args[1].clone().try_into_value::<i32>(vm)?;
    let glyphHeight = args.args[2].clone().try_into_value::<i32>(vm)?;
    let characters_cs = CString::new(args.args[3].clone().try_into_value::<String>(vm)?).unwrap();
    let characters = characters_cs.as_ptr() as *const u8;
    let ret = unsafe { load_font_tty_from_image(image, glyphWidth, glyphHeight, characters) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Load a TTF font from a file in cart.
fn nf_load_font_ttf(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let filename_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let filename = filename_cs.as_ptr() as *const u8;
    let fontSize = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { load_font_ttf(filename, fontSize) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Invert the colors in an image, in-place.
fn nf_image_color_invert(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    unsafe { image_color_invert(image) };
    Ok(vm.ctx.none())
}

/// Calculate a rectangle representing the available alpha border in an image.
fn nf_image_alpha_border(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let threshold = args.args[1].clone().try_into_value::<f32>(vm)?;
    let ret = unsafe { image_alpha_border(image, threshold) } as *const Rectangle;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(rectangle_to_py(unsafe { *ret }, vm))
}

/// Crop an image, in-place.
fn nf_image_crop(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let x = args.args[1].clone().try_into_value::<i32>(vm)?;
    let y = args.args[2].clone().try_into_value::<i32>(vm)?;
    let width = args.args[3].clone().try_into_value::<i32>(vm)?;
    let height = args.args[4].clone().try_into_value::<i32>(vm)?;
    unsafe { image_crop(image, x, y, width, height) };
    Ok(vm.ctx.none())
}

/// Crop an image based on the alpha border, in-place.
fn nf_image_alpha_crop(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let threshold = args.args[1].clone().try_into_value::<f32>(vm)?;
    unsafe { image_alpha_crop(image, threshold) };
    Ok(vm.ctx.none())
}

/// Adjust the brightness of an image, in-place.
fn nf_image_color_brightness(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let factor = args.args[1].clone().try_into_value::<f32>(vm)?;
    unsafe { image_color_brightness(image, factor) };
    Ok(vm.ctx.none())
}

/// Flip an image, in-place.
fn nf_image_flip(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let horizontal = args.args[1].clone().try_into_value::<bool>(vm)?;
    let vertical = args.args[2].clone().try_into_value::<bool>(vm)?;
    unsafe { image_flip(image, horizontal, vertical) };
    Ok(vm.ctx.none())
}

/// Change the contrast of an image, in-place.
fn nf_image_color_contrast(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let contrast = args.args[1].clone().try_into_value::<f32>(vm)?;
    unsafe { image_color_contrast(image, contrast) };
    Ok(vm.ctx.none())
}

/// Use an image as an alpha-mask on another image.
fn nf_image_alpha_mask(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let alphaMask = args.args[1].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    unsafe { image_alpha_mask(image, alphaMask, posX, posY) };
    Ok(vm.ctx.none())
}

/// Create a new image, rotating another image.
fn nf_image_rotate(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    let degrees = args.args[1].clone().try_into_value::<f32>(vm)?;
    let filter = args.args[2].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { image_rotate(image, degrees, filter) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Create a new image of a gradient.
fn nf_image_gradient(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let width = args.args[0].clone().try_into_value::<i32>(vm)?;
    let height = args.args[1].clone().try_into_value::<i32>(vm)?;
    let topLeft = color_from_py(&args.args[2], vm)?;
    let topRight = color_from_py(&args.args[3], vm)?;
    let bottomLeft = color_from_py(&args.args[4], vm)?;
    let bottomRight = color_from_py(&args.args[5], vm)?;
    let ret = unsafe { image_gradient(width, height, topLeft, topRight, bottomLeft, bottomRight) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Unload an image.
fn nf_unload_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let image = args.args[0].clone().try_into_value::<u32>(vm)?;
    unsafe { unload_image(image) };
    Ok(vm.ctx.none())
}

/// Unload a font.
fn nf_unload_font(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let font = args.args[0].clone().try_into_value::<u32>(vm)?;
    unsafe { unload_font(font) };
    Ok(vm.ctx.none())
}

/// Clear an image.
fn nf_clear_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let color = color_from_py(&args.args[1], vm)?;
    unsafe { clear_image(destination, color) };
    Ok(vm.ctx.none())
}

/// Draw a single pixel on an image.
fn nf_draw_point_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let x = args.args[1].clone().try_into_value::<i32>(vm)?;
    let y = args.args[2].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[3], vm)?;
    unsafe { draw_point_on_image(destination, x, y, color) };
    Ok(vm.ctx.none())
}

/// Draw a line on an image.
fn nf_draw_line_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let startPosX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let startPosY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let endPosX = args.args[3].clone().try_into_value::<i32>(vm)?;
    let endPosY = args.args[4].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[5], vm)?;
    unsafe { draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled rectangle on an image.
fn nf_draw_rectangle_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let width = args.args[3].clone().try_into_value::<i32>(vm)?;
    let height = args.args[4].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[5], vm)?;
    unsafe { draw_rectangle_on_image(destination, posX, posY, width, height, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled triangle on an image.
fn nf_draw_triangle_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let x1 = args.args[1].clone().try_into_value::<i32>(vm)?;
    let y1 = args.args[2].clone().try_into_value::<i32>(vm)?;
    let x2 = args.args[3].clone().try_into_value::<i32>(vm)?;
    let y2 = args.args[4].clone().try_into_value::<i32>(vm)?;
    let x3 = args.args[5].clone().try_into_value::<i32>(vm)?;
    let y3 = args.args[6].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[7], vm)?;
    unsafe { draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled ellipse on an image.
fn nf_draw_ellipse_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let centerX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let centerY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let radiusX = args.args[3].clone().try_into_value::<i32>(vm)?;
    let radiusY = args.args[4].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[5], vm)?;
    unsafe { draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, color) };
    Ok(vm.ctx.none())
}

/// Draw a circle on an image.
fn nf_draw_circle_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let centerX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let centerY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let radius = args.args[3].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[4], vm)?;
    unsafe { draw_circle_on_image(destination, centerX, centerY, radius, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled polygon on an image.
fn nf_draw_polygon_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let points_vec: Vec<Vector> = { let list = args.args[1].clone().try_into_value::<vm::builtins::PyListRef>(vm)?; let mut v = Vec::with_capacity(list.borrow_vec().len()); for item in list.borrow_vec().iter() { v.push(vector_from_py(item, vm)?); } v };
    let points = points_vec.as_ptr();
    let points_len = points_vec.len() as i32;
    let color = color_from_py(&args.args[2], vm)?;
    unsafe { draw_polygon_on_image(destination, points, points_len, color) };
    Ok(vm.ctx.none())
}

/// Draw a filled round-rectangle on an image.
fn nf_draw_rectangle_rounded_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let x = args.args[1].clone().try_into_value::<i32>(vm)?;
    let y = args.args[2].clone().try_into_value::<i32>(vm)?;
    let width = args.args[3].clone().try_into_value::<i32>(vm)?;
    let height = args.args[4].clone().try_into_value::<i32>(vm)?;
    let cornerRadius = args.args[5].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[6], vm)?;
    unsafe { draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, color) };
    Ok(vm.ctx.none())
}

/// Draw an image on an image.
fn nf_draw_image_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let src = args.args[1].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    unsafe { draw_image_on_image(destination, src, posX, posY) };
    Ok(vm.ctx.none())
}

/// Draw a tinted image on an image.
fn nf_draw_image_tint_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let src = args.args[1].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    let tint = color_from_py(&args.args[4], vm)?;
    unsafe { draw_image_tint_on_image(destination, src, posX, posY, tint) };
    Ok(vm.ctx.none())
}

/// Draw an image, rotated, on an image.
fn nf_draw_image_rotated_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let src = args.args[1].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    let degrees = args.args[4].clone().try_into_value::<f32>(vm)?;
    let offsetX = args.args[5].clone().try_into_value::<f32>(vm)?;
    let offsetY = args.args[6].clone().try_into_value::<f32>(vm)?;
    let filter = args.args[7].clone().try_into_value::<i32>(vm)?;
    unsafe { draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter) };
    Ok(vm.ctx.none())
}

/// Draw an image, flipped, on an image.
fn nf_draw_image_flipped_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let src = args.args[1].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    let flipHorizontal = args.args[4].clone().try_into_value::<bool>(vm)?;
    let flipVertical = args.args[5].clone().try_into_value::<bool>(vm)?;
    let flipDiagonal = args.args[6].clone().try_into_value::<bool>(vm)?;
    unsafe { draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) };
    Ok(vm.ctx.none())
}

/// Draw an image, scaled, on an image.
fn nf_draw_image_scaled_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let src = args.args[1].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    let scaleX = args.args[4].clone().try_into_value::<f32>(vm)?;
    let scaleY = args.args[5].clone().try_into_value::<f32>(vm)?;
    let offsetX = args.args[6].clone().try_into_value::<f32>(vm)?;
    let offsetY = args.args[7].clone().try_into_value::<f32>(vm)?;
    let filter = args.args[8].clone().try_into_value::<i32>(vm)?;
    unsafe { draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) };
    Ok(vm.ctx.none())
}

/// Draw some text on an image.
fn nf_draw_text_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let font = args.args[1].clone().try_into_value::<u32>(vm)?;
    let text_cs = CString::new(args.args[2].clone().try_into_value::<String>(vm)?).unwrap();
    let text = text_cs.as_ptr() as *const u8;
    let posX = args.args[3].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[4].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[5], vm)?;
    unsafe { draw_text_on_image(destination, font, text, posX, posY, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) rectangle on the screen.
fn nf_draw_rectangle_outline(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let posX = args.args[0].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[1].clone().try_into_value::<i32>(vm)?;
    let width = args.args[2].clone().try_into_value::<i32>(vm)?;
    let height = args.args[3].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[4].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[5], vm)?;
    unsafe { draw_rectangle_outline(posX, posY, width, height, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) triangle on the screen.
fn nf_draw_triangle_outline(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let x1 = args.args[0].clone().try_into_value::<i32>(vm)?;
    let y1 = args.args[1].clone().try_into_value::<i32>(vm)?;
    let x2 = args.args[2].clone().try_into_value::<i32>(vm)?;
    let y2 = args.args[3].clone().try_into_value::<i32>(vm)?;
    let x3 = args.args[4].clone().try_into_value::<i32>(vm)?;
    let y3 = args.args[5].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[6].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[7], vm)?;
    unsafe { draw_triangle_outline(x1, y1, x2, y2, x3, y3, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) ellipse on the screen.
fn nf_draw_ellipse_outline(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let centerX = args.args[0].clone().try_into_value::<i32>(vm)?;
    let centerY = args.args[1].clone().try_into_value::<i32>(vm)?;
    let radiusX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let radiusY = args.args[3].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[4].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[5], vm)?;
    unsafe { draw_ellipse_outline(centerX, centerY, radiusX, radiusY, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) circle on the screen.
fn nf_draw_circle_outline(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let centerX = args.args[0].clone().try_into_value::<i32>(vm)?;
    let centerY = args.args[1].clone().try_into_value::<i32>(vm)?;
    let radius = args.args[2].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[3].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[4], vm)?;
    unsafe { draw_circle_outline(centerX, centerY, radius, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) polygon on the screen.
fn nf_draw_polygon_outline(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let points_vec: Vec<Vector> = { let list = args.args[0].clone().try_into_value::<vm::builtins::PyListRef>(vm)?; let mut v = Vec::with_capacity(list.borrow_vec().len()); for item in list.borrow_vec().iter() { v.push(vector_from_py(item, vm)?); } v };
    let points = points_vec.as_ptr();
    let points_len = points_vec.len() as i32;
    let thickness = args.args[1].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[2], vm)?;
    unsafe { draw_polygon_outline(points, points_len, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) arc on the screen.
fn nf_draw_arc_outline(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let centerX = args.args[0].clone().try_into_value::<i32>(vm)?;
    let centerY = args.args[1].clone().try_into_value::<i32>(vm)?;
    let radius = args.args[2].clone().try_into_value::<f32>(vm)?;
    let startAngle = args.args[3].clone().try_into_value::<f32>(vm)?;
    let endAngle = args.args[4].clone().try_into_value::<f32>(vm)?;
    let segments = args.args[5].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[6].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[7], vm)?;
    unsafe { draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) round-rectangle on the screen.
fn nf_draw_rectangle_rounded_outline(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let x = args.args[0].clone().try_into_value::<i32>(vm)?;
    let y = args.args[1].clone().try_into_value::<i32>(vm)?;
    let width = args.args[2].clone().try_into_value::<i32>(vm)?;
    let height = args.args[3].clone().try_into_value::<i32>(vm)?;
    let cornerRadius = args.args[4].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[5].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[6], vm)?;
    unsafe { draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) rectangle on an image.
fn nf_draw_rectangle_outline_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let width = args.args[3].clone().try_into_value::<i32>(vm)?;
    let height = args.args[4].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[5].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[6], vm)?;
    unsafe { draw_rectangle_outline_on_image(destination, posX, posY, width, height, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) triangle on an image.
fn nf_draw_triangle_outline_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let x1 = args.args[1].clone().try_into_value::<i32>(vm)?;
    let y1 = args.args[2].clone().try_into_value::<i32>(vm)?;
    let x2 = args.args[3].clone().try_into_value::<i32>(vm)?;
    let y2 = args.args[4].clone().try_into_value::<i32>(vm)?;
    let x3 = args.args[5].clone().try_into_value::<i32>(vm)?;
    let y3 = args.args[6].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[7].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[8], vm)?;
    unsafe { draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) ellipse on an image.
fn nf_draw_ellipse_outline_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let centerX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let centerY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let radiusX = args.args[3].clone().try_into_value::<i32>(vm)?;
    let radiusY = args.args[4].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[5].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[6], vm)?;
    unsafe { draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) circle on an image.
fn nf_draw_circle_outline_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let centerX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let centerY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let radius = args.args[3].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[4].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[5], vm)?;
    unsafe { draw_circle_outline_on_image(destination, centerX, centerY, radius, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) polygon on an image.
fn nf_draw_polygon_outline_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let points_vec: Vec<Vector> = { let list = args.args[1].clone().try_into_value::<vm::builtins::PyListRef>(vm)?; let mut v = Vec::with_capacity(list.borrow_vec().len()); for item in list.borrow_vec().iter() { v.push(vector_from_py(item, vm)?); } v };
    let points = points_vec.as_ptr();
    let points_len = points_vec.len() as i32;
    let thickness = args.args[2].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[3], vm)?;
    unsafe { draw_polygon_outline_on_image(destination, points, points_len, thickness, color) };
    Ok(vm.ctx.none())
}

/// Draw a outlined (with thickness) round-rectangle on an image.
fn nf_draw_rectangle_rounded_outline_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let destination = args.args[0].clone().try_into_value::<u32>(vm)?;
    let x = args.args[1].clone().try_into_value::<i32>(vm)?;
    let y = args.args[2].clone().try_into_value::<i32>(vm)?;
    let width = args.args[3].clone().try_into_value::<i32>(vm)?;
    let height = args.args[4].clone().try_into_value::<i32>(vm)?;
    let cornerRadius = args.args[5].clone().try_into_value::<i32>(vm)?;
    let thickness = args.args[6].clone().try_into_value::<i32>(vm)?;
    let color = color_from_py(&args.args[7], vm)?;
    unsafe { draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, thickness, color) };
    Ok(vm.ctx.none())
}

// GUI

/// Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window.
fn nf_gui_begin_window(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let title_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let title = title_cs.as_ptr() as *const u8;
    let rect = rectangle_from_py(&args.args[1], vm)?;
    let ret = unsafe { gui_begin_window(title, rect) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// End the current GUI window.
fn nf_gui_end_window(_args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    unsafe { gui_end_window() };
    Ok(vm.ctx.none())
}

/// A button. Returns true when it is clicked.
fn nf_gui_button(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let label_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let label = label_cs.as_ptr() as *const u8;
    let ret = unsafe { gui_button(label) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// A static text label.
fn nf_gui_label(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let text_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let text = text_cs.as_ptr() as *const u8;
    unsafe { gui_label(text) };
    Ok(vm.ctx.none())
}

/// A block of wrapping text.
fn nf_gui_text(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let text_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let text = text_cs.as_ptr() as *const u8;
    unsafe { gui_text(text) };
    Ok(vm.ctx.none())
}

/// A checkbox. Returns the (possibly changed) state.
fn nf_gui_checkbox(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let label_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let label = label_cs.as_ptr() as *const u8;
    let state = args.args[1].clone().try_into_value::<bool>(vm)?;
    let ret = unsafe { gui_checkbox(label, state) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// A slider. Returns the (possibly changed) value.
fn nf_gui_slider(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let value = args.args[0].clone().try_into_value::<f32>(vm)?;
    let low = args.args[1].clone().try_into_value::<f32>(vm)?;
    let high = args.args[2].clone().try_into_value::<f32>(vm)?;
    let ret = unsafe { gui_slider(value, low, high) };
    Ok(vm.ctx.new_float(ret as f64).into())
}

/// Set the current layout row - the column widths (negative for flexible), and the row height.
fn nf_gui_layout_row(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let widths_vec: Vec<i32> = args.args[0].clone().try_into_value::<Vec<i32>>(vm)?;
    let widths = widths_vec.as_ptr();
    let widths_len = widths_vec.len() as i32;
    let height = args.args[1].clone().try_into_value::<i32>(vm)?;
    unsafe { gui_layout_row(widths, widths_len, height) };
    Ok(vm.ctx.none())
}

/// Finish building the GUI for this frame. Called automatically at the end of update if you do not call it.
fn nf_gui_end(_args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    unsafe { gui_end() };
    Ok(vm.ctx.none())
}

/// Draw the GUI to an image (0 is the screen).
fn nf_gui_draw(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let dst = args.args[0].clone().try_into_value::<u32>(vm)?;
    unsafe { gui_draw(dst) };
    Ok(vm.ctx.none())
}

// INPUT

/// Has the key been pressed? (tracks unpress/read correctly.)
fn nf_key_pressed(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let key = args.args[0].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { key_pressed(key) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Is the key currently down?
fn nf_key_down(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let key = args.args[0].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { key_down(key) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Has the key been released? (tracks press/read correctly.)
fn nf_key_released(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let key = args.args[0].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { key_released(key) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Is the key currently up?
fn nf_key_up(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let key = args.args[0].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { key_up(key) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Has the button been pressed? (tracks unpress/read correctly.)
fn nf_gamepad_button_pressed(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let gamepad = args.args[0].clone().try_into_value::<i32>(vm)?;
    let button = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { gamepad_button_pressed(gamepad, button) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Is the button currently down?
fn nf_gamepad_button_down(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let gamepad = args.args[0].clone().try_into_value::<i32>(vm)?;
    let button = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { gamepad_button_down(gamepad, button) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Has the button been released? (tracks press/read correctly.)
fn nf_gamepad_button_released(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let gamepad = args.args[0].clone().try_into_value::<i32>(vm)?;
    let button = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { gamepad_button_released(gamepad, button) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Get current position of mouse.
fn nf_mouse_position(_args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let ret = unsafe { mouse_position() } as *const Vector;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(vector_to_py(unsafe { *ret }, vm))
}

/// Has the button been pressed? (tracks unpress/read correctly.)
fn nf_mouse_button_pressed(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let button = args.args[0].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { mouse_button_pressed(button) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Is the button currently down?
fn nf_mouse_button_down(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let button = args.args[0].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { mouse_button_down(button) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Has the button been released? (tracks press/read correctly.)
fn nf_mouse_button_released(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let button = args.args[0].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { mouse_button_released(button) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Is the button currently up?
fn nf_mouse_button_up(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let button = args.args[0].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { mouse_button_up(button) };
    Ok(vm.ctx.new_bool(ret).into())
}

// SOUND

/// Load a sound from a file in cart.
fn nf_load_sound(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let filename_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let filename = filename_cs.as_ptr() as *const u8;
    let ret = unsafe { load_sound(filename) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Play a sound.
fn nf_play_sound(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let sound = args.args[0].clone().try_into_value::<u32>(vm)?;
    let r#loop = args.args[1].clone().try_into_value::<bool>(vm)?;
    unsafe { play_sound(sound, r#loop) };
    Ok(vm.ctx.none())
}

/// Stop a sound.
fn nf_stop_sound(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let sound = args.args[0].clone().try_into_value::<u32>(vm)?;
    unsafe { stop_sound(sound) };
    Ok(vm.ctx.none())
}

/// Unload a sound.
fn nf_unload_sound(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let sound = args.args[0].clone().try_into_value::<u32>(vm)?;
    unsafe { unload_sound(sound) };
    Ok(vm.ctx.none())
}

/// Speak some text and return a sound. Set things to 0 for defaults.
fn nf_tts_sound(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let text_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let text = text_cs.as_ptr() as *const u8;
    let phonetic = args.args[1].clone().try_into_value::<bool>(vm)?;
    let pitch = args.args[2].clone().try_into_value::<i32>(vm)?;
    let speed = args.args[3].clone().try_into_value::<i32>(vm)?;
    let throat = args.args[4].clone().try_into_value::<i32>(vm)?;
    let mouth = args.args[5].clone().try_into_value::<i32>(vm)?;
    let sing = args.args[6].clone().try_into_value::<bool>(vm)?;
    let ret = unsafe { tts_sound(text, phonetic, pitch, speed, throat, mouth, sing) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Create Sfx sound.
fn nf_sfx_sound(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let params = sfxparams_from_py(&args.args[0], vm)?;
    let ret = unsafe { sfx_sound(params) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Create Sfx parameters.
fn nf_sfx_generate(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let r#type = args.args[0].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { sfx_generate(r#type) } as *const SfxParams;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(sfxparams_to_py(unsafe { *ret }, vm))
}

// TILE

/// Load a tilemap (a Tiled map, exported as JSON) from a file in cart.
fn nf_load_tilemap(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let filename_cs = CString::new(args.args[0].clone().try_into_value::<String>(vm)?).unwrap();
    let filename = filename_cs.as_ptr() as *const u8;
    let ret = unsafe { load_tilemap(filename) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Unload a tilemap.
fn nf_unload_tilemap(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    unsafe { unload_tilemap(tilemap) };
    Ok(vm.ctx.none())
}

/// Update a tilemap's animation timers (deltaTime is in seconds).
fn nf_tile_update(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let deltaTime = args.args[1].clone().try_into_value::<f32>(vm)?;
    unsafe { tile_update(tilemap, deltaTime) };
    Ok(vm.ctx.none())
}

/// Get the size of a tilemap, in tiles.
fn nf_tile_map_size(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let ret = unsafe { tile_map_size(tilemap) } as *const Dimensions;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(dimensions_to_py(unsafe { *ret }, vm))
}

/// Get the size of a single tile of a tilemap, in pixels.
fn nf_tile_tile_size(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let ret = unsafe { tile_tile_size(tilemap) } as *const Dimensions;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(dimensions_to_py(unsafe { *ret }, vm))
}

/// Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.)
fn nf_tile_map_prop(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let name_cs = CString::new(args.args[1].clone().try_into_value::<String>(vm)?).unwrap();
    let name = name_cs.as_ptr() as *const u8;
    let ret = unsafe { tile_map_prop(tilemap, name) } as *const TilemapProp;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(tilemapprop_to_py(unsafe { *ret }, vm))
}

/// Get the number of custom properties on a tilemap.
fn nf_tile_map_prop_count(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let ret = unsafe { tile_map_prop_count(tilemap) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get a custom property of a tilemap, by index (PROP_NONE when out of range.)
fn nf_tile_map_prop_at(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let index = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_map_prop_at(tilemap, index) } as *const TilemapProp;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(tilemapprop_to_py(unsafe { *ret }, vm))
}

/// Draw a tilemap on the screen.
fn nf_tile_draw(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[2].clone().try_into_value::<i32>(vm)?;
    unsafe { tile_draw(tilemap, posX, posY) };
    Ok(vm.ctx.none())
}

/// Draw a tilemap on the screen, tinted by a color.
fn nf_tile_draw_tint(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[2].clone().try_into_value::<i32>(vm)?;
    let tint = color_from_py(&args.args[3], vm)?;
    unsafe { tile_draw_tint(tilemap, posX, posY, tint) };
    Ok(vm.ctx.none())
}

/// Draw a tilemap on an image.
fn nf_tile_draw_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let dst = args.args[0].clone().try_into_value::<u32>(vm)?;
    let tilemap = args.args[1].clone().try_into_value::<u32>(vm)?;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    unsafe { tile_draw_on_image(dst, tilemap, posX, posY) };
    Ok(vm.ctx.none())
}

/// Render a whole tilemap to a new image.
fn nf_tilemap_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let ret = unsafe { tilemap_image(tilemap) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too.
fn nf_tile_layer_count(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let ret = unsafe { tile_layer_count(tilemap) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get the index of a layer of a tilemap, by name (-1 when there is no such layer.)
fn nf_tile_layer_index(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let name_cs = CString::new(args.args[1].clone().try_into_value::<String>(vm)?).unwrap();
    let name = name_cs.as_ptr() as *const u8;
    let ret = unsafe { tile_layer_index(tilemap, name) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get the name of a layer of a tilemap.
fn nf_tile_layer_name(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_layer_name(tilemap, layer) };
    Ok(cstr_to_py(ret as *const u8, vm))
}

/// Get the kind of a layer of a tilemap.
fn nf_tile_layer_type(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_layer_type(tilemap, layer) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get the size of a layer of a tilemap, in tiles.
fn nf_tile_layer_size(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_layer_size(tilemap, layer) } as *const Dimensions;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(dimensions_to_py(unsafe { *ret }, vm))
}

/// Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing.
fn nf_tile_layer_visible(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_layer_visible(tilemap, layer) };
    Ok(vm.ctx.new_bool(ret).into())
}

/// Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.)
fn nf_tile_layer_prop(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let name_cs = CString::new(args.args[2].clone().try_into_value::<String>(vm)?).unwrap();
    let name = name_cs.as_ptr() as *const u8;
    let ret = unsafe { tile_layer_prop(tilemap, layer, name) } as *const TilemapProp;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(tilemapprop_to_py(unsafe { *ret }, vm))
}

/// Get the number of custom properties on a layer of a tilemap.
fn nf_tile_layer_prop_count(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_layer_prop_count(tilemap, layer) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.)
fn nf_tile_layer_prop_at(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let index = args.args[2].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_layer_prop_at(tilemap, layer, index) } as *const TilemapProp;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(tilemapprop_to_py(unsafe { *ret }, vm))
}

/// Draw a single layer of a tilemap on the screen.
fn nf_tile_draw_layer(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    unsafe { tile_draw_layer(tilemap, layer, posX, posY) };
    Ok(vm.ctx.none())
}

/// Draw a single layer of a tilemap on the screen, tinted by a color.
fn nf_tile_draw_layer_tint(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    let tint = color_from_py(&args.args[4], vm)?;
    unsafe { tile_draw_layer_tint(tilemap, layer, posX, posY, tint) };
    Ok(vm.ctx.none())
}

/// Draw a single layer of a tilemap on an image.
fn nf_tile_draw_layer_on_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let dst = args.args[0].clone().try_into_value::<u32>(vm)?;
    let tilemap = args.args[1].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posX = args.args[3].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[4].clone().try_into_value::<i32>(vm)?;
    unsafe { tile_draw_layer_on_image(dst, tilemap, layer, posX, posY) };
    Ok(vm.ctx.none())
}

/// Render a single layer of a tilemap to a new image.
fn nf_tile_layer_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_layer_image(tilemap, layer) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get the gid of the tile at a column/row in a tilemap layer.
fn nf_tile_get_tile(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let column = args.args[2].clone().try_into_value::<i32>(vm)?;
    let row = args.args[3].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_get_tile(tilemap, layer, column, row) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself.
fn nf_tile_set_tile(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let column = args.args[2].clone().try_into_value::<i32>(vm)?;
    let row = args.args[3].clone().try_into_value::<i32>(vm)?;
    let gid = args.args[4].clone().try_into_value::<i32>(vm)?;
    unsafe { tile_set_tile(tilemap, layer, column, row, gid) };
    Ok(vm.ctx.none())
}

/// Draw a single tile from a tilemap on the screen.
fn nf_tile_draw_tile(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let gid = args.args[1].clone().try_into_value::<i32>(vm)?;
    let posX = args.args[2].clone().try_into_value::<i32>(vm)?;
    let posY = args.args[3].clone().try_into_value::<i32>(vm)?;
    unsafe { tile_draw_tile(tilemap, gid, posX, posY) };
    Ok(vm.ctx.none())
}

/// Get a copy of the image of a single tile in a tilemap.
fn nf_tile_image(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let gid = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_image(tilemap, gid) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them.
fn nf_tile_gid_prop(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let gid = args.args[1].clone().try_into_value::<i32>(vm)?;
    let name_cs = CString::new(args.args[2].clone().try_into_value::<String>(vm)?).unwrap();
    let name = name_cs.as_ptr() as *const u8;
    let ret = unsafe { tile_gid_prop(tilemap, gid, name) } as *const TilemapProp;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(tilemapprop_to_py(unsafe { *ret }, vm))
}

/// Get the number of custom properties on a tile of a tilemap.
fn nf_tile_gid_prop_count(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let gid = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_gid_prop_count(tilemap, gid) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.)
fn nf_tile_gid_prop_at(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let gid = args.args[1].clone().try_into_value::<i32>(vm)?;
    let index = args.args[2].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_gid_prop_at(tilemap, gid, index) } as *const TilemapProp;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(tilemapprop_to_py(unsafe { *ret }, vm))
}

/// Get the number of objects on an object-layer of a tilemap.
fn nf_tile_object_count(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_object_count(tilemap, layer) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get an object from an object-layer of a tilemap.
fn nf_tile_object(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let index = args.args[2].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_object(tilemap, layer, index) } as *const TilemapObject;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(tilemapobject_to_py(unsafe { *ret }, vm))
}

/// Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.)
fn nf_tile_object_index(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let name_cs = CString::new(args.args[2].clone().try_into_value::<String>(vm)?).unwrap();
    let name = name_cs.as_ptr() as *const u8;
    let ret = unsafe { tile_object_index(tilemap, layer, name) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.)
fn nf_tile_object_prop(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let index = args.args[2].clone().try_into_value::<i32>(vm)?;
    let name_cs = CString::new(args.args[3].clone().try_into_value::<String>(vm)?).unwrap();
    let name = name_cs.as_ptr() as *const u8;
    let ret = unsafe { tile_object_prop(tilemap, layer, index, name) } as *const TilemapProp;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(tilemapprop_to_py(unsafe { *ret }, vm))
}

/// Get the number of custom properties on an object of a tilemap.
fn nf_tile_object_prop_count(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let index = args.args[2].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_object_prop_count(tilemap, layer, index) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.)
fn nf_tile_object_prop_at(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let tilemap = args.args[0].clone().try_into_value::<u32>(vm)?;
    let layer = args.args[1].clone().try_into_value::<i32>(vm)?;
    let index = args.args[2].clone().try_into_value::<i32>(vm)?;
    let propIndex = args.args[3].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { tile_object_prop_at(tilemap, layer, index, propIndex) } as *const TilemapProp;
    if ret.is_null() {
        return Ok(vm.ctx.none());
    }
    Ok(tilemapprop_to_py(unsafe { *ret }, vm))
}

// TYPES

// UTILITIES

/// Get system-time (ms) since unix epoch.
fn nf_current_time(_args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let ret = unsafe { current_time() };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get the change in time (seconds) since the last update run.
fn nf_delta_time(_args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let ret = unsafe { delta_time() };
    Ok(vm.ctx.new_float(ret as f64).into())
}

/// Get a random integer between 2 numbers.
fn nf_random_int(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let min = args.args[0].clone().try_into_value::<i32>(vm)?;
    let max = args.args[1].clone().try_into_value::<i32>(vm)?;
    let ret = unsafe { random_int(min, max) };
    Ok(vm.ctx.new_int(ret).into())
}

/// Get the random-seed.
fn nf_random_seed_get(_args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let ret = unsafe { random_seed_get() };
    Ok(vm.ctx.new_int(ret).into())
}

/// Set the random-seed.
fn nf_random_seed_set(args: FuncArgs, vm: &VirtualMachine) -> PyResult<PyObjectRef> {
    let seed = args.args[0].clone().try_into_value::<u64>(vm)?;
    unsafe { random_seed_set(seed) };
    Ok(vm.ctx.none())
}

// CONSTANTS

fn register_constants(scope: &Scope, vm: &VirtualMachine) {
    scope.globals.set_item("SCREEN", vm.ctx.new_int(0).into(), vm).unwrap();
    scope.globals.set_item("SCREEN_WIDTH", vm.ctx.new_int(640).into(), vm).unwrap();
    scope.globals.set_item("SCREEN_HEIGHT", vm.ctx.new_int(480).into(), vm).unwrap();
    scope.globals.set_item("FONT_DEFAULT", vm.ctx.new_int(0).into(), vm).unwrap();
    scope.globals.set_item("LIGHTGRAY", color_to_py(Color { r: 200, g: 200, b: 200, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("GRAY", color_to_py(Color { r: 130, g: 130, b: 130, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("DARKGRAY", color_to_py(Color { r: 80, g: 80, b: 80, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("YELLOW", color_to_py(Color { r: 253, g: 249, b: 0, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("GOLD", color_to_py(Color { r: 255, g: 203, b: 0, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("ORANGE", color_to_py(Color { r: 255, g: 161, b: 0, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("PINK", color_to_py(Color { r: 255, g: 109, b: 194, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("RED", color_to_py(Color { r: 230, g: 41, b: 55, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("MAROON", color_to_py(Color { r: 190, g: 33, b: 55, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("GREEN", color_to_py(Color { r: 0, g: 228, b: 48, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("LIME", color_to_py(Color { r: 0, g: 158, b: 47, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("DARKGREEN", color_to_py(Color { r: 0, g: 117, b: 44, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("SKYBLUE", color_to_py(Color { r: 102, g: 191, b: 255, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("BLUE", color_to_py(Color { r: 0, g: 121, b: 241, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("DARKBLUE", color_to_py(Color { r: 0, g: 82, b: 172, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("PURPLE", color_to_py(Color { r: 200, g: 122, b: 255, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("VIOLET", color_to_py(Color { r: 135, g: 60, b: 190, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("DARKPURPLE", color_to_py(Color { r: 112, g: 31, b: 126, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("BEIGE", color_to_py(Color { r: 211, g: 176, b: 131, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("BROWN", color_to_py(Color { r: 127, g: 106, b: 79, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("DARKBROWN", color_to_py(Color { r: 76, g: 63, b: 47, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("WHITE", color_to_py(Color { r: 255, g: 255, b: 255, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("BLACK", color_to_py(Color { r: 0, g: 0, b: 0, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("BLANK", color_to_py(Color { r: 0, g: 0, b: 0, a: 0 }, vm), vm).unwrap();
    scope.globals.set_item("MAGENTA", color_to_py(Color { r: 255, g: 0, b: 255, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("RAYWHITE", color_to_py(Color { r: 245, g: 245, b: 245, a: 255 }, vm), vm).unwrap();
    scope.globals.set_item("NULL0_VERSION", vm.ctx.new_str("0.0.20").into(), vm).unwrap();
    scope.globals.set_item("FILTER_NEARESTNEIGHBOR", vm.ctx.new_int(0).into(), vm).unwrap();
    scope.globals.set_item("FILTER_BILINEAR", vm.ctx.new_int(1).into(), vm).unwrap();
    scope.globals.set_item("FILTER_SMOOTH", vm.ctx.new_int(2).into(), vm).unwrap();
    scope.globals.set_item("SFX_COIN", vm.ctx.new_int(0).into(), vm).unwrap();
    scope.globals.set_item("SFX_LASER", vm.ctx.new_int(1).into(), vm).unwrap();
    scope.globals.set_item("SFX_EXPLOSION", vm.ctx.new_int(2).into(), vm).unwrap();
    scope.globals.set_item("SFX_POWERUP", vm.ctx.new_int(3).into(), vm).unwrap();
    scope.globals.set_item("SFX_HURT", vm.ctx.new_int(4).into(), vm).unwrap();
    scope.globals.set_item("SFX_JUMP", vm.ctx.new_int(5).into(), vm).unwrap();
    scope.globals.set_item("SFX_SELECT", vm.ctx.new_int(6).into(), vm).unwrap();
    scope.globals.set_item("SFX_SYNTH", vm.ctx.new_int(7).into(), vm).unwrap();
    scope.globals.set_item("KEY_INVALID", vm.ctx.new_int(0).into(), vm).unwrap();
    scope.globals.set_item("KEY_SPACE", vm.ctx.new_int(32).into(), vm).unwrap();
    scope.globals.set_item("KEY_APOSTROPHE", vm.ctx.new_int(39).into(), vm).unwrap();
    scope.globals.set_item("KEY_COMMA", vm.ctx.new_int(44).into(), vm).unwrap();
    scope.globals.set_item("KEY_MINUS", vm.ctx.new_int(45).into(), vm).unwrap();
    scope.globals.set_item("KEY_PERIOD", vm.ctx.new_int(46).into(), vm).unwrap();
    scope.globals.set_item("KEY_SLASH", vm.ctx.new_int(47).into(), vm).unwrap();
    scope.globals.set_item("KEY_0", vm.ctx.new_int(48).into(), vm).unwrap();
    scope.globals.set_item("KEY_1", vm.ctx.new_int(49).into(), vm).unwrap();
    scope.globals.set_item("KEY_2", vm.ctx.new_int(50).into(), vm).unwrap();
    scope.globals.set_item("KEY_3", vm.ctx.new_int(51).into(), vm).unwrap();
    scope.globals.set_item("KEY_4", vm.ctx.new_int(52).into(), vm).unwrap();
    scope.globals.set_item("KEY_5", vm.ctx.new_int(53).into(), vm).unwrap();
    scope.globals.set_item("KEY_6", vm.ctx.new_int(54).into(), vm).unwrap();
    scope.globals.set_item("KEY_7", vm.ctx.new_int(55).into(), vm).unwrap();
    scope.globals.set_item("KEY_8", vm.ctx.new_int(56).into(), vm).unwrap();
    scope.globals.set_item("KEY_9", vm.ctx.new_int(57).into(), vm).unwrap();
    scope.globals.set_item("KEY_SEMICOLON", vm.ctx.new_int(59).into(), vm).unwrap();
    scope.globals.set_item("KEY_EQUAL", vm.ctx.new_int(61).into(), vm).unwrap();
    scope.globals.set_item("KEY_A", vm.ctx.new_int(65).into(), vm).unwrap();
    scope.globals.set_item("KEY_B", vm.ctx.new_int(66).into(), vm).unwrap();
    scope.globals.set_item("KEY_C", vm.ctx.new_int(67).into(), vm).unwrap();
    scope.globals.set_item("KEY_D", vm.ctx.new_int(68).into(), vm).unwrap();
    scope.globals.set_item("KEY_E", vm.ctx.new_int(69).into(), vm).unwrap();
    scope.globals.set_item("KEY_F", vm.ctx.new_int(70).into(), vm).unwrap();
    scope.globals.set_item("KEY_G", vm.ctx.new_int(71).into(), vm).unwrap();
    scope.globals.set_item("KEY_H", vm.ctx.new_int(72).into(), vm).unwrap();
    scope.globals.set_item("KEY_I", vm.ctx.new_int(73).into(), vm).unwrap();
    scope.globals.set_item("KEY_J", vm.ctx.new_int(74).into(), vm).unwrap();
    scope.globals.set_item("KEY_K", vm.ctx.new_int(75).into(), vm).unwrap();
    scope.globals.set_item("KEY_L", vm.ctx.new_int(76).into(), vm).unwrap();
    scope.globals.set_item("KEY_M", vm.ctx.new_int(77).into(), vm).unwrap();
    scope.globals.set_item("KEY_N", vm.ctx.new_int(78).into(), vm).unwrap();
    scope.globals.set_item("KEY_O", vm.ctx.new_int(79).into(), vm).unwrap();
    scope.globals.set_item("KEY_P", vm.ctx.new_int(80).into(), vm).unwrap();
    scope.globals.set_item("KEY_Q", vm.ctx.new_int(81).into(), vm).unwrap();
    scope.globals.set_item("KEY_R", vm.ctx.new_int(82).into(), vm).unwrap();
    scope.globals.set_item("KEY_S", vm.ctx.new_int(83).into(), vm).unwrap();
    scope.globals.set_item("KEY_T", vm.ctx.new_int(84).into(), vm).unwrap();
    scope.globals.set_item("KEY_U", vm.ctx.new_int(85).into(), vm).unwrap();
    scope.globals.set_item("KEY_V", vm.ctx.new_int(86).into(), vm).unwrap();
    scope.globals.set_item("KEY_W", vm.ctx.new_int(87).into(), vm).unwrap();
    scope.globals.set_item("KEY_X", vm.ctx.new_int(88).into(), vm).unwrap();
    scope.globals.set_item("KEY_Y", vm.ctx.new_int(89).into(), vm).unwrap();
    scope.globals.set_item("KEY_Z", vm.ctx.new_int(90).into(), vm).unwrap();
    scope.globals.set_item("KEY_LEFT_BRACKET", vm.ctx.new_int(91).into(), vm).unwrap();
    scope.globals.set_item("KEY_BACKSLASH", vm.ctx.new_int(92).into(), vm).unwrap();
    scope.globals.set_item("KEY_RIGHT_BRACKET", vm.ctx.new_int(93).into(), vm).unwrap();
    scope.globals.set_item("KEY_GRAVE_ACCENT", vm.ctx.new_int(96).into(), vm).unwrap();
    scope.globals.set_item("KEY_WORLD_1", vm.ctx.new_int(161).into(), vm).unwrap();
    scope.globals.set_item("KEY_WORLD_2", vm.ctx.new_int(162).into(), vm).unwrap();
    scope.globals.set_item("KEY_ESCAPE", vm.ctx.new_int(256).into(), vm).unwrap();
    scope.globals.set_item("KEY_ENTER", vm.ctx.new_int(257).into(), vm).unwrap();
    scope.globals.set_item("KEY_TAB", vm.ctx.new_int(258).into(), vm).unwrap();
    scope.globals.set_item("KEY_BACKSPACE", vm.ctx.new_int(259).into(), vm).unwrap();
    scope.globals.set_item("KEY_INSERT", vm.ctx.new_int(260).into(), vm).unwrap();
    scope.globals.set_item("KEY_DELETE", vm.ctx.new_int(261).into(), vm).unwrap();
    scope.globals.set_item("KEY_RIGHT", vm.ctx.new_int(262).into(), vm).unwrap();
    scope.globals.set_item("KEY_LEFT", vm.ctx.new_int(263).into(), vm).unwrap();
    scope.globals.set_item("KEY_DOWN", vm.ctx.new_int(264).into(), vm).unwrap();
    scope.globals.set_item("KEY_UP", vm.ctx.new_int(265).into(), vm).unwrap();
    scope.globals.set_item("KEY_PAGE_UP", vm.ctx.new_int(266).into(), vm).unwrap();
    scope.globals.set_item("KEY_PAGE_DOWN", vm.ctx.new_int(267).into(), vm).unwrap();
    scope.globals.set_item("KEY_HOME", vm.ctx.new_int(268).into(), vm).unwrap();
    scope.globals.set_item("KEY_END", vm.ctx.new_int(269).into(), vm).unwrap();
    scope.globals.set_item("KEY_CAPS_LOCK", vm.ctx.new_int(280).into(), vm).unwrap();
    scope.globals.set_item("KEY_SCROLL_LOCK", vm.ctx.new_int(281).into(), vm).unwrap();
    scope.globals.set_item("KEY_NUM_LOCK", vm.ctx.new_int(282).into(), vm).unwrap();
    scope.globals.set_item("KEY_PRINT_SCREEN", vm.ctx.new_int(283).into(), vm).unwrap();
    scope.globals.set_item("KEY_PAUSE", vm.ctx.new_int(284).into(), vm).unwrap();
    scope.globals.set_item("KEY_F1", vm.ctx.new_int(290).into(), vm).unwrap();
    scope.globals.set_item("KEY_F2", vm.ctx.new_int(291).into(), vm).unwrap();
    scope.globals.set_item("KEY_F3", vm.ctx.new_int(292).into(), vm).unwrap();
    scope.globals.set_item("KEY_F4", vm.ctx.new_int(293).into(), vm).unwrap();
    scope.globals.set_item("KEY_F5", vm.ctx.new_int(294).into(), vm).unwrap();
    scope.globals.set_item("KEY_F6", vm.ctx.new_int(295).into(), vm).unwrap();
    scope.globals.set_item("KEY_F7", vm.ctx.new_int(296).into(), vm).unwrap();
    scope.globals.set_item("KEY_F8", vm.ctx.new_int(297).into(), vm).unwrap();
    scope.globals.set_item("KEY_F9", vm.ctx.new_int(298).into(), vm).unwrap();
    scope.globals.set_item("KEY_F10", vm.ctx.new_int(299).into(), vm).unwrap();
    scope.globals.set_item("KEY_F11", vm.ctx.new_int(300).into(), vm).unwrap();
    scope.globals.set_item("KEY_F12", vm.ctx.new_int(301).into(), vm).unwrap();
    scope.globals.set_item("KEY_F13", vm.ctx.new_int(302).into(), vm).unwrap();
    scope.globals.set_item("KEY_F14", vm.ctx.new_int(303).into(), vm).unwrap();
    scope.globals.set_item("KEY_F15", vm.ctx.new_int(304).into(), vm).unwrap();
    scope.globals.set_item("KEY_F16", vm.ctx.new_int(305).into(), vm).unwrap();
    scope.globals.set_item("KEY_F17", vm.ctx.new_int(306).into(), vm).unwrap();
    scope.globals.set_item("KEY_F18", vm.ctx.new_int(307).into(), vm).unwrap();
    scope.globals.set_item("KEY_F19", vm.ctx.new_int(308).into(), vm).unwrap();
    scope.globals.set_item("KEY_F20", vm.ctx.new_int(309).into(), vm).unwrap();
    scope.globals.set_item("KEY_F21", vm.ctx.new_int(310).into(), vm).unwrap();
    scope.globals.set_item("KEY_F22", vm.ctx.new_int(311).into(), vm).unwrap();
    scope.globals.set_item("KEY_F23", vm.ctx.new_int(312).into(), vm).unwrap();
    scope.globals.set_item("KEY_F24", vm.ctx.new_int(313).into(), vm).unwrap();
    scope.globals.set_item("KEY_F25", vm.ctx.new_int(314).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_0", vm.ctx.new_int(320).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_1", vm.ctx.new_int(321).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_2", vm.ctx.new_int(322).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_3", vm.ctx.new_int(323).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_4", vm.ctx.new_int(324).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_5", vm.ctx.new_int(325).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_6", vm.ctx.new_int(326).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_7", vm.ctx.new_int(327).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_8", vm.ctx.new_int(328).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_9", vm.ctx.new_int(329).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_DECIMAL", vm.ctx.new_int(330).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_DIVIDE", vm.ctx.new_int(331).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_MULTIPLY", vm.ctx.new_int(332).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_SUBTRACT", vm.ctx.new_int(333).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_ADD", vm.ctx.new_int(334).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_ENTER", vm.ctx.new_int(335).into(), vm).unwrap();
    scope.globals.set_item("KEY_KP_EQUAL", vm.ctx.new_int(336).into(), vm).unwrap();
    scope.globals.set_item("KEY_LEFT_SHIFT", vm.ctx.new_int(340).into(), vm).unwrap();
    scope.globals.set_item("KEY_LEFT_CONTROL", vm.ctx.new_int(341).into(), vm).unwrap();
    scope.globals.set_item("KEY_LEFT_ALT", vm.ctx.new_int(342).into(), vm).unwrap();
    scope.globals.set_item("KEY_LEFT_SUPER", vm.ctx.new_int(343).into(), vm).unwrap();
    scope.globals.set_item("KEY_RIGHT_SHIFT", vm.ctx.new_int(344).into(), vm).unwrap();
    scope.globals.set_item("KEY_RIGHT_CONTROL", vm.ctx.new_int(345).into(), vm).unwrap();
    scope.globals.set_item("KEY_RIGHT_ALT", vm.ctx.new_int(346).into(), vm).unwrap();
    scope.globals.set_item("KEY_RIGHT_SUPER", vm.ctx.new_int(347).into(), vm).unwrap();
    scope.globals.set_item("KEY_MENU", vm.ctx.new_int(348).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_UNKNOWN", vm.ctx.new_int(0).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_UP", vm.ctx.new_int(1).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_RIGHT", vm.ctx.new_int(2).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_DOWN", vm.ctx.new_int(3).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_LEFT", vm.ctx.new_int(4).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_Y", vm.ctx.new_int(5).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_B", vm.ctx.new_int(6).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_A", vm.ctx.new_int(7).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_X", vm.ctx.new_int(8).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_LEFT_SHOULDER", vm.ctx.new_int(9).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_LEFT_TRIGGER", vm.ctx.new_int(10).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_RIGHT_SHOULDER", vm.ctx.new_int(11).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_RIGHT_TRIGGER", vm.ctx.new_int(12).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_SELECT", vm.ctx.new_int(13).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_MENU", vm.ctx.new_int(14).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_START", vm.ctx.new_int(15).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_LEFT_THUMB", vm.ctx.new_int(16).into(), vm).unwrap();
    scope.globals.set_item("GAMEPAD_BUTTON_RIGHT_THUMB", vm.ctx.new_int(17).into(), vm).unwrap();
    scope.globals.set_item("MOUSE_BUTTON_UNKNOWN", vm.ctx.new_int(0).into(), vm).unwrap();
    scope.globals.set_item("MOUSE_BUTTON_LEFT", vm.ctx.new_int(1).into(), vm).unwrap();
    scope.globals.set_item("MOUSE_BUTTON_RIGHT", vm.ctx.new_int(2).into(), vm).unwrap();
    scope.globals.set_item("MOUSE_BUTTON_MIDDLE", vm.ctx.new_int(3).into(), vm).unwrap();
    scope.globals.set_item("LAYER_NONE", vm.ctx.new_int(0).into(), vm).unwrap();
    scope.globals.set_item("LAYER_TILE", vm.ctx.new_int(1).into(), vm).unwrap();
    scope.globals.set_item("LAYER_OBJECT", vm.ctx.new_int(2).into(), vm).unwrap();
    scope.globals.set_item("LAYER_IMAGE", vm.ctx.new_int(3).into(), vm).unwrap();
    scope.globals.set_item("LAYER_GROUP", vm.ctx.new_int(4).into(), vm).unwrap();
    scope.globals.set_item("PROP_NONE", vm.ctx.new_int(0).into(), vm).unwrap();
    scope.globals.set_item("PROP_INT", vm.ctx.new_int(1).into(), vm).unwrap();
    scope.globals.set_item("PROP_BOOL", vm.ctx.new_int(2).into(), vm).unwrap();
    scope.globals.set_item("PROP_FLOAT", vm.ctx.new_int(3).into(), vm).unwrap();
    scope.globals.set_item("PROP_STRING", vm.ctx.new_int(4).into(), vm).unwrap();
    scope.globals.set_item("PROP_COLOR", vm.ctx.new_int(5).into(), vm).unwrap();
}

fn register_all(scope: &Scope, vm: &VirtualMachine) {
    scope.globals.set_item("color_tint", vm.new_function("color_tint", nf_color_tint).into(), vm).unwrap();
    scope.globals.set_item("color_fade", vm.new_function("color_fade", nf_color_fade).into(), vm).unwrap();
    scope.globals.set_item("color_brightness", vm.new_function("color_brightness", nf_color_brightness).into(), vm).unwrap();
    scope.globals.set_item("color_invert", vm.new_function("color_invert", nf_color_invert).into(), vm).unwrap();
    scope.globals.set_item("color_alpha_blend", vm.new_function("color_alpha_blend", nf_color_alpha_blend).into(), vm).unwrap();
    scope.globals.set_item("color_contrast", vm.new_function("color_contrast", nf_color_contrast).into(), vm).unwrap();
    scope.globals.set_item("color_bilinear_interpolate", vm.new_function("color_bilinear_interpolate", nf_color_bilinear_interpolate).into(), vm).unwrap();
    scope.globals.set_item("new_image", vm.new_function("new_image", nf_new_image).into(), vm).unwrap();
    scope.globals.set_item("image_copy", vm.new_function("image_copy", nf_image_copy).into(), vm).unwrap();
    scope.globals.set_item("image_subimage", vm.new_function("image_subimage", nf_image_subimage).into(), vm).unwrap();
    scope.globals.set_item("clear", vm.new_function("clear", nf_clear).into(), vm).unwrap();
    scope.globals.set_item("draw_point", vm.new_function("draw_point", nf_draw_point).into(), vm).unwrap();
    scope.globals.set_item("draw_line", vm.new_function("draw_line", nf_draw_line).into(), vm).unwrap();
    scope.globals.set_item("draw_rectangle", vm.new_function("draw_rectangle", nf_draw_rectangle).into(), vm).unwrap();
    scope.globals.set_item("draw_triangle", vm.new_function("draw_triangle", nf_draw_triangle).into(), vm).unwrap();
    scope.globals.set_item("draw_ellipse", vm.new_function("draw_ellipse", nf_draw_ellipse).into(), vm).unwrap();
    scope.globals.set_item("draw_circle", vm.new_function("draw_circle", nf_draw_circle).into(), vm).unwrap();
    scope.globals.set_item("draw_polygon", vm.new_function("draw_polygon", nf_draw_polygon).into(), vm).unwrap();
    scope.globals.set_item("draw_arc", vm.new_function("draw_arc", nf_draw_arc).into(), vm).unwrap();
    scope.globals.set_item("draw_rectangle_rounded", vm.new_function("draw_rectangle_rounded", nf_draw_rectangle_rounded).into(), vm).unwrap();
    scope.globals.set_item("draw_image", vm.new_function("draw_image", nf_draw_image).into(), vm).unwrap();
    scope.globals.set_item("draw_image_tint", vm.new_function("draw_image_tint", nf_draw_image_tint).into(), vm).unwrap();
    scope.globals.set_item("draw_image_rotated", vm.new_function("draw_image_rotated", nf_draw_image_rotated).into(), vm).unwrap();
    scope.globals.set_item("draw_image_flipped", vm.new_function("draw_image_flipped", nf_draw_image_flipped).into(), vm).unwrap();
    scope.globals.set_item("draw_image_scaled", vm.new_function("draw_image_scaled", nf_draw_image_scaled).into(), vm).unwrap();
    scope.globals.set_item("draw_text", vm.new_function("draw_text", nf_draw_text).into(), vm).unwrap();
    scope.globals.set_item("save_image", vm.new_function("save_image", nf_save_image).into(), vm).unwrap();
    scope.globals.set_item("load_image", vm.new_function("load_image", nf_load_image).into(), vm).unwrap();
    scope.globals.set_item("image_resize", vm.new_function("image_resize", nf_image_resize).into(), vm).unwrap();
    scope.globals.set_item("image_scale", vm.new_function("image_scale", nf_image_scale).into(), vm).unwrap();
    scope.globals.set_item("image_color_replace", vm.new_function("image_color_replace", nf_image_color_replace).into(), vm).unwrap();
    scope.globals.set_item("image_color_tint", vm.new_function("image_color_tint", nf_image_color_tint).into(), vm).unwrap();
    scope.globals.set_item("image_color_fade", vm.new_function("image_color_fade", nf_image_color_fade).into(), vm).unwrap();
    scope.globals.set_item("font_copy", vm.new_function("font_copy", nf_font_copy).into(), vm).unwrap();
    scope.globals.set_item("font_scale", vm.new_function("font_scale", nf_font_scale).into(), vm).unwrap();
    scope.globals.set_item("load_font_bmf", vm.new_function("load_font_bmf", nf_load_font_bmf).into(), vm).unwrap();
    scope.globals.set_item("load_font_bmf_from_image", vm.new_function("load_font_bmf_from_image", nf_load_font_bmf_from_image).into(), vm).unwrap();
    scope.globals.set_item("measure_text", vm.new_function("measure_text", nf_measure_text).into(), vm).unwrap();
    scope.globals.set_item("measure_image", vm.new_function("measure_image", nf_measure_image).into(), vm).unwrap();
    scope.globals.set_item("load_font_tty", vm.new_function("load_font_tty", nf_load_font_tty).into(), vm).unwrap();
    scope.globals.set_item("load_font_tty_from_image", vm.new_function("load_font_tty_from_image", nf_load_font_tty_from_image).into(), vm).unwrap();
    scope.globals.set_item("load_font_ttf", vm.new_function("load_font_ttf", nf_load_font_ttf).into(), vm).unwrap();
    scope.globals.set_item("image_color_invert", vm.new_function("image_color_invert", nf_image_color_invert).into(), vm).unwrap();
    scope.globals.set_item("image_alpha_border", vm.new_function("image_alpha_border", nf_image_alpha_border).into(), vm).unwrap();
    scope.globals.set_item("image_crop", vm.new_function("image_crop", nf_image_crop).into(), vm).unwrap();
    scope.globals.set_item("image_alpha_crop", vm.new_function("image_alpha_crop", nf_image_alpha_crop).into(), vm).unwrap();
    scope.globals.set_item("image_color_brightness", vm.new_function("image_color_brightness", nf_image_color_brightness).into(), vm).unwrap();
    scope.globals.set_item("image_flip", vm.new_function("image_flip", nf_image_flip).into(), vm).unwrap();
    scope.globals.set_item("image_color_contrast", vm.new_function("image_color_contrast", nf_image_color_contrast).into(), vm).unwrap();
    scope.globals.set_item("image_alpha_mask", vm.new_function("image_alpha_mask", nf_image_alpha_mask).into(), vm).unwrap();
    scope.globals.set_item("image_rotate", vm.new_function("image_rotate", nf_image_rotate).into(), vm).unwrap();
    scope.globals.set_item("image_gradient", vm.new_function("image_gradient", nf_image_gradient).into(), vm).unwrap();
    scope.globals.set_item("unload_image", vm.new_function("unload_image", nf_unload_image).into(), vm).unwrap();
    scope.globals.set_item("unload_font", vm.new_function("unload_font", nf_unload_font).into(), vm).unwrap();
    scope.globals.set_item("clear_image", vm.new_function("clear_image", nf_clear_image).into(), vm).unwrap();
    scope.globals.set_item("draw_point_on_image", vm.new_function("draw_point_on_image", nf_draw_point_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_line_on_image", vm.new_function("draw_line_on_image", nf_draw_line_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_rectangle_on_image", vm.new_function("draw_rectangle_on_image", nf_draw_rectangle_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_triangle_on_image", vm.new_function("draw_triangle_on_image", nf_draw_triangle_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_ellipse_on_image", vm.new_function("draw_ellipse_on_image", nf_draw_ellipse_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_circle_on_image", vm.new_function("draw_circle_on_image", nf_draw_circle_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_polygon_on_image", vm.new_function("draw_polygon_on_image", nf_draw_polygon_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_rectangle_rounded_on_image", vm.new_function("draw_rectangle_rounded_on_image", nf_draw_rectangle_rounded_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_image_on_image", vm.new_function("draw_image_on_image", nf_draw_image_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_image_tint_on_image", vm.new_function("draw_image_tint_on_image", nf_draw_image_tint_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_image_rotated_on_image", vm.new_function("draw_image_rotated_on_image", nf_draw_image_rotated_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_image_flipped_on_image", vm.new_function("draw_image_flipped_on_image", nf_draw_image_flipped_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_image_scaled_on_image", vm.new_function("draw_image_scaled_on_image", nf_draw_image_scaled_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_text_on_image", vm.new_function("draw_text_on_image", nf_draw_text_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_rectangle_outline", vm.new_function("draw_rectangle_outline", nf_draw_rectangle_outline).into(), vm).unwrap();
    scope.globals.set_item("draw_triangle_outline", vm.new_function("draw_triangle_outline", nf_draw_triangle_outline).into(), vm).unwrap();
    scope.globals.set_item("draw_ellipse_outline", vm.new_function("draw_ellipse_outline", nf_draw_ellipse_outline).into(), vm).unwrap();
    scope.globals.set_item("draw_circle_outline", vm.new_function("draw_circle_outline", nf_draw_circle_outline).into(), vm).unwrap();
    scope.globals.set_item("draw_polygon_outline", vm.new_function("draw_polygon_outline", nf_draw_polygon_outline).into(), vm).unwrap();
    scope.globals.set_item("draw_arc_outline", vm.new_function("draw_arc_outline", nf_draw_arc_outline).into(), vm).unwrap();
    scope.globals.set_item("draw_rectangle_rounded_outline", vm.new_function("draw_rectangle_rounded_outline", nf_draw_rectangle_rounded_outline).into(), vm).unwrap();
    scope.globals.set_item("draw_rectangle_outline_on_image", vm.new_function("draw_rectangle_outline_on_image", nf_draw_rectangle_outline_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_triangle_outline_on_image", vm.new_function("draw_triangle_outline_on_image", nf_draw_triangle_outline_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_ellipse_outline_on_image", vm.new_function("draw_ellipse_outline_on_image", nf_draw_ellipse_outline_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_circle_outline_on_image", vm.new_function("draw_circle_outline_on_image", nf_draw_circle_outline_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_polygon_outline_on_image", vm.new_function("draw_polygon_outline_on_image", nf_draw_polygon_outline_on_image).into(), vm).unwrap();
    scope.globals.set_item("draw_rectangle_rounded_outline_on_image", vm.new_function("draw_rectangle_rounded_outline_on_image", nf_draw_rectangle_rounded_outline_on_image).into(), vm).unwrap();
    scope.globals.set_item("gui_begin_window", vm.new_function("gui_begin_window", nf_gui_begin_window).into(), vm).unwrap();
    scope.globals.set_item("gui_end_window", vm.new_function("gui_end_window", nf_gui_end_window).into(), vm).unwrap();
    scope.globals.set_item("gui_button", vm.new_function("gui_button", nf_gui_button).into(), vm).unwrap();
    scope.globals.set_item("gui_label", vm.new_function("gui_label", nf_gui_label).into(), vm).unwrap();
    scope.globals.set_item("gui_text", vm.new_function("gui_text", nf_gui_text).into(), vm).unwrap();
    scope.globals.set_item("gui_checkbox", vm.new_function("gui_checkbox", nf_gui_checkbox).into(), vm).unwrap();
    scope.globals.set_item("gui_slider", vm.new_function("gui_slider", nf_gui_slider).into(), vm).unwrap();
    scope.globals.set_item("gui_layout_row", vm.new_function("gui_layout_row", nf_gui_layout_row).into(), vm).unwrap();
    scope.globals.set_item("gui_end", vm.new_function("gui_end", nf_gui_end).into(), vm).unwrap();
    scope.globals.set_item("gui_draw", vm.new_function("gui_draw", nf_gui_draw).into(), vm).unwrap();
    scope.globals.set_item("key_pressed", vm.new_function("key_pressed", nf_key_pressed).into(), vm).unwrap();
    scope.globals.set_item("key_down", vm.new_function("key_down", nf_key_down).into(), vm).unwrap();
    scope.globals.set_item("key_released", vm.new_function("key_released", nf_key_released).into(), vm).unwrap();
    scope.globals.set_item("key_up", vm.new_function("key_up", nf_key_up).into(), vm).unwrap();
    scope.globals.set_item("gamepad_button_pressed", vm.new_function("gamepad_button_pressed", nf_gamepad_button_pressed).into(), vm).unwrap();
    scope.globals.set_item("gamepad_button_down", vm.new_function("gamepad_button_down", nf_gamepad_button_down).into(), vm).unwrap();
    scope.globals.set_item("gamepad_button_released", vm.new_function("gamepad_button_released", nf_gamepad_button_released).into(), vm).unwrap();
    scope.globals.set_item("mouse_position", vm.new_function("mouse_position", nf_mouse_position).into(), vm).unwrap();
    scope.globals.set_item("mouse_button_pressed", vm.new_function("mouse_button_pressed", nf_mouse_button_pressed).into(), vm).unwrap();
    scope.globals.set_item("mouse_button_down", vm.new_function("mouse_button_down", nf_mouse_button_down).into(), vm).unwrap();
    scope.globals.set_item("mouse_button_released", vm.new_function("mouse_button_released", nf_mouse_button_released).into(), vm).unwrap();
    scope.globals.set_item("mouse_button_up", vm.new_function("mouse_button_up", nf_mouse_button_up).into(), vm).unwrap();
    scope.globals.set_item("load_sound", vm.new_function("load_sound", nf_load_sound).into(), vm).unwrap();
    scope.globals.set_item("play_sound", vm.new_function("play_sound", nf_play_sound).into(), vm).unwrap();
    scope.globals.set_item("stop_sound", vm.new_function("stop_sound", nf_stop_sound).into(), vm).unwrap();
    scope.globals.set_item("unload_sound", vm.new_function("unload_sound", nf_unload_sound).into(), vm).unwrap();
    scope.globals.set_item("tts_sound", vm.new_function("tts_sound", nf_tts_sound).into(), vm).unwrap();
    scope.globals.set_item("sfx_sound", vm.new_function("sfx_sound", nf_sfx_sound).into(), vm).unwrap();
    scope.globals.set_item("sfx_generate", vm.new_function("sfx_generate", nf_sfx_generate).into(), vm).unwrap();
    scope.globals.set_item("load_tilemap", vm.new_function("load_tilemap", nf_load_tilemap).into(), vm).unwrap();
    scope.globals.set_item("unload_tilemap", vm.new_function("unload_tilemap", nf_unload_tilemap).into(), vm).unwrap();
    scope.globals.set_item("tile_update", vm.new_function("tile_update", nf_tile_update).into(), vm).unwrap();
    scope.globals.set_item("tile_map_size", vm.new_function("tile_map_size", nf_tile_map_size).into(), vm).unwrap();
    scope.globals.set_item("tile_tile_size", vm.new_function("tile_tile_size", nf_tile_tile_size).into(), vm).unwrap();
    scope.globals.set_item("tile_map_prop", vm.new_function("tile_map_prop", nf_tile_map_prop).into(), vm).unwrap();
    scope.globals.set_item("tile_map_prop_count", vm.new_function("tile_map_prop_count", nf_tile_map_prop_count).into(), vm).unwrap();
    scope.globals.set_item("tile_map_prop_at", vm.new_function("tile_map_prop_at", nf_tile_map_prop_at).into(), vm).unwrap();
    scope.globals.set_item("tile_draw", vm.new_function("tile_draw", nf_tile_draw).into(), vm).unwrap();
    scope.globals.set_item("tile_draw_tint", vm.new_function("tile_draw_tint", nf_tile_draw_tint).into(), vm).unwrap();
    scope.globals.set_item("tile_draw_on_image", vm.new_function("tile_draw_on_image", nf_tile_draw_on_image).into(), vm).unwrap();
    scope.globals.set_item("tilemap_image", vm.new_function("tilemap_image", nf_tilemap_image).into(), vm).unwrap();
    scope.globals.set_item("tile_layer_count", vm.new_function("tile_layer_count", nf_tile_layer_count).into(), vm).unwrap();
    scope.globals.set_item("tile_layer_index", vm.new_function("tile_layer_index", nf_tile_layer_index).into(), vm).unwrap();
    scope.globals.set_item("tile_layer_name", vm.new_function("tile_layer_name", nf_tile_layer_name).into(), vm).unwrap();
    scope.globals.set_item("tile_layer_type", vm.new_function("tile_layer_type", nf_tile_layer_type).into(), vm).unwrap();
    scope.globals.set_item("tile_layer_size", vm.new_function("tile_layer_size", nf_tile_layer_size).into(), vm).unwrap();
    scope.globals.set_item("tile_layer_visible", vm.new_function("tile_layer_visible", nf_tile_layer_visible).into(), vm).unwrap();
    scope.globals.set_item("tile_layer_prop", vm.new_function("tile_layer_prop", nf_tile_layer_prop).into(), vm).unwrap();
    scope.globals.set_item("tile_layer_prop_count", vm.new_function("tile_layer_prop_count", nf_tile_layer_prop_count).into(), vm).unwrap();
    scope.globals.set_item("tile_layer_prop_at", vm.new_function("tile_layer_prop_at", nf_tile_layer_prop_at).into(), vm).unwrap();
    scope.globals.set_item("tile_draw_layer", vm.new_function("tile_draw_layer", nf_tile_draw_layer).into(), vm).unwrap();
    scope.globals.set_item("tile_draw_layer_tint", vm.new_function("tile_draw_layer_tint", nf_tile_draw_layer_tint).into(), vm).unwrap();
    scope.globals.set_item("tile_draw_layer_on_image", vm.new_function("tile_draw_layer_on_image", nf_tile_draw_layer_on_image).into(), vm).unwrap();
    scope.globals.set_item("tile_layer_image", vm.new_function("tile_layer_image", nf_tile_layer_image).into(), vm).unwrap();
    scope.globals.set_item("tile_get_tile", vm.new_function("tile_get_tile", nf_tile_get_tile).into(), vm).unwrap();
    scope.globals.set_item("tile_set_tile", vm.new_function("tile_set_tile", nf_tile_set_tile).into(), vm).unwrap();
    scope.globals.set_item("tile_draw_tile", vm.new_function("tile_draw_tile", nf_tile_draw_tile).into(), vm).unwrap();
    scope.globals.set_item("tile_image", vm.new_function("tile_image", nf_tile_image).into(), vm).unwrap();
    scope.globals.set_item("tile_gid_prop", vm.new_function("tile_gid_prop", nf_tile_gid_prop).into(), vm).unwrap();
    scope.globals.set_item("tile_gid_prop_count", vm.new_function("tile_gid_prop_count", nf_tile_gid_prop_count).into(), vm).unwrap();
    scope.globals.set_item("tile_gid_prop_at", vm.new_function("tile_gid_prop_at", nf_tile_gid_prop_at).into(), vm).unwrap();
    scope.globals.set_item("tile_object_count", vm.new_function("tile_object_count", nf_tile_object_count).into(), vm).unwrap();
    scope.globals.set_item("tile_object", vm.new_function("tile_object", nf_tile_object).into(), vm).unwrap();
    scope.globals.set_item("tile_object_index", vm.new_function("tile_object_index", nf_tile_object_index).into(), vm).unwrap();
    scope.globals.set_item("tile_object_prop", vm.new_function("tile_object_prop", nf_tile_object_prop).into(), vm).unwrap();
    scope.globals.set_item("tile_object_prop_count", vm.new_function("tile_object_prop_count", nf_tile_object_prop_count).into(), vm).unwrap();
    scope.globals.set_item("tile_object_prop_at", vm.new_function("tile_object_prop_at", nf_tile_object_prop_at).into(), vm).unwrap();
    scope.globals.set_item("current_time", vm.new_function("current_time", nf_current_time).into(), vm).unwrap();
    scope.globals.set_item("delta_time", vm.new_function("delta_time", nf_delta_time).into(), vm).unwrap();
    scope.globals.set_item("random_int", vm.new_function("random_int", nf_random_int).into(), vm).unwrap();
    scope.globals.set_item("random_seed_get", vm.new_function("random_seed_get", nf_random_seed_get).into(), vm).unwrap();
    scope.globals.set_item("random_seed_set", vm.new_function("random_seed_set", nf_random_seed_set).into(), vm).unwrap();
    register_constants(scope, vm);
}

thread_local! {
    static INTERPRETER: OnceCell<Interpreter> = OnceCell::new();
    static SCOPE: OnceCell<Scope> = OnceCell::new();
}

fn call_named(vm: &VirtualMachine, scope: &Scope, name: &str, args: Vec<PyObjectRef>) {
    if let Ok(f) = scope.globals.get_item(name, vm) {
        if f.is_callable() {
            if let Err(e) = f.call(vm::function::PosArgs::new(args), vm) {
                vm.print_exception(e);
            }
        }
    }
}

fn main() {
    let interpreter = Interpreter::without_stdlib(Default::default());
    INTERPRETER.with(|c| c.set(interpreter).ok().unwrap());
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            let scope = vm.new_scope_with_builtins();
            register_all(&scope, vm);

            let src = std::fs::read_to_string("main.py").unwrap_or_default();
            match vm.compile(&src, vm::compiler::Mode::Exec, "<cart>") {
                Ok(code) => {
                    if let Err(e) = vm.run_code_obj(code, scope.clone()) {
                        vm.print_exception(e);
                    }
                }
                Err(e) => {
                    let exc = e.into_pyexception(vm, Some(&src));
                    vm.print_exception(exc);
                }
            }

            SCOPE.with(|s| s.set(scope).ok().unwrap());
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "load", vec![]));
        });
    });
}

#[no_mangle]
pub extern "C" fn update() {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "update", vec![]));
        });
    });
}

#[no_mangle]
pub extern "C" fn unload() {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "unload", vec![]));
        });
    });
}

#[no_mangle]
pub extern "C" fn buttonDown(button: i32, player: u32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "buttonDown", vec![vm.ctx.new_int(button).into(), vm.ctx.new_int(player).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn buttonUp(button: i32, player: u32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "buttonUp", vec![vm.ctx.new_int(button).into(), vm.ctx.new_int(player).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn keyDown(key: i32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "keyDown", vec![vm.ctx.new_int(key).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn keyUp(key: i32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "keyUp", vec![vm.ctx.new_int(key).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn mouseDown(button: u32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "mouseDown", vec![vm.ctx.new_int(button).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn mouseUp(button: u32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "mouseUp", vec![vm.ctx.new_int(button).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn mouseMoved(x: f32, y: f32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "mouseMoved", vec![vm.ctx.new_float(x as f64).into(), vm.ctx.new_float(y as f64).into()]));
        });
    });
}
