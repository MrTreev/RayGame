#include "raylib/window.h"

int main() {
    raylib::Window window(640, 360, "RayGame");
    while (!window.should_close()) {}
    return 0;
}
