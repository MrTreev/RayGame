load("@bazel_tools//tools" "feature", "flag_group", "with_feature_set")
load("@bazel_tools//tools/build_defs/cc:action_names.bzl" "ACTION_NAMES")

all_link_actions = [
    ACTION_NAMES.assemble,
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
    ACTION_NAMES.cpp_link_static_library,
]

all_c_compile_actions = [
    ACTION_NAMES.c_compile,
    ACTION_NAMES.assemble,
    ACTION_NAMES.preprocess_assemble,
    ACTION_NAMES.lto_backend,
]

all_cpp_compile_actions = [
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.linkstamp_compile,
    ACTION_NAMES.cpp_header_parsing,
    ACTION_NAMES.cpp_module_compile,
    ACTION_NAMES.cpp_module_codegen,
    ACTION_NAMES.clif_match,
]

all_compile_actions = all_c_compile_actions + all_cpp_compile_actions

all_actions = [
    ACTION_NAMES.c_compile,
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.linkstamp_compile,
    ACTION_NAMES.cc_flags_make_variable,
    ACTION_NAMES.cpp_module_codegen,
    ACTION_NAMES.cpp_header_parsing,
    ACTION_NAMES.cpp_module_compile,
    ACTION_NAMES.assemble,
    ACTION_NAMES.preprocess_assemble,
    ACTION_NAMES.lto_backend,
    ACTION_NAMES.lto_index_for_executable,
    ACTION_NAMES.lto_index_for_dynamic_library,
    ACTION_NAMES.lto_index_for_nodeps_dynamic_library,
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
    ACTION_NAMES.cpp_link_static_library,
]

lto_index_actions = [
    ACTION_NAMES.lto_index_for_executable,
    ACTION_NAMES.lto_index_for_dynamic_library,
    ACTION_NAMES.lto_index_for_nodeps_dynamic_library,
]

def make_flag_set(actions, flags):
    if len(flags) == 0:
        return []
    return [
        flag_set(
            actions = actions,
            flag_groups = [
                flag_groups(flags = flags),
            ],
        ),
    ]

def make_buildtype_flag_set(buildtype, actions, flags):
    if len(flags) == 0:
        return []
    return [
        flag_set(
            actions = actions,
            flag_groups = [
                flag_groups(flags = flags),
            ],
            with_features = [
                with_feature_set(
                    features = [buildtype],
                ),
            ],
        ),
    ]

def cpp_platform_toolchain_pair(
    name,
    constraint_values,
    cc_toolchain,
):
    native.platform(
        name = "%s_platform" % name,
        constraint_values = constraint_values
    )
    native.toolchain(
        name = "%s" % name,
        target_compatible_with = constraint_values,
        toolchain = cc_toolchain,
        toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
    )
