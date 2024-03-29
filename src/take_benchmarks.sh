bazel build main --copt=-DNDEBUG

find benchmarks/qasm_bench/medium -type f -name "*.qasm" ! -wholename "**/original/*.qasm" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12 true
find benchmarks/qasm_bench/small -type f -name "*.qasm" ! -wholename "**/original/*.qasm" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12 true
find benchmarks/qasm_bench/large -type f -name "*.qasm" ! -wholename "**/original/*.qasm" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12 true
find benchmarks/tket_bench -type f -name "*.qasm" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12 true