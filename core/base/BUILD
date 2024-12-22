cc_library(
	name = "base",
    deps = [
        ":concepts",
        ":condition",
        ":config",
        ":debug",
        ":exception",
        ":logger",
        ":types",
    ],
	visibility = [ "//visibility:public" ]
)

cc_library(
    name = "concepts",
    hdrs = ["concepts.h"],
    srcs = ["concepts.cpp"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "concepts_test",
    srcs = ["concepts_test.cpp"],
    deps = [
        ":concepts",
        "//test"
    ],
    size = "small",
)

cc_library(
    name = "condition",
    hdrs = ["condition.h"],
    srcs = ["condition.cpp"],
    deps = [
        ":config",
        ":exception",
        ":concepts",
        ":logger",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "condition_test",
    srcs = ["condition_test.cpp"],
    deps = [
        ":condition",
        "//test"
    ],
    size = "small",
)

cc_library(
    name = "config",
    hdrs = ["config.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "config_test",
    srcs = ["config_test.cpp"],
    deps = [
        ":config",
        "//test"
    ],
    size = "small",
)

cc_library(
    name = "debug",
    hdrs = ["debug.h"],
    srcs = ["debug.cpp"],
    deps = [
        ":config",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "debug_test",
    srcs = ["debug_test.cpp"],
    deps = [
        ":debug",
        "//test"
    ],
    size = "small",
)

cc_library(
    name = "exception",
    hdrs = ["exception.h"],
    srcs = ["exception.cpp"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "exception_test",
    srcs = ["exception_test.cpp"],
    deps = [
        ":exception",
        "//test"
    ],
    size = "small",
)

cc_library(
    name = "logger",
    hdrs = ["logger.h"],
    srcs = ["logger.cpp"],
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
    visibility = ["//visibility:public"],
)

cc_test(
    name = "logger_test",
    srcs = ["logger_test.cpp"],
    deps = [
        ":logger",
        "//test"
    ],
    size = "small",
)

cc_library(
    name = "types",
    hdrs = ["types.h"],
    srcs = ["types.cpp"],
    deps = [
        ":debug",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "types_test",
    srcs = ["types_test.cpp"],
    deps = [
        ":types",
        "//test"
    ],
    size = "small",
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
