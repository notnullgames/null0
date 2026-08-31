class Main {
  static function main() {
    Null0.onLoad = () -> {
      Null0.clear(Null0.BLUE);
      Null0.drawCircle(100, 100, 50, Null0.RED);
      Null0.drawText(Null0.FONT_DEFAULT, "hello from haxe", 130, 90, Null0.WHITE);
    };

    Null0.onUpdate = () -> {
      // runs every frame
    };
  }
}

// other callbacks you can set in main():
//
//   Null0.onUnload = () -> {}
//   Null0.onButtonUp = (button:GamepadButton, player:Int) -> {}
//   Null0.onButtonDown = (button:GamepadButton, player:Int) -> {}
//   Null0.onKeyUp = (key:Key) -> {}
//   Null0.onKeyDown = (key:Key) -> {}
//   Null0.onMouseDown = (button:MouseButton) -> {}
//   Null0.onMouseUp = (button:MouseButton) -> {}
//   Null0.onMouseMoved = (x:Single, y:Single) -> {}
//
// types live in the Null0 module: import Null0.Color, import Null0.Key, ...
