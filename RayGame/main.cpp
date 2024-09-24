#include "core/logger.h"
#include <format>

int main() {
    std::string tmp = std::format("test");
    core::log::debug("test");
}
