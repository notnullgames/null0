module main;

import null0;

fn void load() @export("load") {
    null0::clear(null0::BLUE);
    null0::draw_circle(100, 100, 50, null0::RED);
}

// callbacks (optional - implement as needed)

// fn void update() @export("update") {}
// fn void unload() @export("unload") {}
// fn void buttonUp(int button, uint player) @export("buttonUp") {}
// fn void buttonDown(int button, uint player) @export("buttonDown") {}
// fn void keyUp(int key) @export("keyUp") {}
// fn void keyDown(int key) @export("keyDown") {}
// fn void mouseDown(int button) @export("mouseDown") {}
// fn void mouseUp(int button) @export("mouseUp") {}
// fn void mouseMoved(float x, float y) @export("mouseMoved") {}
