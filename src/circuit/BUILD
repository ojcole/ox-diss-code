load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "stabiliser_tableau",
    srcs = [
        "stabiliser_tableau.cc",
    ],
    hdrs = ["stabiliser_tableau.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":helpers",
        ":pauli_exponential",
        ":qubit_manager",
        "//phase",
        "@staq",
        "@staq//:staq_tools",
    ],
)

cc_library(
    name = "clifford_gate",
    srcs = ["clifford_gate.cc"],
    hdrs = ["clifford_gate.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":qubit_manager",
        "//phase",
    ],
)

cc_library(
    name = "helpers",
    srcs = ["helpers.cc"],
    hdrs = ["helpers.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":clifford_gate",
        ":single_qubit_unitary",
        ":z_gate",
        "@staq",
        "@staq//:staq_tools",
    ],
)

cc_library(
    name = "pauli_circuit",
    srcs = ["pauli_circuit.cc"],
    hdrs = ["pauli_circuit.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":clifford_gate",
        ":helpers",
        ":pauli_dag",
        ":pauli_exponential",
        ":stabiliser_tableau",
        "//phase",
        "@staq//:staq_tools",
    ],
)

cc_library(
    name = "pauli_dag",
    srcs = ["pauli_dag.cc"],
    hdrs = ["pauli_dag.h"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
    deps = [
        ":diagonaliser",
        ":gray_synther",
        ":pauli_exponential",
        ":stabiliser_tableau",
        "@moodycamel",
        "@sparsepp",
    ],
)

cc_library(
    name = "pauli_graph",
    srcs = ["pauli_graph.cc"],
    hdrs = ["pauli_graph.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":pauli_exponential",
    ],
)

cc_library(
    name = "pauli_string",
    srcs = ["pauli_string.cc"],
    hdrs = ["pauli_string.h"],
    visibility = ["//visibility:public"],
    deps = [],
)

cc_library(
    name = "pauli_exponential",
    srcs = ["pauli_exponential.cc"],
    hdrs = ["pauli_exponential.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":clifford_gate",
        ":helpers",
        ":qubit_manager",
        "@staq//:staq_tools",
    ],
)

cc_library(
    name = "qubit_manager",
    srcs = ["qubit_manager.cc"],
    hdrs = ["qubit_manager.h"],
    visibility = ["//visibility:public"],
    deps = [":qubit"],
)

cc_library(
    name = "qubit",
    srcs = [],
    hdrs = ["qubit.h"],
    visibility = ["//visibility:public"],
    deps = [],
)

cc_library(
    name = "z_gate",
    srcs = ["z_gate.cc"],
    hdrs = ["z_gate.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":qubit_manager",
    ],
)

cc_library(
    name = "single_qubit_unitary",
    srcs = ["single_qubit_unitary.cc"],
    hdrs = ["single_qubit_unitary.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":pauli_string",
        ":qubit_manager",
        "//phase",
    ],
)

cc_library(
    name = "diagonaliser",
    srcs = ["diagonaliser.cc"],
    hdrs = ["diagonaliser.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":pauli_exponential",
        ":qubit_manager",
    ],
)

cc_library(
    name = "gray_synther",
    srcs = ["gray_synther.cc"],
    hdrs = ["gray_synther.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":helpers",
        ":pauli_exponential",
        "@staq",
    ],
)

cc_test(
    name = "stabiliser_tableau_test",
    size = "small",
    srcs = ["stabiliser_tableau_test.cc"],
    deps = [
        ":qubit_manager",
        ":stabiliser_tableau",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
