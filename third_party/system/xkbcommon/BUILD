cc_library(
    name = "xkbcommon",
    deps = [":libxkbcommon-import"],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "libxkbcommon-import",
    hdrs = [":libxkbcommon-headers"],
    interface_library = ":libxkbcommon-sofile",
    system_provided = True,
)

LIBXKBCOMMONHDRS = [
    "xkbcommon/xkbcommon.h",
    "xkbcommon/xkbcommon-compat.h",
    "xkbcommon/xkbcommon-compose.h",
    "xkbcommon/xkbcommon-keysyms.h",
    "xkbcommon/xkbcommon-names.h",
    "xkbcommon/xkbcommon-x11.h",
    "xkbcommon/xkbregistry.h",
]

genrule(
    name = "libxkbcommon-headers",
    outs = LIBXKBCOMMONHDRS,
    cmd = "mkdir -p \"{outdir}\" && cp {infiles} \"{outdir}\"".format(
        outdir = "$(RULEDIR)/xkbcommon",
        infiles = " ".join(["/usr/include/{}".format(f) for f in LIBXKBCOMMONHDRS]),
    ),
)

genrule(
    name = "libxkbcommon-sofile",
    outs = ["libxkbcommon.so"],
    cmd = "cp /usr/lib/libxkbcommon.so $(RULEDIR)",
)
