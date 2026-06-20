load("//rules:rg_cc.bzl", "rg_cc_binary")
load("//rules:rg_resmk.bzl", "rg_resmk")

rg_resmk(
    name = "generated_png_image",
    resources = [
        "pngtest.png",
        "square.png",
    ],
)

rg_cc_binary(
    name = "generated_image",
    srcs = [
        "main.cpp",
    ],
    deps = [
        "//raygame/core:core_extra",
        ":generated_png_image",
    ],
)
