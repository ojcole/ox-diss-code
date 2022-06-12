load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "staq-tools-int",
    srcs = [],
    hdrs = glob(
        [
            "qasmtools/include/**/*.hpp",
        ],
    ),
    strip_include_prefix = "qasmtools/include",
    visibility = ["//visibility:private"],
)

cc_library(
    name = "staq-tools",
    srcs = [],
    hdrs = glob(
        [
            "qasmtools/include/**/*.hpp",
        ],
    ),
    include_prefix = "staq",
    strip_include_prefix = "qasmtools/include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "staq",
    srcs = [],
    hdrs = glob(
        [
            "include/**/*.hpp",
        ],
    ),
    include_prefix = "staq",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [":staq-tools-int"],
)
