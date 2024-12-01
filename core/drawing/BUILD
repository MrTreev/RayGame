cc_library(
	name = "drawing",
	hdrs = [
		"colour.h",
		"pixel.h",
	],
	srcs = [
		"colour.cpp",
		"pixel.cpp",
	],
	deps = [
		"//core/base",
	],
	visibility = [ "//visibility:public" ],
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
