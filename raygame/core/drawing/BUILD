load("//rules:rg_cc.bzl", "rg_cc_library")

rg_cc_library(
    name = "drawing",
    hdrs = [
        "image.h",
        "pixel.h",
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
            "**/*.h",
            "**/*.dox",
        ],
        allow_empty = True,
    ),
    visibility = ["//visibility:public"],
)
