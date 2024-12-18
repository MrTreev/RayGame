package(default_visibility = ["//visibility:public"])

constraint_setting(
    name = "random_type",
    default_constraint_value = "deterministic",
)

constraint_value(
    name = "deterministic",
    constraint_setting = ":random_type",
)

constraint_value(
    name = "non-deterministic",
    constraint_setting = ":random_type",
)

