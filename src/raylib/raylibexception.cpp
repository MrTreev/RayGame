#include "raylib/raylibexception.h"

raylib::RaylibException::RaylibException(const std::string& message)
    : std::runtime_error(message) {}
