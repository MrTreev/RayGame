PROC_HDR_FMT = """#pragma once
{pragma}
#include {include}
"""

def _rg_wayland_protocol_impl(ctx):
    """
    Create the all the parts required for a wayland protocol.
    Args:
      name: Rule name.
      protocol: Protocol name
      deps: Library deps
    """
    _file_xml = ctx.file.xml
    _file_hdr = ctx.outputs.header
    _file_src = ctx.outputs.source
    _file_mod = ctx.outputs.modhdr
    _pragma   = ctx.attr.pragma

    ctx.actions.run_shell(
        inputs  = [_file_xml],
        outputs = [_file_hdr],
        command = "wayland-scanner client-header {xml} {hdr}".format(
			xml = _file_xml.path,
            hdr = _file_hdr.path,
		),
    )

    ctx.actions.run_shell(
        inputs  = [_file_xml],
        outputs = [_file_src],
        command = "wayland-scanner public-code {xml} {src}".format(
			xml = _file_xml.path,
            src = _file_src.path,
		),
    )

    ctx.actions.write(
        output = _file_mod,
        is_executable = False,
        content = PROC_HDR_FMT.format(
            include = "<{}>".format(_file_hdr.basename),
            pragma = _pragma,
        ),
    )

_rg_wayland_protocol_rule = rule(
    implementation = _rg_wayland_protocol_impl,
    attrs = {
        "protocol": attr.string(),
        "xml":      attr.label(allow_single_file = [".xml"]),
        "pragma":   attr.string(mandatory = True),
        "header":   attr.output(mandatory = True),
        "modhdr":   attr.output(mandatory = True),
        "source":   attr.output(mandatory = True),
    },
)

def rg_wayland_protocol(**kwargs):
    name        = kwargs.pop("name")
    protocol    = kwargs.pop("protocol",    default = name)
    xml_file    = kwargs.pop("xml",         default = "%s.xml" % protocol)
    header      = kwargs.pop("header",      default = "{proto}-client-protocol-impl.h".format(proto=protocol))
    modhdr      = kwargs.pop("modhdr",      default = "{proto}-client-protocol.h".format(proto=protocol))
    source      = kwargs.pop("source",      default = "{proto}-protocol.c".format(proto=protocol))
    deps        = kwargs.pop("deps",        default = [])
    dirname     = "%s_incdir" % protocol
    protocol_target = "_{}_wayland_protocol".format(name)

    _rg_wayland_protocol_rule(
        name     = protocol_target,
        protocol = protocol,
        xml      = xml_file,
        header   = header,
        modhdr   = modhdr,
        source   = source,
        pragma   = select({
            "@rules_cc//cc/compiler:clang":     "#pragma clang system_header",
            "@rules_cc//cc/compiler:clang-cl":  "#pragma clang system_header",
            "@rules_cc//cc/compiler:gcc":       "#pragma GCC system_header",
            "@rules_cc//cc/compiler:mingw-gcc": "#pragma GCC system_header",
            "@rules_cc//cc/compiler:msvc-cl":   "#pragma system_header",
        }),
    )

    native.cc_library(
        name        = name,
        hdrs        = [modhdr],
        srcs        = [source, header],
        conlyopts   = ["-w"],
        includes    = ["."],
        **kwargs
    )
