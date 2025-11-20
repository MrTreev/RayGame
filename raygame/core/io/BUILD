load("//rules:rg_cc.bzl", "rg_cc_single", "rg_cc_library")

rg_cc_library(
    name = "io",
    deps = [
        ":file",
    ],
)

rg_cc_single(
    name = "file",
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
