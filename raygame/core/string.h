#pragma once
#include <string>

namespace core::string {
enum class AnsiColour : uint8_t {
    RED,     // "\033[31m"
    GREEN,   // "\033[32m"
    YELLOW,  // "\033[33m"
    BLUE,    // "\033[34m"
    MAGENTA, // "\033[35m"
    CYAN,    // "\033[36m"
    WHITE,   // "\033[37m"
    RESET,   // "\033[0m"
};

constexpr std::string text_colour(AnsiColour col) {
    switch (col) {
    case AnsiColour::RED:     return "\033[31m";
    case AnsiColour::GREEN:   return "\033[32m";
    case AnsiColour::YELLOW:  return "\033[33m";
    case AnsiColour::BLUE:    return "\033[34m";
    case AnsiColour::MAGENTA: return "\033[35m";
    case AnsiColour::CYAN:    return "\033[36m";
    case AnsiColour::WHITE:   return "\033[37m";
    case AnsiColour::RESET:   return "\033[0m";
    }
}

constexpr std::string colourise(AnsiColour col, const std::string_view str) {
    std::string final{};
    final.append(text_colour(col));
    final.append(str);
    final.append(text_colour(AnsiColour::RESET));
    return final;
}
} // namespace core::string
