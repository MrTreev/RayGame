load("//rules/toolchains/helpers.bzl", "make_buildtype_flag_set")

def buildtype_feature(
    buildtype,
    arch,
    cpu,
    compiler,
    version,
    extra_copts,
    extra_cxxopts,
    extra_linkopts,
):
    return feature(
        name = buildtype,
        flag_sets =
            make_buildtype_flag_set(buildtype, all_c_compile_actions, conlyopts(buildtype, arch, cpu, compiler, version)),
    )
