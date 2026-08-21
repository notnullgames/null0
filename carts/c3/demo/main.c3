module main;

import null0;

// persistent frame counter, incremented once per update()
int frame = 0;

fn void update() @export("update") {
    null0::clear(null0::DARKGRAY);
    null0::draw_text(null0::FONT_DEFAULT, "null0 demo", 20, 20, null0::WHITE);

    null0::draw_rectangle(40, 80, 100, 70, null0::RED);
    null0::draw_circle(220, 115, 45, null0::GREEN);
    null0::draw_triangle(320, 150, 400, 150, 360, 60, null0::BLUE);
    null0::draw_line(40, 250, 600, 250, null0::LIGHTGRAY);

    // hexagon - an array of Vector structs
    null0::Vector[6] hexagon = {
        { 460, 80 },
        { 520, 80 },
        { 550, 140 },
        { 520, 200 },
        { 460, 200 },
        { 430, 140 },
    };
    null0::draw_polygon(&hexagon[0], 6, null0::PURPLE);

    frame++;
    int x = frame % 600;
    null0::draw_circle(x + 20, 350, 20, null0::YELLOW);

    null0::draw_text(null0::FONT_DEFAULT, "shapes + animation + text", 20, 440, null0::ORANGE);
}

// callbacks (optional - implement as needed)

// fn void load() @export("load") {}
// fn void unload() @export("unload") {}
// fn void buttonUp(int button, uint player) @export("buttonUp") {}
// fn void buttonDown(int button, uint player) @export("buttonDown") {}
// fn void keyUp(int key) @export("keyUp") {}
// fn void keyDown(int key) @export("keyDown") {}
// fn void mouseDown(int button) @export("mouseDown") {}
// fn void mouseUp(int button) @export("mouseUp") {}
// fn void mouseMoved(float x, float y) @export("mouseMoved") {}
