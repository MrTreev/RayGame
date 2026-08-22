load("//rules:rg_cc.bzl", "rg_cc_singletest")

rg_cc_singletest(
    name = "resmk",
    deps = [
        "//raygame/core/io",
        "//raygame/tools/resmk:resmk_lib",
    ],
    data = [
        "//raygame/tools/resmk",
        "data/pngtest.cpp",
        "data/pngtest.hpp",
        "data/pngtest.png",
    ],
)
