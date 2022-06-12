load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "phase",
    srcs = [
        "phase.cc",
    ],
    hdrs = ["phase.h"],
    copts = [],
    visibility = ["//visibility:public"],
    deps = [
        "@staq//:staq-tools",
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
