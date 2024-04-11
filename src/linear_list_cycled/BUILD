cc_binary(
    name = "list_bin",
    srcs = ["main.c"],
    deps = ["iterator_cyc", "list_cyc"],
)

cc_library(
    name = "iterator_cyc",
    srcs = ["iterator/iterator.c"],
    hdrs = ["iterator/iterator.h"],
)

cc_library(
    name = "list_cyc",
    srcs = ["list/list.c"],
    hdrs = ["list/list.h"],
)