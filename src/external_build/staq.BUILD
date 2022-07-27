load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "staq_tools_int",
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
    name = "staq_tools",
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
    name = "staq_int",
    srcs = [],
    hdrs = glob(
        [
            "include/**/*.hpp",
        ],
    ),
    strip_include_prefix = "include",
    visibility = ["//visibility:private"],
    deps = [":staq_tools_int"],
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
    deps = [
        ":staq_int",
        ":staq_tools_int",
        "@nlohmann_json",
    ],
)
