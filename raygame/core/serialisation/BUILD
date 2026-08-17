load("//rules:rg_cc.bzl", "rg_cc_single")

rg_cc_single(
    name = "serialisation",
    deps = [
        "//raygame/core:types",
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
