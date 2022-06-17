load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "fraction",
    srcs = [
        "fraction.cc",
    ],
    hdrs = ["fraction.h"],
    copts = [],
    visibility = ["//visibility:public"],
    deps = [],
)

cc_library(
    name = "phase",
    srcs = [
        "phase.cc",
    ],
    hdrs = ["phase.h"],
    copts = [],
    visibility = ["//visibility:public"],
    deps = [
        ":fraction",
        "@staq//:staq_tools",
    ],
)

cc_test(
    name = "phase_test",
    size = "small",
    srcs = ["phase_test.cc"],
    deps = [
        ":phase",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
