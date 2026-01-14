// This file is auto-generated from raylib_api.json
// Do not edit manually - run: npm run codegen:cartjs
//
// NOTE: This file is meant to be included in main.c, not compiled separately.
// main.c should already have included raycart.h and quickjs.h before including this file.

// Type converters - primitives
static JSValue bool_to_js(bool value) {
  return JS_NewBool(ctx, value);
}

static JSValue i32_to_js(int32_t value) {
  return JS_NewInt32(ctx, value);
}

static JSValue u32_to_js(uint32_t value) {
  return JS_NewUint32(ctx, value);
}

static JSValue f32_to_js(float value) {
  return JS_NewFloat64(ctx, (double)value);
}

static JSValue u64_to_js(uint64_t value) {
  if (value <= 0x1FFFFFFFFFFFFF) {
    return JS_NewFloat64(ctx, (double)value);
  }
  return JS_NewBigInt64(ctx, (int64_t)value);
}

static JSValue string_to_js(const char* value) {
  return JS_NewString(ctx, value);
}

static bool bool_from_js(JSValue val) {
  return JS_ToBool(ctx, val);
}

static int32_t i32_from_js(JSValue val) {
  int32_t result = 0;
  JS_ToInt32(ctx, &result, val);
  return result;
}

static uint32_t u32_from_js(JSValue val) {
  uint32_t result = 0;
  JS_ToUint32(ctx, &result, val);
  return result;
}

static float f32_from_js(JSValue val) {
  double result = 0.0;
  JS_ToFloat64(ctx, &result, val);
  return (float)result;
}

static uint64_t u64_from_js(JSValue val) {
  uint64_t result = 0;

  if (JS_IsNumber(val)) {
    double d;
    if (JS_ToFloat64(ctx, &d, val) == 0) {
      result = (uint64_t)d;
    }
  } else if (JS_IsBigInt(ctx, val)) {
    int64_t signed_result = 0;
    if (JS_ToBigInt64(ctx, &signed_result, val) == 0) {
      result = (uint64_t)signed_result;
    }
  }

  return result;
}

static const char* string_from_js(JSValue val) {
  return JS_ToCString(ctx, val);
}

// Type converters - structs (forward declarations)
static JSValue image_to_js(Image value);
static Image image_from_js(JSValue obj);
static JSValue vector2_to_js(Vector2 value);
static Vector2 vector2_from_js(JSValue obj);
static JSValue color_to_js(Color value);
static Color color_from_js(JSValue obj);
static JSValue camera2d_to_js(Camera2D value);
static Camera2D camera2d_from_js(JSValue obj);
static JSValue camera3d_to_js(Camera3D value);
static Camera3D camera3d_from_js(JSValue obj);
static JSValue rendertexture_to_js(RenderTexture value);
static RenderTexture rendertexture_from_js(JSValue obj);
static JSValue shader_to_js(Shader value);
static Shader shader_from_js(JSValue obj);
static JSValue vrstereoconfig_to_js(VrStereoConfig value);
static VrStereoConfig vrstereoconfig_from_js(JSValue obj);
static JSValue vrdeviceinfo_to_js(VrDeviceInfo value);
static VrDeviceInfo vrdeviceinfo_from_js(JSValue obj);
static JSValue matrix_to_js(Matrix value);
static Matrix matrix_from_js(JSValue obj);
static JSValue texture_to_js(Texture value);
static Texture texture_from_js(JSValue obj);
static JSValue ray_to_js(Ray value);
static Ray ray_from_js(JSValue obj);
static JSValue vector3_to_js(Vector3 value);
static Vector3 vector3_from_js(JSValue obj);
static JSValue filepathlist_to_js(FilePathList value);
static FilePathList filepathlist_from_js(JSValue obj);
static JSValue automationeventlist_to_js(AutomationEventList value);
static AutomationEventList automationeventlist_from_js(JSValue obj);
static JSValue automationevent_to_js(AutomationEvent value);
static AutomationEvent automationevent_from_js(JSValue obj);
static JSValue rectangle_to_js(Rectangle value);
static Rectangle rectangle_from_js(JSValue obj);
static JSValue font_to_js(Font value);
static Font font_from_js(JSValue obj);
static JSValue npatchinfo_to_js(NPatchInfo value);
static NPatchInfo npatchinfo_from_js(JSValue obj);
static JSValue vector4_to_js(Vector4 value);
static Vector4 vector4_from_js(JSValue obj);
static JSValue glyphinfo_to_js(GlyphInfo value);
static GlyphInfo glyphinfo_from_js(JSValue obj);
static JSValue model_to_js(Model value);
static Model model_from_js(JSValue obj);
static JSValue mesh_to_js(Mesh value);
static Mesh mesh_from_js(JSValue obj);
static JSValue boundingbox_to_js(BoundingBox value);
static BoundingBox boundingbox_from_js(JSValue obj);
static JSValue material_to_js(Material value);
static Material material_from_js(JSValue obj);
static JSValue raycollision_to_js(RayCollision value);
static RayCollision raycollision_from_js(JSValue obj);
static JSValue wave_to_js(Wave value);
static Wave wave_from_js(JSValue obj);
static JSValue sound_to_js(Sound value);
static Sound sound_from_js(JSValue obj);
static JSValue music_to_js(Music value);
static Music music_from_js(JSValue obj);
static JSValue audiostream_to_js(AudioStream value);
static AudioStream audiostream_from_js(JSValue obj);

// Type converters - structs (implementations)
static JSValue image_to_js(Image value) {
  JSValue obj = JS_NewObject(ctx);
  // TODO: handle pointer field data
  JS_SetPropertyStr(ctx, obj, "width", i32_to_js(value.width));
  JS_SetPropertyStr(ctx, obj, "height", i32_to_js(value.height));
  JS_SetPropertyStr(ctx, obj, "mipmaps", i32_to_js(value.mipmaps));
  JS_SetPropertyStr(ctx, obj, "format", i32_to_js(value.format));
  return obj;
}



static Image image_from_js(JSValue obj) {
  Image result = {0};
  // TODO: handle pointer field data
  JSValue width_val = JS_GetPropertyStr(ctx, obj, "width");
  if (!JS_IsUndefined(width_val)) {
    result.width = i32_from_js(width_val);
  }
  JS_FreeValue(ctx, width_val);
  JSValue height_val = JS_GetPropertyStr(ctx, obj, "height");
  if (!JS_IsUndefined(height_val)) {
    result.height = i32_from_js(height_val);
  }
  JS_FreeValue(ctx, height_val);
  JSValue mipmaps_val = JS_GetPropertyStr(ctx, obj, "mipmaps");
  if (!JS_IsUndefined(mipmaps_val)) {
    result.mipmaps = i32_from_js(mipmaps_val);
  }
  JS_FreeValue(ctx, mipmaps_val);
  JSValue format_val = JS_GetPropertyStr(ctx, obj, "format");
  if (!JS_IsUndefined(format_val)) {
    result.format = i32_from_js(format_val);
  }
  JS_FreeValue(ctx, format_val);
  return result;
}

static JSValue vector2_to_js(Vector2 value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "x", f32_to_js(value.x));
  JS_SetPropertyStr(ctx, obj, "y", f32_to_js(value.y));
  return obj;
}



static Vector2 vector2_from_js(JSValue obj) {
  Vector2 result = {0};
  JSValue x_val = JS_GetPropertyStr(ctx, obj, "x");
  if (!JS_IsUndefined(x_val)) {
    result.x = f32_from_js(x_val);
  }
  JS_FreeValue(ctx, x_val);
  JSValue y_val = JS_GetPropertyStr(ctx, obj, "y");
  if (!JS_IsUndefined(y_val)) {
    result.y = f32_from_js(y_val);
  }
  JS_FreeValue(ctx, y_val);
  return result;
}

static JSValue color_to_js(Color value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "r", u32_to_js(value.r));
  JS_SetPropertyStr(ctx, obj, "g", u32_to_js(value.g));
  JS_SetPropertyStr(ctx, obj, "b", u32_to_js(value.b));
  JS_SetPropertyStr(ctx, obj, "a", u32_to_js(value.a));
  return obj;
}



static Color color_from_js(JSValue obj) {
  Color result = {0};
  JSValue r_val = JS_GetPropertyStr(ctx, obj, "r");
  if (!JS_IsUndefined(r_val)) {
    result.r = u32_from_js(r_val);
  }
  JS_FreeValue(ctx, r_val);
  JSValue g_val = JS_GetPropertyStr(ctx, obj, "g");
  if (!JS_IsUndefined(g_val)) {
    result.g = u32_from_js(g_val);
  }
  JS_FreeValue(ctx, g_val);
  JSValue b_val = JS_GetPropertyStr(ctx, obj, "b");
  if (!JS_IsUndefined(b_val)) {
    result.b = u32_from_js(b_val);
  }
  JS_FreeValue(ctx, b_val);
  JSValue a_val = JS_GetPropertyStr(ctx, obj, "a");
  if (!JS_IsUndefined(a_val)) {
    result.a = u32_from_js(a_val);
  }
  JS_FreeValue(ctx, a_val);
  return result;
}

static JSValue camera2d_to_js(Camera2D value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "offset", vector2_to_js(value.offset));
  JS_SetPropertyStr(ctx, obj, "target", vector2_to_js(value.target));
  JS_SetPropertyStr(ctx, obj, "rotation", f32_to_js(value.rotation));
  JS_SetPropertyStr(ctx, obj, "zoom", f32_to_js(value.zoom));
  return obj;
}



static Camera2D camera2d_from_js(JSValue obj) {
  Camera2D result = {0};
  JSValue offset_val = JS_GetPropertyStr(ctx, obj, "offset");
  if (!JS_IsUndefined(offset_val)) {
    result.offset = vector2_from_js(offset_val);
  }
  JS_FreeValue(ctx, offset_val);
  JSValue target_val = JS_GetPropertyStr(ctx, obj, "target");
  if (!JS_IsUndefined(target_val)) {
    result.target = vector2_from_js(target_val);
  }
  JS_FreeValue(ctx, target_val);
  JSValue rotation_val = JS_GetPropertyStr(ctx, obj, "rotation");
  if (!JS_IsUndefined(rotation_val)) {
    result.rotation = f32_from_js(rotation_val);
  }
  JS_FreeValue(ctx, rotation_val);
  JSValue zoom_val = JS_GetPropertyStr(ctx, obj, "zoom");
  if (!JS_IsUndefined(zoom_val)) {
    result.zoom = f32_from_js(zoom_val);
  }
  JS_FreeValue(ctx, zoom_val);
  return result;
}

static JSValue camera3d_to_js(Camera3D value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "position", vector3_to_js(value.position));
  JS_SetPropertyStr(ctx, obj, "target", vector3_to_js(value.target));
  JS_SetPropertyStr(ctx, obj, "up", vector3_to_js(value.up));
  JS_SetPropertyStr(ctx, obj, "fovy", f32_to_js(value.fovy));
  JS_SetPropertyStr(ctx, obj, "projection", i32_to_js(value.projection));
  return obj;
}



static Camera3D camera3d_from_js(JSValue obj) {
  Camera3D result = {0};
  JSValue position_val = JS_GetPropertyStr(ctx, obj, "position");
  if (!JS_IsUndefined(position_val)) {
    result.position = vector3_from_js(position_val);
  }
  JS_FreeValue(ctx, position_val);
  JSValue target_val = JS_GetPropertyStr(ctx, obj, "target");
  if (!JS_IsUndefined(target_val)) {
    result.target = vector3_from_js(target_val);
  }
  JS_FreeValue(ctx, target_val);
  JSValue up_val = JS_GetPropertyStr(ctx, obj, "up");
  if (!JS_IsUndefined(up_val)) {
    result.up = vector3_from_js(up_val);
  }
  JS_FreeValue(ctx, up_val);
  JSValue fovy_val = JS_GetPropertyStr(ctx, obj, "fovy");
  if (!JS_IsUndefined(fovy_val)) {
    result.fovy = f32_from_js(fovy_val);
  }
  JS_FreeValue(ctx, fovy_val);
  JSValue projection_val = JS_GetPropertyStr(ctx, obj, "projection");
  if (!JS_IsUndefined(projection_val)) {
    result.projection = i32_from_js(projection_val);
  }
  JS_FreeValue(ctx, projection_val);
  return result;
}

static JSValue rendertexture_to_js(RenderTexture value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "id", u32_to_js(value.id));
  JS_SetPropertyStr(ctx, obj, "texture", texture_to_js(value.texture));
  JS_SetPropertyStr(ctx, obj, "depth", texture_to_js(value.depth));
  return obj;
}



static RenderTexture rendertexture_from_js(JSValue obj) {
  RenderTexture result = {0};
  JSValue id_val = JS_GetPropertyStr(ctx, obj, "id");
  if (!JS_IsUndefined(id_val)) {
    result.id = u32_from_js(id_val);
  }
  JS_FreeValue(ctx, id_val);
  JSValue texture_val = JS_GetPropertyStr(ctx, obj, "texture");
  if (!JS_IsUndefined(texture_val)) {
    result.texture = texture_from_js(texture_val);
  }
  JS_FreeValue(ctx, texture_val);
  JSValue depth_val = JS_GetPropertyStr(ctx, obj, "depth");
  if (!JS_IsUndefined(depth_val)) {
    result.depth = texture_from_js(depth_val);
  }
  JS_FreeValue(ctx, depth_val);
  return result;
}

static JSValue shader_to_js(Shader value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "id", u32_to_js(value.id));
  // TODO: handle pointer field locs
  return obj;
}



static Shader shader_from_js(JSValue obj) {
  Shader result = {0};
  JSValue id_val = JS_GetPropertyStr(ctx, obj, "id");
  if (!JS_IsUndefined(id_val)) {
    result.id = u32_from_js(id_val);
  }
  JS_FreeValue(ctx, id_val);
  // TODO: handle pointer field locs
  return result;
}

static JSValue vrstereoconfig_to_js(VrStereoConfig value) {
  JSValue obj = JS_NewObject(ctx);
  return obj;
}



static VrStereoConfig vrstereoconfig_from_js(JSValue obj) {
  VrStereoConfig result = {0};
  return result;
}

static JSValue vrdeviceinfo_to_js(VrDeviceInfo value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "hResolution", i32_to_js(value.hResolution));
  JS_SetPropertyStr(ctx, obj, "vResolution", i32_to_js(value.vResolution));
  JS_SetPropertyStr(ctx, obj, "hScreenSize", f32_to_js(value.hScreenSize));
  JS_SetPropertyStr(ctx, obj, "vScreenSize", f32_to_js(value.vScreenSize));
  JS_SetPropertyStr(ctx, obj, "eyeToScreenDistance", f32_to_js(value.eyeToScreenDistance));
  JS_SetPropertyStr(ctx, obj, "lensSeparationDistance", f32_to_js(value.lensSeparationDistance));
  JS_SetPropertyStr(ctx, obj, "interpupillaryDistance", f32_to_js(value.interpupillaryDistance));
  return obj;
}



static VrDeviceInfo vrdeviceinfo_from_js(JSValue obj) {
  VrDeviceInfo result = {0};
  JSValue hResolution_val = JS_GetPropertyStr(ctx, obj, "hResolution");
  if (!JS_IsUndefined(hResolution_val)) {
    result.hResolution = i32_from_js(hResolution_val);
  }
  JS_FreeValue(ctx, hResolution_val);
  JSValue vResolution_val = JS_GetPropertyStr(ctx, obj, "vResolution");
  if (!JS_IsUndefined(vResolution_val)) {
    result.vResolution = i32_from_js(vResolution_val);
  }
  JS_FreeValue(ctx, vResolution_val);
  JSValue hScreenSize_val = JS_GetPropertyStr(ctx, obj, "hScreenSize");
  if (!JS_IsUndefined(hScreenSize_val)) {
    result.hScreenSize = f32_from_js(hScreenSize_val);
  }
  JS_FreeValue(ctx, hScreenSize_val);
  JSValue vScreenSize_val = JS_GetPropertyStr(ctx, obj, "vScreenSize");
  if (!JS_IsUndefined(vScreenSize_val)) {
    result.vScreenSize = f32_from_js(vScreenSize_val);
  }
  JS_FreeValue(ctx, vScreenSize_val);
  JSValue eyeToScreenDistance_val = JS_GetPropertyStr(ctx, obj, "eyeToScreenDistance");
  if (!JS_IsUndefined(eyeToScreenDistance_val)) {
    result.eyeToScreenDistance = f32_from_js(eyeToScreenDistance_val);
  }
  JS_FreeValue(ctx, eyeToScreenDistance_val);
  JSValue lensSeparationDistance_val = JS_GetPropertyStr(ctx, obj, "lensSeparationDistance");
  if (!JS_IsUndefined(lensSeparationDistance_val)) {
    result.lensSeparationDistance = f32_from_js(lensSeparationDistance_val);
  }
  JS_FreeValue(ctx, lensSeparationDistance_val);
  JSValue interpupillaryDistance_val = JS_GetPropertyStr(ctx, obj, "interpupillaryDistance");
  if (!JS_IsUndefined(interpupillaryDistance_val)) {
    result.interpupillaryDistance = f32_from_js(interpupillaryDistance_val);
  }
  JS_FreeValue(ctx, interpupillaryDistance_val);
  return result;
}

static JSValue matrix_to_js(Matrix value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "m0", f32_to_js(value.m0));
  JS_SetPropertyStr(ctx, obj, "m4", f32_to_js(value.m4));
  JS_SetPropertyStr(ctx, obj, "m8", f32_to_js(value.m8));
  JS_SetPropertyStr(ctx, obj, "m12", f32_to_js(value.m12));
  JS_SetPropertyStr(ctx, obj, "m1", f32_to_js(value.m1));
  JS_SetPropertyStr(ctx, obj, "m5", f32_to_js(value.m5));
  JS_SetPropertyStr(ctx, obj, "m9", f32_to_js(value.m9));
  JS_SetPropertyStr(ctx, obj, "m13", f32_to_js(value.m13));
  JS_SetPropertyStr(ctx, obj, "m2", f32_to_js(value.m2));
  JS_SetPropertyStr(ctx, obj, "m6", f32_to_js(value.m6));
  JS_SetPropertyStr(ctx, obj, "m10", f32_to_js(value.m10));
  JS_SetPropertyStr(ctx, obj, "m14", f32_to_js(value.m14));
  JS_SetPropertyStr(ctx, obj, "m3", f32_to_js(value.m3));
  JS_SetPropertyStr(ctx, obj, "m7", f32_to_js(value.m7));
  JS_SetPropertyStr(ctx, obj, "m11", f32_to_js(value.m11));
  JS_SetPropertyStr(ctx, obj, "m15", f32_to_js(value.m15));
  return obj;
}



static Matrix matrix_from_js(JSValue obj) {
  Matrix result = {0};
  JSValue m0_val = JS_GetPropertyStr(ctx, obj, "m0");
  if (!JS_IsUndefined(m0_val)) {
    result.m0 = f32_from_js(m0_val);
  }
  JS_FreeValue(ctx, m0_val);
  JSValue m4_val = JS_GetPropertyStr(ctx, obj, "m4");
  if (!JS_IsUndefined(m4_val)) {
    result.m4 = f32_from_js(m4_val);
  }
  JS_FreeValue(ctx, m4_val);
  JSValue m8_val = JS_GetPropertyStr(ctx, obj, "m8");
  if (!JS_IsUndefined(m8_val)) {
    result.m8 = f32_from_js(m8_val);
  }
  JS_FreeValue(ctx, m8_val);
  JSValue m12_val = JS_GetPropertyStr(ctx, obj, "m12");
  if (!JS_IsUndefined(m12_val)) {
    result.m12 = f32_from_js(m12_val);
  }
  JS_FreeValue(ctx, m12_val);
  JSValue m1_val = JS_GetPropertyStr(ctx, obj, "m1");
  if (!JS_IsUndefined(m1_val)) {
    result.m1 = f32_from_js(m1_val);
  }
  JS_FreeValue(ctx, m1_val);
  JSValue m5_val = JS_GetPropertyStr(ctx, obj, "m5");
  if (!JS_IsUndefined(m5_val)) {
    result.m5 = f32_from_js(m5_val);
  }
  JS_FreeValue(ctx, m5_val);
  JSValue m9_val = JS_GetPropertyStr(ctx, obj, "m9");
  if (!JS_IsUndefined(m9_val)) {
    result.m9 = f32_from_js(m9_val);
  }
  JS_FreeValue(ctx, m9_val);
  JSValue m13_val = JS_GetPropertyStr(ctx, obj, "m13");
  if (!JS_IsUndefined(m13_val)) {
    result.m13 = f32_from_js(m13_val);
  }
  JS_FreeValue(ctx, m13_val);
  JSValue m2_val = JS_GetPropertyStr(ctx, obj, "m2");
  if (!JS_IsUndefined(m2_val)) {
    result.m2 = f32_from_js(m2_val);
  }
  JS_FreeValue(ctx, m2_val);
  JSValue m6_val = JS_GetPropertyStr(ctx, obj, "m6");
  if (!JS_IsUndefined(m6_val)) {
    result.m6 = f32_from_js(m6_val);
  }
  JS_FreeValue(ctx, m6_val);
  JSValue m10_val = JS_GetPropertyStr(ctx, obj, "m10");
  if (!JS_IsUndefined(m10_val)) {
    result.m10 = f32_from_js(m10_val);
  }
  JS_FreeValue(ctx, m10_val);
  JSValue m14_val = JS_GetPropertyStr(ctx, obj, "m14");
  if (!JS_IsUndefined(m14_val)) {
    result.m14 = f32_from_js(m14_val);
  }
  JS_FreeValue(ctx, m14_val);
  JSValue m3_val = JS_GetPropertyStr(ctx, obj, "m3");
  if (!JS_IsUndefined(m3_val)) {
    result.m3 = f32_from_js(m3_val);
  }
  JS_FreeValue(ctx, m3_val);
  JSValue m7_val = JS_GetPropertyStr(ctx, obj, "m7");
  if (!JS_IsUndefined(m7_val)) {
    result.m7 = f32_from_js(m7_val);
  }
  JS_FreeValue(ctx, m7_val);
  JSValue m11_val = JS_GetPropertyStr(ctx, obj, "m11");
  if (!JS_IsUndefined(m11_val)) {
    result.m11 = f32_from_js(m11_val);
  }
  JS_FreeValue(ctx, m11_val);
  JSValue m15_val = JS_GetPropertyStr(ctx, obj, "m15");
  if (!JS_IsUndefined(m15_val)) {
    result.m15 = f32_from_js(m15_val);
  }
  JS_FreeValue(ctx, m15_val);
  return result;
}

static JSValue texture_to_js(Texture value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "id", u32_to_js(value.id));
  JS_SetPropertyStr(ctx, obj, "width", i32_to_js(value.width));
  JS_SetPropertyStr(ctx, obj, "height", i32_to_js(value.height));
  JS_SetPropertyStr(ctx, obj, "mipmaps", i32_to_js(value.mipmaps));
  JS_SetPropertyStr(ctx, obj, "format", i32_to_js(value.format));
  return obj;
}



static Texture texture_from_js(JSValue obj) {
  Texture result = {0};
  JSValue id_val = JS_GetPropertyStr(ctx, obj, "id");
  if (!JS_IsUndefined(id_val)) {
    result.id = u32_from_js(id_val);
  }
  JS_FreeValue(ctx, id_val);
  JSValue width_val = JS_GetPropertyStr(ctx, obj, "width");
  if (!JS_IsUndefined(width_val)) {
    result.width = i32_from_js(width_val);
  }
  JS_FreeValue(ctx, width_val);
  JSValue height_val = JS_GetPropertyStr(ctx, obj, "height");
  if (!JS_IsUndefined(height_val)) {
    result.height = i32_from_js(height_val);
  }
  JS_FreeValue(ctx, height_val);
  JSValue mipmaps_val = JS_GetPropertyStr(ctx, obj, "mipmaps");
  if (!JS_IsUndefined(mipmaps_val)) {
    result.mipmaps = i32_from_js(mipmaps_val);
  }
  JS_FreeValue(ctx, mipmaps_val);
  JSValue format_val = JS_GetPropertyStr(ctx, obj, "format");
  if (!JS_IsUndefined(format_val)) {
    result.format = i32_from_js(format_val);
  }
  JS_FreeValue(ctx, format_val);
  return result;
}

static JSValue ray_to_js(Ray value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "position", vector3_to_js(value.position));
  JS_SetPropertyStr(ctx, obj, "direction", vector3_to_js(value.direction));
  return obj;
}



static Ray ray_from_js(JSValue obj) {
  Ray result = {0};
  JSValue position_val = JS_GetPropertyStr(ctx, obj, "position");
  if (!JS_IsUndefined(position_val)) {
    result.position = vector3_from_js(position_val);
  }
  JS_FreeValue(ctx, position_val);
  JSValue direction_val = JS_GetPropertyStr(ctx, obj, "direction");
  if (!JS_IsUndefined(direction_val)) {
    result.direction = vector3_from_js(direction_val);
  }
  JS_FreeValue(ctx, direction_val);
  return result;
}

static JSValue vector3_to_js(Vector3 value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "x", f32_to_js(value.x));
  JS_SetPropertyStr(ctx, obj, "y", f32_to_js(value.y));
  JS_SetPropertyStr(ctx, obj, "z", f32_to_js(value.z));
  return obj;
}



static Vector3 vector3_from_js(JSValue obj) {
  Vector3 result = {0};
  JSValue x_val = JS_GetPropertyStr(ctx, obj, "x");
  if (!JS_IsUndefined(x_val)) {
    result.x = f32_from_js(x_val);
  }
  JS_FreeValue(ctx, x_val);
  JSValue y_val = JS_GetPropertyStr(ctx, obj, "y");
  if (!JS_IsUndefined(y_val)) {
    result.y = f32_from_js(y_val);
  }
  JS_FreeValue(ctx, y_val);
  JSValue z_val = JS_GetPropertyStr(ctx, obj, "z");
  if (!JS_IsUndefined(z_val)) {
    result.z = f32_from_js(z_val);
  }
  JS_FreeValue(ctx, z_val);
  return result;
}

