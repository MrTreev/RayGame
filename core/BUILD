cc_library(
    name = "core",
    srcs = [
        "colours.cpp",
        "condition.cpp",
        "config.cpp",
        "exception.cpp",
        "image.cpp",
        "logger.cpp",
        "math.cpp",
        "pixel.cpp",
        "spritesheet.cpp",
        "texture.cpp",
        "types.cpp",
        "window.cpp",
    ],
    hdrs = [
        "colours.h",
        "condition.h",
        "config.h",
        "exception.h",
        "image.h",
        "logger.h",
        "math.h",
        "pixel.h",
        "spritesheet.h",
        "texture.h",
        "types.h",
        "window.h",
    ],
    deps = [ "//core/windowimpl", ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "doxygen_files",
    srcs = [
        "//core/windowimpl:doxygen_files",
    ] + glob([
        "**/*.h",
        "**/*.inl",
        "**/*.dox",
    ]),
    visibility = [ "//visibility:public" ],
)

filegroup(
    name = "doxygen_data_files",
    srcs = [],
    visibility = [ "//visibility:public" ],
)
