load("@bazel_skylib//rules:common_settings.bzl", "string_flag", "bool_flag")

string_flag(
    name = "level",
    values = [
        "trace",
        "debug",
        "info",
        "warning",
        "error",
        "fatal",
    ],
    build_setting_default = "debug",
    visibility = ["//visibility:public"],
)

string_flag(
    name = "source_location",
    values = [
        "full",
        "base",
        "none",
    ],
    build_setting_default = "full",
    visibility = ["//visibility:public"],
)
