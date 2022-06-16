load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "stabiliser_tableau",
    srcs = [
        "stabiliser_tableau.cc",
    ],
    hdrs = ["stabiliser_tableau.h"],
    copts = [],
    visibility = ["//visibility:public"],
    deps = [
        "//phase",
        "@staq",
        "@staq//:staq-tools",
    ],
)
