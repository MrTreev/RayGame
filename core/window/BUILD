cc_library(
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
		"//core/base",
		"//core/math",
		"//core/drawing",
	],
    implementation_deps = [
        "//third_party/wayland",
        "//third_party/system/xkbcommon",
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
