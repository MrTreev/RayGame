load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

def rg_cc_binary(name, **kwargs):
    cc_binary(
        name = name,
        srcs = kwargs.pop("srcs", []),
        deps = kwargs.pop("deps", []),
        visibility = kwargs.pop("visibility", ["//visibility:public"]),
        **kwargs
    )

def rg_cc_library(name, **kwargs):
    cc_library(
        name = name,
        hdrs = kwargs.pop("hdrs", []),
        srcs = kwargs.pop("srcs", []),
        deps = kwargs.pop("deps", []),
        visibility = kwargs.pop("visibility", ["//visibility:public"]),
        **kwargs
    )

def rg_cc_single(name, **kwargs):
    rg_cc_library(
        name = name,
        hdrs = [name + ".h"],
        srcs = [name + ".cpp"],
        visibility = kwargs.pop("visibility", ["//visibility:public"]),
        **kwargs
    )

def rg_cc_test(name, **kwargs):
    my_deps = kwargs.pop("deps", [])
    testlib = kwargs.pop("testlib", ["//tests/raytest"])
    cc_test(
        name = name,
        srcs = kwargs.pop("srcs", []),
        deps = my_deps + testlib,
        visibility = kwargs.pop("visibility", ["//visibility:public"]),
        **kwargs
    )

def rg_cc_singletest(name, **kwargs):
    rg_cc_test(
        name = name,
        srcs = [name + ".cpp"],
        visibility = kwargs.pop("visibility", ["//visibility:public"]),
        **kwargs
    )
