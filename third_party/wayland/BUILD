load("@rules_cc//cc:defs.bzl", "cc_library")
load(":wayland_protocol.bzl", "rg_wayland_protocol")

cc_library(
    name = "wayland",
    implementation_deps = [
        "//third_party/system/wayland-client",
        "//third_party/system/xkbcommon",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":wayland-client-protocol",
        ":xdg-shell-client-protocol",
    ],
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
