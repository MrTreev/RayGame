load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

def _rg_cc_library_impl(
    name,
    srcs,
    hdrs,
    tsts,
    deps,
    size,
    testlibs,
    testonlydeps,
    create_test,
    visibility,
    **kwargs
):
    my_deps = deps or []
    cc_library(
        name = name,
        deps = deps,
        hdrs = hdrs,
        srcs = srcs,
        visibility = visibility,
        **kwargs
    )

    if create_test:
        cc_test(
            name = name + "_test",
            srcs = tsts,
            deps = [":" + name] + testonlydeps + testlibs,
            size = size,
            visibility = visibility,
        )

rg_cc_library = macro(
    inherit_attrs = native.cc_library,
    attrs = {
        "create_test":  attr.bool(default=False),
        "testlibs":     attr.label_list(default=["//test"]),
        "testonlydeps": attr.label_list(default=[]),
        "tsts":         attr.label_list(default=[]),
        "size":         attr.string(default="small", configurable=False),
    },
    implementation = _rg_cc_library_impl,
)

def rg_cc_single(name, **kwargs):
    visibility = kwargs.pop("visibility", default=["//visibility:public"])
    create_test = kwargs.pop("create_test", default=True)
    hdrs = [name + ".h"]
    srcs = [name + ".cpp"]
    if create_test:
        tsts = [name + "_test.cpp"]
        rg_cc_library(
            name = name,
            hdrs = hdrs,
            srcs = srcs,
            tsts = tsts,
            create_test = create_test,
            visibility = visibility,
            **kwargs
        )
    else:
        rg_cc_library(
            name = name,
            hdrs = hdrs,
            srcs = srcs,
            create_test = create_test,
            visibility = visibility,
            **kwargs
        )
