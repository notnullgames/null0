class Main {
  static function main() {
    Null0.onLoad = () -> {
      Null0.clear(Null0.BLUE);
      Null0.drawCircle(100, 100, 50, Null0.RED);
      Null0.drawText(Null0.FONT_DEFAULT, "hello from Haxe", 170, 92, Null0.WHITE);
    };
  }
}

// other callbacks you can set in main():
//
//   Null0.onUpdate = () -> {}
//   Null0.onButtonDown = (button:GamepadButton, player:Int) -> {}
