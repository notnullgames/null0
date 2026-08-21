// demo haxe cart for null0 (compiles via HL/C)
//
// exercises more of the API than simple/: shapes, an Array<Vector> polygon,
// text, and per-frame animation state.

class Main {
  static var frame = 0;

  static function main() {
    Null0.onUpdate = () -> {
      frame++;

      Null0.clear(Null0.DARKGRAY);
      Null0.drawText(Null0.FONT_DEFAULT, "null0 demo", 20, 20, Null0.WHITE);
      Null0.drawRectangle(40, 80, 100, 70, Null0.RED);
      Null0.drawCircle(220, 115, 45, Null0.GREEN);
      Null0.drawTriangle(320, 150, 400, 150, 360, 60, Null0.BLUE);
      Null0.drawLine(40, 250, 600, 250, Null0.LIGHTGRAY);

      // hexagon - the Array<Vector> array-arg call
      var hexagon = [
        new Null0.Vector(460, 80),
        new Null0.Vector(520, 80),
        new Null0.Vector(550, 140),
        new Null0.Vector(520, 200),
        new Null0.Vector(460, 200),
        new Null0.Vector(430, 140),
      ];
      Null0.drawPolygon(hexagon, Null0.PURPLE);

      // a circle sweeping left-to-right across the bottom, proving
      // onUpdate is called repeatedly and state persists
      var x = frame % 600;
      Null0.drawCircle(x + 20, 350, 20, Null0.YELLOW);

      Null0.drawText(Null0.FONT_DEFAULT, "shapes + animation + text", 20, 440, Null0.ORANGE);
    };
  }
}
