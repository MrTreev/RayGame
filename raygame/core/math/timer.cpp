#include "raygame/core/math/timer.h"

namespace core::math {
template class Timer<
    std::chrono::high_resolution_clock,
    std::chrono::high_resolution_clock::duration>;
} // namespace core::math
