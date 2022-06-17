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
        ":helpers",
        "//phase",
    ],
)

cc_library(
    name = "helpers",
    srcs = ["helpers.cc"],
    hdrs = ["helpers.h"],
    visibility = ["//visibility:public"],
    deps = [
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
        ":pauli",
        ":pauli_dag",
        ":stabiliser_tableau",
        "//phase",
        "@staq//:staq_tools",
    ],
)

cc_library(
    name = "pauli_dag",
    srcs = ["pauli_dag.cc"],
    hdrs = ["pauli_dag.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":pauli",
    ],
)

cc_library(
    name = "pauli_graph",
    srcs = ["pauli_graph.cc"],
    hdrs = ["pauli_graph.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":pauli",
    ],
)

cc_library(
    name = "pauli",
    srcs = ["pauli.cc"],
    hdrs = ["pauli.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":clifford_gate",
        ":qubit_manager",
        "@staq//:staq_tools",
    ],
)

cc_library(
    name = "qubit_manager",
    srcs = ["qubit_manager.cc"],
    hdrs = ["qubit_manager.h"],
    visibility = ["//visibility:public"],
    deps = [":helpers"],
)
