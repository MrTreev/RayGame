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
		"//raygame/core/math:vector",
	],
    implementation_deps = [
		"//raygame/core/base:condition",
		"//raygame/core/base:logger",
		"//raygame/core/base:types",
		"//raygame/core/drawing:colour",
		"//raygame/core/math:arithmetic",
		"//raygame/core/math:numeric_cast",
		"//raygame/core/math:random",
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
