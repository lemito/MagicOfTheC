cc_library(
    name = "stack_arr_lib",
    srcs = ["stack_arr_lib.c"],
    hdrs = ["stack_arr_lib.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "stack_arr_bin",
    srcs = ["stack_arr.c"],
    deps = [":stack_arr_lib"],
)
