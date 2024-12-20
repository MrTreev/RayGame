def _rg_system_library_impl(name, libname, libhdrs, hdrdir, **kwargs):
    import_lib = "rg_system_library_{}-import".format(name)
    import_hdrs = "rg_system_library_{}-import-headers".format(name)
    if hdrdir != '':
        fulldir = hdrdir + "/"
    else:
        fulldir = ""
    import_full_hdrs = [fulldir]
    native.genrule(
        name = import_hdrs,
        outs = [libhdrs],
        cmd = "mkdir -p \"{outdir}\" && cp {infiles} \"{outdir}\"".format(
            infiles = libhdrs,
            outdir = "$(RULEDIR)/%s" % hdrdir,
        ),
        visibility = ["//macro:__pkg__"],
    )
    native.cc_import(
        name = import_lib,
        hdrs = [":" + import_hdrs],
        interface_library = libname,
        system_provided = True,
        visibility = ["//macro:__pkg__"],
    )
    native.cc_library(
        name = name,
        deps = [":" + import_lib],
        **kwargs
    )

rg_system_library = macro(
    inherit_attrs = native.cc_library,
    attrs = {
        "libname": attr.string(mandatory = True),
        "libhdrs": attr.string_list(mandatory = True),
        "hdrdir":  attr.string(default = "", mandatory = False),
    },
    implementation = _rg_system_library_impl,
)
