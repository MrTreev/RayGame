#include "core/window/x11.h"

int main() {
    auto mywindow = core::window::X11Window();
    while (mywindow.next_frame()) {}
}
