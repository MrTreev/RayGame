load("@rules_cc//cc/toolchains:args.bzl", "cc_args")

cc_args(
	names = "compile_settings",
	actions = [
        "@rules_cc//cc/toolchains/actions:c_compile",
        "@rules_cc//cc/toolchains/actions:cpp_compile_actions",
	],
    args = [
		"-std=c++2c",
	],
    visibility = ["//visibility:public"],
)

cc_args(
    name = "warnings",
    actions = [
        "@rules_cc//cc/toolchains/actions:c_compile",
        "@rules_cc//cc/toolchains/actions:cpp_compile_actions",
    ],
    args = [
        "-Weverything",
        "-pedantic",
        "-Wno-padded",
        "-Wno-c99-extensions",
        "-Wno-c99-compat",
        "-Wno-c++-compat",
        "-Wno-c++20-compat",
        "-Wno-c++98-compat",
        "-Wno-c++98-compat-pedantic",
        "-Wno-pre-c++20-compat-pedantic",
        "-Wno-pre-c++17-compat-pedantic",
        "-Wno-switch-default",
        "-Wno-c++20-extensions",
        "-Wno-unused-macros",
    ],
    visibility = ["//visibility:public"],
)

cc_args(
    name = "no_canonical_prefixes",
    actions = [
        "@rules_cc//cc/toolchains/actions:c_compile",
        "@rules_cc//cc/toolchains/actions:cpp_compile_actions",
    ],
    args = ["-no-canonical-prefixes"],
    visibility = ["//visibility:public"],
)
