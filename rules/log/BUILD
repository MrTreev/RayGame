load("@bazel_skylib//rules:common_settings.bzl", "string_flag", "bool_flag")
package(default_visibility = ["//visibility:public"])

string_flag(
    name = "level",
    values = [
        "trace",
        "debug",
        "info",
        "note",
        "progress",
        "warning",
        "error",
        "fatal",
    ],
    build_setting_default = "debug",
)

bool_flag(
    name = "source_location",
    build_setting_default = True,
)
