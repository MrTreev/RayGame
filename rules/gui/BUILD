load("@bazel_skylib//rules:common_settings.bzl", "string_flag")

string_flag(
    name = "linux_backend",
    values = [
        "wayland",
        "x11",
    ],
    build_setting_default = "wayland",
    visibility = ["//visibility:private"],
)

config_setting(
    name = "dwm",
    constraint_values = ["//rules/os:windows"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "cocoa",
    constraint_values = ["//rules/os:mac"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "wayland",
    constraint_values = ["//rules/os:linux"],
    flag_values = { ":linux_backend": "wayland" },
    visibility = ["//visibility:public"],
)

config_setting(
    name = "x11",
    constraint_values = ["//rules/os:linux"],
    flag_values = { ":linux_backend": "x11" },
    visibility = ["//visibility:public"],
)
