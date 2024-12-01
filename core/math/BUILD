cc_library(
	name = "math",
	hdrs = [
    	"arithmetic/safe_add.h",
    	"arithmetic/safe_div.h",
    	"arithmetic/safe_mult.h",
    	"arithmetic/safe_sub.h",
    	"arithmetic.h",
    	"math.h",
    	"mathrule.h",
    	"numeric_cast.h",
    	"random.h",
    	"rect.h",
    	"vector.h",
	],
	srcs = [
    	"arithmetic/safe_add.cpp",
    	"arithmetic/safe_div.cpp",
    	"arithmetic/safe_mult.cpp",
    	"arithmetic/safe_sub.cpp",
    	"arithmetic.cpp",
    	"math.cpp",
    	"mathrule.cpp",
    	"numeric_cast.cpp",
    	"random.cpp",
    	"rect.cpp",
    	"vector.cpp",
	],
	deps = [
		"//core/base",
	],
	visibility = [ "//visibility:public" ]
)

cc_library(
	name = "math_full_random",
	hdrs = [
    	"//core/math/arithmetic:headers",
    	"arithmetic.h",
    	"math.h",
    	"mathrule.h",
    	"numeric_cast.h",
    	"random.h",
    	"rect.h",
    	"vector.h",
	],
	srcs = [
    	"//core/math/arithmetic:sources",
    	"arithmetic.cpp",
    	"math.cpp",
    	"mathrule.cpp",
    	"numeric_cast.cpp",
    	"random.cpp",
    	"rect.cpp",
    	"vector.cpp",
	],
    defines = ["RAYGAME_USE_FULL_RANDOM"],
	deps = [
		"//core/base",
	],
	visibility = [ "//visibility:public" ]
)

cc_library(
    name = "test",
    deps = [":math", "//test"],
	visibility = [ "//core/math:__subpackages__" ]
)

cc_test(
    name = "numeric_cast",
    srcs = ["numeric_cast_test.cpp"],
    deps = [":test"],
    size = "small",
)

cc_test(
    name = "random",
    srcs = ["random_test.cpp"],
    deps = [":test"],
    size = "small",
)

cc_test(
    name = "random_full",
    srcs = ["random_test.cpp"],
    deps = [":math_full_random", "//test"],
    defines = ["RAYGAME_USE_FULL_RANDOM"],
    size = "small",
)

cc_test(
    name = "math_test",
    srcs = ["math_test.cpp"],
    deps = [":test"],
    size = "small",
)

cc_test(
    name = "mathrule",
    srcs = ["mathrule_test.cpp"],
    deps = [":test"],
    size = "small",
)

cc_test(
    name = "vector",
    srcs = ["vector_test.cpp"],
    deps = [":test"],
    size = "small",
)

cc_test(
    name = "rect",
    srcs = ["rect_test.cpp"],
    deps = [":test"],
    size = "small",
)

cc_test(
    name = "safe_add",
    srcs = ["arithmetic/safe_add_test.cpp"],
    deps = [":test"],
    size = "small",
)

cc_test(
    name = "safe_sub",
    srcs = ["arithmetic/safe_sub_test.cpp"],
    deps = [":test"],
    size = "small",
)

cc_test(
    name = "safe_mult",
    srcs = ["arithmetic/safe_mult_test.cpp"],
    deps = [":test"],
    size = "small",
)

cc_test(
    name = "safe_div",
    srcs = ["arithmetic/safe_div_test.cpp"],
    deps = [":test"],
    size = "small",
)

filegroup(
    name = "doxyfiles",
    srcs = glob([
            "**/*.h",
            "**/*.dox",
        ],
        allow_empty = True,
    ),
    visibility = ["//visibility:public"],
)
