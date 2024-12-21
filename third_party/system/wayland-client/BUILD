cc_library(
    name = "wayland-client",
    deps = [":libwayland-client-import"],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "libwayland-client-import",
    hdrs = [":libwayland-client-headers"],
    interface_library = "libwayland-client.so",
    system_provided = True,
)

genrule(
    name = "libwayland-client-headers",
    outs = [
        "libwayland/wayland-client.h",
        "libwayland/wayland-client-core.h",
        "libwayland/wayland-client-protocol.h",
    ],
    cmd = "cp {} {} {} \"$(RULEDIR)/libwayland\"".format(
        "/usr/include/wayland-client.h",
        "/usr/include/wayland-client-core.h",
        "/usr/include/wayland-client-protocol.h",
    ),
)
