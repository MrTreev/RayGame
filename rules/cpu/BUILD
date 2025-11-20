load("@bazel_skylib//lib:selects.bzl", "selects")

config_setting(
    name = "aarch32",
    constraint_values = ["@platforms//cpu:aarch32"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "aarch64",
    constraint_values = ["@platforms//cpu:aarch64"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "armv6-m",
    constraint_values = ["@platforms//cpu:armv6-m"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "armv7-m",
    constraint_values = ["@platforms//cpu:armv7-m"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "armv7e-m",
    constraint_values = ["@platforms//cpu:armv7e-m"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "armv7e-mf",
    constraint_values = ["@platforms//cpu:armv7e-mf"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "armv8-m",
    constraint_values = ["@platforms//cpu:armv8-m"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "arm64_32",
    constraint_values = ["@platforms//cpu:arm64_32"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "arm64e",
    constraint_values = ["@platforms//cpu:arm64e"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "armv7",
    constraint_values = ["@platforms//cpu:armv7"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "armv7k",
    constraint_values = ["@platforms//cpu:armv7k"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "cortex-r52",
    constraint_values = ["@platforms//cpu:cortex-r52"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "cortex-r82",
    constraint_values = ["@platforms//cpu:cortex-r82"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "i386",
    constraint_values = ["@platforms//cpu:i386"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "ppc",
    constraint_values = ["@platforms//cpu:ppc"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "ppc32",
    constraint_values = ["@platforms//cpu:ppc32"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "ppc64le",
    constraint_values = ["@platforms//cpu:ppc64le"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "x86_32",
    constraint_values = ["@platforms//cpu:x86_32"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "x86_64",
    constraint_values = ["@platforms//cpu:x86_64"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "wasm32",
    constraint_values = ["@platforms//cpu:wasm32"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "wasm64",
    constraint_values = ["@platforms//cpu:wasm64"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "mips64",
    constraint_values = ["@platforms//cpu:mips64"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "riscv32",
    constraint_values = ["@platforms//cpu:riscv32"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "riscv64",
    constraint_values = ["@platforms//cpu:riscv64"],
    visibility = ["//visibility:public"],
)

selects.config_setting_group(
    name = "any_64_bit",
    match_any = [
        ":aarch64",
        ":arm64e",
        ":cortex-r82",
        ":ppc",
        ":ppc64le",
        ":x86_64",
        ":wasm64",
        ":mips64",
        ":riscv64",
    ],
    visibility = ["//visibility:private"],
)

selects.config_setting_group(
    name = "any_32_bit",
    match_any = [
        ":aarch32",
        ":armv6-m",
        ":armv7-m",
        ":armv7e-m",
        ":armv7e-mf",
        ":armv8-m",
        ":arm64_32",
        ":armv7",
        ":armv7k",
        ":cortex-r52",
        ":i386",
        ":ppc32",
        ":x86_32",
        ":wasm32",
        ":riscv32",
    ],
    visibility = ["//visibility:private"],
)

selects.config_setting_group(
    name = "any_arm",
    match_any = [
        ":aarch32",
        ":aarch64",
        ":armv6-m",
        ":armv7-m",
        ":armv7e-m",
        ":armv7e-mf",
        ":armv8-m",
        ":arm64_32",
        ":arm64e",
        ":armv7",
        ":armv7k",
        ":cortex-r52",
        ":cortex-r82",
    ],
    visibility = ["//visibility:private"],
)

config_setting(
    name = "64bit",
    constraint_values = [":any_64_bit"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "32bit",
    constraint_values = [":any_32_bit"],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "arm",
    constraint_values = [":any_arm"],
    visibility = ["//visibility:public"],
)
