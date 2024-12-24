load("//rules:rg_cc_singlefile.bzl", "rg_cc_single")

rg_cc_single(
    name = "safe_add",
    deps = [
        "//raygame/core/base:config",
        "//raygame/core/base:condition",
        "//raygame/core/base:debug",
        "//raygame/core/base:exception",
        "//raygame/core/math:math",
        "//raygame/core/math:numeric_cast",
    ],
)

rg_cc_single(
    name = "safe_div",
    deps = [
        "//raygame/core/base:debug",
        "//raygame/core/base:exception",
        "//raygame/core/math:math",
        "//raygame/core/math:numeric_cast",
    ],
)

rg_cc_single(
    name = "safe_mult",
    deps = [
        "//raygame/core/base:condition",
        "//raygame/core/base:config",
        "//raygame/core/base:debug",
        "//raygame/core/base:exception",
        "//raygame/core/math:numeric_cast",
    ],
)

rg_cc_single(
    name = "safe_sub",
    deps = [
        "//raygame/core/base:config",
        "//raygame/core/base:debug",
        "//raygame/core/base:exception",
        "//raygame/core/math:numeric_cast",
        ":safe_add",
    ],
)
