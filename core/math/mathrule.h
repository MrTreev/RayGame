#pragma once
#include <string>

namespace core::math {

//! Rule for dealing with out-of-range errors
enum class MathRule {
    //! Throw an exception
    STRICT,
    //! Do nothing, return whatever would be normally returned
    ALLOW,
    //! Clamp to the range representable by the desired type
    CLAMP,
};

//! Default MathRule, STRICT for debug, ALLOW for production
static constexpr MathRule MR_DEFAULT = MathRule::STRICT;

} // namespace core::math

namespace core {

constexpr std::string to_string(core::math::MathRule mr) {
    switch (mr) {
    case core::math::MathRule::STRICT:
        return "STRICT";
    case core::math::MathRule::ALLOW:
        return "ALLOW";
    case core::math::MathRule::CLAMP:
        return "CLAMP";
    }
}

} // namespace core
