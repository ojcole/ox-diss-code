load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    copts = [],
    data = [
        "@//qasm_bench/medium:dnn_n8.qasm",
        "@//qasm_files:clifford.qasm",
        "@//qasm_files:h2.qasm",
        "@//qasm_files:test.qasm",
        "@//tket_bench/h2",
    ],
    deps = [
        "//circuit:pauli_circuit",
        "//phase",
        "@staq",
        "@staq//:staq_tools",
    ],
)
