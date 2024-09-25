cc_library(
    name = "core",
    srcs = glob(["**/*.h"]),
    hdrs = glob(["**/*.cpp"]),
    visibility = ["//visibility:public"],
    deps = ["//core/windowimpl"],
)

filegroup(
    name = "doxygen_files",
    srcs = [
        "//core/windowimpl:doxygen_files",
    ] + glob([
        "**/*.h",
        "**/*.dox",
    ]),
    visibility = [ "//visibility:public" ],
)
