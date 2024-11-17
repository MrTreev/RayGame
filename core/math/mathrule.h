#pragma once
#include "core/base/config.h"
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

constexpr std::string to_string(MathRule mr) {
    switch (mr) {
    case core::math::MathRule::STRICT:
        return "STRICT";
    case MathRule::ALLOW:
        return "ALLOW";
    case MathRule::CLAMP:
        return "CLAMP";
    }
}

namespace {
consteval MathRule default_mathrule() {
    if constexpr (core::config::BUILD_TYPE == core::config::BuildType::DEBUG) {
        return MathRule::STRICT;
    } else {
        return MathRule::ALLOW;
    }
}
} // namespace

//! Default MathRule, STRICT for debug, ALLOW for production
static constexpr MathRule MR_DEFAULT = default_mathrule();

} // namespace core::math
