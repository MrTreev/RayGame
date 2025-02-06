#pragma once

#if !defined(RAYGAME_ASSERT)
#    include <cassert>
#endif

#    define RAYGAME_ASSERT(condition, ...)                                     \
        assert(condition __VA_OPT__(, ) __VA_ARGS__)
