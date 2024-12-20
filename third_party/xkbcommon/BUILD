load("//rules/system:system_library.bzl", "rg_system_library")

rg_system_library(
    name = "libxkbcommon",
    libname = "libxkbcommon.so",
    libhdrs = [
        "xkbcommon/xkbcommon.h",
        "xkbcommon/xkbcommon-compat.h",
        "xkbcommon/xkbcommon-compose.h",
        "xkbcommon/xkbcommon-keysyms.h",
        "xkbcommon/xkbcommon-names.h",
        "xkbcommon/xkbcommon-x11.h",
        "xkbcommon/xkbregistry.h",
    ],
    hdrdir = "xkbcommon",
    visibility = ["//visibility:public"],
)

# cc_library(
#     name = "libxkbcommon",
#     deps = [":libxkbcommon-import"],
#     visibility = ["//visibility:public"],
# )
#
# cc_import(
#     name = "libxkbcommon-import",
#     hdrs = [":libxkbcommon-headers"],
#     interface_library = "libxkbcommon.so",
#     system_provided = True,
# )
#
# LIBXKBCOMMONHDRS = [
#     "xkbcommon/xkbcommon.h",
#     "xkbcommon/xkbcommon-compat.h",
#     "xkbcommon/xkbcommon-compose.h",
#     "xkbcommon/xkbcommon-keysyms.h",
#     "xkbcommon/xkbcommon-names.h",
#     "xkbcommon/xkbcommon-x11.h",
#     "xkbcommon/xkbregistry.h",
# ]
#
# genrule(
#     name = "libxkbcommon-headers",
#     outs = LIBXKBCOMMONHDRS,
#     cmd = "mkdir -p \"{outdir}\" && cp {infiles} \"{outdir}\"".format(
#         outdir = "$(RULEDIR)/xkbcommon",
#         infiles = " ".join(["/usr/include/{}".format(f) for f in LIBXKBCOMMONHDRS]),
#     ),
# )
