cc_library(
	name = "drawing",
	hdrs = [
		"window.h",
		"x11.h",
		"wayland.h",
	],
	srcs = [
		"window.cpp",
		"x11.cpp",
		"wayland.cpp",
	],
	deps = [
		"//core/base",
		"//core/math",
		"//core/drawing",
        "//core/window/detail",
	],
	visibility = [ "//visibility:public" ]
)
