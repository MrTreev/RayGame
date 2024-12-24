load("//rules:rg_cc_singlefile.bzl", "rg_cc_single")

rg_cc_single(
    name = "safe_add",
    deps = [
        "//raygame/core:config",
        "//raygame/core:condition",
        "//raygame/core:debug",
        "//raygame/core:exception",
        "//raygame/core/math:math",
        "//raygame/core/math:numeric_cast",
    ],
)

rg_cc_single(
    name = "safe_div",
    deps = [
        "//raygame/core:debug",
        "//raygame/core:exception",
        "//raygame/core/math:math",
        "//raygame/core/math:numeric_cast",
    ],
)

rg_cc_single(
    name = "safe_mult",
    deps = [
        "//raygame/core:condition",
        "//raygame/core:config",
        "//raygame/core:debug",
        "//raygame/core:exception",
        "//raygame/core/math:numeric_cast",
    ],
)

rg_cc_single(
    name = "safe_sub",
    deps = [
        "//raygame/core:config",
        "//raygame/core:debug",
        "//raygame/core:exception",
        "//raygame/core/math:numeric_cast",
        ":safe_add",
    ],
)
