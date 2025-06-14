#pragma once
#include "raygame/core/types.h"
#include <string>

namespace core::math {

//! Rule for dealing with out-of-range errors
enum class MathRule : uint8_t {
    //! Throw an exception
    STRICT,
    //! Return a std::expected
    EXPECT,
    //! Do nothing, return whatever would be normally returned
    ALLOW,
    //! Clamp to the range representable by the desired type
    CLAMP,
};

//! Default MathRule, STRICT for debug, ALLOW for production
static constexpr MathRule MR_DEFAULT = MathRule::STRICT;

} // namespace core::math

namespace core {

constexpr std::string to_string(core::math::MathRule rule) {
    switch (rule) {
    case core::math::MathRule::STRICT: return "STRICT";
    case core::math::MathRule::EXPECT: return "EXPECT";
    case core::math::MathRule::ALLOW:  return "ALLOW";
    case core::math::MathRule::CLAMP:  return "CLAMP";
    }
}

} // namespace core
