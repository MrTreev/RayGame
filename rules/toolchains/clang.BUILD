load("@bazel_skylib//rules/directory:directory.bzl", "directory")
load("@bazel_skylib//rules/directory:subdirectory.bzl", "subdirectory")

package(default_visibility = ["//visibility:public"])

exports_files(glob(["bin/**"]))

# Directory-based rules in this toolchain only referece things in
# lib/ or include/ subdirectories.
directory(
    name = "toolchain_root",
    srcs = glob([
        "lib/**",
        "include/**",
    ]),
)

subdirectory(
    name = "include-c++-v1",
    parent = ":toolchain_root",
    path = "include/c++/v1",
)

subdirectory(
    name = "lib-clang-include",
    parent = ":toolchain_root",
    path = "lib/clang/19/include",
)

subdirectory(
    name = "include-x86_64-unknown-linux-gnu-c++-v1",
    parent = ":toolchain_root",
    path = "include/x86_64-unknown-linux-gnu/c++/v1",
)

filegroup(
    name = "builtin_headers",
    srcs = [
        ":include-c++-v1",
        ":include-x86_64-unknown-linux-gnu-c++-v1",
        ":lib-clang-include",
    ],
)

# Various supporting files needed to run the linker.
filegroup(
    name = "linker_builtins",
    data = glob([
        "bin/lld*",
        "bin/ld*",
        "lib/**/*.a",
        "lib/**/*.so*",
        "lib/**/*.o",
    ]) + [
        ":multicall_support_files",
    ],
)

# Some toolchain distributions use busybox-style handling of tools, so things
# like `clang++` just redirect to a `llvm` binary. This glob catches this
# binary if it's included in the distribution, and is a no-op if the multicall
# binary doesn't exist.
filegroup(
    name = "multicall_support_files",
    srcs = glob(
        ["bin/llvm"],
        allow_empty = True,
    ),
)
