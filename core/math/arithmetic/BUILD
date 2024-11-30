filegroup(
    name = "headers",
    srcs = [
    	"safe_add.h",
    	"safe_div.h",
    	"safe_mult.h",
    	"safe_sub.h",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "sources",
    srcs = [
    	"safe_add.cpp",
    	"safe_div.cpp",
    	"safe_mult.cpp",
    	"safe_sub.cpp",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "safe_add",
    srcs = ["safe_add_test.cpp"],
    deps = ["//core/math:test"],
    size = "small",
)

cc_test(
    name = "safe_sub",
    srcs = ["safe_sub_test.cpp"],
    deps = ["//core/math:test"],
    size = "small",
)

cc_test(
    name = "safe_mult",
    srcs = ["safe_mult_test.cpp"],
    deps = ["//core/math:test"],
    size = "small",
)

cc_test(
    name = "safe_div",
    srcs = ["safe_div_test.cpp"],
    deps = ["//core/math:test"],
    size = "small",
)
