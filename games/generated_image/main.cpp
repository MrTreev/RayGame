#include "raygame/core/application/application.h"

int main() {
    core::Application mywindow{};
    while (mywindow.next_frame()) {}
}
