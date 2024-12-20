load(":wayland_protocol.bzl", "rg_wayland_protocol")

cc_library(
    name = "wayland",
    deps = [
        ":libwayland-client",
        "//third_party/xkbcommon:libxkbcommon",
        ":xdg-shell-client-protocol",
        ":wayland-client-protocol",
    ],
    visibility = ["//visibility:public"],
)

rg_wayland_protocol(
    name = "xdg-shell-client-protocol",
    protocol = "xdg-shell",
    visibility = ["//visibility:public"],
)

rg_wayland_protocol(
    name = "wayland-client-protocol",
    protocol = "wayland",
    visibility = ["//visibility:public"],
)

cc_import(
    name = "libwayland-client-import",
    hdrs = [":libwayland-client-headers"],
    interface_library = "libwayland-client.so",
    system_provided = True,
)

cc_library(
    name = "libwayland-client",
    deps = [":libwayland-client-import"],
    visibility = ["//visibility:public"],
)

genrule(
    name = "libwayland-client-headers",
    outs = [
        "libwayland/wayland-client.h",
        "libwayland/wayland-client-core.h",
        "libwayland/wayland-client-protocol.h",
    ],
    cmd = "cp {} {} {} \"$(RULEDIR)/libwayland\"".format(
        "/usr/include/wayland-client.h",
        "/usr/include/wayland-client-core.h",
        "/usr/include/wayland-client-protocol.h",
    ),
)
