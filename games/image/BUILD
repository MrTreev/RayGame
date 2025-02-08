cc_library(
    name = "resources",
    hdrs = ["defs.h"],
    srcs = [
        "icon.cpp",
        "cottage.h",
        "icon.h",
    ],
    deps = [
        "//raygame/core/drawing:image",
    ],
)

cc_binary(
    name = "image",
    deps = [
        "//raygame/core/window",
        "//raygame/core/drawing:image",
        "//raygame/core:logger",
        ":resources",
    ],
    srcs = [
        "main.cpp",
    ],
)
