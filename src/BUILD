load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    copts = [],
    data = [
        "@//qasm_bench/medium",
        "@//qasm_files",
        "@//tket_bench/h2",
        "@//tket_bench/h4",
    ],
    deps = [
        "//circuit:pauli_circuit",
        "//phase",
        "@staq",
        "@staq//:staq_tools",
    ],
)

cc_binary(
    name = "pyzxify",
    srcs = ["pyzxify.cc"],
    data = [
        "@//qasm_bench/medium",
        "@//qasm_files",
        "@//tket_bench/h2",
    ],
    deps = [
        "//circuit:helpers",
        "@staq",
        "@staq//:staq_tools",
    ],
)
