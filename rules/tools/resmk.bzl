load("@rules_cc//cc:defs.bzl", "cc_library")

def _resmk_rule_impl(ctx):
    namespace = ctx.attr.namespace
    resources = ctx.files.resources
    outhdr = ctx.outputs.outhdr
    outsrc = ctx.outputs.outsrc
    args = ctx.actions.args()
    args.add(outhdr.path)
    if len(namespace) != 0:
        args.add("--namespace", namespace.path)
    for resource in resources:
        args.add(resource.path)
    print(args)
    ctx.actions.run(
        mnemonic = "ResmkRun",
        executable = ctx.executable._resmk,
        arguments = [args],
        inputs = resources,
        outputs = [outhdr, outsrc],
    )

resmk_rule = rule(
    implementation = _resmk_rule_impl,
    attrs = {
        "namespace": attr.string(default = ""),
        "resources": attr.label_list(allow_files = [".png"]),
        "outhdr": attr.output(),
        "outsrc": attr.output(),
        "_resmk": attr.label(
            default = Label("//raygame/tools/resmk"),
            allow_single_file = True,
            executable = True,
            cfg = "exec",
        ),
    },
)

def _resmk_macro(name, namespace, resources, visibility):
    outhdr = name + ".h"
    outsrc = name + ".cpp"
    resmk_rule(
        name = name + "_files",
        namespace = namespace,
        resources = resources,
        outhdr = outhdr,
        outsrc = outsrc,
    )
    cc_library(
        name = name,
        hdrs = [outhdr],
        srcs = [outsrc],
        deps = ["//raygame/core/drawing"],
        visibility = visibility,
    )

resmk = macro(
    implementation = _resmk_macro,
    attrs = {
        "namespace": attr.string(default = ""),
        "resources": attr.label_list(allow_files = [".png"]),
    },
)