static JSValue filepathlist_to_js(FilePathList value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "capacity", u32_to_js(value.capacity));
  JS_SetPropertyStr(ctx, obj, "count", u32_to_js(value.count));
  JS_SetPropertyStr(ctx, obj, "paths", string_to_js(value.paths));
  return obj;
}



static FilePathList filepathlist_from_js(JSValue obj) {
  FilePathList result = {0};
  JSValue capacity_val = JS_GetPropertyStr(ctx, obj, "capacity");
  if (!JS_IsUndefined(capacity_val)) {
    result.capacity = u32_from_js(capacity_val);
  }
  JS_FreeValue(ctx, capacity_val);
  JSValue count_val = JS_GetPropertyStr(ctx, obj, "count");
  if (!JS_IsUndefined(count_val)) {
    result.count = u32_from_js(count_val);
  }
  JS_FreeValue(ctx, count_val);
  JSValue paths_val = JS_GetPropertyStr(ctx, obj, "paths");
  if (!JS_IsUndefined(paths_val)) {
    result.paths = string_from_js(paths_val);
  }
  JS_FreeValue(ctx, paths_val);
  return result;
}

static JSValue automationeventlist_to_js(AutomationEventList value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "capacity", u32_to_js(value.capacity));
  JS_SetPropertyStr(ctx, obj, "count", u32_to_js(value.count));
  // TODO: handle pointer field events
  return obj;
}



static AutomationEventList automationeventlist_from_js(JSValue obj) {
  AutomationEventList result = {0};
  JSValue capacity_val = JS_GetPropertyStr(ctx, obj, "capacity");
  if (!JS_IsUndefined(capacity_val)) {
    result.capacity = u32_from_js(capacity_val);
  }
  JS_FreeValue(ctx, capacity_val);
  JSValue count_val = JS_GetPropertyStr(ctx, obj, "count");
  if (!JS_IsUndefined(count_val)) {
    result.count = u32_from_js(count_val);
  }
  JS_FreeValue(ctx, count_val);
  // TODO: handle pointer field events
  return result;
}

static JSValue automationevent_to_js(AutomationEvent value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "frame", u32_to_js(value.frame));
  JS_SetPropertyStr(ctx, obj, "type", u32_to_js(value.type));
  return obj;
}



static AutomationEvent automationevent_from_js(JSValue obj) {
  AutomationEvent result = {0};
  JSValue frame_val = JS_GetPropertyStr(ctx, obj, "frame");
  if (!JS_IsUndefined(frame_val)) {
    result.frame = u32_from_js(frame_val);
  }
  JS_FreeValue(ctx, frame_val);
  JSValue type_val = JS_GetPropertyStr(ctx, obj, "type");
  if (!JS_IsUndefined(type_val)) {
    result.type = u32_from_js(type_val);
  }
  JS_FreeValue(ctx, type_val);
  return result;
}

static JSValue rectangle_to_js(Rectangle value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "x", f32_to_js(value.x));
  JS_SetPropertyStr(ctx, obj, "y", f32_to_js(value.y));
  JS_SetPropertyStr(ctx, obj, "width", f32_to_js(value.width));
  JS_SetPropertyStr(ctx, obj, "height", f32_to_js(value.height));
  return obj;
}



static Rectangle rectangle_from_js(JSValue obj) {
  Rectangle result = {0};
  JSValue x_val = JS_GetPropertyStr(ctx, obj, "x");
  if (!JS_IsUndefined(x_val)) {
    result.x = f32_from_js(x_val);
  }
  JS_FreeValue(ctx, x_val);
  JSValue y_val = JS_GetPropertyStr(ctx, obj, "y");
  if (!JS_IsUndefined(y_val)) {
    result.y = f32_from_js(y_val);
  }
  JS_FreeValue(ctx, y_val);
  JSValue width_val = JS_GetPropertyStr(ctx, obj, "width");
  if (!JS_IsUndefined(width_val)) {
    result.width = f32_from_js(width_val);
  }
  JS_FreeValue(ctx, width_val);
  JSValue height_val = JS_GetPropertyStr(ctx, obj, "height");
  if (!JS_IsUndefined(height_val)) {
    result.height = f32_from_js(height_val);
  }
  JS_FreeValue(ctx, height_val);
  return result;
}

static JSValue font_to_js(Font value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "baseSize", i32_to_js(value.baseSize));
  JS_SetPropertyStr(ctx, obj, "glyphCount", i32_to_js(value.glyphCount));
  JS_SetPropertyStr(ctx, obj, "glyphPadding", i32_to_js(value.glyphPadding));
  JS_SetPropertyStr(ctx, obj, "texture", texture_to_js(value.texture));
  // TODO: handle pointer field recs
  // TODO: handle pointer field glyphs
  return obj;
}



static Font font_from_js(JSValue obj) {
  Font result = {0};
  JSValue baseSize_val = JS_GetPropertyStr(ctx, obj, "baseSize");
  if (!JS_IsUndefined(baseSize_val)) {
    result.baseSize = i32_from_js(baseSize_val);
  }
  JS_FreeValue(ctx, baseSize_val);
  JSValue glyphCount_val = JS_GetPropertyStr(ctx, obj, "glyphCount");
  if (!JS_IsUndefined(glyphCount_val)) {
    result.glyphCount = i32_from_js(glyphCount_val);
  }
  JS_FreeValue(ctx, glyphCount_val);
  JSValue glyphPadding_val = JS_GetPropertyStr(ctx, obj, "glyphPadding");
  if (!JS_IsUndefined(glyphPadding_val)) {
    result.glyphPadding = i32_from_js(glyphPadding_val);
  }
  JS_FreeValue(ctx, glyphPadding_val);
  JSValue texture_val = JS_GetPropertyStr(ctx, obj, "texture");
  if (!JS_IsUndefined(texture_val)) {
    result.texture = texture_from_js(texture_val);
  }
  JS_FreeValue(ctx, texture_val);
  // TODO: handle pointer field recs
  // TODO: handle pointer field glyphs
  return result;
}

static JSValue npatchinfo_to_js(NPatchInfo value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "source", rectangle_to_js(value.source));
  JS_SetPropertyStr(ctx, obj, "left", i32_to_js(value.left));
  JS_SetPropertyStr(ctx, obj, "top", i32_to_js(value.top));
  JS_SetPropertyStr(ctx, obj, "right", i32_to_js(value.right));
  JS_SetPropertyStr(ctx, obj, "bottom", i32_to_js(value.bottom));
  JS_SetPropertyStr(ctx, obj, "layout", i32_to_js(value.layout));
  return obj;
}



static NPatchInfo npatchinfo_from_js(JSValue obj) {
  NPatchInfo result = {0};
  JSValue source_val = JS_GetPropertyStr(ctx, obj, "source");
  if (!JS_IsUndefined(source_val)) {
    result.source = rectangle_from_js(source_val);
  }
  JS_FreeValue(ctx, source_val);
  JSValue left_val = JS_GetPropertyStr(ctx, obj, "left");
  if (!JS_IsUndefined(left_val)) {
    result.left = i32_from_js(left_val);
  }
  JS_FreeValue(ctx, left_val);
  JSValue top_val = JS_GetPropertyStr(ctx, obj, "top");
  if (!JS_IsUndefined(top_val)) {
    result.top = i32_from_js(top_val);
  }
  JS_FreeValue(ctx, top_val);
  JSValue right_val = JS_GetPropertyStr(ctx, obj, "right");
  if (!JS_IsUndefined(right_val)) {
    result.right = i32_from_js(right_val);
  }
  JS_FreeValue(ctx, right_val);
  JSValue bottom_val = JS_GetPropertyStr(ctx, obj, "bottom");
  if (!JS_IsUndefined(bottom_val)) {
    result.bottom = i32_from_js(bottom_val);
  }
  JS_FreeValue(ctx, bottom_val);
  JSValue layout_val = JS_GetPropertyStr(ctx, obj, "layout");
  if (!JS_IsUndefined(layout_val)) {
    result.layout = i32_from_js(layout_val);
  }
  JS_FreeValue(ctx, layout_val);
  return result;
}

static JSValue vector4_to_js(Vector4 value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "x", f32_to_js(value.x));
  JS_SetPropertyStr(ctx, obj, "y", f32_to_js(value.y));
  JS_SetPropertyStr(ctx, obj, "z", f32_to_js(value.z));
  JS_SetPropertyStr(ctx, obj, "w", f32_to_js(value.w));
  return obj;
}



static Vector4 vector4_from_js(JSValue obj) {
  Vector4 result = {0};
  JSValue x_val = JS_GetPropertyStr(ctx, obj, "x");
  if (!JS_IsUndefined(x_val)) {
    result.x = f32_from_js(x_val);
  }
  JS_FreeValue(ctx, x_val);
  JSValue y_val = JS_GetPropertyStr(ctx, obj, "y");
  if (!JS_IsUndefined(y_val)) {
    result.y = f32_from_js(y_val);
  }
  JS_FreeValue(ctx, y_val);
  JSValue z_val = JS_GetPropertyStr(ctx, obj, "z");
  if (!JS_IsUndefined(z_val)) {
    result.z = f32_from_js(z_val);
  }
  JS_FreeValue(ctx, z_val);
  JSValue w_val = JS_GetPropertyStr(ctx, obj, "w");
  if (!JS_IsUndefined(w_val)) {
    result.w = f32_from_js(w_val);
  }
  JS_FreeValue(ctx, w_val);
  return result;
}

static JSValue glyphinfo_to_js(GlyphInfo value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "value", i32_to_js(value.value));
  JS_SetPropertyStr(ctx, obj, "offsetX", i32_to_js(value.offsetX));
  JS_SetPropertyStr(ctx, obj, "offsetY", i32_to_js(value.offsetY));
  JS_SetPropertyStr(ctx, obj, "advanceX", i32_to_js(value.advanceX));
  JS_SetPropertyStr(ctx, obj, "image", image_to_js(value.image));
  return obj;
}



static GlyphInfo glyphinfo_from_js(JSValue obj) {
  GlyphInfo result = {0};
  JSValue value_val = JS_GetPropertyStr(ctx, obj, "value");
  if (!JS_IsUndefined(value_val)) {
    result.value = i32_from_js(value_val);
  }
  JS_FreeValue(ctx, value_val);
  JSValue offsetX_val = JS_GetPropertyStr(ctx, obj, "offsetX");
  if (!JS_IsUndefined(offsetX_val)) {
    result.offsetX = i32_from_js(offsetX_val);
  }
  JS_FreeValue(ctx, offsetX_val);
  JSValue offsetY_val = JS_GetPropertyStr(ctx, obj, "offsetY");
  if (!JS_IsUndefined(offsetY_val)) {
    result.offsetY = i32_from_js(offsetY_val);
  }
  JS_FreeValue(ctx, offsetY_val);
  JSValue advanceX_val = JS_GetPropertyStr(ctx, obj, "advanceX");
  if (!JS_IsUndefined(advanceX_val)) {
    result.advanceX = i32_from_js(advanceX_val);
  }
  JS_FreeValue(ctx, advanceX_val);
  JSValue image_val = JS_GetPropertyStr(ctx, obj, "image");
  if (!JS_IsUndefined(image_val)) {
    result.image = image_from_js(image_val);
  }
  JS_FreeValue(ctx, image_val);
  return result;
}

static JSValue model_to_js(Model value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "transform", matrix_to_js(value.transform));
  JS_SetPropertyStr(ctx, obj, "meshCount", i32_to_js(value.meshCount));
  JS_SetPropertyStr(ctx, obj, "materialCount", i32_to_js(value.materialCount));
  // TODO: handle pointer field meshes
  // TODO: handle pointer field materials
  // TODO: handle pointer field meshMaterial
  JS_SetPropertyStr(ctx, obj, "boneCount", i32_to_js(value.boneCount));
  // TODO: handle pointer field bones
  // TODO: handle pointer field bindPose
  return obj;
}



static Model model_from_js(JSValue obj) {
  Model result = {0};
  JSValue transform_val = JS_GetPropertyStr(ctx, obj, "transform");
  if (!JS_IsUndefined(transform_val)) {
    result.transform = matrix_from_js(transform_val);
  }
  JS_FreeValue(ctx, transform_val);
  JSValue meshCount_val = JS_GetPropertyStr(ctx, obj, "meshCount");
  if (!JS_IsUndefined(meshCount_val)) {
    result.meshCount = i32_from_js(meshCount_val);
  }
  JS_FreeValue(ctx, meshCount_val);
  JSValue materialCount_val = JS_GetPropertyStr(ctx, obj, "materialCount");
  if (!JS_IsUndefined(materialCount_val)) {
    result.materialCount = i32_from_js(materialCount_val);
  }
  JS_FreeValue(ctx, materialCount_val);
  // TODO: handle pointer field meshes
  // TODO: handle pointer field materials
  // TODO: handle pointer field meshMaterial
  JSValue boneCount_val = JS_GetPropertyStr(ctx, obj, "boneCount");
  if (!JS_IsUndefined(boneCount_val)) {
    result.boneCount = i32_from_js(boneCount_val);
  }
  JS_FreeValue(ctx, boneCount_val);
  // TODO: handle pointer field bones
  // TODO: handle pointer field bindPose
  return result;
}

static JSValue mesh_to_js(Mesh value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "vertexCount", i32_to_js(value.vertexCount));
  JS_SetPropertyStr(ctx, obj, "triangleCount", i32_to_js(value.triangleCount));
  // TODO: handle pointer field vertices
  // TODO: handle pointer field texcoords
  // TODO: handle pointer field texcoords2
  // TODO: handle pointer field normals
  // TODO: handle pointer field tangents
  JS_SetPropertyStr(ctx, obj, "colors", string_to_js(value.colors));
  // TODO: handle pointer field indices
  // TODO: handle pointer field animVertices
  // TODO: handle pointer field animNormals
  JS_SetPropertyStr(ctx, obj, "boneIds", string_to_js(value.boneIds));
  // TODO: handle pointer field boneWeights
  // TODO: handle pointer field boneMatrices
  JS_SetPropertyStr(ctx, obj, "boneCount", i32_to_js(value.boneCount));
  JS_SetPropertyStr(ctx, obj, "vaoId", u32_to_js(value.vaoId));
  // TODO: handle pointer field vboId
  return obj;
}



static Mesh mesh_from_js(JSValue obj) {
  Mesh result = {0};
  JSValue vertexCount_val = JS_GetPropertyStr(ctx, obj, "vertexCount");
  if (!JS_IsUndefined(vertexCount_val)) {
    result.vertexCount = i32_from_js(vertexCount_val);
  }
  JS_FreeValue(ctx, vertexCount_val);
  JSValue triangleCount_val = JS_GetPropertyStr(ctx, obj, "triangleCount");
  if (!JS_IsUndefined(triangleCount_val)) {
    result.triangleCount = i32_from_js(triangleCount_val);
  }
  JS_FreeValue(ctx, triangleCount_val);
  // TODO: handle pointer field vertices
  // TODO: handle pointer field texcoords
  // TODO: handle pointer field texcoords2
  // TODO: handle pointer field normals
  // TODO: handle pointer field tangents
  JSValue colors_val = JS_GetPropertyStr(ctx, obj, "colors");
  if (!JS_IsUndefined(colors_val)) {
    result.colors = string_from_js(colors_val);
  }
  JS_FreeValue(ctx, colors_val);
  // TODO: handle pointer field indices
  // TODO: handle pointer field animVertices
  // TODO: handle pointer field animNormals
  JSValue boneIds_val = JS_GetPropertyStr(ctx, obj, "boneIds");
  if (!JS_IsUndefined(boneIds_val)) {
    result.boneIds = string_from_js(boneIds_val);
  }
  JS_FreeValue(ctx, boneIds_val);
  // TODO: handle pointer field boneWeights
  // TODO: handle pointer field boneMatrices
  JSValue boneCount_val = JS_GetPropertyStr(ctx, obj, "boneCount");
  if (!JS_IsUndefined(boneCount_val)) {
    result.boneCount = i32_from_js(boneCount_val);
  }
  JS_FreeValue(ctx, boneCount_val);
  JSValue vaoId_val = JS_GetPropertyStr(ctx, obj, "vaoId");
  if (!JS_IsUndefined(vaoId_val)) {
    result.vaoId = u32_from_js(vaoId_val);
  }
  JS_FreeValue(ctx, vaoId_val);
  // TODO: handle pointer field vboId
  return result;
}

static JSValue boundingbox_to_js(BoundingBox value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "min", vector3_to_js(value.min));
  JS_SetPropertyStr(ctx, obj, "max", vector3_to_js(value.max));
  return obj;
}



static BoundingBox boundingbox_from_js(JSValue obj) {
  BoundingBox result = {0};
  JSValue min_val = JS_GetPropertyStr(ctx, obj, "min");
  if (!JS_IsUndefined(min_val)) {
    result.min = vector3_from_js(min_val);
  }
  JS_FreeValue(ctx, min_val);
  JSValue max_val = JS_GetPropertyStr(ctx, obj, "max");
  if (!JS_IsUndefined(max_val)) {
    result.max = vector3_from_js(max_val);
  }
  JS_FreeValue(ctx, max_val);
  return result;
}

static JSValue material_to_js(Material value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "shader", shader_to_js(value.shader));
  // TODO: handle pointer field maps
  return obj;
}



static Material material_from_js(JSValue obj) {
  Material result = {0};
  JSValue shader_val = JS_GetPropertyStr(ctx, obj, "shader");
  if (!JS_IsUndefined(shader_val)) {
    result.shader = shader_from_js(shader_val);
  }
  JS_FreeValue(ctx, shader_val);
  // TODO: handle pointer field maps
  return result;
}

static JSValue raycollision_to_js(RayCollision value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "hit", bool_to_js(value.hit));
  JS_SetPropertyStr(ctx, obj, "distance", f32_to_js(value.distance));
  JS_SetPropertyStr(ctx, obj, "point", vector3_to_js(value.point));
  JS_SetPropertyStr(ctx, obj, "normal", vector3_to_js(value.normal));
  return obj;
}



static RayCollision raycollision_from_js(JSValue obj) {
  RayCollision result = {0};
  JSValue hit_val = JS_GetPropertyStr(ctx, obj, "hit");
  if (!JS_IsUndefined(hit_val)) {
    result.hit = bool_from_js(hit_val);
  }
  JS_FreeValue(ctx, hit_val);
  JSValue distance_val = JS_GetPropertyStr(ctx, obj, "distance");
  if (!JS_IsUndefined(distance_val)) {
    result.distance = f32_from_js(distance_val);
  }
  JS_FreeValue(ctx, distance_val);
  JSValue point_val = JS_GetPropertyStr(ctx, obj, "point");
  if (!JS_IsUndefined(point_val)) {
    result.point = vector3_from_js(point_val);
  }
  JS_FreeValue(ctx, point_val);
  JSValue normal_val = JS_GetPropertyStr(ctx, obj, "normal");
  if (!JS_IsUndefined(normal_val)) {
    result.normal = vector3_from_js(normal_val);
  }
  JS_FreeValue(ctx, normal_val);
  return result;
}

static JSValue wave_to_js(Wave value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "frameCount", u32_to_js(value.frameCount));
  JS_SetPropertyStr(ctx, obj, "sampleRate", u32_to_js(value.sampleRate));
  JS_SetPropertyStr(ctx, obj, "sampleSize", u32_to_js(value.sampleSize));
  JS_SetPropertyStr(ctx, obj, "channels", u32_to_js(value.channels));
  // TODO: handle pointer field data
  return obj;
}



static Wave wave_from_js(JSValue obj) {
  Wave result = {0};
  JSValue frameCount_val = JS_GetPropertyStr(ctx, obj, "frameCount");
  if (!JS_IsUndefined(frameCount_val)) {
    result.frameCount = u32_from_js(frameCount_val);
  }
  JS_FreeValue(ctx, frameCount_val);
  JSValue sampleRate_val = JS_GetPropertyStr(ctx, obj, "sampleRate");
  if (!JS_IsUndefined(sampleRate_val)) {
    result.sampleRate = u32_from_js(sampleRate_val);
  }
  JS_FreeValue(ctx, sampleRate_val);
  JSValue sampleSize_val = JS_GetPropertyStr(ctx, obj, "sampleSize");
  if (!JS_IsUndefined(sampleSize_val)) {
    result.sampleSize = u32_from_js(sampleSize_val);
  }
  JS_FreeValue(ctx, sampleSize_val);
  JSValue channels_val = JS_GetPropertyStr(ctx, obj, "channels");
  if (!JS_IsUndefined(channels_val)) {
    result.channels = u32_from_js(channels_val);
  }
  JS_FreeValue(ctx, channels_val);
  // TODO: handle pointer field data
  return result;
}

static JSValue sound_to_js(Sound value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "stream", audiostream_to_js(value.stream));
  JS_SetPropertyStr(ctx, obj, "frameCount", u32_to_js(value.frameCount));
  return obj;
}



static Sound sound_from_js(JSValue obj) {
  Sound result = {0};
  JSValue stream_val = JS_GetPropertyStr(ctx, obj, "stream");
  if (!JS_IsUndefined(stream_val)) {
    result.stream = audiostream_from_js(stream_val);
  }
  JS_FreeValue(ctx, stream_val);
  JSValue frameCount_val = JS_GetPropertyStr(ctx, obj, "frameCount");
  if (!JS_IsUndefined(frameCount_val)) {
    result.frameCount = u32_from_js(frameCount_val);
  }
  JS_FreeValue(ctx, frameCount_val);
  return result;
}

static JSValue music_to_js(Music value) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "stream", audiostream_to_js(value.stream));
  JS_SetPropertyStr(ctx, obj, "frameCount", u32_to_js(value.frameCount));
  JS_SetPropertyStr(ctx, obj, "looping", bool_to_js(value.looping));
  JS_SetPropertyStr(ctx, obj, "ctxType", i32_to_js(value.ctxType));
  // TODO: handle pointer field ctxData
  return obj;
}



static Music music_from_js(JSValue obj) {
  Music result = {0};
  JSValue stream_val = JS_GetPropertyStr(ctx, obj, "stream");
  if (!JS_IsUndefined(stream_val)) {
    result.stream = audiostream_from_js(stream_val);
  }
  JS_FreeValue(ctx, stream_val);
  JSValue frameCount_val = JS_GetPropertyStr(ctx, obj, "frameCount");
  if (!JS_IsUndefined(frameCount_val)) {
    result.frameCount = u32_from_js(frameCount_val);
  }
  JS_FreeValue(ctx, frameCount_val);
  JSValue looping_val = JS_GetPropertyStr(ctx, obj, "looping");
  if (!JS_IsUndefined(looping_val)) {
    result.looping = bool_from_js(looping_val);
  }
  JS_FreeValue(ctx, looping_val);
  JSValue ctxType_val = JS_GetPropertyStr(ctx, obj, "ctxType");
  if (!JS_IsUndefined(ctxType_val)) {
    result.ctxType = i32_from_js(ctxType_val);
  }
  JS_FreeValue(ctx, ctxType_val);
  // TODO: handle pointer field ctxData
  return result;
}

static JSValue audiostream_to_js(AudioStream value) {
  JSValue obj = JS_NewObject(ctx);
  // TODO: handle pointer field buffer
  // TODO: handle pointer field processor
  JS_SetPropertyStr(ctx, obj, "sampleRate", u32_to_js(value.sampleRate));
  JS_SetPropertyStr(ctx, obj, "sampleSize", u32_to_js(value.sampleSize));
  JS_SetPropertyStr(ctx, obj, "channels", u32_to_js(value.channels));
  return obj;
}



static AudioStream audiostream_from_js(JSValue obj) {
  AudioStream result = {0};
  // TODO: handle pointer field buffer
  // TODO: handle pointer field processor
  JSValue sampleRate_val = JS_GetPropertyStr(ctx, obj, "sampleRate");
  if (!JS_IsUndefined(sampleRate_val)) {
    result.sampleRate = u32_from_js(sampleRate_val);
  }
  JS_FreeValue(ctx, sampleRate_val);
  JSValue sampleSize_val = JS_GetPropertyStr(ctx, obj, "sampleSize");
  if (!JS_IsUndefined(sampleSize_val)) {
    result.sampleSize = u32_from_js(sampleSize_val);
  }
  JS_FreeValue(ctx, sampleSize_val);
  JSValue channels_val = JS_GetPropertyStr(ctx, obj, "channels");
  if (!JS_IsUndefined(channels_val)) {
    result.channels = u32_from_js(channels_val);
  }
  JS_FreeValue(ctx, channels_val);
  return result;
}

// Variadic function implementations (cart-side)

// TextFormat - Text formatting with variables (sprintf style)
static char textFormatBuffer[1024];
static JSValue js_TextFormat(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 1) return JS_UNDEFINED;

  const char* format = string_from_js(argv[0]);
  if (!format) return JS_UNDEFINED;

  // Build format arguments - convert JS values to C types
  // This is simplified - only handles common cases
  char buffer[1024];
  int offset = 0;
  int argIdx = 1;

  for (int i = 0; format[i] && offset < sizeof(buffer) - 1; i++) {
    if (format[i] == '%' && format[i+1] && format[i+1] != '%') {
      if (argIdx >= argc) break;

      // Simple type detection based on format specifier
      if (format[i+1] == 'd' || format[i+1] == 'i') {
        int val = i32_from_js(argv[argIdx++]);
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%d", val);
        i++;
      } else if (format[i+1] == 'f') {
        float val = f32_from_js(argv[argIdx++]);
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%f", val);
        i++;
      } else if (format[i+1] == 's') {
        const char* val = string_from_js(argv[argIdx++]);
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%s", val ? val : "");
        i++;
      } else {
        buffer[offset++] = format[i];
      }
    } else if (format[i] == '%' && format[i+1] == '%') {
      buffer[offset++] = '%';
      i++;
    } else {
      buffer[offset++] = format[i];
    }
  }
  buffer[offset] = '\0';

  JS_FreeCString(ctx, format);
  return string_to_js(buffer);
}

