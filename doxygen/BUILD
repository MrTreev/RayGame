load("//rules:doxygen.bzl", "doxygen")
doxygen(
    name = "doxygen",
    srcs = [
        "//core:doxygen_files",
        "//system:doxygen_files",
        "//world:doxygen_files",
    ],
    data = [
        "//core:doxygen_data_files",
        "//system:doxygen_data_files",
        "//world:doxygen_data_files",
    ],
    doxygen_config_file = "template.Doxyfile",
    tags = [ "manual" ],
    templates = [],
    vars = {
        "{project_name}": "RayGame",
        "{extra_options}": "",
    },
    visibility = ["//visibility:public"],
)

