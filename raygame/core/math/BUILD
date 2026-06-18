load("//rules:rg_cc.bzl", "rg_cc_library")

rg_cc_library(
    name = "math",
    hdrs = [
        "arithmetic.h",
        "arithmetic/safe_add.h",
        "arithmetic/safe_div.h",
        "arithmetic/safe_mult.h",
        "arithmetic/safe_sub.h",
        "math.h",
        "mathrule.h",
        "numeric_cast.h",
        "random.h",
        "rect.h",
        "ring_average.h",
        "timer.h",
        "vector.h",
    ],
    srcs = [
        "arithmetic.cpp",
        "arithmetic/safe_add.cpp",
        "arithmetic/safe_div.cpp",
        "arithmetic/safe_mult.cpp",
        "arithmetic/safe_sub.cpp",
        "math.cpp",
        "mathrule.cpp",
        "numeric_cast.cpp",
        "random.cpp",
        "rect.cpp",
        "ring_average.cpp",
        "timer.cpp",
        "vector.cpp",
    ],
    local_defines = select({
        "//rules/math:deterministic": ["RAYGAME_RANDOM_DETERMINISTIC=true"],
        "//rules/math:non-deterministic": ["RAYGAME_USE_FULL_RANDOM=true"],
    }),
    deps = [
        "//raygame/core",
    ],
)

filegroup(
    name = "doxyfiles",
    srcs = glob([
            "**/*.h",
            "**/*.dox",
        ],
        allow_empty = True,
    ),
    visibility = ["//visibility:public"],
)
