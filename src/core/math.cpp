#include "core/math.h" // IWYU pragma: keep

std::ostream& operator<<(std::ostream& os, core::math::MathRule c) {
    switch (c) {
    case core::math::MathRule::STRICT:
        os << "STRICT";
        break;
    case core::math::MathRule::ALLOW:
        os << "ALLOW";
        break;
    case core::math::MathRule::CLAMP:
        os << "CLAMP";
        break;
    }
    return os;
}
