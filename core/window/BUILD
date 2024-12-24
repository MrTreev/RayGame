load("//rules:rg_cc_singlefile.bzl", "rg_cc_library")

rg_cc_library(
    name = "window",
	hdrs = [
		"window.h",
		"x11.h",
		"wayland.h",
	],
	srcs = [
		"window.cpp",
		"x11.cpp",
		"wayland.cpp",
        "detail/wayland.h",
		"detail/wayland.cpp",
	],
	deps = [
		"//core/math:vector",
	],
    implementation_deps = [
		"//core/base:condition",
		"//core/base:logger",
		"//core/base:types",
		"//core/drawing:colour",
		"//core/math:arithmetic",
		"//core/math:numeric_cast",
		"//core/math:random",
        "//third_party/wayland",
        "//third_party/system/xkbcommon",
        "//third_party/system/x11",
    ],
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
