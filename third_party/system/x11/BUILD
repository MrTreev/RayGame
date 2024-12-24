cc_library(
    name = "x11",
    deps = [":libx11-import"],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "libx11-import",
    hdrs = [":libx11-headers"],
    interface_library = ":libx11-sofile",
    system_provided = True,
)

LIBX11HDRS = [
    "X11/Xlib.h",
]

genrule(
    name = "libx11-headers",
    outs = LIBX11HDRS,
    cmd = "mkdir -p \"{outdir}\" && cp {infiles} \"{outdir}\"".format(
        outdir = "$(RULEDIR)/X11",
        infiles = " ".join(["/usr/include/{}".format(f) for f in LIBX11HDRS]),
    ),
)

genrule(
    name = "libx11-sofile",
    outs = ["libX11.so"],
    cmd = "cp /usr/lib/libX11.so $(RULEDIR)",
)
