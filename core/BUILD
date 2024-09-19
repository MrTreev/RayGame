cc_library(
    name = "core",
    srcs = glob([
        "*.h",
        "windowimpl/*.h",
    ]) + select({
        "@platforms//os:linux": glob(["windowimpl/wayland/*.h"]),
    }),
    hdrs = glob([
        "*.cpp",
        "windowimpl/*.cpp",
    ]) + select({
        "@platforms//os:linux": glob(["windowimpl/wayland/*.cpp"]),
    }),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "doxygen_files",
    srcs = [
        "//core/windowimpl:doxygen_files",
    ] + glob([
        "**/*.h",
        "**/*.inl",
        "**/*.dox",
    ]),
    visibility = [ "//visibility:public" ],
)

filegroup(
    name = "doxygen_data_files",
    srcs = [],
    visibility = [ "//visibility:public" ],
)
