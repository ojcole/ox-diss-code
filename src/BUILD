load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    copts = [],
    data = ["@//qasm_files:clifford.qasm"],
    deps = [
        "//phase",
        "//stabilisers:stabiliser_tableau",
        "@staq",
        "@staq//:staq-tools",
    ],
)
