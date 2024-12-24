load("//rules:rg_cc_singlefile.bzl", "rg_cc_single")

rg_cc_single(
    name = "safe_add",
    deps = [
        "//core/base:config",
        "//core/base:condition",
        "//core/base:debug",
        "//core/base:exception",
        "//core/math:math",
        "//core/math:numeric_cast",
    ],
)

rg_cc_single(
    name = "safe_div",
    deps = [
        "//core/base:debug",
        "//core/base:exception",
        "//core/math:math",
        "//core/math:numeric_cast",
    ],
)

rg_cc_single(
    name = "safe_mult",
    deps = [
        "//core/base:condition",
        "//core/base:config",
        "//core/base:debug",
        "//core/base:exception",
        "//core/math:numeric_cast",
    ],
)

rg_cc_single(
    name = "safe_sub",
    deps = [
        "//core/base:config",
        "//core/base:debug",
        "//core/base:exception",
        "//core/math:numeric_cast",
        ":safe_add",
    ],
)
