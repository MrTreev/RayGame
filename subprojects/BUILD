alias(
    name = "doxygen",
    actual = select({
        "@platforms//os:linux": "@linux_x64_doxygen//:doxygen_exe",
        "//conditions:default": "@platforms//:incompatible",
    }),
    tags = ["manual"],
    visibility = ["//visibility:public"],
)
