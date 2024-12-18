cc_library(
    name = "libwayland-client",
    deps = [":wayland-client"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libxkbcommon",
    deps = [":xkbcommon"],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "wayland-client",
    hdrs = [":wayland-client_headers"],
    interface_library = "libwayland-client.so",
    system_provided = True,
)

cc_import(
    name = "wayland-cursor",
    hdrs = [":wayland-cursor_headers"],
    interface_library = "libwayland-cursor.so",
    system_provided = True,
)

cc_import(
    name = "xkbcommon",
    hdrs = [ ":xkbcommon_headers", ],
    interface_library = "libxkbcommon.so",
    system_provided = True,
)

genrule(
    name = "wayland-cursor_headers",
    outs = ["wayland-cursor.h"],
    cmd = "cp /usr/include/wayland-cursor.h \"$(RULEDIR)\"",
)

genrule(
    name = "wayland-client_headers",
    outs = ["wayland-client.h"],
    cmd = "cp /usr/include/wayland-client.h \"$(RULEDIR)\"",
)

genrule(
    name = "xkbcommon_headers",
    outs = [
        "xkbcommon/xkbcommon.h",
        "xkbcommon/xkbcommon-compat.h",
        "xkbcommon/xkbcommon-compose.h",
        "xkbcommon/xkbcommon-keysyms.h",
        "xkbcommon/xkbcommon-names.h",
        "xkbcommon/xkbcommon-x11.h",
        "xkbcommon/xkbregistry.h",
    ],
    cmd = "mkdir -p \"$(RULEDIR)/xkbcommon\" && cp /usr/include/xkbcommon/* \"$(RULEDIR)/xkbcommon/\"",
)
