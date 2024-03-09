def _impl(ctx):
    ctx.actions.run(
        inputs = ctx.files.header_template + ctx.files.source_template,
        outputs = [
            ctx.outputs.header_output,
            ctx.outputs.source_output,
        ],
        executable = ctx.executable.code_gen,
        arguments = [
            "--header_template",
            ctx.files.header_template[0].path,
            "--header_output",
            ctx.outputs.header_output.path,
            "--source_template",
            ctx.files.source_template[0].path,
            "--source_output",
            ctx.outputs.source_output.path,
        ],
    )

_codegen = rule(
    attrs = {
        "code_gen": attr.label(
            cfg = "exec",
            executable = True,
            mandatory = True,
        ),
        "header_output": attr.output(
            doc = "Generated header",
            mandatory = True,
        ),
        "header_template": attr.label(
            allow_single_file = True,
            doc = "Header template",
            mandatory = True,
        ),
        "source_template": attr.label(
            allow_single_file = True,
            doc = "Source template",
            mandatory = True,
        ),
        "source_output": attr.output(
            doc = "Generated source",
            mandatory = True,
        ),
    },
    implementation = _impl,
)

def cc_gen_library(
        library_name,
        code_gen,
        header_template,
        source_template,
        deps = [],
        **kwargs):
    """Generate a cc_library given a codegen tool and templates."""

    # Stick with the convention that template files will be stripped of everything after the last '.'. So,
    # foo.cpp.template will become foo.cpp
    header_output = ".".join(header_template.split(".")[:-1])
    source_output = ".".join(source_template.split(".")[:-1])
    _codegen(
        name = library_name + "_codegen",
        code_gen = code_gen,
        header_output = header_output,
        header_template = header_template,
        source_output = source_output,
        source_template = source_template,
        visibility = [],
    )

    # Create a cc_library with `library_name` as the name (which can be referred to by targets that need to depend on
    # the library built from the generated code)
    native.cc_library(
        name = library_name,
        hdrs = [header_output],
        srcs = [source_output],
        deps = deps,
        **kwargs
    )
