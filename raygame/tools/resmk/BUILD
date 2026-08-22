load("//rules:rg_cc.bzl", "rg_cc_binary", "rg_cc_library")

rg_cc_library(
    name = "resmk_lib",
    hdrs = [
        "resources/png.hpp",
        "resources/resmk.hpp",
        "resources/resource.hpp",
    ],
    srcs = [
        "resources/png.cpp",
        "resources/resmk.cpp",
        "resources/resource.cpp",
    ],
    deps = [
        "//raygame/core",
        "//raygame/core/drawing",
        "//raygame/core/io",
        "//third_party/stb:image",
    ],
    visibility = ["//visibility:public"],
)

rg_cc_binary(
    name = "resmk",
    srcs = [
        "main.cpp",
    ],
    deps = [
        ":resmk_lib"
    ],
    visibility = ["//visibility:public"],
)
