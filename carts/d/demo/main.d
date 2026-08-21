import null0;

// persistent frame counter, incremented once per update()
static int frame = 0;

// hexagon for draw_polygon: an array of Vector structs
static immutable Vector[6] hexPoints = [
    Vector(460, 80),
    Vector(520, 80),
    Vector(550, 140),
    Vector(520, 200),
    Vector(460, 200),
    Vector(430, 140),
];

export extern(C) void update() {
    clear(DARKGRAY);
    draw_text(FONT_DEFAULT, "null0 demo", 20, 20, WHITE);
    draw_rectangle(40, 80, 100, 70, RED);
    draw_circle(220, 115, 45, GREEN);
    draw_triangle(320, 150, 400, 150, 360, 60, BLUE);
    draw_line(40, 250, 600, 250, LIGHTGRAY);
    draw_polygon(hexPoints.ptr, cast(int) hexPoints.length, PURPLE);

    // animate a circle sweeping left-to-right across the bottom of the screen
    frame++;
    int x = frame % 600;
    draw_circle(x + 20, 350, 20, YELLOW);

    draw_text(FONT_DEFAULT, "shapes + animation + text", 20, 440, ORANGE);
}

// callbacks (optional - implement as needed)

// export extern(C) void load() {}
// export extern(C) void unload() {}
// export extern(C) void buttonUp(GamepadButton button, uint player) {}
// export extern(C) void buttonDown(GamepadButton button, uint player) {}
// export extern(C) void keyUp(Key key) {}
// export extern(C) void keyDown(Key key) {}
// export extern(C) void mouseDown(MouseButton button) {}
// export extern(C) void mouseUp(MouseButton button) {}
// export extern(C) void mouseMoved(float x, float y) {}
