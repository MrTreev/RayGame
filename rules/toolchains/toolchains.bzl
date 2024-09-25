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
            make_buildtype_flag_set(buildtype, all_c_compile_actions, conlyopts(buildtype, arch, cpu, compiler, version)) +
            make_buildtype_flag_set(buildtype, all_c_compile_actions + all_cpp_compile_actions, copts(buildtype, arch, cpu, compiler, version)) +
            make_buildtype_flag_set(buildtype, all_cpp_compile_actions, cxxopts(buildtype, arch, cpu, compiler, version)) +
            make_buildtype_flag_set(buildtype, all_link_actions + lto_index_actions, linkopts(buildtype, arch, cpu, compiler, version)) +
            make_flag_set(all_c_compile_actions + all_cpp_compile_actions, extra_copts) +
            make_flag_set(all_cpp_compile_actions, extra_cxxopts) +
            make_flag_set(all_link_actions, extra_linkopts),
    )

def sanitizer(name, flag):
    return feature(
        name = name,
        enabled = False,
        flag_sets = [
            flag_set(
                actions = all_c_compile_actions + all_cpp_compile_actions,
                flag_groups = [
                    flag_group(flags = [flag]),
                ],
            ),
            flag_set(
                actions = all_link_actions + lto_index_actions,
                flag_groups = [
                    flag_group(flags = [flag]),
                ],
            )
        ],
    )

def buildtype_feature(
    buildtype,
    arch,
    cpu,
    compiler,
    version,
    extra_copts,
    extra_cxxopts,
    extra_linkopts,
    premerge_buildtypes = [],
):
    features = []
    features.extend(cc_toolchain_config(compiler, version))
    features.extend([
        feature(
            name = "warnings",
            enabled = True,
            flag_sets =
                make_buildtype_flag_set("dbg", all_c_compile_actions + all_cpp_compile_actions, c_warnings(arch, cpu, compiler, version, "dbg" in premerge_buildtypes)) +
                make_buildtype_flag_set("dbg", all_c_compile_actions, conly_warnings(arch, cpu, compiler, version, "dbg" in premerge_buildtypes)) +
                make_buildtype_flag_set("dbg", all_cpp_compile_actions, cxx_warnings(arch, cpu, compiler, version, "dbg" in premerge_buildtypes)) +
                make_buildtype_flag_set("fast", all_c_compile_actions + all_cpp_compile_actions, c_warnings(arch, cpu, compiler, version, "fast" in premerge_buildtypes)) +
                make_buildtype_flag_set("fast", all_c_compile_actions, conly_warnings(arch, cpu, compiler, version, "fast" in premerge_buildtypes)) +
                make_buildtype_flag_set("fast", all_cpp_compile_actions, cxx_warnings(arch, cpu, compiler, version, "fast" in premerge_buildtypes)) +
                make_buildtype_flag_set("opt", all_c_compile_actions + all_cpp_compile_actions, c_warnings(arch, cpu, compiler, version, "opt" in premerge_buildtypes)) +
                make_buildtype_flag_set("opt", all_c_compile_actions, conly_warnings(arch, cpu, compiler, version, "opt" in premerge_buildtypes)) +
                make_buildtype_flag_set("opt", all_cpp_compile_actions, cxx_warnings(arch, cpu, compiler, version, "opt" in premerge_buildtypes)),
        ),
        buildtype_feature("dbg", arch, cpu, compiler, version, extra_copts, extra_cxxopts, extra_linkopts),
        buildtype_feature("fast", arch, cpu, compiler, version, extra_copts, extra_cxxopts, extra_linkopts),
        buildtype_feature("opt", arch, cpu, compiler, version, extra_copts, extra_cxxopts, extra_linkopts),
        sanitizer("asan", "-fsanitize=address"),
        sanitizer("tsan", "-fsanitize=thread"),
        sanitizer("msan", "-fsanitize=memory"),
        sanitizer("ubsan", "-fsanitize=undefined"),
        sanitizer("dataflow", "-fsanitize=dataflow"),
        sanitizer("controlflow", "-fsanitize=cfi"),
        sanitizer("kernelflow", "-fsanitize=kcfi"),
        sanitizer("safestack", "-fsanitize=safe-stack"),
        sanitizer("realtime", "-fsanitize=realtime"),
    ])
