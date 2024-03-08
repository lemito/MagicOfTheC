cc_library(
    name = "vector_lib",
    srcs = ["vector_lib.c"],
    hdrs = ["vector_lib.h"],
)

cc_binary(
    name = "vector_bin",
    srcs = ["vector.c"],
    deps = ["@MagicOfTheC//src/vector:vector_lib"],
)