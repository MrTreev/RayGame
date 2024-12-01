load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")
load("@doxygen//:doxygen.bzl", "doxygen")

refresh_compile_commands(
    name = "compile_commands",
    targets = ["//..."],
    visibility = ["//visibility:public"],
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
        "GENERATE_HTML = YES",
        "GENERATE_LATEX = NO",
        "QUIET = YES",
        "WARNINGS = YES",
        "EXTRACT_ALL = YES",
        "SHOW_GROUPED_MEMB_INC = YES",
        "SORT_BRIEF_DOCS = YES",
        "SORT_MEMBERS_CTORS_1ST = YES",
        "SORT_GROUP_NAMES = YES",
        "SORT_BY_SCOPE_NAME = YES",
        "SOURCE_BROWSER = YES",
        "REFERENCES_RELATION = YES",
        "REFERENCED_BY_RELATION = YES",
        "REFERENCES_LINK_SOURCE = YES",
        "SOURCE_TOOLTIPS = YES",
        "HTML_COLORSTYLE = TOGGLE",
    ],
    outs = ["html"],
    tags = ["manual"],
    visibility = ["//visibility:public"],
)
