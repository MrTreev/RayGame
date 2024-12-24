load("//rules:rg_cc_singlefile.bzl", "rg_cc_single")

rg_cc_single(
    name = "arithmetic",
    create_test = False,
    deps = [
        "//core/math/arithmetic:safe_add",
        "//core/math/arithmetic:safe_div",
        "//core/math/arithmetic:safe_mult",
        "//core/math/arithmetic:safe_sub",
    ],
)

rg_cc_single(
    name = "math",
    deps = [
        "//core/base:exception",
        "//core/base:types",
        ":mathrule",
    ],
)

rg_cc_single(
    name = "mathrule",
)

rg_cc_single(
    name = "numeric_cast",
    deps = [
        "//core/base:debug",
        "//core/base:exception",
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
        "//core/base:types",
    ],
    implementation_deps = [
        "//core/base:condition",
        "//core/base:config",
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
        "//core/base:types",
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
