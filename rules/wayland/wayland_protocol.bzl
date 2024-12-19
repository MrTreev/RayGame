def _rg_wayland_protocol_impl(ctx):
    """
    Create the all the parts required for a wayland protocol.
    Args:
      name: Rule name.
      protocol: Protocol name
      deps: Library deps
    """
    out_header = ctx.outputs.header
    out_source = ctx.outputs.source
    xml_file = ctx.file.xml

    ctx.actions.run_shell(
        inputs  = [xml_file],
        outputs = [out_header],
        command = "wayland-scanner client-header $@",
        arguments = [xml_file, out_header],
        toolchain = None,
    )

    ctx.actions.run_shell(
        inputs  = [xml_file],
        outputs = [out_source],
        command = "wayland-scanner public-code $@",
        arguments = [xml_file, out_source],
        toolchain = None,
    )

rg_wayland_protocol = rule(
    implementation = _rg_wayland_protocol_impl,
    attrs = {
        "protocol": attr.string(),
        "xml": attr.label(allow_single_file = [".xml"])
        "header": attr.output(mandatory = True)
        "source": attr.output(mandatory = True)
    },
)
