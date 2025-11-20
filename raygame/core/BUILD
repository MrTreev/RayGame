load("//rules:rg_cc.bzl", "rg_cc_library", "rg_cc_single")

rg_cc_library(
    name = "core_extra",
    deps = [
        ":core",
        "//raygame/core/application",
        "//raygame/core/drawing",
        "//raygame/core/io",
        "//raygame/core/math",
        "//raygame/core/serialisation",
    ],
)

rg_cc_library(
    name = "core",
    deps = [
        ":assert",
        ":concepts",
        ":condition",
        ":config",
        ":exception",
        ":logger",
        ":macros",
        ":matrix",
        ":string",
        ":types",
    ],
)

rg_cc_single(
    name = "assert",
    implementation_deps = [
        ":types",
    ],
)

rg_cc_single(
    name = "concepts",
    deps = [
        ":types",
    ]
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
    name = "string",
)

rg_cc_single(
    name = "macros",
)

rg_cc_single(
    name = "config",
    deps = [
        ":macros",
    ],
)

rg_cc_single(
    name = "exception",
    implementation_deps = [
        ":types",
    ],
)

rg_cc_single(
    name = "matrix",
    deps = [
        ":types",
    ],
)

rg_cc_single(
    name = "types",
    deps = [
        ":config",
    ],
    defines = [] + select({
        "//rules/log/source_location:full": ["RAYGAME_SOURCE_LOCATION_FULL"],
        "//rules/log/source_location:base": ["RAYGAME_SOURCE_LOCATION_BASE"],
        "//rules/log/source_location:none": ["RAYGAME_SOURCE_LOCATION_NONE"],
    }))

rg_cc_single(
    name = "logger",
    defines = [] + select({
        "//rules/log/level:trace":    ["RAYGAME_LOG_TRACE"],
        "//rules/log/level:debug":    ["RAYGAME_LOG_DEBUG"],
        "//rules/log/level:info":     ["RAYGAME_LOG_INFO"],
        "//rules/log/level:warning":  ["RAYGAME_LOG_WARNING"],
        "//rules/log/level:error":    ["RAYGAME_LOG_ERROR"],
        "//rules/log/level:fatal":    ["RAYGAME_LOG_FATAL"],
    }),
    deps = [
        ":config",
        ":types",
        ":string",
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
        "//raygame/core/application:doxyfiles",
        "//raygame/core/drawing:doxyfiles",
        "//raygame/core/io:doxyfiles",
        "//raygame/core/math:doxyfiles",
        "//raygame/core/serialisation:doxyfiles",
    ],
    visibility = ["//visibility:public"],
)
