bazel build main

find benchmarks/qasm_bench/medium -type f -name "*.qasm" ! -wholename "**/original/*.qasm" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12
find benchmarks/qasm_bench/small -type f -name "*.qasm" ! -wholename "**/original/*.qasm" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12
find benchmarks/qasm_bench/large -type f -name "*.qasm" ! -wholename "**/original/*.qasm" -and ! -name "*ising_model*" -and ! -name "*vqe_n24*" -and ! -name "*bwt_n21*" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12
find benchmarks/tket_bench -type f -name "*.qasm" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12