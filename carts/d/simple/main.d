import null0;

export extern(C) void load() {
    clear(BLUE);
    draw_circle(100, 100, 50, RED);
    draw_text(FONT_DEFAULT, "hello from D", 170, 92, WHITE);
}

// callbacks (optional - implement as needed)
//
//   export extern(C) void update() {}
