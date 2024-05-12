#pragma once

#include <stdexcept>
#include <string>

namespace raylib {

class RaylibException: public std::runtime_error {
public:
    explicit RaylibException(const std::string& message);
};

} // namespace raylib
