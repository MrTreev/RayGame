load("//rules:rg_cc.bzl", "rg_cc_library")

rg_cc_library(
    name = "drawing",
    hdrs = [
        "image.hpp",
        "pixel.hpp",
    ],
    srcs = [
        "image.cpp",
        "pixel.cpp",
    ],
    deps = [
        "//raygame/core",
        "//raygame/core/math",
    ],
)

filegroup(
    name = "doxyfiles",
    srcs = glob([
            "**/*.hpp",
            "**/*.dox",
        ],
        allow_empty = True,
    ),
    visibility = ["//visibility:public"],
)
