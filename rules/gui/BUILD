load("@bazel_skylib//rules:common_settings.bzl", "string_flag")

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
    visibility = ["//visibility:public"],
)

config_setting(
    name = "x11",
    constraint_values = ["//rules/os:linux"],
    visibility = ["//visibility:public"],
)
