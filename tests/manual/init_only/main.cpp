#include "raygame/core/application/application.hpp"

int main() {
    core::Application mywindow{};
    while (mywindow.next_frame()) {}
}
