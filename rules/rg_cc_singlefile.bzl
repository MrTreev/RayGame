load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

def _rg_cc_singlefile_impl(name, create_test, testlibs, testonlydeps, visibility, deps, **kwargs):
    my_deps = deps or []
    cc_library(
        name = name,
        deps = my_deps,
        hdrs = [name + ".h"],
        srcs = [name + ".cpp"],
        visibility = visibility,
        **kwargs
    )

    if create_test:
        target_name = ":" + name
        testdeps = [target_name] + testonlydeps + testlibs
        cc_test(
            name = name + "_test",
            srcs = [name + "_test.cpp"],
            deps = testdeps,
            visibility = visibility,
        )

rg_cc_singlefile = macro(
    inherit_attrs = native.cc_library,
    attrs = {
        "create_test": attr.bool(default=True),
        "testlibs": attr.label_list(default=["//test"]),
        "testonlydeps": attr.label_list(default=[]),
        "hdrs": None,
        "srcs": None,
    },
    implementation = _rg_cc_singlefile_impl,
)
