load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    copts = [],
    data = [
        "@//qasm_bench/large",
        "@//qasm_bench/medium",
        "@//qasm_bench/small",
        "@//qasm_files",
        "@//tket_bench/c2h4",
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
    name = "compare_cliffords",
    srcs = ["compare_cliffords.cc"],
    data = [
        "@//qasm_bench/large",
        "@//qasm_bench/medium",
        "@//qasm_bench/small",
        "@//qasm_files",
        "@//tket_bench/h2",
        "@//tket_bench/h4",
    ],
    deps = [
        "//circuit:stabiliser_tableau",
        "@staq//:staq_tools",
    ],
)

cc_binary(
    name = "pyzxify",
    srcs = ["pyzxify.cc"],
    data = [
        "@//qasm_bench/large",
        "@//qasm_bench/medium",
        "@//qasm_bench/small",
        "@//qasm_files",
        "@//tket_bench/h2",
    ],
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
