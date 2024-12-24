load("//rules:rg_cc_singlefile.bzl", "rg_cc_single")

rg_cc_single(
    name = "arithmetic",
    create_test = False,
    deps = [
        "//raygame/core/math/arithmetic:safe_add",
        "//raygame/core/math/arithmetic:safe_div",
        "//raygame/core/math/arithmetic:safe_mult",
        "//raygame/core/math/arithmetic:safe_sub",
    ],
)

rg_cc_single(
    name = "math",
    deps = [
        "//raygame/core/base:exception",
        "//raygame/core/base:types",
        ":mathrule",
    ],
)

rg_cc_single(
    name = "mathrule",
)

rg_cc_single(
    name = "numeric_cast",
    deps = [
        "//raygame/core/base:debug",
        "//raygame/core/base:exception",
        ":mathrule",
    ],
)

rg_cc_single(
    name = "random",
    defines = select({
        "//rules/math:deterministic": [],
        "//rules/math:non-deterministic": ["RAYGAME_USE_FULL_RANDOM"],
    }),
    deps = [
        "//raygame/core/base:types",
    ],
    implementation_deps = [
        "//raygame/core/base:condition",
        "//raygame/core/base:config",
    ],
)

rg_cc_single(
    name = "rect",
    deps = [
        ":arithmetic",
        ":vector",
    ],
)

rg_cc_single(
    name = "vector",
    deps = [
        "//raygame/core/base:types",
        ":arithmetic",
        ":mathrule",
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
