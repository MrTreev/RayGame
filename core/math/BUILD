cc_library(
	name = "math",
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
