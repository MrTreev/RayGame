cc_library(
    name = "wayland-client",
    deps = [":libwayland-client-import"],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "libwayland-client-import",
    hdrs = [":libwayland-client-headers"],
    interface_library = ":libwayland-client-sofile",
    system_provided = True,
)

genrule(
    name = "libwayland-client-headers",
    outs = [
        "wayland-client.h",
        "wayland-client-core.h",
        "wayland-client-protocol.h",
    ],
    cmd = "cp {} {} {} \"$(RULEDIR)\"".format(
        "/usr/include/wayland-client.h",
        "/usr/include/wayland-client-core.h",
        "/usr/include/wayland-client-protocol.h",
    ),
)

genrule(
    name = "libwayland-client-sofile",
    outs = ["libwayland-client.so"],
    cmd = "cp /usr/lib/libwayland-client.so $(RULEDIR)",
)
