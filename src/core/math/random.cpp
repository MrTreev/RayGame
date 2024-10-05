#include "core/math/random.h" // IWYU pragma: keep
#include <random>

namespace {
uint64_t seed = 42;

// Disable global constructor warnings for global random_device, as it is a singleton anyway
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
std::random_device dev;
#pragma clang diagnostic pop
} // namespace

uint64_t core::math::detail::rand_seed() {
    if constexpr (random_seed) {
        return dev();
    } else {
        ++seed;
        return seed;
    }
}
