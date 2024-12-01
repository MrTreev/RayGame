cc_library(
	name = "base",
	hdrs = [
    	"condition.h",
    	"config.h",
    	"debug.h",
    	"exception.h",
    	"logger.h",
    	"types.h",
	],
	srcs = [
    	"condition.cpp",
    	"config.cpp",
    	"debug.cpp",
    	"exception.cpp",
    	"logger.cpp",
    	"types.cpp",
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
	visibility = [ "//visibility:public" ]
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
