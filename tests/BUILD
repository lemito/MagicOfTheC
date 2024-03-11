cc_test(
    name = "vector_unittest",
    size = "small",
    srcs = ["vector_unittest.cc"],
    copts = [
        "-Iexternal/gtest/googletest/include",
        "-Iexternal/gtest/googletest",
    ],
    deps = [
        "//src/vector:vector_lib",
        "@gtest//:main",
    ],
)

sh_binary(
    name = "my_binary",
    srcs = ["my_binary.sh"],
    deps = [
        "@bazel_tools//tools/bash/runfiles",
    ],
)
