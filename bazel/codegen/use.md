load("//:codegen.bzl", "cc_gen_library")


cc_gen_library(
    library_name = "foo",
    code_gen = ":code_generator",
    header_template = "foo.hpp.template",
    source_template = "foo.cpp.template",
)