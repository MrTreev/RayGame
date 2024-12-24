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
    defines = select({
        "//rules/logging:trace":    ["RAYGAME_LOG_TRACE"],
        "//rules/logging:debug":    ["RAYGAME_LOG_DEBUG"],
        "//rules/logging:info":     ["RAYGAME_LOG_INFO"],
        "//rules/logging:note":     ["RAYGAME_LOG_NOTE"],
        "//rules/logging:progress": ["RAYGAME_LOG_PROGRESS"],
        "//rules/logging:warning":  ["RAYGAME_LOG_WARNING"],
        "//rules/logging:error":    ["RAYGAME_LOG_ERROR"],
        "//rules/logging:fatal":    ["RAYGAME_LOG_FATAL"],
    }),
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
