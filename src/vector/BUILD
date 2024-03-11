# visibility("public")

cc_library(
    name = "vector_lib",
    srcs = ["vector_lib.c"],
    hdrs = ["vector_lib.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "vector_bin",
    srcs = ["vector.c"],
    deps = [":vector_lib"],
)
