# How run test inside project?

## Install bazel
On macOS: `brew install bazelisk`.

On Windows: `choco install bazelisk`.

Each adds bazelisk to the `PATH` as both `bazelisk` and `bazel`.

On Linux: You can download Bazelisk binary on our [Releases](https://github.com/bazelbuild/bazelisk/releases) page and add it to your `PATH` manually, which also works on macOS and Windows.

Bazelisk is also published to npm.
Frontend developers may want to install it with `npm install -g @bazel/bazelisk`.

> You will notice that it serves an analogous function for Bazel as the
> [`nvm` utility](https://github.com/nvm-sh/nvm) which manages your version of Node.js.
--------
* Run:
```bash
bazel run //src/queue:queue_arr_bin
```
* Build
```bash
bazel build //src/queue:queue_arr_bin
```

# How to use libraries in your project?

* Add library to your WORKSPACE file
```py
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "MagicOfTheC",
    urls = ["https://github.com/lemito/MagicOfTheC/archive/refs/tags/release.zip"],
    strip_prefix = "MagicOfTheC-release",
)
```

* Then add deps to your BUILD file
```
cc_binary(
    name = "my_file",
    srcs = ["my_file.c"],
    deps = ["@MagicOfTheC//src/vector:vector_lib"],
)
```