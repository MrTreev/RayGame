load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test", "cc_binary")

def rg_cc_binary(name, **kwargs):
    cc_binary(
        name = name,
        srcs = kwargs.pop("srcs", default=[]),
        deps = kwargs.pop("deps", default=[]),
        visibility = kwargs.pop("visibility", default=["//visibility:public"]),
        **kwargs
    )

def rg_cc_library(name, **kwargs):
    cc_library(
        name = name,
        hdrs = kwargs.pop("hdrs", default=[]),
        srcs = kwargs.pop("srcs", default=[]),
        deps = kwargs.pop("deps", default=[]),
        visibility = kwargs.pop("visibility", default=["//visibility:public"]),
        **kwargs
    )

def rg_cc_single(name, **kwargs):
    rg_cc_library(
        name = name,
        hdrs = [name + ".h"],
        srcs = [name + ".cpp"],
        visibility = kwargs.pop("visibility", default=["//visibility:public"]),
        **kwargs
    )

def rg_cc_test(name, **kwargs):
    my_deps = kwargs.pop("deps", default=[])
    testlib = kwargs.pop("testlib", default=["//tests/raytest"])
    cc_test(
        name = name,
        srcs = kwargs.pop("srcs", default=[]),
        deps = my_deps + testlib,
        visibility = kwargs.pop("visibility", default=["//visibility:public"]),
        **kwargs
    )

def rg_cc_singletest(name, **kwargs):
    rg_cc_test(
        name = name,
        srcs = [name + ".cpp"],
        visibility = kwargs.pop("visibility", default=["//visibility:public"]),
        **kwargs
    )
