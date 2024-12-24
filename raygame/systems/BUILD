filegroup(
    name = "doxyfiles",
    srcs = glob([
            "**/*.h",
            "**/*.dox",
        ],
        allow_empty = True,
    ) + [
        "//raygame/systems/core:doxyfiles",
        "//raygame/systems/pf1e:doxyfiles",
    ],
    visibility = ["//visibility:public"],
)
