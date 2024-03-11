cc_library(
    name = "main",
    srcs = glob(
        ["googletest/src/*.cc"],
        exclude = ["googletest/src/gtest-all.cc"]
    ),
    hdrs = glob([
        "googletest/include/**/*.h",
        "googletest/src/*.h"
    ]),
    copts = [
      "-Iexternal/gtest/googletest/include",
      "-Iexternal/gtest/googletest",
    ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)