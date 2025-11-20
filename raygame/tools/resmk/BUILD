load("//rules:rg_cc.bzl", "rg_cc_binary")

rg_cc_binary(
    name = "resmk",
    srcs = [
        "main.cpp",
        "resources/png.h",
        "resources/png.cpp",
        "resources/resource.h",
        "resources/resource.cpp",
    ],
    deps = [
        "//raygame/core",
        "//raygame/core/drawing",
        "//raygame/core/io",
        "//third_party/stb:image",
    ],
)
