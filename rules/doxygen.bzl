load("@bazel_skylib//lib:paths.bzl", "paths")

def _doxygen_impl(ctx):
    output_dir = ctx.actions.declare_directory("html")
    warn_logfile = ctx.actions.declare_file("warnings.txt")

    vars = {
        "{doc_source_dir_path}": paths.dirname(ctx.build_file_path),
        "{output_directory}": output_dir.dirname,
        "{warn_logfile}": warn_logfile.path,
    }

    vars["{layout_file}"] = ctx.file.layout_file.path if ctx.file.layout_file != None else ""

    for k, v in ctx.attr.vars.items():
        vars[k] = ctx.expand_location(v)
    srcs = []
    for src in ctx.files.templates:
        dst = ctx.actions.declare_file(src.basename[len(".template"):])
        ctx.actions.expand_template(
            template = src,
            output = dst,
            substitutions = vars,
        )
        srcs.append(dst)
    srcs += ctx.files.srcs
    parsed_doxygen_config_file = ctx.actions.declare_file(ctx.file.doxygen_config_file.basename + ".parsed")

    data_srcs = [s.path for s in srcs if s.extension in ("png", "gif", "css", "xml")]
    if len(data_srcs) > 0:
        fail("`data` the following files in `srcs` should be added to `data` too prevent doxygen parsing them", data_srcs)
    config_vars = {
        "{input}": " ".join([s.path for s in srcs]),
    }
    config_vars.update(vars)
    ctx.actions.expand_template(
        template = ctx.file.doxygen_config_file,
        output = parsed_doxygen_config_file,
        substitutions = config_vars,
    )

    tool_inputs, tool_manifests = ctx.resolve_tools(tools = [ctx.attr._doxygen])

    doxygen_exe_dirname = paths.dirname(ctx.executable._doxygen.path)
    doxygen_workspace_name = paths.basename(doxygen_exe_dirname)
    doxygen_exe_name = paths.basename(ctx.executable._doxygen.path)
    doxygen_runfiles_path = "{0}/{1}.runfiles/{2}/{1}".format(
        doxygen_exe_dirname,
        doxygen_exe_name,
        doxygen_workspace_name
    )
    ctx.actions.run(
        executable = doxygen_runfiles_path,
        inputs = srcs + [parsed_doxygen_config_file] + tool_inputs.to_list() + ctx.files.data + ctx.files.layout_file,
        outputs = [output_dir, warn_logfile],
        arguments = [parsed_doxygen_config_file.path],
        use_default_shell_env = True,
        input_manifests = tool_manifests,
    )
    return [
        DefaultInfo(
            files = depset([output_dir]),
        ),
    ]

doxygen = rule(
    implementation = _doxygen_impl,
    doc = """
          Rule to generate docs using Doxygen
          Args:
            doxygen: Label to the doxygen executable.
            doxygen_config_file: configuration file template to be used.
            layout_file: Optional doxygen LAYOUT_FILE.
            srcs: All source files needed e.g. doxygen headers and .dox files.
            data: extra data files such as examples, pngs, and css files.
            templates: extra sources that will be treated as templates to expand
            vars: template substitution variables that will be used to expand configuration files and templates
    """,
    attrs = {
        "_doxygen": attr.label(
            mandatory=False,
            cfg="host",
            allow_single_file=True,
            executable=True,
            default="//subprojects:doxygen",
        ),
        "doxygen_config_file": attr.label(allow_single_file=True),
        "layout_file": attr.label(allow_single_file=True),
        "srcs": attr.label_list(allow_files=True),
        "data": attr.label_list(allow_files=True),
        "templates": attr.label_list(allow_files=True),
        "vars": attr.string_dict(),
    },
)
