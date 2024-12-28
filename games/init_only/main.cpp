#include "raygame/core/window/window.h"

int main() {
    auto mywindow = core::window::dispatch();
    while (mywindow->next_frame()) {}
}
