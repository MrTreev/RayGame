load("//rules:rg_cc_singlefile.bzl", "rg_cc_single")

rg_cc_single(
    name = "colour",
    deps = [
        ":pixel"
    ],
)

rg_cc_single(
    name = "pixel",
    deps = [
        "//raygame/core:types"
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
