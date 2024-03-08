load("//bazel:c_compile.bzl", "c_compile")

c_compile(
    name = "vector",
    src = "vector.c",
)

cc_library(
    name = "vector_lib",
    srcs = ["vector_lib.c"],
    hdrs = ["vector_lib.h"],
)

cc_binary(
    name = "vector_bin",
    srcs = ["vector.c"],
    deps = [":vector_lib"],
)