load("@rules_cc//cc/toolchains:tool.bzl", "cc_tool")
load("@rules_cc//cc/toolchains:tool_map.bzl", "cc_tool_map")

alias(
    name = "all_tools",
    actual = select({
        "@platforms//os:macos": ":macos_tools",
        "//conditions:default": ":default_tools",
    }),
    visibility = ["//visibility:public"],
)

COMMON_TOOLS = {
    "@rules_cc//cc/toolchains/actions:assembly_actions": ":clang",
    "@rules_cc//cc/toolchains/actions:cpp_compile_actions": ":clang++",
    "@rules_cc//cc/toolchains/actions:link_actions": ":lld",
    "@rules_cc//cc/toolchains/actions:objcopy_embed_data": ":llvm-objcopy",
    "@rules_cc//cc/toolchains/actions:strip": ":llvm-strip",
}

cc_tool_map(
    name = "default_tools",
    tools = COMMON_TOOLS | {
        "@rules_cc//cc/toolchains/actions:ar_actions": ":llvm-ar",
    },
    visibility = ["//visibility:private"],
)

cc_tool_map(
    name = "macos_tools",
    tools = COMMON_TOOLS | {
        "@rules_cc//cc/toolchains/actions:ar_actions": ":llvm-libtool-darwin",
    },
    visibility = ["//visibility:private"],
)

cc_tool(
    name = "clang",
    src = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:bin/clang",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:bin/clang",
    }),
    data = [
        ":exec_platform_builtin_headers",
        ":exec_platform_multicall_support_files",
    ],
)

cc_tool(
    name = "clang++",
    src = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:bin/clang++",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:bin/clang++",
    }),
    data = [
        ":exec_platform_builtin_headers",
        ":exec_platform_multicall_support_files",
    ],
)

cc_tool(
    name = "lld",
    src = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:bin/clang++",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:bin/clang++",
    }),
    data = [
        ":exec_platform_builtin_headers",
        ":exec_platform_linker_builtins",
        ":exec_platform_multicall_support_files",
    ],
)

cc_tool(
    name = "llvm-ar",
    src = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:bin/llvm-ar",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:bin/llvm-ar",
    }),
    data = [":exec_platform_multicall_support_files"],
)

cc_tool(
    name = "llvm-libtool-darwin",
    src = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:bin/llvm-libtool-darwin",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:bin/llvm-libtool-darwin",
    }),
    data = [":exec_platform_multicall_support_files"],
)

cc_tool(
    name = "llvm-objcopy",
    src = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:bin/llvm-objcopy",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:bin/llvm-objcopy",
    }),
    data = [":exec_platform_multicall_support_files"],
)

cc_tool(
    name = "llvm-objdump",
    src = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:bin/llvm-objdump",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:bin/llvm-objdump",
    }),
    data = [":exec_platform_multicall_support_files"],
)

cc_tool(
    name = "llvm-cov",
    src = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:bin/llvm-cov",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:bin/llvm-cov",
    }),
    data = [":exec_platform_multicall_support_files"],
)

cc_tool(
    name = "llvm-strip",
    src = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:bin/llvm-strip",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:bin/llvm-strip",
    }),
    data = [":exec_platform_multicall_support_files"],
)

cc_tool(
    name = "clang-tidy",
    src = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:bin/clang-tidy",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:bin/clang-tidy",
    }),
    data = [
        ":exec_platform_builtin_headers",
        ":exec_platform_multicall_support_files",
    ],
)

#################################
#   Platform-specific aliases   #
#################################

alias(
    name = "exec_platform_builtin_headers",
    actual = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:builtin_headers",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:builtin_headers",
    }),
    visibility = ["//visibility:private"],
)

alias(
    name = "exec_platform_multicall_support_files",
    actual = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:multicall_support_files",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:multicall_support_files",
    }),
    visibility = ["//visibility:private"],
)

alias(
    name = "exec_platform_linker_builtins",
    actual = select({
        "//rules/constraints:linux_aarch64": "@clang-linux-aarch64//:linker_builtins",
        "//rules/constraints:linux_x86_64": "@clang-linux-x86_64//:linker_builtins",
    }),
    visibility = ["//visibility:private"],
)
