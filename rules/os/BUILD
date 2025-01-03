load("@bazel_skylib//lib:selects.bzl", "selects")

alias(
    name = "android",
    actual = "@platforms//os:android",
    visibility = ["//visibility:public"],
)

alias(
    name = "freebsd",
    actual = "@platforms//os:freebsd",
    visibility = ["//visibility:public"],
)

alias(
    name = "netbsd",
    actual = "@platforms//os:netbsd",
    visibility = ["//visibility:public"],
)

alias(
    name = "openbsd",
    actual = "@platforms//os:openbsd",
    visibility = ["//visibility:public"],
)

alias(
    name = "linux",
    actual = "@platforms//os:linux",
    visibility = ["//visibility:public"],
)

alias(
    name = "mac",
    actual = "@platforms//os:macos",
    visibility = ["//visibility:public"],
)

alias(
    name = "qnx",
    actual = "@platforms//os:qnx",
    visibility = ["//visibility:public"],
)

alias(
    name = "windows",
    actual = "@platforms//os:windows",
    visibility = ["//visibility:public"],
)

selects.config_setting_group(
    name = "any_bsd",
    match_any = [":freebsd", ":netbsd", ":openbsd"],
    visibility = ["//visibility:private"],
)

config_setting(
    name = "bsd",
    constraint_values  = [":any_bsd"],
    visibility = ["//visibility:public"],
)
