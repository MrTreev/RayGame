load("@bazel_skylib//rules:native_binary.bzl", "native_binary")

native_binary(
    name = "doxygen_exe",
    src = select({
        "@platforms//os:windows": "doxygen.exe",
        "//conditions:default": "bin/doxygen",
    }),
    out = select({
        "@platforms//os:windows": "doxygen.exe",
        "//conditions:default": "doxygen",
    }),
    data = select({
        "@platforms//os:linux": [],
        "@platforms//os:windows": ["libclang.dll"],
    }),
    visibility = [ "//visibility:public" ],
)
