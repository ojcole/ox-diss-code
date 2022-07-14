#!/usr/bin/python3

import sys

if len(sys.argv) < 3:
    print("wah")
    exit(0)

import pyzx as zx


def new_state(qubits: int):
    s = zx.Graph()
    outs = []
    for i in range(qubits):
        outs.append(s.add_vertex(zx.VertexType.BOUNDARY, i, 1))
        in1 = s.add_vertex(zx.VertexType.X, i, 0)
        s.add_edge((in1, outs[-1]))
    s.set_outputs(outs)
    s.set_inputs([])
    return s


file = open(sys.argv[1], "r+")
file2 = open(sys.argv[2], "r+")
lines = "\n".join(file.readlines())
lines2 = "\n".join(file2.readlines())

a = zx.qasm(lines)
b = zx.qasm(lines2)

state = new_state(a.qubits)

a = a.to_graph() * state
b = b.to_graph() * state

print(zx.compare_tensors(a, b, False))
