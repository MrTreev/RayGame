load("//rules:rg_cc_singlefile.bzl", "rg_cc_single")

rg_cc_single(
    name = "concepts",
)

rg_cc_single(
    name = "condition",
    deps = [
        ":config",
        ":exception",
        ":concepts",
    ],
    implementation_deps = [
        ":logger",
    ],
)

rg_cc_single(
    name = "config",
    defines = [
        ] + select({
            "//rules/log/level:trace":    ["RAYGAME_LOG_TRACE"],
            "//rules/log/level:debug":    ["RAYGAME_LOG_DEBUG"],
            "//rules/log/level:info":     ["RAYGAME_LOG_INFO"],
            "//rules/log/level:note":     ["RAYGAME_LOG_NOTE"],
            "//rules/log/level:progress": ["RAYGAME_LOG_PROGRESS"],
            "//rules/log/level:warning":  ["RAYGAME_LOG_WARNING"],
            "//rules/log/level:error":    ["RAYGAME_LOG_ERROR"],
            "//rules/log/level:fatal":    ["RAYGAME_LOG_FATAL"],
        }) + select({
            "//rules/log/source_location:enabled":  ["RAYGAME_ENABLE_SOURCE_LOC"],
            "//rules/log/source_location:disabled": ["RAYGAME_DISABLE_SOURCE_LOC"],
        }),
)

rg_cc_single(
    name = "debug",
    deps = [
        ":config",
    ],
)

rg_cc_single(
    name = "exception",
)

rg_cc_single(
    name = "logger",
    deps = [
        ":config",
        ":types",
    ],
)

rg_cc_single(
    name = "types",
    deps = [
        ":debug",
    ],
)

filegroup(
    name = "doxyfiles",
    srcs = glob([
            "**/*.h",
            "**/*.dox",
        ],
        allow_empty = True,
    ) + [
        "//raygame/core/drawing:doxyfiles",
        "//raygame/core/math:doxyfiles",
        "//raygame/core/window:doxyfiles",
    ],
    visibility = ["//visibility:public"],
)
