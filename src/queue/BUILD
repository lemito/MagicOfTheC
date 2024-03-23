cc_binary(
    name = "queue_arr_bin",
    srcs = ["queue_arr.c"],
    deps = ["queue_static_lib"],
)

cc_library(
    name = "queue_static_lib",
    srcs = ["queue_static_lib.c"],
    hdrs = ["queue_static_lib.h"],
)

cc_binary(
    name = "queue_dyn_bin",
    srcs = ["queue_dyn.c"],
    deps = ["queue_dyn_lib"],
)

cc_library(
    name = "queue_dyn_lib",
    srcs = ["queue_dyn_lib.c"],
    hdrs = ["queue_dyn_lib.h"],
)