cc_library(
    name = "tree_lib",
    srcs = ["tree_lib.c"],
    hdrs = ["tree_lib.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "tree_bin",
    srcs = ["tree.c"],
    deps = [":tree_lib"],
)
