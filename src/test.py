import pyzx as zx
import math


def compare_tensors(ta, tb, verbose=False):
    ma = -math.inf
    mai = -1
    mb = -math.inf
    mbi = -1
    for j, x in enumerate(ta.flat):
        if x > ma:
            ma = x
            mai = j
    for j, x in enumerate(tb.flat):
        if x > mb:
            mb = x
            mbi = j
    max_i = mai if ma > mb else mbi
    epsilon = 1e-8
    for i in range(len(ta.flat)):
        diff = abs((ta.flat[i] / ta.flat[max_i]) -
                   (tb.flat[i] / tb.flat[max_i]))
        if diff > epsilon:
            if verbose:
                print(diff)
                print(i)
                print(ta.flat[i], tb.flat[i])
                print(max_i)
                print(ta.flat[max_i], tb.flat[max_i])
                print((ta.flat[i] / ta.flat[max_i]),
                      (tb.flat[i] / tb.flat[max_i]))
            return False

    return True


def compare_circs(ga, gb, verbose=False):
    ta = ga.to_tensor(preserve_scalar=False)
    tb = gb.to_tensor(preserve_scalar=False)
    return compare_tensors


def print_tensor_pair(ta, tb):
    for j, x in enumerate(ta.flat):
        print(ta.flat[j], tb.flat[j])


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


file = open("test1.qasm", "r+")
file2 = open("test.qasm", "r+")
lines = "\n".join(file.readlines())
lines2 = "\n".join(file2.readlines())

state15 = new_state(16)

a = zx.qasm(lines).to_graph()
b = zx.qasm(lines2).to_graph()

a = a * state15
b = b * state15

ta = a.to_tensor(preserve_scalar=False)
tb = b.to_tensor(preserve_scalar=False)

print(compare_tensors(ta, tb, True))
# print_tensor_pair(ta, tb)
