load("//rules/wayland:wayland_protocol.bzl", "rg_wayland_protocol")

cc_library(
    name = "wayland-protocols",
    hdrs = [
        "wayland-client-protocol.h",
        "xdg-shell-client-protocol.h",
    ],
    srcs = [
        "wayland-protocol.c",
        "xdg-shell-protocol.c",
    ],
    includes = ["."],
    conlyopts = ["-w"], # Disable warnings as this is generated external code
    deps = [
        ":libwayland-client",
        ":libxkbcommon",
    ],
    visibility = ["//visibility:public"],
)

rg_

cc_library(
    name = "libwayland-client",
    deps = [":libwayland-client-import"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libxkbcommon",
    deps = [":libxkbcommon-import"],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "libwayland-client-import",
    hdrs = [":wayland-client-headers"],
    interface_library = "libwayland-client.so",
    system_provided = True,
)

cc_import(
    name = "libxkbcommon-import",
    hdrs = [":libxkbcommon-headers"],
    interface_library = "libxkbcommon.so",
    system_provided = True,
)

genrule(
    name = "libwayland-client-headers",
    outs = [
        "wayland-client.h",
        "wayland-client-core.h",
        "wayland-client-protocol.h",
    ],
    cmd = "cp /usr/include/wayland-client.h /usr/include/wayland-client-core.h /usr/include/wayland-client-core.h \"$(RULEDIR)\"",
)

genrule(
    name = "libxkbcommon-headers",
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
