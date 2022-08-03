load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    copts = [],
    deps = [
        "//circuit:pauli_circuit",
        "//phase",
        "@staq",
        "@staq//:staq_tools",
    ],
)

cc_binary(
    name = "compare_cliffords",
    srcs = ["compare_cliffords.cc"],
    deps = [
        "//circuit:stabiliser_tableau",
        "@staq//:staq_tools",
    ],
)

cc_binary(
    name = "pyzxify",
    srcs = ["pyzxify.cc"],
    deps = [
        "//circuit:helpers",
        "@staq",
        "@staq//:staq_tools",
    ],
)

cc_binary(
    name = "test",
    srcs = ["test.cc"],
    deps = ["//phase"],
)

cc_binary(
    name = "normalise",
    srcs = ["normalise.cc"],
    deps = [
        "@staq",
        "@staq//:staq_tools",
    ],
)