// TraceLog - Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
static JSValue js_TraceLog(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 2) return JS_UNDEFINED;

  int logLevel = i32_from_js(argv[0]);
  const char* text = string_from_js(argv[1]);
  if (!text) return JS_UNDEFINED;

  const char* logLevelStr = "UNKNOWN";
  switch (logLevel) {
    case 0: logLevelStr = "ALL"; break;
    case 1: logLevelStr = "TRACE"; break;
    case 2: logLevelStr = "DEBUG"; break;
    case 3: logLevelStr = "INFO"; break;
    case 4: logLevelStr = "WARNING"; break;
    case 5: logLevelStr = "ERROR"; break;
    case 6: logLevelStr = "FATAL"; break;
    case 7: logLevelStr = "NONE"; break;
  }

  // Simple implementation - just use the text as-is with additional args
  fprintf(stderr, "[%s] %s", logLevelStr, text);

  // If there are additional arguments, try to print them
  for (int i = 2; i < argc; i++) {
    if (JS_IsNumber(argv[i])) {
      fprintf(stderr, " %d", i32_from_js(argv[i]));
    } else if (JS_IsString(argv[i])) {
      const char* str = string_from_js(argv[i]);
      fprintf(stderr, " %s", str ? str : "");
      JS_FreeCString(ctx, str);
    }
  }
  fprintf(stderr, "\n");

  JS_FreeCString(ctx, text);
  return JS_UNDEFINED;
}

// Function wrappers
static JSValue js_InitWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  InitWindow(i32_from_js(argv[0]), i32_from_js(argv[1]), string_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_CloseWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  CloseWindow();
  return JS_UNDEFINED;
}

static JSValue js_WindowShouldClose(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(WindowShouldClose());
}

static JSValue js_IsWindowReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsWindowReady());
}

static JSValue js_IsWindowFullscreen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsWindowFullscreen());
}

static JSValue js_IsWindowHidden(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsWindowHidden());
}

static JSValue js_IsWindowMinimized(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsWindowMinimized());
}

static JSValue js_IsWindowMaximized(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsWindowMaximized());
}

static JSValue js_IsWindowFocused(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsWindowFocused());
}

static JSValue js_IsWindowResized(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsWindowResized());
}

static JSValue js_IsWindowState(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsWindowState(u32_from_js(argv[0])));
}

static JSValue js_SetWindowState(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetWindowState(u32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ClearWindowState(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  ClearWindowState(u32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ToggleFullscreen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  ToggleFullscreen();
  return JS_UNDEFINED;
}

static JSValue js_ToggleBorderlessWindowed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  ToggleBorderlessWindowed();
  return JS_UNDEFINED;
}

static JSValue js_MaximizeWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  MaximizeWindow();
  return JS_UNDEFINED;
}

static JSValue js_MinimizeWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  MinimizeWindow();
  return JS_UNDEFINED;
}

static JSValue js_RestoreWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  RestoreWindow();
  return JS_UNDEFINED;
}

static JSValue js_SetWindowIcon(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetWindowIcon(image_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SetWindowTitle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetWindowTitle(string_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SetWindowPosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetWindowPosition(i32_from_js(argv[0]), i32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetWindowMonitor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetWindowMonitor(i32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SetWindowMinSize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetWindowMinSize(i32_from_js(argv[0]), i32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetWindowMaxSize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetWindowMaxSize(i32_from_js(argv[0]), i32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetWindowSize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetWindowSize(i32_from_js(argv[0]), i32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetWindowOpacity(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetWindowOpacity(f32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SetWindowFocused(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetWindowFocused();
  return JS_UNDEFINED;
}

static JSValue js_GetScreenWidth(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetScreenWidth());
}

static JSValue js_GetScreenHeight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetScreenHeight());
}

static JSValue js_GetRenderWidth(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetRenderWidth());
}

static JSValue js_GetRenderHeight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetRenderHeight());
}

static JSValue js_GetMonitorCount(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetMonitorCount());
}

static JSValue js_GetCurrentMonitor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetCurrentMonitor());
}

static JSValue js_GetMonitorPosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetMonitorPosition(i32_from_js(argv[0])));
}

static JSValue js_GetMonitorWidth(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetMonitorWidth(i32_from_js(argv[0])));
}

static JSValue js_GetMonitorHeight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetMonitorHeight(i32_from_js(argv[0])));
}

static JSValue js_GetMonitorPhysicalWidth(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetMonitorPhysicalWidth(i32_from_js(argv[0])));
}

static JSValue js_GetMonitorPhysicalHeight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetMonitorPhysicalHeight(i32_from_js(argv[0])));
}

static JSValue js_GetMonitorRefreshRate(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetMonitorRefreshRate(i32_from_js(argv[0])));
}

static JSValue js_GetWindowPosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetWindowPosition());
}

static JSValue js_GetWindowScaleDPI(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetWindowScaleDPI());
}

static JSValue js_GetMonitorName(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetMonitorName(i32_from_js(argv[0])));
}

static JSValue js_SetClipboardText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetClipboardText(string_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_GetClipboardText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetClipboardText());
}

static JSValue js_EnableEventWaiting(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  EnableEventWaiting();
  return JS_UNDEFINED;
}

static JSValue js_DisableEventWaiting(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DisableEventWaiting();
  return JS_UNDEFINED;
}

static JSValue js_ShowCursor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  ShowCursor();
  return JS_UNDEFINED;
}

static JSValue js_HideCursor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  HideCursor();
  return JS_UNDEFINED;
}

static JSValue js_IsCursorHidden(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsCursorHidden());
}

static JSValue js_EnableCursor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  EnableCursor();
  return JS_UNDEFINED;
}

static JSValue js_DisableCursor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DisableCursor();
  return JS_UNDEFINED;
}

static JSValue js_IsCursorOnScreen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsCursorOnScreen());
}

static JSValue js_ClearBackground(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  ClearBackground(color_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_BeginDrawing(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  BeginDrawing();
  return JS_UNDEFINED;
}

static JSValue js_EndDrawing(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  EndDrawing();
  return JS_UNDEFINED;
}

static JSValue js_BeginMode2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  BeginMode2D(camera2d_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_EndMode2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  EndMode2D();
  return JS_UNDEFINED;
}

static JSValue js_BeginMode3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  BeginMode3D(camera3d_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_EndMode3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  EndMode3D();
  return JS_UNDEFINED;
}

static JSValue js_BeginTextureMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  BeginTextureMode(rendertexture_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_EndTextureMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  EndTextureMode();
  return JS_UNDEFINED;
}

static JSValue js_BeginShaderMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  BeginShaderMode(shader_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_EndShaderMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  EndShaderMode();
  return JS_UNDEFINED;
}

static JSValue js_BeginBlendMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  BeginBlendMode(i32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_EndBlendMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  EndBlendMode();
  return JS_UNDEFINED;
}

static JSValue js_BeginScissorMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  BeginScissorMode(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_EndScissorMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  EndScissorMode();
  return JS_UNDEFINED;
}

static JSValue js_BeginVrStereoMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  BeginVrStereoMode(vrstereoconfig_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_EndVrStereoMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  EndVrStereoMode();
  return JS_UNDEFINED;
}

static JSValue js_LoadVrStereoConfig(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vrstereoconfig_to_js(LoadVrStereoConfig(vrdeviceinfo_from_js(argv[0])));
}

static JSValue js_UnloadVrStereoConfig(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadVrStereoConfig(vrstereoconfig_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_LoadShader(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return shader_to_js(LoadShader(string_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_LoadShaderFromMemory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return shader_to_js(LoadShaderFromMemory(string_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_IsShaderValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsShaderValid(shader_from_js(argv[0])));
}

static JSValue js_GetShaderLocation(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetShaderLocation(shader_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_GetShaderLocationAttrib(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetShaderLocationAttrib(shader_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_SetShaderValueMatrix(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetShaderValueMatrix(shader_from_js(argv[0]), i32_from_js(argv[1]), matrix_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_SetShaderValueTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetShaderValueTexture(shader_from_js(argv[0]), i32_from_js(argv[1]), texture_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_UnloadShader(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadShader(shader_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_GetScreenToWorldRay(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return ray_to_js(GetScreenToWorldRay(vector2_from_js(argv[0]), camera3d_from_js(argv[1])));
}

static JSValue js_GetScreenToWorldRayEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return ray_to_js(GetScreenToWorldRayEx(vector2_from_js(argv[0]), camera3d_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3])));
}

static JSValue js_GetWorldToScreen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetWorldToScreen(vector3_from_js(argv[0]), camera3d_from_js(argv[1])));
}

static JSValue js_GetWorldToScreenEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetWorldToScreenEx(vector3_from_js(argv[0]), camera3d_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3])));
}

static JSValue js_GetWorldToScreen2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetWorldToScreen2D(vector2_from_js(argv[0]), camera2d_from_js(argv[1])));
}

static JSValue js_GetScreenToWorld2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetScreenToWorld2D(vector2_from_js(argv[0]), camera2d_from_js(argv[1])));
}

static JSValue js_GetCameraMatrix(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return matrix_to_js(GetCameraMatrix(camera3d_from_js(argv[0])));
}

static JSValue js_GetCameraMatrix2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return matrix_to_js(GetCameraMatrix2D(camera2d_from_js(argv[0])));
}

static JSValue js_SetTargetFPS(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetTargetFPS(i32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_GetFrameTime(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(GetFrameTime());
}

static JSValue js_GetTime(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(GetTime());
}

static JSValue js_GetFPS(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetFPS());
}

static JSValue js_SwapScreenBuffer(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SwapScreenBuffer();
  return JS_UNDEFINED;
}

static JSValue js_PollInputEvents(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  PollInputEvents();
  return JS_UNDEFINED;
}

static JSValue js_WaitTime(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  WaitTime(f32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SetRandomSeed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetRandomSeed(u32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_GetRandomValue(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetRandomValue(i32_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_TakeScreenshot(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  TakeScreenshot(string_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SetConfigFlags(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetConfigFlags(u32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_OpenURL(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  OpenURL(string_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SetTraceLogLevel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetTraceLogLevel(i32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_UnloadFileData(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadFileData(string_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ExportDataAsCode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ExportDataAsCode(string_from_js(argv[0]), i32_from_js(argv[1]), string_from_js(argv[2])));
}

static JSValue js_LoadFileText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(LoadFileText(string_from_js(argv[0])));
}

static JSValue js_UnloadFileText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadFileText(string_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SaveFileText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(SaveFileText(string_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_FileExists(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(FileExists(string_from_js(argv[0])));
}

static JSValue js_DirectoryExists(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(DirectoryExists(string_from_js(argv[0])));
}

static JSValue js_IsFileExtension(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsFileExtension(string_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_GetFileLength(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetFileLength(string_from_js(argv[0])));
}

static JSValue js_GetFileModTime(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetFileModTime(string_from_js(argv[0])));
}

static JSValue js_GetFileExtension(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetFileExtension(string_from_js(argv[0])));
}

static JSValue js_GetFileName(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetFileName(string_from_js(argv[0])));
}

static JSValue js_GetFileNameWithoutExt(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetFileNameWithoutExt(string_from_js(argv[0])));
}

static JSValue js_GetDirectoryPath(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetDirectoryPath(string_from_js(argv[0])));
}

static JSValue js_GetPrevDirectoryPath(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetPrevDirectoryPath(string_from_js(argv[0])));
}

static JSValue js_GetWorkingDirectory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetWorkingDirectory());
}

static JSValue js_GetApplicationDirectory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetApplicationDirectory());
}

static JSValue js_MakeDirectory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(MakeDirectory(string_from_js(argv[0])));
}

static JSValue js_ChangeDirectory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ChangeDirectory(string_from_js(argv[0])));
}

static JSValue js_IsPathFile(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsPathFile(string_from_js(argv[0])));
}

static JSValue js_IsFileNameValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsFileNameValid(string_from_js(argv[0])));
}

static JSValue js_LoadDirectoryFiles(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return filepathlist_to_js(LoadDirectoryFiles(string_from_js(argv[0])));
}

static JSValue js_LoadDirectoryFilesEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return filepathlist_to_js(LoadDirectoryFilesEx(string_from_js(argv[0]), string_from_js(argv[1]), bool_from_js(argv[2])));
}

static JSValue js_UnloadDirectoryFiles(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadDirectoryFiles(filepathlist_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_IsFileDropped(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsFileDropped());
}

static JSValue js_LoadDroppedFiles(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return filepathlist_to_js(LoadDroppedFiles());
}

static JSValue js_UnloadDroppedFiles(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadDroppedFiles(filepathlist_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ComputeCRC32(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return u32_to_js(ComputeCRC32(string_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_LoadAutomationEventList(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return automationeventlist_to_js(LoadAutomationEventList(string_from_js(argv[0])));
}

static JSValue js_UnloadAutomationEventList(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadAutomationEventList(automationeventlist_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ExportAutomationEventList(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ExportAutomationEventList(automationeventlist_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_SetAutomationEventBaseFrame(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetAutomationEventBaseFrame(i32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_StartAutomationEventRecording(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  StartAutomationEventRecording();
  return JS_UNDEFINED;
}

static JSValue js_StopAutomationEventRecording(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  StopAutomationEventRecording();
  return JS_UNDEFINED;
}

static JSValue js_PlayAutomationEvent(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  PlayAutomationEvent(automationevent_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_IsKeyPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsKeyPressed(i32_from_js(argv[0])));
}

static JSValue js_IsKeyPressedRepeat(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsKeyPressedRepeat(i32_from_js(argv[0])));
}

static JSValue js_IsKeyDown(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsKeyDown(i32_from_js(argv[0])));
}

static JSValue js_IsKeyReleased(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsKeyReleased(i32_from_js(argv[0])));
}

static JSValue js_IsKeyUp(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsKeyUp(i32_from_js(argv[0])));
}

static JSValue js_GetKeyPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetKeyPressed());
}

static JSValue js_GetCharPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetCharPressed());
}

static JSValue js_GetKeyName(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetKeyName(i32_from_js(argv[0])));
}

static JSValue js_SetExitKey(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetExitKey(i32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_IsGamepadAvailable(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsGamepadAvailable(i32_from_js(argv[0])));
}

static JSValue js_GetGamepadName(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(GetGamepadName(i32_from_js(argv[0])));
}

static JSValue js_IsGamepadButtonPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsGamepadButtonPressed(i32_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_IsGamepadButtonDown(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsGamepadButtonDown(i32_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_IsGamepadButtonReleased(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsGamepadButtonReleased(i32_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_IsGamepadButtonUp(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsGamepadButtonUp(i32_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_GetGamepadButtonPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetGamepadButtonPressed());
}

static JSValue js_GetGamepadAxisCount(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetGamepadAxisCount(i32_from_js(argv[0])));
}

static JSValue js_GetGamepadAxisMovement(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(GetGamepadAxisMovement(i32_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_SetGamepadMappings(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(SetGamepadMappings(string_from_js(argv[0])));
}

static JSValue js_SetGamepadVibration(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetGamepadVibration(i32_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_IsMouseButtonPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsMouseButtonPressed(i32_from_js(argv[0])));
}

static JSValue js_IsMouseButtonDown(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsMouseButtonDown(i32_from_js(argv[0])));
}

static JSValue js_IsMouseButtonReleased(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsMouseButtonReleased(i32_from_js(argv[0])));
}

static JSValue js_IsMouseButtonUp(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsMouseButtonUp(i32_from_js(argv[0])));
}

static JSValue js_GetMouseX(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetMouseX());
}

static JSValue js_GetMouseY(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetMouseY());
}

static JSValue js_GetMousePosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetMousePosition());
}

static JSValue js_GetMouseDelta(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetMouseDelta());
}

static JSValue js_SetMousePosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetMousePosition(i32_from_js(argv[0]), i32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetMouseOffset(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetMouseOffset(i32_from_js(argv[0]), i32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetMouseScale(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetMouseScale(f32_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_GetMouseWheelMove(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(GetMouseWheelMove());
}

static JSValue js_GetMouseWheelMoveV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetMouseWheelMoveV());
}

static JSValue js_SetMouseCursor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetMouseCursor(i32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_GetTouchX(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetTouchX());
}

static JSValue js_GetTouchY(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetTouchY());
}

static JSValue js_GetTouchPosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetTouchPosition(i32_from_js(argv[0])));
}

static JSValue js_GetTouchPointId(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetTouchPointId(i32_from_js(argv[0])));
}

static JSValue js_GetTouchPointCount(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetTouchPointCount());
}

static JSValue js_SetGesturesEnabled(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetGesturesEnabled(u32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_IsGestureDetected(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsGestureDetected(u32_from_js(argv[0])));
}

static JSValue js_GetGestureDetected(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetGestureDetected());
}

static JSValue js_GetGestureHoldDuration(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(GetGestureHoldDuration());
}

static JSValue js_GetGestureDragVector(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetGestureDragVector());
}

static JSValue js_GetGestureDragAngle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(GetGestureDragAngle());
}

static JSValue js_GetGesturePinchVector(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetGesturePinchVector());
}

static JSValue js_GetGesturePinchAngle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(GetGesturePinchAngle());
}

static JSValue js_SetShapesTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetShapesTexture(texture_from_js(argv[0]), rectangle_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_GetShapesTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return texture_to_js(GetShapesTexture());
}

static JSValue js_GetShapesTextureRectangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return rectangle_to_js(GetShapesTextureRectangle());
}

