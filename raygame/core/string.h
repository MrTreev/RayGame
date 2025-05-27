#pragma once
#include <string>

namespace core {
class String: public std::string {
public:
    //NOLINTNEXTLINE(hicpp-explicit-conversions)
    String(std::string other)
        : std::string(std::move(other)) {}

    //NOLINTNEXTLINE(hicpp-explicit-conversions)
    String(const char* other)
        : std::string(other) {}
};
} // namespace core
