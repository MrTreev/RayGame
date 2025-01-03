#include "raygame/core/window/window.h"

int main() {
    core::window::Window mywindow{};
    while (mywindow.next_frame()) {}
}
