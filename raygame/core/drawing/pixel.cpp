#include "raygame/core/drawing/pixel.h" // IWYU pragma: keep
#include <string>

#define CHECK_COLOUR(COL)                                                                          \
    if (*this == ::core::colour::COL) {                                                            \
        return #COL;                                                                               \
    }                                                                                              \
    static_assert(true)

std::string core::Pixel::colour() const {
    CHECK_COLOUR(VOID);
    CHECK_COLOUR(BLACK);
    CHECK_COLOUR(WHITE);
    CHECK_COLOUR(RED);
    CHECK_COLOUR(GREEN);
    CHECK_COLOUR(BLUE);
    return std::string(*this);
}