static JSValue js_DrawPixel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawPixel(i32_from_js(argv[0]), i32_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawPixelV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawPixelV(vector2_from_js(argv[0]), color_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_DrawLine(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawLine(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawLineV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawLineV(vector2_from_js(argv[0]), vector2_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawLineEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawLineEx(vector2_from_js(argv[0]), vector2_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawLineBezier(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawLineBezier(vector2_from_js(argv[0]), vector2_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCircle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCircle(i32_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCircleSector(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCircleSector(vector2_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCircleSectorLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCircleSectorLines(vector2_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCircleGradient(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCircleGradient(i32_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCircleV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCircleV(vector2_from_js(argv[0]), f32_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCircleLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCircleLines(i32_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCircleLinesV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCircleLinesV(vector2_from_js(argv[0]), f32_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawEllipse(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawEllipse(i32_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawEllipseLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawEllipseLines(i32_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRing(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRing(vector2_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), f32_from_js(argv[4]), i32_from_js(argv[5]), color_from_js(argv[6]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRingLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRingLines(vector2_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), f32_from_js(argv[4]), i32_from_js(argv[5]), color_from_js(argv[6]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangle(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangleV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangleV(vector2_from_js(argv[0]), vector2_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangleRec(rectangle_from_js(argv[0]), color_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectanglePro(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectanglePro(rectangle_from_js(argv[0]), vector2_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangleGradientV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangleGradientV(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangleGradientH(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangleGradientH(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangleGradientEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangleGradientEx(rectangle_from_js(argv[0]), color_from_js(argv[1]), color_from_js(argv[2]), color_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangleLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangleLines(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangleLinesEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangleLinesEx(rectangle_from_js(argv[0]), f32_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRounded(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangleRounded(rectangle_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRoundedLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangleRoundedLines(rectangle_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRoundedLinesEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRectangleRoundedLinesEx(rectangle_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTriangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTriangle(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTriangleLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTriangleLines(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawPoly(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawPoly(vector2_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawPolyLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawPolyLines(vector2_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawPolyLinesEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawPolyLinesEx(vector2_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), f32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentLinear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawSplineSegmentLinear(vector2_from_js(argv[0]), vector2_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentBasis(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawSplineSegmentBasis(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), vector2_from_js(argv[3]), f32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentCatmullRom(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawSplineSegmentCatmullRom(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), vector2_from_js(argv[3]), f32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentBezierQuadratic(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawSplineSegmentBezierQuadratic(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentBezierCubic(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawSplineSegmentBezierCubic(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), vector2_from_js(argv[3]), f32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_GetSplinePointLinear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetSplinePointLinear(vector2_from_js(argv[0]), vector2_from_js(argv[1]), f32_from_js(argv[2])));
}

static JSValue js_GetSplinePointBasis(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetSplinePointBasis(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), vector2_from_js(argv[3]), f32_from_js(argv[4])));
}

static JSValue js_GetSplinePointCatmullRom(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetSplinePointCatmullRom(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), vector2_from_js(argv[3]), f32_from_js(argv[4])));
}

static JSValue js_GetSplinePointBezierQuad(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetSplinePointBezierQuad(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), f32_from_js(argv[3])));
}

static JSValue js_GetSplinePointBezierCubic(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(GetSplinePointBezierCubic(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), vector2_from_js(argv[3]), f32_from_js(argv[4])));
}

static JSValue js_CheckCollisionRecs(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionRecs(rectangle_from_js(argv[0]), rectangle_from_js(argv[1])));
}

static JSValue js_CheckCollisionCircles(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionCircles(vector2_from_js(argv[0]), f32_from_js(argv[1]), vector2_from_js(argv[2]), f32_from_js(argv[3])));
}

static JSValue js_CheckCollisionCircleRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionCircleRec(vector2_from_js(argv[0]), f32_from_js(argv[1]), rectangle_from_js(argv[2])));
}

static JSValue js_CheckCollisionCircleLine(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionCircleLine(vector2_from_js(argv[0]), f32_from_js(argv[1]), vector2_from_js(argv[2]), vector2_from_js(argv[3])));
}

static JSValue js_CheckCollisionPointRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionPointRec(vector2_from_js(argv[0]), rectangle_from_js(argv[1])));
}

static JSValue js_CheckCollisionPointCircle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionPointCircle(vector2_from_js(argv[0]), vector2_from_js(argv[1]), f32_from_js(argv[2])));
}

static JSValue js_CheckCollisionPointTriangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionPointTriangle(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), vector2_from_js(argv[3])));
}

static JSValue js_CheckCollisionPointLine(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionPointLine(vector2_from_js(argv[0]), vector2_from_js(argv[1]), vector2_from_js(argv[2]), i32_from_js(argv[3])));
}

static JSValue js_GetCollisionRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return rectangle_to_js(GetCollisionRec(rectangle_from_js(argv[0]), rectangle_from_js(argv[1])));
}

static JSValue js_LoadImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(LoadImage(string_from_js(argv[0])));
}

static JSValue js_LoadImageRaw(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(LoadImageRaw(string_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4])));
}

static JSValue js_LoadImageFromMemory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(LoadImageFromMemory(string_from_js(argv[0]), string_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_LoadImageFromTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(LoadImageFromTexture(texture_from_js(argv[0])));
}

static JSValue js_LoadImageFromScreen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(LoadImageFromScreen());
}

static JSValue js_IsImageValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsImageValid(image_from_js(argv[0])));
}

static JSValue js_UnloadImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadImage(image_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ExportImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ExportImage(image_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_ExportImageAsCode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ExportImageAsCode(image_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_GenImageColor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(GenImageColor(i32_from_js(argv[0]), i32_from_js(argv[1]), color_from_js(argv[2])));
}

static JSValue js_GenImageGradientLinear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(GenImageGradientLinear(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), color_from_js(argv[3]), color_from_js(argv[4])));
}

static JSValue js_GenImageGradientRadial(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(GenImageGradientRadial(i32_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]), color_from_js(argv[4])));
}

static JSValue js_GenImageGradientSquare(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(GenImageGradientSquare(i32_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]), color_from_js(argv[4])));
}

static JSValue js_GenImageChecked(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(GenImageChecked(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]), color_from_js(argv[5])));
}

static JSValue js_GenImageWhiteNoise(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(GenImageWhiteNoise(i32_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2])));
}

static JSValue js_GenImagePerlinNoise(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(GenImagePerlinNoise(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), f32_from_js(argv[4])));
}

static JSValue js_GenImageCellular(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(GenImageCellular(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_GenImageText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(GenImageText(i32_from_js(argv[0]), i32_from_js(argv[1]), string_from_js(argv[2])));
}

static JSValue js_ImageCopy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(ImageCopy(image_from_js(argv[0])));
}

static JSValue js_ImageFromImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(ImageFromImage(image_from_js(argv[0]), rectangle_from_js(argv[1])));
}

static JSValue js_ImageFromChannel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(ImageFromChannel(image_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_ImageText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(ImageText(string_from_js(argv[0]), i32_from_js(argv[1]), color_from_js(argv[2])));
}

static JSValue js_ImageTextEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return image_to_js(ImageTextEx(font_from_js(argv[0]), string_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4])));
}

static JSValue js_GetImageAlphaBorder(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return rectangle_to_js(GetImageAlphaBorder(image_from_js(argv[0]), f32_from_js(argv[1])));
}

static JSValue js_GetImageColor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(GetImageColor(image_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_LoadTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return texture_to_js(LoadTexture(string_from_js(argv[0])));
}

static JSValue js_LoadTextureFromImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return texture_to_js(LoadTextureFromImage(image_from_js(argv[0])));
}

static JSValue js_LoadTextureCubemap(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return texture_to_js(LoadTextureCubemap(image_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_LoadRenderTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return rendertexture_to_js(LoadRenderTexture(i32_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_IsTextureValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsTextureValid(texture_from_js(argv[0])));
}

static JSValue js_UnloadTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadTexture(texture_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_IsRenderTextureValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsRenderTextureValid(rendertexture_from_js(argv[0])));
}

static JSValue js_UnloadRenderTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadRenderTexture(rendertexture_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SetTextureFilter(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetTextureFilter(texture_from_js(argv[0]), i32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetTextureWrap(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetTextureWrap(texture_from_js(argv[0]), i32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTexture(texture_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTextureV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTextureV(texture_from_js(argv[0]), vector2_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTextureEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTextureEx(texture_from_js(argv[0]), vector2_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTextureRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTextureRec(texture_from_js(argv[0]), rectangle_from_js(argv[1]), vector2_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTexturePro(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTexturePro(texture_from_js(argv[0]), rectangle_from_js(argv[1]), rectangle_from_js(argv[2]), vector2_from_js(argv[3]), f32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTextureNPatch(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTextureNPatch(texture_from_js(argv[0]), npatchinfo_from_js(argv[1]), rectangle_from_js(argv[2]), vector2_from_js(argv[3]), f32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_ColorIsEqual(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ColorIsEqual(color_from_js(argv[0]), color_from_js(argv[1])));
}

static JSValue js_Fade(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(Fade(color_from_js(argv[0]), f32_from_js(argv[1])));
}

static JSValue js_ColorToInt(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(ColorToInt(color_from_js(argv[0])));
}

static JSValue js_ColorNormalize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector4_to_js(ColorNormalize(color_from_js(argv[0])));
}

static JSValue js_ColorFromNormalized(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(ColorFromNormalized(vector4_from_js(argv[0])));
}

static JSValue js_ColorToHSV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector3_to_js(ColorToHSV(color_from_js(argv[0])));
}

static JSValue js_ColorFromHSV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(ColorFromHSV(f32_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2])));
}

static JSValue js_ColorTint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(ColorTint(color_from_js(argv[0]), color_from_js(argv[1])));
}

static JSValue js_ColorBrightness(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(ColorBrightness(color_from_js(argv[0]), f32_from_js(argv[1])));
}

static JSValue js_ColorContrast(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(ColorContrast(color_from_js(argv[0]), f32_from_js(argv[1])));
}

static JSValue js_ColorAlpha(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(ColorAlpha(color_from_js(argv[0]), f32_from_js(argv[1])));
}

static JSValue js_ColorAlphaBlend(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(ColorAlphaBlend(color_from_js(argv[0]), color_from_js(argv[1]), color_from_js(argv[2])));
}

static JSValue js_ColorLerp(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(ColorLerp(color_from_js(argv[0]), color_from_js(argv[1]), f32_from_js(argv[2])));
}

static JSValue js_GetColor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return color_to_js(GetColor(u32_from_js(argv[0])));
}

static JSValue js_GetPixelDataSize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetPixelDataSize(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_GetFontDefault(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return font_to_js(GetFontDefault());
}

static JSValue js_LoadFont(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return font_to_js(LoadFont(string_from_js(argv[0])));
}

static JSValue js_LoadFontFromImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return font_to_js(LoadFontFromImage(image_from_js(argv[0]), color_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_IsFontValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsFontValid(font_from_js(argv[0])));
}

static JSValue js_UnloadFont(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadFont(font_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ExportFontAsCode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ExportFontAsCode(font_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_DrawFPS(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawFPS(i32_from_js(argv[0]), i32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_DrawText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawText(string_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTextEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTextEx(font_from_js(argv[0]), string_from_js(argv[1]), vector2_from_js(argv[2]), f32_from_js(argv[3]), f32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTextPro(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTextPro(font_from_js(argv[0]), string_from_js(argv[1]), vector2_from_js(argv[2]), vector2_from_js(argv[3]), f32_from_js(argv[4]), f32_from_js(argv[5]), f32_from_js(argv[6]), color_from_js(argv[7]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTextCodepoint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTextCodepoint(font_from_js(argv[0]), i32_from_js(argv[1]), vector2_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_SetTextLineSpacing(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetTextLineSpacing(i32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_MeasureText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(MeasureText(string_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_MeasureTextEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return vector2_to_js(MeasureTextEx(font_from_js(argv[0]), string_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3])));
}

static JSValue js_GetGlyphIndex(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetGlyphIndex(font_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_GetGlyphInfo(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return glyphinfo_to_js(GetGlyphInfo(font_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_GetGlyphAtlasRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return rectangle_to_js(GetGlyphAtlasRec(font_from_js(argv[0]), i32_from_js(argv[1])));
}

static JSValue js_UnloadUTF8(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadUTF8(string_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_GetCodepointCount(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(GetCodepointCount(string_from_js(argv[0])));
}

static JSValue js_TextCopy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(TextCopy(string_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_TextIsEqual(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(TextIsEqual(string_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_TextLength(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return u32_to_js(TextLength(string_from_js(argv[0])));
}

static JSValue js_TextSubtext(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(TextSubtext(string_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_TextReplace(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(TextReplace(string_from_js(argv[0]), string_from_js(argv[1]), string_from_js(argv[2])));
}

static JSValue js_TextInsert(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(TextInsert(string_from_js(argv[0]), string_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_TextJoin(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(TextJoin(string_from_js(argv[0]), i32_from_js(argv[1]), string_from_js(argv[2])));
}

static JSValue js_TextFindIndex(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(TextFindIndex(string_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_TextToUpper(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(TextToUpper(string_from_js(argv[0])));
}

static JSValue js_TextToLower(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(TextToLower(string_from_js(argv[0])));
}

static JSValue js_TextToPascal(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(TextToPascal(string_from_js(argv[0])));
}

static JSValue js_TextToSnake(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(TextToSnake(string_from_js(argv[0])));
}

static JSValue js_TextToCamel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return string_to_js(TextToCamel(string_from_js(argv[0])));
}

static JSValue js_TextToInteger(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return i32_to_js(TextToInteger(string_from_js(argv[0])));
}

static JSValue js_TextToFloat(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(TextToFloat(string_from_js(argv[0])));
}

static JSValue js_DrawLine3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawLine3D(vector3_from_js(argv[0]), vector3_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawPoint3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawPoint3D(vector3_from_js(argv[0]), color_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCircle3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCircle3D(vector3_from_js(argv[0]), f32_from_js(argv[1]), vector3_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawTriangle3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawTriangle3D(vector3_from_js(argv[0]), vector3_from_js(argv[1]), vector3_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCube(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCube(vector3_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCubeV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCubeV(vector3_from_js(argv[0]), vector3_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCubeWires(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCubeWires(vector3_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCubeWiresV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCubeWiresV(vector3_from_js(argv[0]), vector3_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawSphere(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawSphere(vector3_from_js(argv[0]), f32_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawSphereEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawSphereEx(vector3_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawSphereWires(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawSphereWires(vector3_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCylinder(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCylinder(vector3_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCylinderEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCylinderEx(vector3_from_js(argv[0]), vector3_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCylinderWires(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCylinderWires(vector3_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCylinderWiresEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCylinderWiresEx(vector3_from_js(argv[0]), vector3_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCapsule(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCapsule(vector3_from_js(argv[0]), vector3_from_js(argv[1]), f32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawCapsuleWires(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawCapsuleWires(vector3_from_js(argv[0]), vector3_from_js(argv[1]), f32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawPlane(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawPlane(vector3_from_js(argv[0]), vector2_from_js(argv[1]), color_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_DrawRay(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawRay(ray_from_js(argv[0]), color_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_DrawGrid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawGrid(i32_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_LoadModel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return model_to_js(LoadModel(string_from_js(argv[0])));
}

static JSValue js_LoadModelFromMesh(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return model_to_js(LoadModelFromMesh(mesh_from_js(argv[0])));
}

static JSValue js_IsModelValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsModelValid(model_from_js(argv[0])));
}

static JSValue js_UnloadModel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadModel(model_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_GetModelBoundingBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return boundingbox_to_js(GetModelBoundingBox(model_from_js(argv[0])));
}

static JSValue js_DrawModel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawModel(model_from_js(argv[0]), vector3_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawModelEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawModelEx(model_from_js(argv[0]), vector3_from_js(argv[1]), vector3_from_js(argv[2]), f32_from_js(argv[3]), vector3_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawModelWires(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawModelWires(model_from_js(argv[0]), vector3_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawModelWiresEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawModelWiresEx(model_from_js(argv[0]), vector3_from_js(argv[1]), vector3_from_js(argv[2]), f32_from_js(argv[3]), vector3_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawModelPoints(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawModelPoints(model_from_js(argv[0]), vector3_from_js(argv[1]), f32_from_js(argv[2]), color_from_js(argv[3]));
  return JS_UNDEFINED;
}

static JSValue js_DrawModelPointsEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawModelPointsEx(model_from_js(argv[0]), vector3_from_js(argv[1]), vector3_from_js(argv[2]), f32_from_js(argv[3]), vector3_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawBoundingBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawBoundingBox(boundingbox_from_js(argv[0]), color_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_DrawBillboard(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawBillboard(camera3d_from_js(argv[0]), texture_from_js(argv[1]), vector3_from_js(argv[2]), f32_from_js(argv[3]), color_from_js(argv[4]));
  return JS_UNDEFINED;
}

static JSValue js_DrawBillboardRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawBillboardRec(camera3d_from_js(argv[0]), texture_from_js(argv[1]), rectangle_from_js(argv[2]), vector3_from_js(argv[3]), vector2_from_js(argv[4]), color_from_js(argv[5]));
  return JS_UNDEFINED;
}

static JSValue js_DrawBillboardPro(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawBillboardPro(camera3d_from_js(argv[0]), texture_from_js(argv[1]), rectangle_from_js(argv[2]), vector3_from_js(argv[3]), vector3_from_js(argv[4]), vector2_from_js(argv[5]), vector2_from_js(argv[6]), f32_from_js(argv[7]), color_from_js(argv[8]));
  return JS_UNDEFINED;
}

static JSValue js_UnloadMesh(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadMesh(mesh_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_DrawMesh(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  DrawMesh(mesh_from_js(argv[0]), material_from_js(argv[1]), matrix_from_js(argv[2]));
  return JS_UNDEFINED;
}

static JSValue js_GetMeshBoundingBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return boundingbox_to_js(GetMeshBoundingBox(mesh_from_js(argv[0])));
}

static JSValue js_ExportMesh(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ExportMesh(mesh_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_ExportMeshAsCode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ExportMeshAsCode(mesh_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_GenMeshPoly(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshPoly(i32_from_js(argv[0]), f32_from_js(argv[1])));
}

static JSValue js_GenMeshPlane(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshPlane(f32_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3])));
}

static JSValue js_GenMeshCube(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshCube(f32_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2])));
}

static JSValue js_GenMeshSphere(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshSphere(f32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_GenMeshHemiSphere(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshHemiSphere(f32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_GenMeshCylinder(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshCylinder(f32_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_GenMeshCone(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshCone(f32_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_GenMeshTorus(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshTorus(f32_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3])));
}

static JSValue js_GenMeshKnot(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshKnot(f32_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3])));
}

static JSValue js_GenMeshHeightmap(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshHeightmap(image_from_js(argv[0]), vector3_from_js(argv[1])));
}

static JSValue js_GenMeshCubicmap(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return mesh_to_js(GenMeshCubicmap(image_from_js(argv[0]), vector3_from_js(argv[1])));
}

static JSValue js_LoadMaterialDefault(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return material_to_js(LoadMaterialDefault());
}

static JSValue js_IsMaterialValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsMaterialValid(material_from_js(argv[0])));
}

static JSValue js_UnloadMaterial(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadMaterial(material_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_CheckCollisionSpheres(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionSpheres(vector3_from_js(argv[0]), f32_from_js(argv[1]), vector3_from_js(argv[2]), f32_from_js(argv[3])));
}

static JSValue js_CheckCollisionBoxes(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionBoxes(boundingbox_from_js(argv[0]), boundingbox_from_js(argv[1])));
}

static JSValue js_CheckCollisionBoxSphere(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(CheckCollisionBoxSphere(boundingbox_from_js(argv[0]), vector3_from_js(argv[1]), f32_from_js(argv[2])));
}

static JSValue js_GetRayCollisionSphere(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return raycollision_to_js(GetRayCollisionSphere(ray_from_js(argv[0]), vector3_from_js(argv[1]), f32_from_js(argv[2])));
}

static JSValue js_GetRayCollisionBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return raycollision_to_js(GetRayCollisionBox(ray_from_js(argv[0]), boundingbox_from_js(argv[1])));
}

static JSValue js_GetRayCollisionMesh(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return raycollision_to_js(GetRayCollisionMesh(ray_from_js(argv[0]), mesh_from_js(argv[1]), matrix_from_js(argv[2])));
}

static JSValue js_GetRayCollisionTriangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return raycollision_to_js(GetRayCollisionTriangle(ray_from_js(argv[0]), vector3_from_js(argv[1]), vector3_from_js(argv[2]), vector3_from_js(argv[3])));
}

static JSValue js_GetRayCollisionQuad(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return raycollision_to_js(GetRayCollisionQuad(ray_from_js(argv[0]), vector3_from_js(argv[1]), vector3_from_js(argv[2]), vector3_from_js(argv[3]), vector3_from_js(argv[4])));
}

static JSValue js_InitAudioDevice(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  InitAudioDevice();
  return JS_UNDEFINED;
}

static JSValue js_CloseAudioDevice(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  CloseAudioDevice();
  return JS_UNDEFINED;
}

static JSValue js_IsAudioDeviceReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsAudioDeviceReady());
}

static JSValue js_SetMasterVolume(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetMasterVolume(f32_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_GetMasterVolume(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(GetMasterVolume());
}

static JSValue js_LoadWave(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return wave_to_js(LoadWave(string_from_js(argv[0])));
}

static JSValue js_LoadWaveFromMemory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return wave_to_js(LoadWaveFromMemory(string_from_js(argv[0]), string_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_IsWaveValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsWaveValid(wave_from_js(argv[0])));
}

static JSValue js_LoadSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return sound_to_js(LoadSound(string_from_js(argv[0])));
}

static JSValue js_LoadSoundFromWave(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return sound_to_js(LoadSoundFromWave(wave_from_js(argv[0])));
}

static JSValue js_LoadSoundAlias(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return sound_to_js(LoadSoundAlias(sound_from_js(argv[0])));
}

static JSValue js_IsSoundValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsSoundValid(sound_from_js(argv[0])));
}

static JSValue js_UnloadWave(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadWave(wave_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_UnloadSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadSound(sound_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_UnloadSoundAlias(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadSoundAlias(sound_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ExportWave(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ExportWave(wave_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_ExportWaveAsCode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(ExportWaveAsCode(wave_from_js(argv[0]), string_from_js(argv[1])));
}

static JSValue js_PlaySound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  PlaySound(sound_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_StopSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  StopSound(sound_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_PauseSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  PauseSound(sound_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ResumeSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  ResumeSound(sound_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_IsSoundPlaying(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsSoundPlaying(sound_from_js(argv[0])));
}

static JSValue js_SetSoundVolume(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetSoundVolume(sound_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetSoundPitch(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetSoundPitch(sound_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetSoundPan(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetSoundPan(sound_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_WaveCopy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return wave_to_js(WaveCopy(wave_from_js(argv[0])));
}

static JSValue js_LoadMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return music_to_js(LoadMusicStream(string_from_js(argv[0])));
}

static JSValue js_LoadMusicStreamFromMemory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return music_to_js(LoadMusicStreamFromMemory(string_from_js(argv[0]), string_from_js(argv[1]), i32_from_js(argv[2])));
}

static JSValue js_IsMusicValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsMusicValid(music_from_js(argv[0])));
}

static JSValue js_UnloadMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadMusicStream(music_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_PlayMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  PlayMusicStream(music_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_IsMusicStreamPlaying(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsMusicStreamPlaying(music_from_js(argv[0])));
}

static JSValue js_UpdateMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UpdateMusicStream(music_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_StopMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  StopMusicStream(music_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_PauseMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  PauseMusicStream(music_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ResumeMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  ResumeMusicStream(music_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SeekMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SeekMusicStream(music_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetMusicVolume(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetMusicVolume(music_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetMusicPitch(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetMusicPitch(music_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetMusicPan(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetMusicPan(music_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_GetMusicTimeLength(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(GetMusicTimeLength(music_from_js(argv[0])));
}

static JSValue js_GetMusicTimePlayed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return f32_to_js(GetMusicTimePlayed(music_from_js(argv[0])));
}

static JSValue js_LoadAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return audiostream_to_js(LoadAudioStream(u32_from_js(argv[0]), u32_from_js(argv[1]), u32_from_js(argv[2])));
}

static JSValue js_IsAudioStreamValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsAudioStreamValid(audiostream_from_js(argv[0])));
}

static JSValue js_UnloadAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  UnloadAudioStream(audiostream_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_IsAudioStreamProcessed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsAudioStreamProcessed(audiostream_from_js(argv[0])));
}

static JSValue js_PlayAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  PlayAudioStream(audiostream_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_PauseAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  PauseAudioStream(audiostream_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_ResumeAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  ResumeAudioStream(audiostream_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_IsAudioStreamPlaying(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return bool_to_js(IsAudioStreamPlaying(audiostream_from_js(argv[0])));
}

static JSValue js_StopAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  StopAudioStream(audiostream_from_js(argv[0]));
  return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamVolume(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetAudioStreamVolume(audiostream_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamPitch(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetAudioStreamPitch(audiostream_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamPan(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetAudioStreamPan(audiostream_from_js(argv[0]), f32_from_js(argv[1]));
  return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamBufferSizeDefault(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  SetAudioStreamBufferSizeDefault(i32_from_js(argv[0]));
  return JS_UNDEFINED;
}

// Expose everything to JavaScript
void expose_things_to_js() {
  // Color constants
  JS_SetPropertyStr(ctx, global, "LIGHTGRAY", color_to_js(LIGHTGRAY));
  JS_SetPropertyStr(ctx, global, "GRAY", color_to_js(GRAY));
  JS_SetPropertyStr(ctx, global, "DARKGRAY", color_to_js(DARKGRAY));
  JS_SetPropertyStr(ctx, global, "YELLOW", color_to_js(YELLOW));
  JS_SetPropertyStr(ctx, global, "GOLD", color_to_js(GOLD));
  JS_SetPropertyStr(ctx, global, "ORANGE", color_to_js(ORANGE));
  JS_SetPropertyStr(ctx, global, "PINK", color_to_js(PINK));
  JS_SetPropertyStr(ctx, global, "RED", color_to_js(RED));
  JS_SetPropertyStr(ctx, global, "MAROON", color_to_js(MAROON));
  JS_SetPropertyStr(ctx, global, "GREEN", color_to_js(GREEN));
  JS_SetPropertyStr(ctx, global, "LIME", color_to_js(LIME));
  JS_SetPropertyStr(ctx, global, "DARKGREEN", color_to_js(DARKGREEN));
  JS_SetPropertyStr(ctx, global, "SKYBLUE", color_to_js(SKYBLUE));
  JS_SetPropertyStr(ctx, global, "BLUE", color_to_js(BLUE));
  JS_SetPropertyStr(ctx, global, "DARKBLUE", color_to_js(DARKBLUE));
  JS_SetPropertyStr(ctx, global, "PURPLE", color_to_js(PURPLE));
  JS_SetPropertyStr(ctx, global, "VIOLET", color_to_js(VIOLET));
  JS_SetPropertyStr(ctx, global, "DARKPURPLE", color_to_js(DARKPURPLE));
  JS_SetPropertyStr(ctx, global, "BEIGE", color_to_js(BEIGE));
  JS_SetPropertyStr(ctx, global, "BROWN", color_to_js(BROWN));
  JS_SetPropertyStr(ctx, global, "DARKBROWN", color_to_js(DARKBROWN));
  JS_SetPropertyStr(ctx, global, "WHITE", color_to_js(WHITE));
  JS_SetPropertyStr(ctx, global, "BLACK", color_to_js(BLACK));
  JS_SetPropertyStr(ctx, global, "BLANK", color_to_js(BLANK));
  JS_SetPropertyStr(ctx, global, "MAGENTA", color_to_js(MAGENTA));
  JS_SetPropertyStr(ctx, global, "RAYWHITE", color_to_js(RAYWHITE));

  // Enum values
  JS_SetPropertyStr(ctx, global, "FLAG_VSYNC_HINT", i32_to_js(FLAG_VSYNC_HINT));
  JS_SetPropertyStr(ctx, global, "FLAG_FULLSCREEN_MODE", i32_to_js(FLAG_FULLSCREEN_MODE));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_RESIZABLE", i32_to_js(FLAG_WINDOW_RESIZABLE));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_UNDECORATED", i32_to_js(FLAG_WINDOW_UNDECORATED));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_HIDDEN", i32_to_js(FLAG_WINDOW_HIDDEN));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_MINIMIZED", i32_to_js(FLAG_WINDOW_MINIMIZED));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_MAXIMIZED", i32_to_js(FLAG_WINDOW_MAXIMIZED));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_UNFOCUSED", i32_to_js(FLAG_WINDOW_UNFOCUSED));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_TOPMOST", i32_to_js(FLAG_WINDOW_TOPMOST));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_ALWAYS_RUN", i32_to_js(FLAG_WINDOW_ALWAYS_RUN));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_TRANSPARENT", i32_to_js(FLAG_WINDOW_TRANSPARENT));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_HIGHDPI", i32_to_js(FLAG_WINDOW_HIGHDPI));
  JS_SetPropertyStr(ctx, global, "FLAG_WINDOW_MOUSE_PASSTHROUGH", i32_to_js(FLAG_WINDOW_MOUSE_PASSTHROUGH));
  JS_SetPropertyStr(ctx, global, "FLAG_BORDERLESS_WINDOWED_MODE", i32_to_js(FLAG_BORDERLESS_WINDOWED_MODE));
  JS_SetPropertyStr(ctx, global, "FLAG_MSAA_4X_HINT", i32_to_js(FLAG_MSAA_4X_HINT));
  JS_SetPropertyStr(ctx, global, "FLAG_INTERLACED_HINT", i32_to_js(FLAG_INTERLACED_HINT));
  JS_SetPropertyStr(ctx, global, "LOG_ALL", i32_to_js(LOG_ALL));
  JS_SetPropertyStr(ctx, global, "LOG_TRACE", i32_to_js(LOG_TRACE));
  JS_SetPropertyStr(ctx, global, "LOG_DEBUG", i32_to_js(LOG_DEBUG));
  JS_SetPropertyStr(ctx, global, "LOG_INFO", i32_to_js(LOG_INFO));
  JS_SetPropertyStr(ctx, global, "LOG_WARNING", i32_to_js(LOG_WARNING));
  JS_SetPropertyStr(ctx, global, "LOG_ERROR", i32_to_js(LOG_ERROR));
  JS_SetPropertyStr(ctx, global, "LOG_FATAL", i32_to_js(LOG_FATAL));
  JS_SetPropertyStr(ctx, global, "LOG_NONE", i32_to_js(LOG_NONE));
  JS_SetPropertyStr(ctx, global, "KEY_NULL", i32_to_js(KEY_NULL));
  JS_SetPropertyStr(ctx, global, "KEY_APOSTROPHE", i32_to_js(KEY_APOSTROPHE));
  JS_SetPropertyStr(ctx, global, "KEY_COMMA", i32_to_js(KEY_COMMA));
  JS_SetPropertyStr(ctx, global, "KEY_MINUS", i32_to_js(KEY_MINUS));
  JS_SetPropertyStr(ctx, global, "KEY_PERIOD", i32_to_js(KEY_PERIOD));
  JS_SetPropertyStr(ctx, global, "KEY_SLASH", i32_to_js(KEY_SLASH));
  JS_SetPropertyStr(ctx, global, "KEY_ZERO", i32_to_js(KEY_ZERO));
  JS_SetPropertyStr(ctx, global, "KEY_ONE", i32_to_js(KEY_ONE));
  JS_SetPropertyStr(ctx, global, "KEY_TWO", i32_to_js(KEY_TWO));
  JS_SetPropertyStr(ctx, global, "KEY_THREE", i32_to_js(KEY_THREE));
  JS_SetPropertyStr(ctx, global, "KEY_FOUR", i32_to_js(KEY_FOUR));
  JS_SetPropertyStr(ctx, global, "KEY_FIVE", i32_to_js(KEY_FIVE));
  JS_SetPropertyStr(ctx, global, "KEY_SIX", i32_to_js(KEY_SIX));
  JS_SetPropertyStr(ctx, global, "KEY_SEVEN", i32_to_js(KEY_SEVEN));
  JS_SetPropertyStr(ctx, global, "KEY_EIGHT", i32_to_js(KEY_EIGHT));
  JS_SetPropertyStr(ctx, global, "KEY_NINE", i32_to_js(KEY_NINE));
  JS_SetPropertyStr(ctx, global, "KEY_SEMICOLON", i32_to_js(KEY_SEMICOLON));
  JS_SetPropertyStr(ctx, global, "KEY_EQUAL", i32_to_js(KEY_EQUAL));
  JS_SetPropertyStr(ctx, global, "KEY_A", i32_to_js(KEY_A));
  JS_SetPropertyStr(ctx, global, "KEY_B", i32_to_js(KEY_B));
  JS_SetPropertyStr(ctx, global, "KEY_C", i32_to_js(KEY_C));
  JS_SetPropertyStr(ctx, global, "KEY_D", i32_to_js(KEY_D));
  JS_SetPropertyStr(ctx, global, "KEY_E", i32_to_js(KEY_E));
  JS_SetPropertyStr(ctx, global, "KEY_F", i32_to_js(KEY_F));
  JS_SetPropertyStr(ctx, global, "KEY_G", i32_to_js(KEY_G));
  JS_SetPropertyStr(ctx, global, "KEY_H", i32_to_js(KEY_H));
  JS_SetPropertyStr(ctx, global, "KEY_I", i32_to_js(KEY_I));
  JS_SetPropertyStr(ctx, global, "KEY_J", i32_to_js(KEY_J));
  JS_SetPropertyStr(ctx, global, "KEY_K", i32_to_js(KEY_K));
  JS_SetPropertyStr(ctx, global, "KEY_L", i32_to_js(KEY_L));
  JS_SetPropertyStr(ctx, global, "KEY_M", i32_to_js(KEY_M));
  JS_SetPropertyStr(ctx, global, "KEY_N", i32_to_js(KEY_N));
  JS_SetPropertyStr(ctx, global, "KEY_O", i32_to_js(KEY_O));
  JS_SetPropertyStr(ctx, global, "KEY_P", i32_to_js(KEY_P));
  JS_SetPropertyStr(ctx, global, "KEY_Q", i32_to_js(KEY_Q));
  JS_SetPropertyStr(ctx, global, "KEY_R", i32_to_js(KEY_R));
  JS_SetPropertyStr(ctx, global, "KEY_S", i32_to_js(KEY_S));
  JS_SetPropertyStr(ctx, global, "KEY_T", i32_to_js(KEY_T));
  JS_SetPropertyStr(ctx, global, "KEY_U", i32_to_js(KEY_U));
  JS_SetPropertyStr(ctx, global, "KEY_V", i32_to_js(KEY_V));
  JS_SetPropertyStr(ctx, global, "KEY_W", i32_to_js(KEY_W));
  JS_SetPropertyStr(ctx, global, "KEY_X", i32_to_js(KEY_X));
  JS_SetPropertyStr(ctx, global, "KEY_Y", i32_to_js(KEY_Y));
  JS_SetPropertyStr(ctx, global, "KEY_Z", i32_to_js(KEY_Z));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT_BRACKET", i32_to_js(KEY_LEFT_BRACKET));
  JS_SetPropertyStr(ctx, global, "KEY_BACKSLASH", i32_to_js(KEY_BACKSLASH));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT_BRACKET", i32_to_js(KEY_RIGHT_BRACKET));
  JS_SetPropertyStr(ctx, global, "KEY_GRAVE", i32_to_js(KEY_GRAVE));
  JS_SetPropertyStr(ctx, global, "KEY_SPACE", i32_to_js(KEY_SPACE));
  JS_SetPropertyStr(ctx, global, "KEY_ESCAPE", i32_to_js(KEY_ESCAPE));
  JS_SetPropertyStr(ctx, global, "KEY_ENTER", i32_to_js(KEY_ENTER));
  JS_SetPropertyStr(ctx, global, "KEY_TAB", i32_to_js(KEY_TAB));
  JS_SetPropertyStr(ctx, global, "KEY_BACKSPACE", i32_to_js(KEY_BACKSPACE));
  JS_SetPropertyStr(ctx, global, "KEY_INSERT", i32_to_js(KEY_INSERT));
  JS_SetPropertyStr(ctx, global, "KEY_DELETE", i32_to_js(KEY_DELETE));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT", i32_to_js(KEY_RIGHT));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT", i32_to_js(KEY_LEFT));
  JS_SetPropertyStr(ctx, global, "KEY_DOWN", i32_to_js(KEY_DOWN));
  JS_SetPropertyStr(ctx, global, "KEY_UP", i32_to_js(KEY_UP));
  JS_SetPropertyStr(ctx, global, "KEY_PAGE_UP", i32_to_js(KEY_PAGE_UP));
  JS_SetPropertyStr(ctx, global, "KEY_PAGE_DOWN", i32_to_js(KEY_PAGE_DOWN));
  JS_SetPropertyStr(ctx, global, "KEY_HOME", i32_to_js(KEY_HOME));
  JS_SetPropertyStr(ctx, global, "KEY_END", i32_to_js(KEY_END));
  JS_SetPropertyStr(ctx, global, "KEY_CAPS_LOCK", i32_to_js(KEY_CAPS_LOCK));
  JS_SetPropertyStr(ctx, global, "KEY_SCROLL_LOCK", i32_to_js(KEY_SCROLL_LOCK));
  JS_SetPropertyStr(ctx, global, "KEY_NUM_LOCK", i32_to_js(KEY_NUM_LOCK));
  JS_SetPropertyStr(ctx, global, "KEY_PRINT_SCREEN", i32_to_js(KEY_PRINT_SCREEN));
  JS_SetPropertyStr(ctx, global, "KEY_PAUSE", i32_to_js(KEY_PAUSE));
  JS_SetPropertyStr(ctx, global, "KEY_F1", i32_to_js(KEY_F1));
  JS_SetPropertyStr(ctx, global, "KEY_F2", i32_to_js(KEY_F2));
  JS_SetPropertyStr(ctx, global, "KEY_F3", i32_to_js(KEY_F3));
  JS_SetPropertyStr(ctx, global, "KEY_F4", i32_to_js(KEY_F4));
  JS_SetPropertyStr(ctx, global, "KEY_F5", i32_to_js(KEY_F5));
  JS_SetPropertyStr(ctx, global, "KEY_F6", i32_to_js(KEY_F6));
  JS_SetPropertyStr(ctx, global, "KEY_F7", i32_to_js(KEY_F7));
  JS_SetPropertyStr(ctx, global, "KEY_F8", i32_to_js(KEY_F8));
  JS_SetPropertyStr(ctx, global, "KEY_F9", i32_to_js(KEY_F9));
  JS_SetPropertyStr(ctx, global, "KEY_F10", i32_to_js(KEY_F10));
  JS_SetPropertyStr(ctx, global, "KEY_F11", i32_to_js(KEY_F11));
  JS_SetPropertyStr(ctx, global, "KEY_F12", i32_to_js(KEY_F12));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT_SHIFT", i32_to_js(KEY_LEFT_SHIFT));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT_CONTROL", i32_to_js(KEY_LEFT_CONTROL));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT_ALT", i32_to_js(KEY_LEFT_ALT));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT_SUPER", i32_to_js(KEY_LEFT_SUPER));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT_SHIFT", i32_to_js(KEY_RIGHT_SHIFT));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT_CONTROL", i32_to_js(KEY_RIGHT_CONTROL));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT_ALT", i32_to_js(KEY_RIGHT_ALT));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT_SUPER", i32_to_js(KEY_RIGHT_SUPER));
  JS_SetPropertyStr(ctx, global, "KEY_KB_MENU", i32_to_js(KEY_KB_MENU));
  JS_SetPropertyStr(ctx, global, "KEY_KP_0", i32_to_js(KEY_KP_0));
  JS_SetPropertyStr(ctx, global, "KEY_KP_1", i32_to_js(KEY_KP_1));
  JS_SetPropertyStr(ctx, global, "KEY_KP_2", i32_to_js(KEY_KP_2));
  JS_SetPropertyStr(ctx, global, "KEY_KP_3", i32_to_js(KEY_KP_3));
  JS_SetPropertyStr(ctx, global, "KEY_KP_4", i32_to_js(KEY_KP_4));
  JS_SetPropertyStr(ctx, global, "KEY_KP_5", i32_to_js(KEY_KP_5));
  JS_SetPropertyStr(ctx, global, "KEY_KP_6", i32_to_js(KEY_KP_6));
  JS_SetPropertyStr(ctx, global, "KEY_KP_7", i32_to_js(KEY_KP_7));
  JS_SetPropertyStr(ctx, global, "KEY_KP_8", i32_to_js(KEY_KP_8));
  JS_SetPropertyStr(ctx, global, "KEY_KP_9", i32_to_js(KEY_KP_9));
  JS_SetPropertyStr(ctx, global, "KEY_KP_DECIMAL", i32_to_js(KEY_KP_DECIMAL));
  JS_SetPropertyStr(ctx, global, "KEY_KP_DIVIDE", i32_to_js(KEY_KP_DIVIDE));
  JS_SetPropertyStr(ctx, global, "KEY_KP_MULTIPLY", i32_to_js(KEY_KP_MULTIPLY));
  JS_SetPropertyStr(ctx, global, "KEY_KP_SUBTRACT", i32_to_js(KEY_KP_SUBTRACT));
  JS_SetPropertyStr(ctx, global, "KEY_KP_ADD", i32_to_js(KEY_KP_ADD));
  JS_SetPropertyStr(ctx, global, "KEY_KP_ENTER", i32_to_js(KEY_KP_ENTER));
  JS_SetPropertyStr(ctx, global, "KEY_KP_EQUAL", i32_to_js(KEY_KP_EQUAL));
  JS_SetPropertyStr(ctx, global, "KEY_BACK", i32_to_js(KEY_BACK));
  JS_SetPropertyStr(ctx, global, "KEY_MENU", i32_to_js(KEY_MENU));
  JS_SetPropertyStr(ctx, global, "KEY_VOLUME_UP", i32_to_js(KEY_VOLUME_UP));
  JS_SetPropertyStr(ctx, global, "KEY_VOLUME_DOWN", i32_to_js(KEY_VOLUME_DOWN));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_LEFT", i32_to_js(MOUSE_BUTTON_LEFT));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_RIGHT", i32_to_js(MOUSE_BUTTON_RIGHT));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_MIDDLE", i32_to_js(MOUSE_BUTTON_MIDDLE));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_SIDE", i32_to_js(MOUSE_BUTTON_SIDE));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_EXTRA", i32_to_js(MOUSE_BUTTON_EXTRA));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_FORWARD", i32_to_js(MOUSE_BUTTON_FORWARD));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_BACK", i32_to_js(MOUSE_BUTTON_BACK));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_DEFAULT", i32_to_js(MOUSE_CURSOR_DEFAULT));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_ARROW", i32_to_js(MOUSE_CURSOR_ARROW));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_IBEAM", i32_to_js(MOUSE_CURSOR_IBEAM));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_CROSSHAIR", i32_to_js(MOUSE_CURSOR_CROSSHAIR));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_POINTING_HAND", i32_to_js(MOUSE_CURSOR_POINTING_HAND));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_RESIZE_EW", i32_to_js(MOUSE_CURSOR_RESIZE_EW));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_RESIZE_NS", i32_to_js(MOUSE_CURSOR_RESIZE_NS));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_RESIZE_NWSE", i32_to_js(MOUSE_CURSOR_RESIZE_NWSE));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_RESIZE_NESW", i32_to_js(MOUSE_CURSOR_RESIZE_NESW));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_RESIZE_ALL", i32_to_js(MOUSE_CURSOR_RESIZE_ALL));
  JS_SetPropertyStr(ctx, global, "MOUSE_CURSOR_NOT_ALLOWED", i32_to_js(MOUSE_CURSOR_NOT_ALLOWED));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_UNKNOWN", i32_to_js(GAMEPAD_BUTTON_UNKNOWN));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT_FACE_UP", i32_to_js(GAMEPAD_BUTTON_LEFT_FACE_UP));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT_FACE_RIGHT", i32_to_js(GAMEPAD_BUTTON_LEFT_FACE_RIGHT));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT_FACE_DOWN", i32_to_js(GAMEPAD_BUTTON_LEFT_FACE_DOWN));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT_FACE_LEFT", i32_to_js(GAMEPAD_BUTTON_LEFT_FACE_LEFT));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT_FACE_UP", i32_to_js(GAMEPAD_BUTTON_RIGHT_FACE_UP));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT", i32_to_js(GAMEPAD_BUTTON_RIGHT_FACE_RIGHT));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT_FACE_DOWN", i32_to_js(GAMEPAD_BUTTON_RIGHT_FACE_DOWN));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT_FACE_LEFT", i32_to_js(GAMEPAD_BUTTON_RIGHT_FACE_LEFT));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT_TRIGGER_1", i32_to_js(GAMEPAD_BUTTON_LEFT_TRIGGER_1));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT_TRIGGER_2", i32_to_js(GAMEPAD_BUTTON_LEFT_TRIGGER_2));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT_TRIGGER_1", i32_to_js(GAMEPAD_BUTTON_RIGHT_TRIGGER_1));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT_TRIGGER_2", i32_to_js(GAMEPAD_BUTTON_RIGHT_TRIGGER_2));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_MIDDLE_LEFT", i32_to_js(GAMEPAD_BUTTON_MIDDLE_LEFT));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_MIDDLE", i32_to_js(GAMEPAD_BUTTON_MIDDLE));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_MIDDLE_RIGHT", i32_to_js(GAMEPAD_BUTTON_MIDDLE_RIGHT));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT_THUMB", i32_to_js(GAMEPAD_BUTTON_LEFT_THUMB));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT_THUMB", i32_to_js(GAMEPAD_BUTTON_RIGHT_THUMB));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_AXIS_LEFT_X", i32_to_js(GAMEPAD_AXIS_LEFT_X));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_AXIS_LEFT_Y", i32_to_js(GAMEPAD_AXIS_LEFT_Y));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_AXIS_RIGHT_X", i32_to_js(GAMEPAD_AXIS_RIGHT_X));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_AXIS_RIGHT_Y", i32_to_js(GAMEPAD_AXIS_RIGHT_Y));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_AXIS_LEFT_TRIGGER", i32_to_js(GAMEPAD_AXIS_LEFT_TRIGGER));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_AXIS_RIGHT_TRIGGER", i32_to_js(GAMEPAD_AXIS_RIGHT_TRIGGER));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_ALBEDO", i32_to_js(MATERIAL_MAP_ALBEDO));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_METALNESS", i32_to_js(MATERIAL_MAP_METALNESS));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_NORMAL", i32_to_js(MATERIAL_MAP_NORMAL));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_ROUGHNESS", i32_to_js(MATERIAL_MAP_ROUGHNESS));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_OCCLUSION", i32_to_js(MATERIAL_MAP_OCCLUSION));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_EMISSION", i32_to_js(MATERIAL_MAP_EMISSION));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_HEIGHT", i32_to_js(MATERIAL_MAP_HEIGHT));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_CUBEMAP", i32_to_js(MATERIAL_MAP_CUBEMAP));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_IRRADIANCE", i32_to_js(MATERIAL_MAP_IRRADIANCE));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_PREFILTER", i32_to_js(MATERIAL_MAP_PREFILTER));
  JS_SetPropertyStr(ctx, global, "MATERIAL_MAP_BRDF", i32_to_js(MATERIAL_MAP_BRDF));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_VERTEX_POSITION", i32_to_js(SHADER_LOC_VERTEX_POSITION));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_VERTEX_TEXCOORD01", i32_to_js(SHADER_LOC_VERTEX_TEXCOORD01));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_VERTEX_TEXCOORD02", i32_to_js(SHADER_LOC_VERTEX_TEXCOORD02));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_VERTEX_NORMAL", i32_to_js(SHADER_LOC_VERTEX_NORMAL));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_VERTEX_TANGENT", i32_to_js(SHADER_LOC_VERTEX_TANGENT));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_VERTEX_COLOR", i32_to_js(SHADER_LOC_VERTEX_COLOR));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MATRIX_MVP", i32_to_js(SHADER_LOC_MATRIX_MVP));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MATRIX_VIEW", i32_to_js(SHADER_LOC_MATRIX_VIEW));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MATRIX_PROJECTION", i32_to_js(SHADER_LOC_MATRIX_PROJECTION));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MATRIX_MODEL", i32_to_js(SHADER_LOC_MATRIX_MODEL));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MATRIX_NORMAL", i32_to_js(SHADER_LOC_MATRIX_NORMAL));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_VECTOR_VIEW", i32_to_js(SHADER_LOC_VECTOR_VIEW));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_COLOR_DIFFUSE", i32_to_js(SHADER_LOC_COLOR_DIFFUSE));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_COLOR_SPECULAR", i32_to_js(SHADER_LOC_COLOR_SPECULAR));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_COLOR_AMBIENT", i32_to_js(SHADER_LOC_COLOR_AMBIENT));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_ALBEDO", i32_to_js(SHADER_LOC_MAP_ALBEDO));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_METALNESS", i32_to_js(SHADER_LOC_MAP_METALNESS));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_NORMAL", i32_to_js(SHADER_LOC_MAP_NORMAL));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_ROUGHNESS", i32_to_js(SHADER_LOC_MAP_ROUGHNESS));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_OCCLUSION", i32_to_js(SHADER_LOC_MAP_OCCLUSION));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_EMISSION", i32_to_js(SHADER_LOC_MAP_EMISSION));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_HEIGHT", i32_to_js(SHADER_LOC_MAP_HEIGHT));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_CUBEMAP", i32_to_js(SHADER_LOC_MAP_CUBEMAP));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_IRRADIANCE", i32_to_js(SHADER_LOC_MAP_IRRADIANCE));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_PREFILTER", i32_to_js(SHADER_LOC_MAP_PREFILTER));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_MAP_BRDF", i32_to_js(SHADER_LOC_MAP_BRDF));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_VERTEX_BONEIDS", i32_to_js(SHADER_LOC_VERTEX_BONEIDS));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_VERTEX_BONEWEIGHTS", i32_to_js(SHADER_LOC_VERTEX_BONEWEIGHTS));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_BONE_MATRICES", i32_to_js(SHADER_LOC_BONE_MATRICES));
  JS_SetPropertyStr(ctx, global, "SHADER_LOC_VERTEX_INSTANCE_TX", i32_to_js(SHADER_LOC_VERTEX_INSTANCE_TX));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_FLOAT", i32_to_js(SHADER_UNIFORM_FLOAT));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_VEC2", i32_to_js(SHADER_UNIFORM_VEC2));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_VEC3", i32_to_js(SHADER_UNIFORM_VEC3));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_VEC4", i32_to_js(SHADER_UNIFORM_VEC4));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_INT", i32_to_js(SHADER_UNIFORM_INT));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_IVEC2", i32_to_js(SHADER_UNIFORM_IVEC2));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_IVEC3", i32_to_js(SHADER_UNIFORM_IVEC3));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_IVEC4", i32_to_js(SHADER_UNIFORM_IVEC4));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_UINT", i32_to_js(SHADER_UNIFORM_UINT));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_UIVEC2", i32_to_js(SHADER_UNIFORM_UIVEC2));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_UIVEC3", i32_to_js(SHADER_UNIFORM_UIVEC3));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_UIVEC4", i32_to_js(SHADER_UNIFORM_UIVEC4));
  JS_SetPropertyStr(ctx, global, "SHADER_UNIFORM_SAMPLER2D", i32_to_js(SHADER_UNIFORM_SAMPLER2D));
  JS_SetPropertyStr(ctx, global, "SHADER_ATTRIB_FLOAT", i32_to_js(SHADER_ATTRIB_FLOAT));
  JS_SetPropertyStr(ctx, global, "SHADER_ATTRIB_VEC2", i32_to_js(SHADER_ATTRIB_VEC2));
  JS_SetPropertyStr(ctx, global, "SHADER_ATTRIB_VEC3", i32_to_js(SHADER_ATTRIB_VEC3));
  JS_SetPropertyStr(ctx, global, "SHADER_ATTRIB_VEC4", i32_to_js(SHADER_ATTRIB_VEC4));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_GRAYSCALE", i32_to_js(PIXELFORMAT_UNCOMPRESSED_GRAYSCALE));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA", i32_to_js(PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R5G6B5", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R5G6B5));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R8G8B8", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R8G8B8));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R5G5B5A1", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R5G5B5A1));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R4G4B4A4", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R4G4B4A4));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R8G8B8A8", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R8G8B8A8));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R32", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R32));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R32G32B32", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R32G32B32));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R32G32B32A32", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R32G32B32A32));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R16", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R16));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R16G16B16", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R16G16B16));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_UNCOMPRESSED_R16G16B16A16", i32_to_js(PIXELFORMAT_UNCOMPRESSED_R16G16B16A16));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_DXT1_RGB", i32_to_js(PIXELFORMAT_COMPRESSED_DXT1_RGB));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_DXT1_RGBA", i32_to_js(PIXELFORMAT_COMPRESSED_DXT1_RGBA));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_DXT3_RGBA", i32_to_js(PIXELFORMAT_COMPRESSED_DXT3_RGBA));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_DXT5_RGBA", i32_to_js(PIXELFORMAT_COMPRESSED_DXT5_RGBA));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_ETC1_RGB", i32_to_js(PIXELFORMAT_COMPRESSED_ETC1_RGB));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_ETC2_RGB", i32_to_js(PIXELFORMAT_COMPRESSED_ETC2_RGB));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA", i32_to_js(PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_PVRT_RGB", i32_to_js(PIXELFORMAT_COMPRESSED_PVRT_RGB));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_PVRT_RGBA", i32_to_js(PIXELFORMAT_COMPRESSED_PVRT_RGBA));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA", i32_to_js(PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA));
  JS_SetPropertyStr(ctx, global, "PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA", i32_to_js(PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA));
  JS_SetPropertyStr(ctx, global, "TEXTURE_FILTER_POINT", i32_to_js(TEXTURE_FILTER_POINT));
  JS_SetPropertyStr(ctx, global, "TEXTURE_FILTER_BILINEAR", i32_to_js(TEXTURE_FILTER_BILINEAR));
  JS_SetPropertyStr(ctx, global, "TEXTURE_FILTER_TRILINEAR", i32_to_js(TEXTURE_FILTER_TRILINEAR));
  JS_SetPropertyStr(ctx, global, "TEXTURE_FILTER_ANISOTROPIC_4X", i32_to_js(TEXTURE_FILTER_ANISOTROPIC_4X));
  JS_SetPropertyStr(ctx, global, "TEXTURE_FILTER_ANISOTROPIC_8X", i32_to_js(TEXTURE_FILTER_ANISOTROPIC_8X));
  JS_SetPropertyStr(ctx, global, "TEXTURE_FILTER_ANISOTROPIC_16X", i32_to_js(TEXTURE_FILTER_ANISOTROPIC_16X));
  JS_SetPropertyStr(ctx, global, "TEXTURE_WRAP_REPEAT", i32_to_js(TEXTURE_WRAP_REPEAT));
  JS_SetPropertyStr(ctx, global, "TEXTURE_WRAP_CLAMP", i32_to_js(TEXTURE_WRAP_CLAMP));
  JS_SetPropertyStr(ctx, global, "TEXTURE_WRAP_MIRROR_REPEAT", i32_to_js(TEXTURE_WRAP_MIRROR_REPEAT));
  JS_SetPropertyStr(ctx, global, "TEXTURE_WRAP_MIRROR_CLAMP", i32_to_js(TEXTURE_WRAP_MIRROR_CLAMP));
  JS_SetPropertyStr(ctx, global, "CUBEMAP_LAYOUT_AUTO_DETECT", i32_to_js(CUBEMAP_LAYOUT_AUTO_DETECT));
  JS_SetPropertyStr(ctx, global, "CUBEMAP_LAYOUT_LINE_VERTICAL", i32_to_js(CUBEMAP_LAYOUT_LINE_VERTICAL));
  JS_SetPropertyStr(ctx, global, "CUBEMAP_LAYOUT_LINE_HORIZONTAL", i32_to_js(CUBEMAP_LAYOUT_LINE_HORIZONTAL));
  JS_SetPropertyStr(ctx, global, "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR", i32_to_js(CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR));
  JS_SetPropertyStr(ctx, global, "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE", i32_to_js(CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE));
  JS_SetPropertyStr(ctx, global, "FONT_DEFAULT", i32_to_js(FONT_DEFAULT));
  JS_SetPropertyStr(ctx, global, "FONT_BITMAP", i32_to_js(FONT_BITMAP));
  JS_SetPropertyStr(ctx, global, "FONT_SDF", i32_to_js(FONT_SDF));
  JS_SetPropertyStr(ctx, global, "BLEND_ALPHA", i32_to_js(BLEND_ALPHA));
  JS_SetPropertyStr(ctx, global, "BLEND_ADDITIVE", i32_to_js(BLEND_ADDITIVE));
  JS_SetPropertyStr(ctx, global, "BLEND_MULTIPLIED", i32_to_js(BLEND_MULTIPLIED));
  JS_SetPropertyStr(ctx, global, "BLEND_ADD_COLORS", i32_to_js(BLEND_ADD_COLORS));
  JS_SetPropertyStr(ctx, global, "BLEND_SUBTRACT_COLORS", i32_to_js(BLEND_SUBTRACT_COLORS));
  JS_SetPropertyStr(ctx, global, "BLEND_ALPHA_PREMULTIPLY", i32_to_js(BLEND_ALPHA_PREMULTIPLY));
  JS_SetPropertyStr(ctx, global, "BLEND_CUSTOM", i32_to_js(BLEND_CUSTOM));
  JS_SetPropertyStr(ctx, global, "BLEND_CUSTOM_SEPARATE", i32_to_js(BLEND_CUSTOM_SEPARATE));
  JS_SetPropertyStr(ctx, global, "GESTURE_NONE", i32_to_js(GESTURE_NONE));
  JS_SetPropertyStr(ctx, global, "GESTURE_TAP", i32_to_js(GESTURE_TAP));
  JS_SetPropertyStr(ctx, global, "GESTURE_DOUBLETAP", i32_to_js(GESTURE_DOUBLETAP));
  JS_SetPropertyStr(ctx, global, "GESTURE_HOLD", i32_to_js(GESTURE_HOLD));
  JS_SetPropertyStr(ctx, global, "GESTURE_DRAG", i32_to_js(GESTURE_DRAG));
  JS_SetPropertyStr(ctx, global, "GESTURE_SWIPE_RIGHT", i32_to_js(GESTURE_SWIPE_RIGHT));
  JS_SetPropertyStr(ctx, global, "GESTURE_SWIPE_LEFT", i32_to_js(GESTURE_SWIPE_LEFT));
  JS_SetPropertyStr(ctx, global, "GESTURE_SWIPE_UP", i32_to_js(GESTURE_SWIPE_UP));
  JS_SetPropertyStr(ctx, global, "GESTURE_SWIPE_DOWN", i32_to_js(GESTURE_SWIPE_DOWN));
  JS_SetPropertyStr(ctx, global, "GESTURE_PINCH_IN", i32_to_js(GESTURE_PINCH_IN));
  JS_SetPropertyStr(ctx, global, "GESTURE_PINCH_OUT", i32_to_js(GESTURE_PINCH_OUT));
  JS_SetPropertyStr(ctx, global, "CAMERA_CUSTOM", i32_to_js(CAMERA_CUSTOM));
  JS_SetPropertyStr(ctx, global, "CAMERA_FREE", i32_to_js(CAMERA_FREE));
  JS_SetPropertyStr(ctx, global, "CAMERA_ORBITAL", i32_to_js(CAMERA_ORBITAL));
  JS_SetPropertyStr(ctx, global, "CAMERA_FIRST_PERSON", i32_to_js(CAMERA_FIRST_PERSON));
  JS_SetPropertyStr(ctx, global, "CAMERA_THIRD_PERSON", i32_to_js(CAMERA_THIRD_PERSON));
  JS_SetPropertyStr(ctx, global, "CAMERA_PERSPECTIVE", i32_to_js(CAMERA_PERSPECTIVE));
  JS_SetPropertyStr(ctx, global, "CAMERA_ORTHOGRAPHIC", i32_to_js(CAMERA_ORTHOGRAPHIC));
  JS_SetPropertyStr(ctx, global, "NPATCH_NINE_PATCH", i32_to_js(NPATCH_NINE_PATCH));
  JS_SetPropertyStr(ctx, global, "NPATCH_THREE_PATCH_VERTICAL", i32_to_js(NPATCH_THREE_PATCH_VERTICAL));
  JS_SetPropertyStr(ctx, global, "NPATCH_THREE_PATCH_HORIZONTAL", i32_to_js(NPATCH_THREE_PATCH_HORIZONTAL));

  // Functions
  JS_SetPropertyStr(ctx, global, "InitWindow", JS_NewCFunction(ctx, js_InitWindow, "InitWindow", 3));
  JS_SetPropertyStr(ctx, global, "CloseWindow", JS_NewCFunction(ctx, js_CloseWindow, "CloseWindow", 0));
  JS_SetPropertyStr(ctx, global, "WindowShouldClose", JS_NewCFunction(ctx, js_WindowShouldClose, "WindowShouldClose", 0));
  JS_SetPropertyStr(ctx, global, "IsWindowReady", JS_NewCFunction(ctx, js_IsWindowReady, "IsWindowReady", 0));
  JS_SetPropertyStr(ctx, global, "IsWindowFullscreen", JS_NewCFunction(ctx, js_IsWindowFullscreen, "IsWindowFullscreen", 0));
  JS_SetPropertyStr(ctx, global, "IsWindowHidden", JS_NewCFunction(ctx, js_IsWindowHidden, "IsWindowHidden", 0));
  JS_SetPropertyStr(ctx, global, "IsWindowMinimized", JS_NewCFunction(ctx, js_IsWindowMinimized, "IsWindowMinimized", 0));
  JS_SetPropertyStr(ctx, global, "IsWindowMaximized", JS_NewCFunction(ctx, js_IsWindowMaximized, "IsWindowMaximized", 0));
  JS_SetPropertyStr(ctx, global, "IsWindowFocused", JS_NewCFunction(ctx, js_IsWindowFocused, "IsWindowFocused", 0));
  JS_SetPropertyStr(ctx, global, "IsWindowResized", JS_NewCFunction(ctx, js_IsWindowResized, "IsWindowResized", 0));
  JS_SetPropertyStr(ctx, global, "IsWindowState", JS_NewCFunction(ctx, js_IsWindowState, "IsWindowState", 1));
  JS_SetPropertyStr(ctx, global, "SetWindowState", JS_NewCFunction(ctx, js_SetWindowState, "SetWindowState", 1));
  JS_SetPropertyStr(ctx, global, "ClearWindowState", JS_NewCFunction(ctx, js_ClearWindowState, "ClearWindowState", 1));
  JS_SetPropertyStr(ctx, global, "ToggleFullscreen", JS_NewCFunction(ctx, js_ToggleFullscreen, "ToggleFullscreen", 0));
  JS_SetPropertyStr(ctx, global, "ToggleBorderlessWindowed", JS_NewCFunction(ctx, js_ToggleBorderlessWindowed, "ToggleBorderlessWindowed", 0));
  JS_SetPropertyStr(ctx, global, "MaximizeWindow", JS_NewCFunction(ctx, js_MaximizeWindow, "MaximizeWindow", 0));
  JS_SetPropertyStr(ctx, global, "MinimizeWindow", JS_NewCFunction(ctx, js_MinimizeWindow, "MinimizeWindow", 0));
  JS_SetPropertyStr(ctx, global, "RestoreWindow", JS_NewCFunction(ctx, js_RestoreWindow, "RestoreWindow", 0));
  JS_SetPropertyStr(ctx, global, "SetWindowIcon", JS_NewCFunction(ctx, js_SetWindowIcon, "SetWindowIcon", 1));
  JS_SetPropertyStr(ctx, global, "SetWindowTitle", JS_NewCFunction(ctx, js_SetWindowTitle, "SetWindowTitle", 1));
  JS_SetPropertyStr(ctx, global, "SetWindowPosition", JS_NewCFunction(ctx, js_SetWindowPosition, "SetWindowPosition", 2));
  JS_SetPropertyStr(ctx, global, "SetWindowMonitor", JS_NewCFunction(ctx, js_SetWindowMonitor, "SetWindowMonitor", 1));
  JS_SetPropertyStr(ctx, global, "SetWindowMinSize", JS_NewCFunction(ctx, js_SetWindowMinSize, "SetWindowMinSize", 2));
  JS_SetPropertyStr(ctx, global, "SetWindowMaxSize", JS_NewCFunction(ctx, js_SetWindowMaxSize, "SetWindowMaxSize", 2));
  JS_SetPropertyStr(ctx, global, "SetWindowSize", JS_NewCFunction(ctx, js_SetWindowSize, "SetWindowSize", 2));
  JS_SetPropertyStr(ctx, global, "SetWindowOpacity", JS_NewCFunction(ctx, js_SetWindowOpacity, "SetWindowOpacity", 1));
  JS_SetPropertyStr(ctx, global, "SetWindowFocused", JS_NewCFunction(ctx, js_SetWindowFocused, "SetWindowFocused", 0));
  JS_SetPropertyStr(ctx, global, "GetScreenWidth", JS_NewCFunction(ctx, js_GetScreenWidth, "GetScreenWidth", 0));
  JS_SetPropertyStr(ctx, global, "GetScreenHeight", JS_NewCFunction(ctx, js_GetScreenHeight, "GetScreenHeight", 0));
  JS_SetPropertyStr(ctx, global, "GetRenderWidth", JS_NewCFunction(ctx, js_GetRenderWidth, "GetRenderWidth", 0));
  JS_SetPropertyStr(ctx, global, "GetRenderHeight", JS_NewCFunction(ctx, js_GetRenderHeight, "GetRenderHeight", 0));
  JS_SetPropertyStr(ctx, global, "GetMonitorCount", JS_NewCFunction(ctx, js_GetMonitorCount, "GetMonitorCount", 0));
  JS_SetPropertyStr(ctx, global, "GetCurrentMonitor", JS_NewCFunction(ctx, js_GetCurrentMonitor, "GetCurrentMonitor", 0));
  JS_SetPropertyStr(ctx, global, "GetMonitorPosition", JS_NewCFunction(ctx, js_GetMonitorPosition, "GetMonitorPosition", 1));
  JS_SetPropertyStr(ctx, global, "GetMonitorWidth", JS_NewCFunction(ctx, js_GetMonitorWidth, "GetMonitorWidth", 1));
  JS_SetPropertyStr(ctx, global, "GetMonitorHeight", JS_NewCFunction(ctx, js_GetMonitorHeight, "GetMonitorHeight", 1));
  JS_SetPropertyStr(ctx, global, "GetMonitorPhysicalWidth", JS_NewCFunction(ctx, js_GetMonitorPhysicalWidth, "GetMonitorPhysicalWidth", 1));
  JS_SetPropertyStr(ctx, global, "GetMonitorPhysicalHeight", JS_NewCFunction(ctx, js_GetMonitorPhysicalHeight, "GetMonitorPhysicalHeight", 1));
  JS_SetPropertyStr(ctx, global, "GetMonitorRefreshRate", JS_NewCFunction(ctx, js_GetMonitorRefreshRate, "GetMonitorRefreshRate", 1));
  JS_SetPropertyStr(ctx, global, "GetWindowPosition", JS_NewCFunction(ctx, js_GetWindowPosition, "GetWindowPosition", 0));
  JS_SetPropertyStr(ctx, global, "GetWindowScaleDPI", JS_NewCFunction(ctx, js_GetWindowScaleDPI, "GetWindowScaleDPI", 0));
  JS_SetPropertyStr(ctx, global, "GetMonitorName", JS_NewCFunction(ctx, js_GetMonitorName, "GetMonitorName", 1));
  JS_SetPropertyStr(ctx, global, "SetClipboardText", JS_NewCFunction(ctx, js_SetClipboardText, "SetClipboardText", 1));
  JS_SetPropertyStr(ctx, global, "GetClipboardText", JS_NewCFunction(ctx, js_GetClipboardText, "GetClipboardText", 0));
  JS_SetPropertyStr(ctx, global, "EnableEventWaiting", JS_NewCFunction(ctx, js_EnableEventWaiting, "EnableEventWaiting", 0));
  JS_SetPropertyStr(ctx, global, "DisableEventWaiting", JS_NewCFunction(ctx, js_DisableEventWaiting, "DisableEventWaiting", 0));
  JS_SetPropertyStr(ctx, global, "ShowCursor", JS_NewCFunction(ctx, js_ShowCursor, "ShowCursor", 0));
  JS_SetPropertyStr(ctx, global, "HideCursor", JS_NewCFunction(ctx, js_HideCursor, "HideCursor", 0));
  JS_SetPropertyStr(ctx, global, "IsCursorHidden", JS_NewCFunction(ctx, js_IsCursorHidden, "IsCursorHidden", 0));
  JS_SetPropertyStr(ctx, global, "EnableCursor", JS_NewCFunction(ctx, js_EnableCursor, "EnableCursor", 0));
  JS_SetPropertyStr(ctx, global, "DisableCursor", JS_NewCFunction(ctx, js_DisableCursor, "DisableCursor", 0));
  JS_SetPropertyStr(ctx, global, "IsCursorOnScreen", JS_NewCFunction(ctx, js_IsCursorOnScreen, "IsCursorOnScreen", 0));
  JS_SetPropertyStr(ctx, global, "ClearBackground", JS_NewCFunction(ctx, js_ClearBackground, "ClearBackground", 1));
  JS_SetPropertyStr(ctx, global, "BeginDrawing", JS_NewCFunction(ctx, js_BeginDrawing, "BeginDrawing", 0));
  JS_SetPropertyStr(ctx, global, "EndDrawing", JS_NewCFunction(ctx, js_EndDrawing, "EndDrawing", 0));
  JS_SetPropertyStr(ctx, global, "BeginMode2D", JS_NewCFunction(ctx, js_BeginMode2D, "BeginMode2D", 1));
  JS_SetPropertyStr(ctx, global, "EndMode2D", JS_NewCFunction(ctx, js_EndMode2D, "EndMode2D", 0));
  JS_SetPropertyStr(ctx, global, "BeginMode3D", JS_NewCFunction(ctx, js_BeginMode3D, "BeginMode3D", 1));
  JS_SetPropertyStr(ctx, global, "EndMode3D", JS_NewCFunction(ctx, js_EndMode3D, "EndMode3D", 0));
  JS_SetPropertyStr(ctx, global, "BeginTextureMode", JS_NewCFunction(ctx, js_BeginTextureMode, "BeginTextureMode", 1));
  JS_SetPropertyStr(ctx, global, "EndTextureMode", JS_NewCFunction(ctx, js_EndTextureMode, "EndTextureMode", 0));
  JS_SetPropertyStr(ctx, global, "BeginShaderMode", JS_NewCFunction(ctx, js_BeginShaderMode, "BeginShaderMode", 1));
  JS_SetPropertyStr(ctx, global, "EndShaderMode", JS_NewCFunction(ctx, js_EndShaderMode, "EndShaderMode", 0));
  JS_SetPropertyStr(ctx, global, "BeginBlendMode", JS_NewCFunction(ctx, js_BeginBlendMode, "BeginBlendMode", 1));
  JS_SetPropertyStr(ctx, global, "EndBlendMode", JS_NewCFunction(ctx, js_EndBlendMode, "EndBlendMode", 0));
  JS_SetPropertyStr(ctx, global, "BeginScissorMode", JS_NewCFunction(ctx, js_BeginScissorMode, "BeginScissorMode", 4));
  JS_SetPropertyStr(ctx, global, "EndScissorMode", JS_NewCFunction(ctx, js_EndScissorMode, "EndScissorMode", 0));
  JS_SetPropertyStr(ctx, global, "BeginVrStereoMode", JS_NewCFunction(ctx, js_BeginVrStereoMode, "BeginVrStereoMode", 1));
  JS_SetPropertyStr(ctx, global, "EndVrStereoMode", JS_NewCFunction(ctx, js_EndVrStereoMode, "EndVrStereoMode", 0));
  JS_SetPropertyStr(ctx, global, "LoadVrStereoConfig", JS_NewCFunction(ctx, js_LoadVrStereoConfig, "LoadVrStereoConfig", 1));
  JS_SetPropertyStr(ctx, global, "UnloadVrStereoConfig", JS_NewCFunction(ctx, js_UnloadVrStereoConfig, "UnloadVrStereoConfig", 1));
  JS_SetPropertyStr(ctx, global, "LoadShader", JS_NewCFunction(ctx, js_LoadShader, "LoadShader", 2));
  JS_SetPropertyStr(ctx, global, "LoadShaderFromMemory", JS_NewCFunction(ctx, js_LoadShaderFromMemory, "LoadShaderFromMemory", 2));
  JS_SetPropertyStr(ctx, global, "IsShaderValid", JS_NewCFunction(ctx, js_IsShaderValid, "IsShaderValid", 1));
  JS_SetPropertyStr(ctx, global, "GetShaderLocation", JS_NewCFunction(ctx, js_GetShaderLocation, "GetShaderLocation", 2));
  JS_SetPropertyStr(ctx, global, "GetShaderLocationAttrib", JS_NewCFunction(ctx, js_GetShaderLocationAttrib, "GetShaderLocationAttrib", 2));
  JS_SetPropertyStr(ctx, global, "SetShaderValueMatrix", JS_NewCFunction(ctx, js_SetShaderValueMatrix, "SetShaderValueMatrix", 3));
  JS_SetPropertyStr(ctx, global, "SetShaderValueTexture", JS_NewCFunction(ctx, js_SetShaderValueTexture, "SetShaderValueTexture", 3));
  JS_SetPropertyStr(ctx, global, "UnloadShader", JS_NewCFunction(ctx, js_UnloadShader, "UnloadShader", 1));
  JS_SetPropertyStr(ctx, global, "GetScreenToWorldRay", JS_NewCFunction(ctx, js_GetScreenToWorldRay, "GetScreenToWorldRay", 2));
  JS_SetPropertyStr(ctx, global, "GetScreenToWorldRayEx", JS_NewCFunction(ctx, js_GetScreenToWorldRayEx, "GetScreenToWorldRayEx", 4));
  JS_SetPropertyStr(ctx, global, "GetWorldToScreen", JS_NewCFunction(ctx, js_GetWorldToScreen, "GetWorldToScreen", 2));
  JS_SetPropertyStr(ctx, global, "GetWorldToScreenEx", JS_NewCFunction(ctx, js_GetWorldToScreenEx, "GetWorldToScreenEx", 4));
  JS_SetPropertyStr(ctx, global, "GetWorldToScreen2D", JS_NewCFunction(ctx, js_GetWorldToScreen2D, "GetWorldToScreen2D", 2));
  JS_SetPropertyStr(ctx, global, "GetScreenToWorld2D", JS_NewCFunction(ctx, js_GetScreenToWorld2D, "GetScreenToWorld2D", 2));
  JS_SetPropertyStr(ctx, global, "GetCameraMatrix", JS_NewCFunction(ctx, js_GetCameraMatrix, "GetCameraMatrix", 1));
  JS_SetPropertyStr(ctx, global, "GetCameraMatrix2D", JS_NewCFunction(ctx, js_GetCameraMatrix2D, "GetCameraMatrix2D", 1));
  JS_SetPropertyStr(ctx, global, "SetTargetFPS", JS_NewCFunction(ctx, js_SetTargetFPS, "SetTargetFPS", 1));
  JS_SetPropertyStr(ctx, global, "GetFrameTime", JS_NewCFunction(ctx, js_GetFrameTime, "GetFrameTime", 0));
  JS_SetPropertyStr(ctx, global, "GetTime", JS_NewCFunction(ctx, js_GetTime, "GetTime", 0));
  JS_SetPropertyStr(ctx, global, "GetFPS", JS_NewCFunction(ctx, js_GetFPS, "GetFPS", 0));
  JS_SetPropertyStr(ctx, global, "SwapScreenBuffer", JS_NewCFunction(ctx, js_SwapScreenBuffer, "SwapScreenBuffer", 0));
  JS_SetPropertyStr(ctx, global, "PollInputEvents", JS_NewCFunction(ctx, js_PollInputEvents, "PollInputEvents", 0));
  JS_SetPropertyStr(ctx, global, "WaitTime", JS_NewCFunction(ctx, js_WaitTime, "WaitTime", 1));
  JS_SetPropertyStr(ctx, global, "SetRandomSeed", JS_NewCFunction(ctx, js_SetRandomSeed, "SetRandomSeed", 1));
  JS_SetPropertyStr(ctx, global, "GetRandomValue", JS_NewCFunction(ctx, js_GetRandomValue, "GetRandomValue", 2));
  JS_SetPropertyStr(ctx, global, "TakeScreenshot", JS_NewCFunction(ctx, js_TakeScreenshot, "TakeScreenshot", 1));
  JS_SetPropertyStr(ctx, global, "SetConfigFlags", JS_NewCFunction(ctx, js_SetConfigFlags, "SetConfigFlags", 1));
  JS_SetPropertyStr(ctx, global, "OpenURL", JS_NewCFunction(ctx, js_OpenURL, "OpenURL", 1));
  JS_SetPropertyStr(ctx, global, "SetTraceLogLevel", JS_NewCFunction(ctx, js_SetTraceLogLevel, "SetTraceLogLevel", 1));
  JS_SetPropertyStr(ctx, global, "UnloadFileData", JS_NewCFunction(ctx, js_UnloadFileData, "UnloadFileData", 1));
  JS_SetPropertyStr(ctx, global, "ExportDataAsCode", JS_NewCFunction(ctx, js_ExportDataAsCode, "ExportDataAsCode", 3));
  JS_SetPropertyStr(ctx, global, "LoadFileText", JS_NewCFunction(ctx, js_LoadFileText, "LoadFileText", 1));
  JS_SetPropertyStr(ctx, global, "UnloadFileText", JS_NewCFunction(ctx, js_UnloadFileText, "UnloadFileText", 1));
  JS_SetPropertyStr(ctx, global, "SaveFileText", JS_NewCFunction(ctx, js_SaveFileText, "SaveFileText", 2));
  JS_SetPropertyStr(ctx, global, "FileExists", JS_NewCFunction(ctx, js_FileExists, "FileExists", 1));
  JS_SetPropertyStr(ctx, global, "DirectoryExists", JS_NewCFunction(ctx, js_DirectoryExists, "DirectoryExists", 1));
  JS_SetPropertyStr(ctx, global, "IsFileExtension", JS_NewCFunction(ctx, js_IsFileExtension, "IsFileExtension", 2));
  JS_SetPropertyStr(ctx, global, "GetFileLength", JS_NewCFunction(ctx, js_GetFileLength, "GetFileLength", 1));
  JS_SetPropertyStr(ctx, global, "GetFileModTime", JS_NewCFunction(ctx, js_GetFileModTime, "GetFileModTime", 1));
  JS_SetPropertyStr(ctx, global, "GetFileExtension", JS_NewCFunction(ctx, js_GetFileExtension, "GetFileExtension", 1));
  JS_SetPropertyStr(ctx, global, "GetFileName", JS_NewCFunction(ctx, js_GetFileName, "GetFileName", 1));
  JS_SetPropertyStr(ctx, global, "GetFileNameWithoutExt", JS_NewCFunction(ctx, js_GetFileNameWithoutExt, "GetFileNameWithoutExt", 1));
  JS_SetPropertyStr(ctx, global, "GetDirectoryPath", JS_NewCFunction(ctx, js_GetDirectoryPath, "GetDirectoryPath", 1));
  JS_SetPropertyStr(ctx, global, "GetPrevDirectoryPath", JS_NewCFunction(ctx, js_GetPrevDirectoryPath, "GetPrevDirectoryPath", 1));
  JS_SetPropertyStr(ctx, global, "GetWorkingDirectory", JS_NewCFunction(ctx, js_GetWorkingDirectory, "GetWorkingDirectory", 0));
  JS_SetPropertyStr(ctx, global, "GetApplicationDirectory", JS_NewCFunction(ctx, js_GetApplicationDirectory, "GetApplicationDirectory", 0));
  JS_SetPropertyStr(ctx, global, "MakeDirectory", JS_NewCFunction(ctx, js_MakeDirectory, "MakeDirectory", 1));
  JS_SetPropertyStr(ctx, global, "ChangeDirectory", JS_NewCFunction(ctx, js_ChangeDirectory, "ChangeDirectory", 1));
  JS_SetPropertyStr(ctx, global, "IsPathFile", JS_NewCFunction(ctx, js_IsPathFile, "IsPathFile", 1));
  JS_SetPropertyStr(ctx, global, "IsFileNameValid", JS_NewCFunction(ctx, js_IsFileNameValid, "IsFileNameValid", 1));
  JS_SetPropertyStr(ctx, global, "LoadDirectoryFiles", JS_NewCFunction(ctx, js_LoadDirectoryFiles, "LoadDirectoryFiles", 1));
  JS_SetPropertyStr(ctx, global, "LoadDirectoryFilesEx", JS_NewCFunction(ctx, js_LoadDirectoryFilesEx, "LoadDirectoryFilesEx", 3));
  JS_SetPropertyStr(ctx, global, "UnloadDirectoryFiles", JS_NewCFunction(ctx, js_UnloadDirectoryFiles, "UnloadDirectoryFiles", 1));
  JS_SetPropertyStr(ctx, global, "IsFileDropped", JS_NewCFunction(ctx, js_IsFileDropped, "IsFileDropped", 0));
  JS_SetPropertyStr(ctx, global, "LoadDroppedFiles", JS_NewCFunction(ctx, js_LoadDroppedFiles, "LoadDroppedFiles", 0));
  JS_SetPropertyStr(ctx, global, "UnloadDroppedFiles", JS_NewCFunction(ctx, js_UnloadDroppedFiles, "UnloadDroppedFiles", 1));
  JS_SetPropertyStr(ctx, global, "ComputeCRC32", JS_NewCFunction(ctx, js_ComputeCRC32, "ComputeCRC32", 2));
  JS_SetPropertyStr(ctx, global, "LoadAutomationEventList", JS_NewCFunction(ctx, js_LoadAutomationEventList, "LoadAutomationEventList", 1));
  JS_SetPropertyStr(ctx, global, "UnloadAutomationEventList", JS_NewCFunction(ctx, js_UnloadAutomationEventList, "UnloadAutomationEventList", 1));
  JS_SetPropertyStr(ctx, global, "ExportAutomationEventList", JS_NewCFunction(ctx, js_ExportAutomationEventList, "ExportAutomationEventList", 2));
  JS_SetPropertyStr(ctx, global, "SetAutomationEventBaseFrame", JS_NewCFunction(ctx, js_SetAutomationEventBaseFrame, "SetAutomationEventBaseFrame", 1));
  JS_SetPropertyStr(ctx, global, "StartAutomationEventRecording", JS_NewCFunction(ctx, js_StartAutomationEventRecording, "StartAutomationEventRecording", 0));
  JS_SetPropertyStr(ctx, global, "StopAutomationEventRecording", JS_NewCFunction(ctx, js_StopAutomationEventRecording, "StopAutomationEventRecording", 0));
  JS_SetPropertyStr(ctx, global, "PlayAutomationEvent", JS_NewCFunction(ctx, js_PlayAutomationEvent, "PlayAutomationEvent", 1));
  JS_SetPropertyStr(ctx, global, "IsKeyPressed", JS_NewCFunction(ctx, js_IsKeyPressed, "IsKeyPressed", 1));
  JS_SetPropertyStr(ctx, global, "IsKeyPressedRepeat", JS_NewCFunction(ctx, js_IsKeyPressedRepeat, "IsKeyPressedRepeat", 1));
  JS_SetPropertyStr(ctx, global, "IsKeyDown", JS_NewCFunction(ctx, js_IsKeyDown, "IsKeyDown", 1));
  JS_SetPropertyStr(ctx, global, "IsKeyReleased", JS_NewCFunction(ctx, js_IsKeyReleased, "IsKeyReleased", 1));
  JS_SetPropertyStr(ctx, global, "IsKeyUp", JS_NewCFunction(ctx, js_IsKeyUp, "IsKeyUp", 1));
  JS_SetPropertyStr(ctx, global, "GetKeyPressed", JS_NewCFunction(ctx, js_GetKeyPressed, "GetKeyPressed", 0));
  JS_SetPropertyStr(ctx, global, "GetCharPressed", JS_NewCFunction(ctx, js_GetCharPressed, "GetCharPressed", 0));
  JS_SetPropertyStr(ctx, global, "GetKeyName", JS_NewCFunction(ctx, js_GetKeyName, "GetKeyName", 1));
  JS_SetPropertyStr(ctx, global, "SetExitKey", JS_NewCFunction(ctx, js_SetExitKey, "SetExitKey", 1));
  JS_SetPropertyStr(ctx, global, "IsGamepadAvailable", JS_NewCFunction(ctx, js_IsGamepadAvailable, "IsGamepadAvailable", 1));
  JS_SetPropertyStr(ctx, global, "GetGamepadName", JS_NewCFunction(ctx, js_GetGamepadName, "GetGamepadName", 1));
  JS_SetPropertyStr(ctx, global, "IsGamepadButtonPressed", JS_NewCFunction(ctx, js_IsGamepadButtonPressed, "IsGamepadButtonPressed", 2));
  JS_SetPropertyStr(ctx, global, "IsGamepadButtonDown", JS_NewCFunction(ctx, js_IsGamepadButtonDown, "IsGamepadButtonDown", 2));
  JS_SetPropertyStr(ctx, global, "IsGamepadButtonReleased", JS_NewCFunction(ctx, js_IsGamepadButtonReleased, "IsGamepadButtonReleased", 2));
  JS_SetPropertyStr(ctx, global, "IsGamepadButtonUp", JS_NewCFunction(ctx, js_IsGamepadButtonUp, "IsGamepadButtonUp", 2));
  JS_SetPropertyStr(ctx, global, "GetGamepadButtonPressed", JS_NewCFunction(ctx, js_GetGamepadButtonPressed, "GetGamepadButtonPressed", 0));
  JS_SetPropertyStr(ctx, global, "GetGamepadAxisCount", JS_NewCFunction(ctx, js_GetGamepadAxisCount, "GetGamepadAxisCount", 1));
  JS_SetPropertyStr(ctx, global, "GetGamepadAxisMovement", JS_NewCFunction(ctx, js_GetGamepadAxisMovement, "GetGamepadAxisMovement", 2));
  JS_SetPropertyStr(ctx, global, "SetGamepadMappings", JS_NewCFunction(ctx, js_SetGamepadMappings, "SetGamepadMappings", 1));
  JS_SetPropertyStr(ctx, global, "SetGamepadVibration", JS_NewCFunction(ctx, js_SetGamepadVibration, "SetGamepadVibration", 4));
  JS_SetPropertyStr(ctx, global, "IsMouseButtonPressed", JS_NewCFunction(ctx, js_IsMouseButtonPressed, "IsMouseButtonPressed", 1));
  JS_SetPropertyStr(ctx, global, "IsMouseButtonDown", JS_NewCFunction(ctx, js_IsMouseButtonDown, "IsMouseButtonDown", 1));
  JS_SetPropertyStr(ctx, global, "IsMouseButtonReleased", JS_NewCFunction(ctx, js_IsMouseButtonReleased, "IsMouseButtonReleased", 1));
  JS_SetPropertyStr(ctx, global, "IsMouseButtonUp", JS_NewCFunction(ctx, js_IsMouseButtonUp, "IsMouseButtonUp", 1));
  JS_SetPropertyStr(ctx, global, "GetMouseX", JS_NewCFunction(ctx, js_GetMouseX, "GetMouseX", 0));
  JS_SetPropertyStr(ctx, global, "GetMouseY", JS_NewCFunction(ctx, js_GetMouseY, "GetMouseY", 0));
  JS_SetPropertyStr(ctx, global, "GetMousePosition", JS_NewCFunction(ctx, js_GetMousePosition, "GetMousePosition", 0));
  JS_SetPropertyStr(ctx, global, "GetMouseDelta", JS_NewCFunction(ctx, js_GetMouseDelta, "GetMouseDelta", 0));
  JS_SetPropertyStr(ctx, global, "SetMousePosition", JS_NewCFunction(ctx, js_SetMousePosition, "SetMousePosition", 2));
  JS_SetPropertyStr(ctx, global, "SetMouseOffset", JS_NewCFunction(ctx, js_SetMouseOffset, "SetMouseOffset", 2));
  JS_SetPropertyStr(ctx, global, "SetMouseScale", JS_NewCFunction(ctx, js_SetMouseScale, "SetMouseScale", 2));
  JS_SetPropertyStr(ctx, global, "GetMouseWheelMove", JS_NewCFunction(ctx, js_GetMouseWheelMove, "GetMouseWheelMove", 0));
  JS_SetPropertyStr(ctx, global, "GetMouseWheelMoveV", JS_NewCFunction(ctx, js_GetMouseWheelMoveV, "GetMouseWheelMoveV", 0));
  JS_SetPropertyStr(ctx, global, "SetMouseCursor", JS_NewCFunction(ctx, js_SetMouseCursor, "SetMouseCursor", 1));
  JS_SetPropertyStr(ctx, global, "GetTouchX", JS_NewCFunction(ctx, js_GetTouchX, "GetTouchX", 0));
  JS_SetPropertyStr(ctx, global, "GetTouchY", JS_NewCFunction(ctx, js_GetTouchY, "GetTouchY", 0));
  JS_SetPropertyStr(ctx, global, "GetTouchPosition", JS_NewCFunction(ctx, js_GetTouchPosition, "GetTouchPosition", 1));
  JS_SetPropertyStr(ctx, global, "GetTouchPointId", JS_NewCFunction(ctx, js_GetTouchPointId, "GetTouchPointId", 1));
  JS_SetPropertyStr(ctx, global, "GetTouchPointCount", JS_NewCFunction(ctx, js_GetTouchPointCount, "GetTouchPointCount", 0));
  JS_SetPropertyStr(ctx, global, "SetGesturesEnabled", JS_NewCFunction(ctx, js_SetGesturesEnabled, "SetGesturesEnabled", 1));
  JS_SetPropertyStr(ctx, global, "IsGestureDetected", JS_NewCFunction(ctx, js_IsGestureDetected, "IsGestureDetected", 1));
  JS_SetPropertyStr(ctx, global, "GetGestureDetected", JS_NewCFunction(ctx, js_GetGestureDetected, "GetGestureDetected", 0));
  JS_SetPropertyStr(ctx, global, "GetGestureHoldDuration", JS_NewCFunction(ctx, js_GetGestureHoldDuration, "GetGestureHoldDuration", 0));
  JS_SetPropertyStr(ctx, global, "GetGestureDragVector", JS_NewCFunction(ctx, js_GetGestureDragVector, "GetGestureDragVector", 0));
  JS_SetPropertyStr(ctx, global, "GetGestureDragAngle", JS_NewCFunction(ctx, js_GetGestureDragAngle, "GetGestureDragAngle", 0));
  JS_SetPropertyStr(ctx, global, "GetGesturePinchVector", JS_NewCFunction(ctx, js_GetGesturePinchVector, "GetGesturePinchVector", 0));
  JS_SetPropertyStr(ctx, global, "GetGesturePinchAngle", JS_NewCFunction(ctx, js_GetGesturePinchAngle, "GetGesturePinchAngle", 0));
  JS_SetPropertyStr(ctx, global, "SetShapesTexture", JS_NewCFunction(ctx, js_SetShapesTexture, "SetShapesTexture", 2));
  JS_SetPropertyStr(ctx, global, "GetShapesTexture", JS_NewCFunction(ctx, js_GetShapesTexture, "GetShapesTexture", 0));
  JS_SetPropertyStr(ctx, global, "GetShapesTextureRectangle", JS_NewCFunction(ctx, js_GetShapesTextureRectangle, "GetShapesTextureRectangle", 0));
  JS_SetPropertyStr(ctx, global, "DrawPixel", JS_NewCFunction(ctx, js_DrawPixel, "DrawPixel", 3));
  JS_SetPropertyStr(ctx, global, "DrawPixelV", JS_NewCFunction(ctx, js_DrawPixelV, "DrawPixelV", 2));
  JS_SetPropertyStr(ctx, global, "DrawLine", JS_NewCFunction(ctx, js_DrawLine, "DrawLine", 5));
  JS_SetPropertyStr(ctx, global, "DrawLineV", JS_NewCFunction(ctx, js_DrawLineV, "DrawLineV", 3));
  JS_SetPropertyStr(ctx, global, "DrawLineEx", JS_NewCFunction(ctx, js_DrawLineEx, "DrawLineEx", 4));
  JS_SetPropertyStr(ctx, global, "DrawLineBezier", JS_NewCFunction(ctx, js_DrawLineBezier, "DrawLineBezier", 4));
  JS_SetPropertyStr(ctx, global, "DrawCircle", JS_NewCFunction(ctx, js_DrawCircle, "DrawCircle", 4));
  JS_SetPropertyStr(ctx, global, "DrawCircleSector", JS_NewCFunction(ctx, js_DrawCircleSector, "DrawCircleSector", 6));
  JS_SetPropertyStr(ctx, global, "DrawCircleSectorLines", JS_NewCFunction(ctx, js_DrawCircleSectorLines, "DrawCircleSectorLines", 6));
  JS_SetPropertyStr(ctx, global, "DrawCircleGradient", JS_NewCFunction(ctx, js_DrawCircleGradient, "DrawCircleGradient", 5));
  JS_SetPropertyStr(ctx, global, "DrawCircleV", JS_NewCFunction(ctx, js_DrawCircleV, "DrawCircleV", 3));
  JS_SetPropertyStr(ctx, global, "DrawCircleLines", JS_NewCFunction(ctx, js_DrawCircleLines, "DrawCircleLines", 4));
  JS_SetPropertyStr(ctx, global, "DrawCircleLinesV", JS_NewCFunction(ctx, js_DrawCircleLinesV, "DrawCircleLinesV", 3));
  JS_SetPropertyStr(ctx, global, "DrawEllipse", JS_NewCFunction(ctx, js_DrawEllipse, "DrawEllipse", 5));
  JS_SetPropertyStr(ctx, global, "DrawEllipseLines", JS_NewCFunction(ctx, js_DrawEllipseLines, "DrawEllipseLines", 5));
  JS_SetPropertyStr(ctx, global, "DrawRing", JS_NewCFunction(ctx, js_DrawRing, "DrawRing", 7));
  JS_SetPropertyStr(ctx, global, "DrawRingLines", JS_NewCFunction(ctx, js_DrawRingLines, "DrawRingLines", 7));
  JS_SetPropertyStr(ctx, global, "DrawRectangle", JS_NewCFunction(ctx, js_DrawRectangle, "DrawRectangle", 5));
  JS_SetPropertyStr(ctx, global, "DrawRectangleV", JS_NewCFunction(ctx, js_DrawRectangleV, "DrawRectangleV", 3));
  JS_SetPropertyStr(ctx, global, "DrawRectangleRec", JS_NewCFunction(ctx, js_DrawRectangleRec, "DrawRectangleRec", 2));
  JS_SetPropertyStr(ctx, global, "DrawRectanglePro", JS_NewCFunction(ctx, js_DrawRectanglePro, "DrawRectanglePro", 4));
  JS_SetPropertyStr(ctx, global, "DrawRectangleGradientV", JS_NewCFunction(ctx, js_DrawRectangleGradientV, "DrawRectangleGradientV", 6));
  JS_SetPropertyStr(ctx, global, "DrawRectangleGradientH", JS_NewCFunction(ctx, js_DrawRectangleGradientH, "DrawRectangleGradientH", 6));
  JS_SetPropertyStr(ctx, global, "DrawRectangleGradientEx", JS_NewCFunction(ctx, js_DrawRectangleGradientEx, "DrawRectangleGradientEx", 5));
  JS_SetPropertyStr(ctx, global, "DrawRectangleLines", JS_NewCFunction(ctx, js_DrawRectangleLines, "DrawRectangleLines", 5));
  JS_SetPropertyStr(ctx, global, "DrawRectangleLinesEx", JS_NewCFunction(ctx, js_DrawRectangleLinesEx, "DrawRectangleLinesEx", 3));
  JS_SetPropertyStr(ctx, global, "DrawRectangleRounded", JS_NewCFunction(ctx, js_DrawRectangleRounded, "DrawRectangleRounded", 4));
  JS_SetPropertyStr(ctx, global, "DrawRectangleRoundedLines", JS_NewCFunction(ctx, js_DrawRectangleRoundedLines, "DrawRectangleRoundedLines", 4));
  JS_SetPropertyStr(ctx, global, "DrawRectangleRoundedLinesEx", JS_NewCFunction(ctx, js_DrawRectangleRoundedLinesEx, "DrawRectangleRoundedLinesEx", 5));
  JS_SetPropertyStr(ctx, global, "DrawTriangle", JS_NewCFunction(ctx, js_DrawTriangle, "DrawTriangle", 4));
  JS_SetPropertyStr(ctx, global, "DrawTriangleLines", JS_NewCFunction(ctx, js_DrawTriangleLines, "DrawTriangleLines", 4));
  JS_SetPropertyStr(ctx, global, "DrawPoly", JS_NewCFunction(ctx, js_DrawPoly, "DrawPoly", 5));
  JS_SetPropertyStr(ctx, global, "DrawPolyLines", JS_NewCFunction(ctx, js_DrawPolyLines, "DrawPolyLines", 5));
  JS_SetPropertyStr(ctx, global, "DrawPolyLinesEx", JS_NewCFunction(ctx, js_DrawPolyLinesEx, "DrawPolyLinesEx", 6));
  JS_SetPropertyStr(ctx, global, "DrawSplineSegmentLinear", JS_NewCFunction(ctx, js_DrawSplineSegmentLinear, "DrawSplineSegmentLinear", 4));
  JS_SetPropertyStr(ctx, global, "DrawSplineSegmentBasis", JS_NewCFunction(ctx, js_DrawSplineSegmentBasis, "DrawSplineSegmentBasis", 6));
  JS_SetPropertyStr(ctx, global, "DrawSplineSegmentCatmullRom", JS_NewCFunction(ctx, js_DrawSplineSegmentCatmullRom, "DrawSplineSegmentCatmullRom", 6));
  JS_SetPropertyStr(ctx, global, "DrawSplineSegmentBezierQuadratic", JS_NewCFunction(ctx, js_DrawSplineSegmentBezierQuadratic, "DrawSplineSegmentBezierQuadratic", 5));
  JS_SetPropertyStr(ctx, global, "DrawSplineSegmentBezierCubic", JS_NewCFunction(ctx, js_DrawSplineSegmentBezierCubic, "DrawSplineSegmentBezierCubic", 6));
  JS_SetPropertyStr(ctx, global, "GetSplinePointLinear", JS_NewCFunction(ctx, js_GetSplinePointLinear, "GetSplinePointLinear", 3));
  JS_SetPropertyStr(ctx, global, "GetSplinePointBasis", JS_NewCFunction(ctx, js_GetSplinePointBasis, "GetSplinePointBasis", 5));
  JS_SetPropertyStr(ctx, global, "GetSplinePointCatmullRom", JS_NewCFunction(ctx, js_GetSplinePointCatmullRom, "GetSplinePointCatmullRom", 5));
  JS_SetPropertyStr(ctx, global, "GetSplinePointBezierQuad", JS_NewCFunction(ctx, js_GetSplinePointBezierQuad, "GetSplinePointBezierQuad", 4));
  JS_SetPropertyStr(ctx, global, "GetSplinePointBezierCubic", JS_NewCFunction(ctx, js_GetSplinePointBezierCubic, "GetSplinePointBezierCubic", 5));
  JS_SetPropertyStr(ctx, global, "CheckCollisionRecs", JS_NewCFunction(ctx, js_CheckCollisionRecs, "CheckCollisionRecs", 2));
  JS_SetPropertyStr(ctx, global, "CheckCollisionCircles", JS_NewCFunction(ctx, js_CheckCollisionCircles, "CheckCollisionCircles", 4));
  JS_SetPropertyStr(ctx, global, "CheckCollisionCircleRec", JS_NewCFunction(ctx, js_CheckCollisionCircleRec, "CheckCollisionCircleRec", 3));
  JS_SetPropertyStr(ctx, global, "CheckCollisionCircleLine", JS_NewCFunction(ctx, js_CheckCollisionCircleLine, "CheckCollisionCircleLine", 4));
  JS_SetPropertyStr(ctx, global, "CheckCollisionPointRec", JS_NewCFunction(ctx, js_CheckCollisionPointRec, "CheckCollisionPointRec", 2));
  JS_SetPropertyStr(ctx, global, "CheckCollisionPointCircle", JS_NewCFunction(ctx, js_CheckCollisionPointCircle, "CheckCollisionPointCircle", 3));
  JS_SetPropertyStr(ctx, global, "CheckCollisionPointTriangle", JS_NewCFunction(ctx, js_CheckCollisionPointTriangle, "CheckCollisionPointTriangle", 4));
  JS_SetPropertyStr(ctx, global, "CheckCollisionPointLine", JS_NewCFunction(ctx, js_CheckCollisionPointLine, "CheckCollisionPointLine", 4));
  JS_SetPropertyStr(ctx, global, "GetCollisionRec", JS_NewCFunction(ctx, js_GetCollisionRec, "GetCollisionRec", 2));
  JS_SetPropertyStr(ctx, global, "LoadImage", JS_NewCFunction(ctx, js_LoadImage, "LoadImage", 1));
  JS_SetPropertyStr(ctx, global, "LoadImageRaw", JS_NewCFunction(ctx, js_LoadImageRaw, "LoadImageRaw", 5));
  JS_SetPropertyStr(ctx, global, "LoadImageFromMemory", JS_NewCFunction(ctx, js_LoadImageFromMemory, "LoadImageFromMemory", 3));
  JS_SetPropertyStr(ctx, global, "LoadImageFromTexture", JS_NewCFunction(ctx, js_LoadImageFromTexture, "LoadImageFromTexture", 1));
  JS_SetPropertyStr(ctx, global, "LoadImageFromScreen", JS_NewCFunction(ctx, js_LoadImageFromScreen, "LoadImageFromScreen", 0));
  JS_SetPropertyStr(ctx, global, "IsImageValid", JS_NewCFunction(ctx, js_IsImageValid, "IsImageValid", 1));
  JS_SetPropertyStr(ctx, global, "UnloadImage", JS_NewCFunction(ctx, js_UnloadImage, "UnloadImage", 1));
  JS_SetPropertyStr(ctx, global, "ExportImage", JS_NewCFunction(ctx, js_ExportImage, "ExportImage", 2));
  JS_SetPropertyStr(ctx, global, "ExportImageAsCode", JS_NewCFunction(ctx, js_ExportImageAsCode, "ExportImageAsCode", 2));
  JS_SetPropertyStr(ctx, global, "GenImageColor", JS_NewCFunction(ctx, js_GenImageColor, "GenImageColor", 3));
  JS_SetPropertyStr(ctx, global, "GenImageGradientLinear", JS_NewCFunction(ctx, js_GenImageGradientLinear, "GenImageGradientLinear", 5));
  JS_SetPropertyStr(ctx, global, "GenImageGradientRadial", JS_NewCFunction(ctx, js_GenImageGradientRadial, "GenImageGradientRadial", 5));
  JS_SetPropertyStr(ctx, global, "GenImageGradientSquare", JS_NewCFunction(ctx, js_GenImageGradientSquare, "GenImageGradientSquare", 5));
  JS_SetPropertyStr(ctx, global, "GenImageChecked", JS_NewCFunction(ctx, js_GenImageChecked, "GenImageChecked", 6));
  JS_SetPropertyStr(ctx, global, "GenImageWhiteNoise", JS_NewCFunction(ctx, js_GenImageWhiteNoise, "GenImageWhiteNoise", 3));
  JS_SetPropertyStr(ctx, global, "GenImagePerlinNoise", JS_NewCFunction(ctx, js_GenImagePerlinNoise, "GenImagePerlinNoise", 5));
  JS_SetPropertyStr(ctx, global, "GenImageCellular", JS_NewCFunction(ctx, js_GenImageCellular, "GenImageCellular", 3));
  JS_SetPropertyStr(ctx, global, "GenImageText", JS_NewCFunction(ctx, js_GenImageText, "GenImageText", 3));
  JS_SetPropertyStr(ctx, global, "ImageCopy", JS_NewCFunction(ctx, js_ImageCopy, "ImageCopy", 1));
  JS_SetPropertyStr(ctx, global, "ImageFromImage", JS_NewCFunction(ctx, js_ImageFromImage, "ImageFromImage", 2));
  JS_SetPropertyStr(ctx, global, "ImageFromChannel", JS_NewCFunction(ctx, js_ImageFromChannel, "ImageFromChannel", 2));
  JS_SetPropertyStr(ctx, global, "ImageText", JS_NewCFunction(ctx, js_ImageText, "ImageText", 3));
  JS_SetPropertyStr(ctx, global, "ImageTextEx", JS_NewCFunction(ctx, js_ImageTextEx, "ImageTextEx", 5));
  JS_SetPropertyStr(ctx, global, "GetImageAlphaBorder", JS_NewCFunction(ctx, js_GetImageAlphaBorder, "GetImageAlphaBorder", 2));
  JS_SetPropertyStr(ctx, global, "GetImageColor", JS_NewCFunction(ctx, js_GetImageColor, "GetImageColor", 3));
  JS_SetPropertyStr(ctx, global, "LoadTexture", JS_NewCFunction(ctx, js_LoadTexture, "LoadTexture", 1));
  JS_SetPropertyStr(ctx, global, "LoadTextureFromImage", JS_NewCFunction(ctx, js_LoadTextureFromImage, "LoadTextureFromImage", 1));
  JS_SetPropertyStr(ctx, global, "LoadTextureCubemap", JS_NewCFunction(ctx, js_LoadTextureCubemap, "LoadTextureCubemap", 2));
  JS_SetPropertyStr(ctx, global, "LoadRenderTexture", JS_NewCFunction(ctx, js_LoadRenderTexture, "LoadRenderTexture", 2));
  JS_SetPropertyStr(ctx, global, "IsTextureValid", JS_NewCFunction(ctx, js_IsTextureValid, "IsTextureValid", 1));
  JS_SetPropertyStr(ctx, global, "UnloadTexture", JS_NewCFunction(ctx, js_UnloadTexture, "UnloadTexture", 1));
  JS_SetPropertyStr(ctx, global, "IsRenderTextureValid", JS_NewCFunction(ctx, js_IsRenderTextureValid, "IsRenderTextureValid", 1));
  JS_SetPropertyStr(ctx, global, "UnloadRenderTexture", JS_NewCFunction(ctx, js_UnloadRenderTexture, "UnloadRenderTexture", 1));
  JS_SetPropertyStr(ctx, global, "SetTextureFilter", JS_NewCFunction(ctx, js_SetTextureFilter, "SetTextureFilter", 2));
  JS_SetPropertyStr(ctx, global, "SetTextureWrap", JS_NewCFunction(ctx, js_SetTextureWrap, "SetTextureWrap", 2));
  JS_SetPropertyStr(ctx, global, "DrawTexture", JS_NewCFunction(ctx, js_DrawTexture, "DrawTexture", 4));
  JS_SetPropertyStr(ctx, global, "DrawTextureV", JS_NewCFunction(ctx, js_DrawTextureV, "DrawTextureV", 3));
  JS_SetPropertyStr(ctx, global, "DrawTextureEx", JS_NewCFunction(ctx, js_DrawTextureEx, "DrawTextureEx", 5));
  JS_SetPropertyStr(ctx, global, "DrawTextureRec", JS_NewCFunction(ctx, js_DrawTextureRec, "DrawTextureRec", 4));
  JS_SetPropertyStr(ctx, global, "DrawTexturePro", JS_NewCFunction(ctx, js_DrawTexturePro, "DrawTexturePro", 6));
  JS_SetPropertyStr(ctx, global, "DrawTextureNPatch", JS_NewCFunction(ctx, js_DrawTextureNPatch, "DrawTextureNPatch", 6));
  JS_SetPropertyStr(ctx, global, "ColorIsEqual", JS_NewCFunction(ctx, js_ColorIsEqual, "ColorIsEqual", 2));
  JS_SetPropertyStr(ctx, global, "Fade", JS_NewCFunction(ctx, js_Fade, "Fade", 2));
  JS_SetPropertyStr(ctx, global, "ColorToInt", JS_NewCFunction(ctx, js_ColorToInt, "ColorToInt", 1));
  JS_SetPropertyStr(ctx, global, "ColorNormalize", JS_NewCFunction(ctx, js_ColorNormalize, "ColorNormalize", 1));
  JS_SetPropertyStr(ctx, global, "ColorFromNormalized", JS_NewCFunction(ctx, js_ColorFromNormalized, "ColorFromNormalized", 1));
  JS_SetPropertyStr(ctx, global, "ColorToHSV", JS_NewCFunction(ctx, js_ColorToHSV, "ColorToHSV", 1));
  JS_SetPropertyStr(ctx, global, "ColorFromHSV", JS_NewCFunction(ctx, js_ColorFromHSV, "ColorFromHSV", 3));
  JS_SetPropertyStr(ctx, global, "ColorTint", JS_NewCFunction(ctx, js_ColorTint, "ColorTint", 2));
  JS_SetPropertyStr(ctx, global, "ColorBrightness", JS_NewCFunction(ctx, js_ColorBrightness, "ColorBrightness", 2));
  JS_SetPropertyStr(ctx, global, "ColorContrast", JS_NewCFunction(ctx, js_ColorContrast, "ColorContrast", 2));
  JS_SetPropertyStr(ctx, global, "ColorAlpha", JS_NewCFunction(ctx, js_ColorAlpha, "ColorAlpha", 2));
  JS_SetPropertyStr(ctx, global, "ColorAlphaBlend", JS_NewCFunction(ctx, js_ColorAlphaBlend, "ColorAlphaBlend", 3));
  JS_SetPropertyStr(ctx, global, "ColorLerp", JS_NewCFunction(ctx, js_ColorLerp, "ColorLerp", 3));
  JS_SetPropertyStr(ctx, global, "GetColor", JS_NewCFunction(ctx, js_GetColor, "GetColor", 1));
  JS_SetPropertyStr(ctx, global, "GetPixelDataSize", JS_NewCFunction(ctx, js_GetPixelDataSize, "GetPixelDataSize", 3));
  JS_SetPropertyStr(ctx, global, "GetFontDefault", JS_NewCFunction(ctx, js_GetFontDefault, "GetFontDefault", 0));
  JS_SetPropertyStr(ctx, global, "LoadFont", JS_NewCFunction(ctx, js_LoadFont, "LoadFont", 1));
  JS_SetPropertyStr(ctx, global, "LoadFontFromImage", JS_NewCFunction(ctx, js_LoadFontFromImage, "LoadFontFromImage", 3));
  JS_SetPropertyStr(ctx, global, "IsFontValid", JS_NewCFunction(ctx, js_IsFontValid, "IsFontValid", 1));
  JS_SetPropertyStr(ctx, global, "UnloadFont", JS_NewCFunction(ctx, js_UnloadFont, "UnloadFont", 1));
  JS_SetPropertyStr(ctx, global, "ExportFontAsCode", JS_NewCFunction(ctx, js_ExportFontAsCode, "ExportFontAsCode", 2));
  JS_SetPropertyStr(ctx, global, "DrawFPS", JS_NewCFunction(ctx, js_DrawFPS, "DrawFPS", 2));
  JS_SetPropertyStr(ctx, global, "DrawText", JS_NewCFunction(ctx, js_DrawText, "DrawText", 5));
  JS_SetPropertyStr(ctx, global, "DrawTextEx", JS_NewCFunction(ctx, js_DrawTextEx, "DrawTextEx", 6));
  JS_SetPropertyStr(ctx, global, "DrawTextPro", JS_NewCFunction(ctx, js_DrawTextPro, "DrawTextPro", 8));
  JS_SetPropertyStr(ctx, global, "DrawTextCodepoint", JS_NewCFunction(ctx, js_DrawTextCodepoint, "DrawTextCodepoint", 5));
  JS_SetPropertyStr(ctx, global, "SetTextLineSpacing", JS_NewCFunction(ctx, js_SetTextLineSpacing, "SetTextLineSpacing", 1));
  JS_SetPropertyStr(ctx, global, "MeasureText", JS_NewCFunction(ctx, js_MeasureText, "MeasureText", 2));
  JS_SetPropertyStr(ctx, global, "MeasureTextEx", JS_NewCFunction(ctx, js_MeasureTextEx, "MeasureTextEx", 4));
  JS_SetPropertyStr(ctx, global, "GetGlyphIndex", JS_NewCFunction(ctx, js_GetGlyphIndex, "GetGlyphIndex", 2));
  JS_SetPropertyStr(ctx, global, "GetGlyphInfo", JS_NewCFunction(ctx, js_GetGlyphInfo, "GetGlyphInfo", 2));
  JS_SetPropertyStr(ctx, global, "GetGlyphAtlasRec", JS_NewCFunction(ctx, js_GetGlyphAtlasRec, "GetGlyphAtlasRec", 2));
  JS_SetPropertyStr(ctx, global, "UnloadUTF8", JS_NewCFunction(ctx, js_UnloadUTF8, "UnloadUTF8", 1));
  JS_SetPropertyStr(ctx, global, "GetCodepointCount", JS_NewCFunction(ctx, js_GetCodepointCount, "GetCodepointCount", 1));
  JS_SetPropertyStr(ctx, global, "TextCopy", JS_NewCFunction(ctx, js_TextCopy, "TextCopy", 2));
  JS_SetPropertyStr(ctx, global, "TextIsEqual", JS_NewCFunction(ctx, js_TextIsEqual, "TextIsEqual", 2));
  JS_SetPropertyStr(ctx, global, "TextLength", JS_NewCFunction(ctx, js_TextLength, "TextLength", 1));
  JS_SetPropertyStr(ctx, global, "TextSubtext", JS_NewCFunction(ctx, js_TextSubtext, "TextSubtext", 3));
  JS_SetPropertyStr(ctx, global, "TextReplace", JS_NewCFunction(ctx, js_TextReplace, "TextReplace", 3));
  JS_SetPropertyStr(ctx, global, "TextInsert", JS_NewCFunction(ctx, js_TextInsert, "TextInsert", 3));
  JS_SetPropertyStr(ctx, global, "TextJoin", JS_NewCFunction(ctx, js_TextJoin, "TextJoin", 3));
  JS_SetPropertyStr(ctx, global, "TextFindIndex", JS_NewCFunction(ctx, js_TextFindIndex, "TextFindIndex", 2));
  JS_SetPropertyStr(ctx, global, "TextToUpper", JS_NewCFunction(ctx, js_TextToUpper, "TextToUpper", 1));
  JS_SetPropertyStr(ctx, global, "TextToLower", JS_NewCFunction(ctx, js_TextToLower, "TextToLower", 1));
  JS_SetPropertyStr(ctx, global, "TextToPascal", JS_NewCFunction(ctx, js_TextToPascal, "TextToPascal", 1));
  JS_SetPropertyStr(ctx, global, "TextToSnake", JS_NewCFunction(ctx, js_TextToSnake, "TextToSnake", 1));
  JS_SetPropertyStr(ctx, global, "TextToCamel", JS_NewCFunction(ctx, js_TextToCamel, "TextToCamel", 1));
  JS_SetPropertyStr(ctx, global, "TextToInteger", JS_NewCFunction(ctx, js_TextToInteger, "TextToInteger", 1));
  JS_SetPropertyStr(ctx, global, "TextToFloat", JS_NewCFunction(ctx, js_TextToFloat, "TextToFloat", 1));
  JS_SetPropertyStr(ctx, global, "DrawLine3D", JS_NewCFunction(ctx, js_DrawLine3D, "DrawLine3D", 3));
  JS_SetPropertyStr(ctx, global, "DrawPoint3D", JS_NewCFunction(ctx, js_DrawPoint3D, "DrawPoint3D", 2));
  JS_SetPropertyStr(ctx, global, "DrawCircle3D", JS_NewCFunction(ctx, js_DrawCircle3D, "DrawCircle3D", 5));
  JS_SetPropertyStr(ctx, global, "DrawTriangle3D", JS_NewCFunction(ctx, js_DrawTriangle3D, "DrawTriangle3D", 4));
  JS_SetPropertyStr(ctx, global, "DrawCube", JS_NewCFunction(ctx, js_DrawCube, "DrawCube", 5));
  JS_SetPropertyStr(ctx, global, "DrawCubeV", JS_NewCFunction(ctx, js_DrawCubeV, "DrawCubeV", 3));
  JS_SetPropertyStr(ctx, global, "DrawCubeWires", JS_NewCFunction(ctx, js_DrawCubeWires, "DrawCubeWires", 5));
  JS_SetPropertyStr(ctx, global, "DrawCubeWiresV", JS_NewCFunction(ctx, js_DrawCubeWiresV, "DrawCubeWiresV", 3));
  JS_SetPropertyStr(ctx, global, "DrawSphere", JS_NewCFunction(ctx, js_DrawSphere, "DrawSphere", 3));
  JS_SetPropertyStr(ctx, global, "DrawSphereEx", JS_NewCFunction(ctx, js_DrawSphereEx, "DrawSphereEx", 5));
  JS_SetPropertyStr(ctx, global, "DrawSphereWires", JS_NewCFunction(ctx, js_DrawSphereWires, "DrawSphereWires", 5));
  JS_SetPropertyStr(ctx, global, "DrawCylinder", JS_NewCFunction(ctx, js_DrawCylinder, "DrawCylinder", 6));
  JS_SetPropertyStr(ctx, global, "DrawCylinderEx", JS_NewCFunction(ctx, js_DrawCylinderEx, "DrawCylinderEx", 6));
  JS_SetPropertyStr(ctx, global, "DrawCylinderWires", JS_NewCFunction(ctx, js_DrawCylinderWires, "DrawCylinderWires", 6));
  JS_SetPropertyStr(ctx, global, "DrawCylinderWiresEx", JS_NewCFunction(ctx, js_DrawCylinderWiresEx, "DrawCylinderWiresEx", 6));
  JS_SetPropertyStr(ctx, global, "DrawCapsule", JS_NewCFunction(ctx, js_DrawCapsule, "DrawCapsule", 6));
  JS_SetPropertyStr(ctx, global, "DrawCapsuleWires", JS_NewCFunction(ctx, js_DrawCapsuleWires, "DrawCapsuleWires", 6));
  JS_SetPropertyStr(ctx, global, "DrawPlane", JS_NewCFunction(ctx, js_DrawPlane, "DrawPlane", 3));
  JS_SetPropertyStr(ctx, global, "DrawRay", JS_NewCFunction(ctx, js_DrawRay, "DrawRay", 2));
  JS_SetPropertyStr(ctx, global, "DrawGrid", JS_NewCFunction(ctx, js_DrawGrid, "DrawGrid", 2));
  JS_SetPropertyStr(ctx, global, "LoadModel", JS_NewCFunction(ctx, js_LoadModel, "LoadModel", 1));
  JS_SetPropertyStr(ctx, global, "LoadModelFromMesh", JS_NewCFunction(ctx, js_LoadModelFromMesh, "LoadModelFromMesh", 1));
  JS_SetPropertyStr(ctx, global, "IsModelValid", JS_NewCFunction(ctx, js_IsModelValid, "IsModelValid", 1));
  JS_SetPropertyStr(ctx, global, "UnloadModel", JS_NewCFunction(ctx, js_UnloadModel, "UnloadModel", 1));
  JS_SetPropertyStr(ctx, global, "GetModelBoundingBox", JS_NewCFunction(ctx, js_GetModelBoundingBox, "GetModelBoundingBox", 1));
  JS_SetPropertyStr(ctx, global, "DrawModel", JS_NewCFunction(ctx, js_DrawModel, "DrawModel", 4));
  JS_SetPropertyStr(ctx, global, "DrawModelEx", JS_NewCFunction(ctx, js_DrawModelEx, "DrawModelEx", 6));
  JS_SetPropertyStr(ctx, global, "DrawModelWires", JS_NewCFunction(ctx, js_DrawModelWires, "DrawModelWires", 4));
  JS_SetPropertyStr(ctx, global, "DrawModelWiresEx", JS_NewCFunction(ctx, js_DrawModelWiresEx, "DrawModelWiresEx", 6));
  JS_SetPropertyStr(ctx, global, "DrawModelPoints", JS_NewCFunction(ctx, js_DrawModelPoints, "DrawModelPoints", 4));
  JS_SetPropertyStr(ctx, global, "DrawModelPointsEx", JS_NewCFunction(ctx, js_DrawModelPointsEx, "DrawModelPointsEx", 6));
  JS_SetPropertyStr(ctx, global, "DrawBoundingBox", JS_NewCFunction(ctx, js_DrawBoundingBox, "DrawBoundingBox", 2));
  JS_SetPropertyStr(ctx, global, "DrawBillboard", JS_NewCFunction(ctx, js_DrawBillboard, "DrawBillboard", 5));
  JS_SetPropertyStr(ctx, global, "DrawBillboardRec", JS_NewCFunction(ctx, js_DrawBillboardRec, "DrawBillboardRec", 6));
  JS_SetPropertyStr(ctx, global, "DrawBillboardPro", JS_NewCFunction(ctx, js_DrawBillboardPro, "DrawBillboardPro", 9));
  JS_SetPropertyStr(ctx, global, "UnloadMesh", JS_NewCFunction(ctx, js_UnloadMesh, "UnloadMesh", 1));
  JS_SetPropertyStr(ctx, global, "DrawMesh", JS_NewCFunction(ctx, js_DrawMesh, "DrawMesh", 3));
  JS_SetPropertyStr(ctx, global, "GetMeshBoundingBox", JS_NewCFunction(ctx, js_GetMeshBoundingBox, "GetMeshBoundingBox", 1));
  JS_SetPropertyStr(ctx, global, "ExportMesh", JS_NewCFunction(ctx, js_ExportMesh, "ExportMesh", 2));
  JS_SetPropertyStr(ctx, global, "ExportMeshAsCode", JS_NewCFunction(ctx, js_ExportMeshAsCode, "ExportMeshAsCode", 2));
  JS_SetPropertyStr(ctx, global, "GenMeshPoly", JS_NewCFunction(ctx, js_GenMeshPoly, "GenMeshPoly", 2));
  JS_SetPropertyStr(ctx, global, "GenMeshPlane", JS_NewCFunction(ctx, js_GenMeshPlane, "GenMeshPlane", 4));
  JS_SetPropertyStr(ctx, global, "GenMeshCube", JS_NewCFunction(ctx, js_GenMeshCube, "GenMeshCube", 3));
  JS_SetPropertyStr(ctx, global, "GenMeshSphere", JS_NewCFunction(ctx, js_GenMeshSphere, "GenMeshSphere", 3));
  JS_SetPropertyStr(ctx, global, "GenMeshHemiSphere", JS_NewCFunction(ctx, js_GenMeshHemiSphere, "GenMeshHemiSphere", 3));
  JS_SetPropertyStr(ctx, global, "GenMeshCylinder", JS_NewCFunction(ctx, js_GenMeshCylinder, "GenMeshCylinder", 3));
  JS_SetPropertyStr(ctx, global, "GenMeshCone", JS_NewCFunction(ctx, js_GenMeshCone, "GenMeshCone", 3));
  JS_SetPropertyStr(ctx, global, "GenMeshTorus", JS_NewCFunction(ctx, js_GenMeshTorus, "GenMeshTorus", 4));
  JS_SetPropertyStr(ctx, global, "GenMeshKnot", JS_NewCFunction(ctx, js_GenMeshKnot, "GenMeshKnot", 4));
  JS_SetPropertyStr(ctx, global, "GenMeshHeightmap", JS_NewCFunction(ctx, js_GenMeshHeightmap, "GenMeshHeightmap", 2));
  JS_SetPropertyStr(ctx, global, "GenMeshCubicmap", JS_NewCFunction(ctx, js_GenMeshCubicmap, "GenMeshCubicmap", 2));
  JS_SetPropertyStr(ctx, global, "LoadMaterialDefault", JS_NewCFunction(ctx, js_LoadMaterialDefault, "LoadMaterialDefault", 0));
  JS_SetPropertyStr(ctx, global, "IsMaterialValid", JS_NewCFunction(ctx, js_IsMaterialValid, "IsMaterialValid", 1));
  JS_SetPropertyStr(ctx, global, "UnloadMaterial", JS_NewCFunction(ctx, js_UnloadMaterial, "UnloadMaterial", 1));
  JS_SetPropertyStr(ctx, global, "CheckCollisionSpheres", JS_NewCFunction(ctx, js_CheckCollisionSpheres, "CheckCollisionSpheres", 4));
  JS_SetPropertyStr(ctx, global, "CheckCollisionBoxes", JS_NewCFunction(ctx, js_CheckCollisionBoxes, "CheckCollisionBoxes", 2));
  JS_SetPropertyStr(ctx, global, "CheckCollisionBoxSphere", JS_NewCFunction(ctx, js_CheckCollisionBoxSphere, "CheckCollisionBoxSphere", 3));
  JS_SetPropertyStr(ctx, global, "GetRayCollisionSphere", JS_NewCFunction(ctx, js_GetRayCollisionSphere, "GetRayCollisionSphere", 3));
  JS_SetPropertyStr(ctx, global, "GetRayCollisionBox", JS_NewCFunction(ctx, js_GetRayCollisionBox, "GetRayCollisionBox", 2));
  JS_SetPropertyStr(ctx, global, "GetRayCollisionMesh", JS_NewCFunction(ctx, js_GetRayCollisionMesh, "GetRayCollisionMesh", 3));
  JS_SetPropertyStr(ctx, global, "GetRayCollisionTriangle", JS_NewCFunction(ctx, js_GetRayCollisionTriangle, "GetRayCollisionTriangle", 4));
  JS_SetPropertyStr(ctx, global, "GetRayCollisionQuad", JS_NewCFunction(ctx, js_GetRayCollisionQuad, "GetRayCollisionQuad", 5));
  JS_SetPropertyStr(ctx, global, "InitAudioDevice", JS_NewCFunction(ctx, js_InitAudioDevice, "InitAudioDevice", 0));
  JS_SetPropertyStr(ctx, global, "CloseAudioDevice", JS_NewCFunction(ctx, js_CloseAudioDevice, "CloseAudioDevice", 0));
  JS_SetPropertyStr(ctx, global, "IsAudioDeviceReady", JS_NewCFunction(ctx, js_IsAudioDeviceReady, "IsAudioDeviceReady", 0));
  JS_SetPropertyStr(ctx, global, "SetMasterVolume", JS_NewCFunction(ctx, js_SetMasterVolume, "SetMasterVolume", 1));
  JS_SetPropertyStr(ctx, global, "GetMasterVolume", JS_NewCFunction(ctx, js_GetMasterVolume, "GetMasterVolume", 0));
  JS_SetPropertyStr(ctx, global, "LoadWave", JS_NewCFunction(ctx, js_LoadWave, "LoadWave", 1));
  JS_SetPropertyStr(ctx, global, "LoadWaveFromMemory", JS_NewCFunction(ctx, js_LoadWaveFromMemory, "LoadWaveFromMemory", 3));
  JS_SetPropertyStr(ctx, global, "IsWaveValid", JS_NewCFunction(ctx, js_IsWaveValid, "IsWaveValid", 1));
  JS_SetPropertyStr(ctx, global, "LoadSound", JS_NewCFunction(ctx, js_LoadSound, "LoadSound", 1));
  JS_SetPropertyStr(ctx, global, "LoadSoundFromWave", JS_NewCFunction(ctx, js_LoadSoundFromWave, "LoadSoundFromWave", 1));
  JS_SetPropertyStr(ctx, global, "LoadSoundAlias", JS_NewCFunction(ctx, js_LoadSoundAlias, "LoadSoundAlias", 1));
  JS_SetPropertyStr(ctx, global, "IsSoundValid", JS_NewCFunction(ctx, js_IsSoundValid, "IsSoundValid", 1));
  JS_SetPropertyStr(ctx, global, "UnloadWave", JS_NewCFunction(ctx, js_UnloadWave, "UnloadWave", 1));
  JS_SetPropertyStr(ctx, global, "UnloadSound", JS_NewCFunction(ctx, js_UnloadSound, "UnloadSound", 1));
  JS_SetPropertyStr(ctx, global, "UnloadSoundAlias", JS_NewCFunction(ctx, js_UnloadSoundAlias, "UnloadSoundAlias", 1));
  JS_SetPropertyStr(ctx, global, "ExportWave", JS_NewCFunction(ctx, js_ExportWave, "ExportWave", 2));
  JS_SetPropertyStr(ctx, global, "ExportWaveAsCode", JS_NewCFunction(ctx, js_ExportWaveAsCode, "ExportWaveAsCode", 2));
  JS_SetPropertyStr(ctx, global, "PlaySound", JS_NewCFunction(ctx, js_PlaySound, "PlaySound", 1));
  JS_SetPropertyStr(ctx, global, "StopSound", JS_NewCFunction(ctx, js_StopSound, "StopSound", 1));
  JS_SetPropertyStr(ctx, global, "PauseSound", JS_NewCFunction(ctx, js_PauseSound, "PauseSound", 1));
  JS_SetPropertyStr(ctx, global, "ResumeSound", JS_NewCFunction(ctx, js_ResumeSound, "ResumeSound", 1));
  JS_SetPropertyStr(ctx, global, "IsSoundPlaying", JS_NewCFunction(ctx, js_IsSoundPlaying, "IsSoundPlaying", 1));
  JS_SetPropertyStr(ctx, global, "SetSoundVolume", JS_NewCFunction(ctx, js_SetSoundVolume, "SetSoundVolume", 2));
  JS_SetPropertyStr(ctx, global, "SetSoundPitch", JS_NewCFunction(ctx, js_SetSoundPitch, "SetSoundPitch", 2));
  JS_SetPropertyStr(ctx, global, "SetSoundPan", JS_NewCFunction(ctx, js_SetSoundPan, "SetSoundPan", 2));
  JS_SetPropertyStr(ctx, global, "WaveCopy", JS_NewCFunction(ctx, js_WaveCopy, "WaveCopy", 1));
  JS_SetPropertyStr(ctx, global, "LoadMusicStream", JS_NewCFunction(ctx, js_LoadMusicStream, "LoadMusicStream", 1));
  JS_SetPropertyStr(ctx, global, "LoadMusicStreamFromMemory", JS_NewCFunction(ctx, js_LoadMusicStreamFromMemory, "LoadMusicStreamFromMemory", 3));
  JS_SetPropertyStr(ctx, global, "IsMusicValid", JS_NewCFunction(ctx, js_IsMusicValid, "IsMusicValid", 1));
  JS_SetPropertyStr(ctx, global, "UnloadMusicStream", JS_NewCFunction(ctx, js_UnloadMusicStream, "UnloadMusicStream", 1));
  JS_SetPropertyStr(ctx, global, "PlayMusicStream", JS_NewCFunction(ctx, js_PlayMusicStream, "PlayMusicStream", 1));
  JS_SetPropertyStr(ctx, global, "IsMusicStreamPlaying", JS_NewCFunction(ctx, js_IsMusicStreamPlaying, "IsMusicStreamPlaying", 1));
  JS_SetPropertyStr(ctx, global, "UpdateMusicStream", JS_NewCFunction(ctx, js_UpdateMusicStream, "UpdateMusicStream", 1));
  JS_SetPropertyStr(ctx, global, "StopMusicStream", JS_NewCFunction(ctx, js_StopMusicStream, "StopMusicStream", 1));
  JS_SetPropertyStr(ctx, global, "PauseMusicStream", JS_NewCFunction(ctx, js_PauseMusicStream, "PauseMusicStream", 1));
  JS_SetPropertyStr(ctx, global, "ResumeMusicStream", JS_NewCFunction(ctx, js_ResumeMusicStream, "ResumeMusicStream", 1));
  JS_SetPropertyStr(ctx, global, "SeekMusicStream", JS_NewCFunction(ctx, js_SeekMusicStream, "SeekMusicStream", 2));
  JS_SetPropertyStr(ctx, global, "SetMusicVolume", JS_NewCFunction(ctx, js_SetMusicVolume, "SetMusicVolume", 2));
  JS_SetPropertyStr(ctx, global, "SetMusicPitch", JS_NewCFunction(ctx, js_SetMusicPitch, "SetMusicPitch", 2));
  JS_SetPropertyStr(ctx, global, "SetMusicPan", JS_NewCFunction(ctx, js_SetMusicPan, "SetMusicPan", 2));
  JS_SetPropertyStr(ctx, global, "GetMusicTimeLength", JS_NewCFunction(ctx, js_GetMusicTimeLength, "GetMusicTimeLength", 1));
  JS_SetPropertyStr(ctx, global, "GetMusicTimePlayed", JS_NewCFunction(ctx, js_GetMusicTimePlayed, "GetMusicTimePlayed", 1));
  JS_SetPropertyStr(ctx, global, "LoadAudioStream", JS_NewCFunction(ctx, js_LoadAudioStream, "LoadAudioStream", 3));
  JS_SetPropertyStr(ctx, global, "IsAudioStreamValid", JS_NewCFunction(ctx, js_IsAudioStreamValid, "IsAudioStreamValid", 1));
  JS_SetPropertyStr(ctx, global, "UnloadAudioStream", JS_NewCFunction(ctx, js_UnloadAudioStream, "UnloadAudioStream", 1));
  JS_SetPropertyStr(ctx, global, "IsAudioStreamProcessed", JS_NewCFunction(ctx, js_IsAudioStreamProcessed, "IsAudioStreamProcessed", 1));
  JS_SetPropertyStr(ctx, global, "PlayAudioStream", JS_NewCFunction(ctx, js_PlayAudioStream, "PlayAudioStream", 1));
  JS_SetPropertyStr(ctx, global, "PauseAudioStream", JS_NewCFunction(ctx, js_PauseAudioStream, "PauseAudioStream", 1));
  JS_SetPropertyStr(ctx, global, "ResumeAudioStream", JS_NewCFunction(ctx, js_ResumeAudioStream, "ResumeAudioStream", 1));
  JS_SetPropertyStr(ctx, global, "IsAudioStreamPlaying", JS_NewCFunction(ctx, js_IsAudioStreamPlaying, "IsAudioStreamPlaying", 1));
  JS_SetPropertyStr(ctx, global, "StopAudioStream", JS_NewCFunction(ctx, js_StopAudioStream, "StopAudioStream", 1));
  JS_SetPropertyStr(ctx, global, "SetAudioStreamVolume", JS_NewCFunction(ctx, js_SetAudioStreamVolume, "SetAudioStreamVolume", 2));
  JS_SetPropertyStr(ctx, global, "SetAudioStreamPitch", JS_NewCFunction(ctx, js_SetAudioStreamPitch, "SetAudioStreamPitch", 2));
  JS_SetPropertyStr(ctx, global, "SetAudioStreamPan", JS_NewCFunction(ctx, js_SetAudioStreamPan, "SetAudioStreamPan", 2));
  JS_SetPropertyStr(ctx, global, "SetAudioStreamBufferSizeDefault", JS_NewCFunction(ctx, js_SetAudioStreamBufferSizeDefault, "SetAudioStreamBufferSizeDefault", 1));

  // Variadic functions (cart-side implementations)
  JS_SetPropertyStr(ctx, global, "TextFormat", JS_NewCFunction(ctx, js_TextFormat, "TextFormat", 1));
  JS_SetPropertyStr(ctx, global, "TraceLog", JS_NewCFunction(ctx, js_TraceLog, "TraceLog", 2));
}
