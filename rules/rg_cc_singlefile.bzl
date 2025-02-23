load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

def _rg_cc_library_impl(
    name,
    srcs,
    hdrs,
    tsts,
    copts,
    deps,
    size,
    testlibs,
    testonlydeps,
    create_test,
    private_srcs,
    visibility,
    **kwargs
):
    add_copts = [
        # Diagnostics
        "-fcolor-diagnostics",
        "-Werror",
        "-Wall",
        "-Weverything",
        "-pedantic",
        "-Wthread-safety",
        "-Wself-assign",
        "-Wno-padded",
        "-Wno-c99-extensions",
        "-Wno-c99-compat",
        "-Wno-c++-compat",
        "-Wno-c++20-compat",
        "-Wno-c++98-compat",
        "-Wno-c++98-compat-pedantic",
        "-Wno-pre-c++20-compat-pedantic",
        "-Wno-pre-c++17-compat-pedantic",
        "-Wno-switch-default",
        "-Wno-c++20-extensions",
        "-Wno-unused-macros",
        "-Wno-unsafe-buffer-usage",
        "-Wno-c23-extensions",
    ]
    cc_library(
        name = name,
        deps = deps,
        hdrs = hdrs,
        srcs = srcs + private_srcs,
        copts = copts + add_copts,
        visibility = visibility,
        **kwargs
    )

    if create_test:
        cc_test(
            name = name + "_test",
            srcs = tsts,
            copts = copts + add_copts,
            deps = [":" + name] + testonlydeps + testlibs,
            size = size,
            visibility = visibility,
        )

rg_cc_library = macro(
    inherit_attrs = native.cc_library,
    attrs = {
        "create_test":  attr.bool(default=False),
        "private_srcs": attr.label_list(default=[]),
        "size":         attr.string(default="small", configurable=False),
        "testlibs":     attr.label_list(default=["//raygame/core/test"]),
        "testonlydeps": attr.label_list(default=[]),
        "tsts":         attr.label_list(default=[]),
        "copts":        attr.label_list(default=[])
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
