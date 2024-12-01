load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")
load("@doxygen//:doxygen.bzl", "doxygen")

refresh_compile_commands(
    name = "compile_commands",
    targets = ["//..."],
)

doxygen(
    name = "doxygen",
    srcs = [
        "//core:doxyfiles",
        "README.md",
        # "//rules:doxyfiles",
        # "//test:doxyfiles",
    ],
    use_mdfile_as_mainpage = "README.md",
    project_name = "RayGame",
    project_brief = "Game engine and test game written in C++",
    have_dot = False,
    hide_undoc_members = False,
    builtin_stl_support = True,
    configurations = [
        "CREATE_SUBDIRS = YES",
        "GENERATE_HTML = YES",
        "GENERATE_LATEX = NO",
        "EXTRACT_ALL = YES",
        "EXTRACT_LOCAL_CLASSES = NO",
        "HIDE_SCOPE_NAMES = YES",
        "SHOW_GROUPED_MEMB_INC = YES",
        "SORT_BRIEF_DOCS = YES",
        "SORT_MEMBERS_CTORS_1ST = YES",
        "SORT_GROUP_NAMES = YES",
        "SORT_BY_SCOPE_NAME = YES",
        "QUIET = YES",
        "WARNINGS = YES",
        "WARN_IF_UNDOCUMENTED = YES",
        "WARN_NO_PARAMDOC = YES",
        "WARN_IF_UNDOC_ENUM_VAL = YES",
        "WARN_AS_ERROR = NO",
    ],
    tags = ["manual"],
    visibility = ["//visibility:public"],
)
