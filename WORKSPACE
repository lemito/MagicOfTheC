# http_archive(
#     name = "MagicOfTheC",
#     url = "https://github.com/lemito/MagicOfTheC/archive/refs/heads/main.zip",
# )
workspace(name = "magic_of_the_c")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "gtest",
    build_file = "@//:gtest.BUILD",
    strip_prefix = "googletest-1.14.0",
    url = "https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz",
)
