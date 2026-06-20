load("//rules:rg_cc.bzl", "rg_cc_library")

rg_cc_library(
    name = "raytest",
    hdrs = [
        "raytest.h",
    ],
    srcs = [
        "raytest.cpp",
    ],
    include_prefix = "raytest",
    deps = [
        "//third_party/gtest",
    ],
    implementation_deps = [
        "//raygame/core:config",
        "@rules_cc//cc/runfiles",
    ],
)
