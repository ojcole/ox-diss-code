bazel build main

find qasm_bench/medium -type f -name "*.qasm" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12
find qasm_bench/small -type f -name "*.qasm" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12
find qasm_bench/large -type f -name "*.qasm" ! -name "*ising_model*" -and ! -name "*vqe_n24*" -and ! -name "*bwt_n21*" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12
find tket_bench -type f -name "*.qasm" | xargs -I{} ./bazel-bin/main {} tmp.qasm 12