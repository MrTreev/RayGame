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
		"detail/wl_keyboard.cpp",
		"detail/wl_pointer.cpp",
		"detail/wl_registry.cpp",
		"detail/wl_seat.cpp",
		"detail/wl_surface.cpp",
		"detail/xdg_surface.cpp",
		"detail/xdg_toplevel.cpp",
		"detail/xdg_wm_base.cpp",
	],
	deps = [
		"//raygame/core/math:vector",
	],
    implementation_deps = [
		"//raygame/core:condition",
		"//raygame/core:logger",
		"//raygame/core:types",
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
