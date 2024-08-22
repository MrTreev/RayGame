def cpp_platform_toolchain_pair(
    name,
    constraint_values,
    cc_toolchain,
):
    native.platform(
        name = "%s_platform" % name,
        constraint_values = constraint_values
    )
    native.toolchain(
        name = "%s" % name,
        target_compatible_with = constraint_values,
        toolchain = cc_toolchain,
        toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
    )
