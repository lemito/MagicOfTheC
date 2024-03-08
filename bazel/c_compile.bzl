"""Example showing how to create a rule that just compiles C sources."""

load("@bazel_tools//tools/cpp:toolchain_utils.bzl", "find_cpp_toolchain", "use_cpp_toolchain")
load("@rules_cc//cc:action_names.bzl", "C_COMPILE_ACTION_NAME")

CCompileInfo = provider(doc = "", fields = ["object"])

DISABLED_FEATURES = [
    "module_maps",  # # copybara-comment-this-out-please
]

def _c_compile_impl(ctx):
    cc_toolchain = find_cpp_toolchain(ctx)
    source_file = ctx.file.src
    output_file = ctx.actions.declare_file(ctx.label.name + ".o")
    feature_configuration = cc_common.configure_features(
        ctx = ctx,
        cc_toolchain = cc_toolchain,
        requested_features = ctx.features,
        unsupported_features = DISABLED_FEATURES + ctx.disabled_features,
    )
    c_compiler_path = cc_common.get_tool_for_action(
        feature_configuration = feature_configuration,
        action_name = C_COMPILE_ACTION_NAME,
    )
    c_compile_variables = cc_common.create_compile_variables(
        feature_configuration = feature_configuration,
        cc_toolchain = cc_toolchain,
        user_compile_flags = ctx.fragments.cpp.copts + ctx.fragments.cpp.conlyopts,
        source_file = source_file.path,
        output_file = output_file.path,
    )
    command_line = cc_common.get_memory_inefficient_command_line(
        feature_configuration = feature_configuration,
        action_name = C_COMPILE_ACTION_NAME,
        variables = c_compile_variables,
    )
    env = cc_common.get_environment_variables(
        feature_configuration = feature_configuration,
        action_name = C_COMPILE_ACTION_NAME,
        variables = c_compile_variables,
    )

    ctx.actions.run(
        executable = c_compiler_path,
        arguments = command_line,
        env = env,
        inputs = depset(
            [source_file],
            transitive = [cc_toolchain.all_files],
        ),
        outputs = [output_file],
    )
    return [
        DefaultInfo(files = depset([output_file])),
        CCompileInfo(object = output_file),
    ]

c_compile = rule(
    implementation = _c_compile_impl,
    attrs = {
        "src": attr.label(mandatory = True, allow_single_file = True),
        "_cc_toolchain": attr.label(default = Label("@bazel_tools//tools/cpp:current_cc_toolchain")),
    },
    toolchains = use_cpp_toolchain(),
    fragments = ["cpp"],
)