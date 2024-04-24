#include "raylib/window.h"
char game_name[] = "RayGame";

int main() {
    raylib::Window window(640, 360, game_name);
    SetTargetFPS(60);
    window.maximise();
    int x = 0;
    while (!window.should_close()) {
        window.start_frame();
        DrawFPS(0, 0);
        DrawCircle(x, 25, 12, {255, 255, 255, 255});
        DrawGrid(100, 10);
        x = (x + window.width() / 100) % window.width();
        window.end_frame();
    }
    return 0;
}
