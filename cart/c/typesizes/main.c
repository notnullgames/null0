// this will just show sizes of types (help with bindings)

#include <null0.h>

int main() {
  trace("Here are the sizes of some structs:");
  trace("  Dimensions: %u", sizeof(Dimensions));
  trace("  Vector: %u", sizeof(Vector));
  trace("  Rectangle: %u", sizeof(Rectangle));
  trace("  SfxParams: %u", sizeof(SfxParams));
  trace("  Color: %u", sizeof(Color));
  trace("  FileInfo: %u", sizeof(FileInfo));

  trace("Enums are int, so they should be 4:");
  trace("  ImageFilter: %u", sizeof(ImageFilter));
  trace("  Key: %u", sizeof(Key));
  trace("  GamepadButton: %u", sizeof(GamepadButton));
  trace("  MouseButton: %u", sizeof(MouseButton));
  trace("  SfxPresetType: %u", sizeof(SfxPresetType));
  trace("  SfxWaveType: %u", sizeof(SfxWaveType));
  trace("  FileType: %u", sizeof(FileType));
  return 0;
}