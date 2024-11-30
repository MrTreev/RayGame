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
        "//subprojects/wayland-protocols",
	],
	visibility = [ "//visibility:public" ]
)
