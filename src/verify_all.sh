#!/usr/bin/env bash

bazel build main

find benchmarks -type f -wholename "benchmarks/qasm_bench/small/*.qasm" ! -wholename "**/original/*.qasm" -print0 | while read -d $'\0' file
do
  ./bazel-bin/main $file tmp.qasm 12
  ./verify.py $file tmp.qasm
done

find benchmarks -type f -wholename "benchmarks/qasm_bench/medium/*.qasm" ! -wholename "**/original/*.qasm" -print0 | while read -d $'\0' file
do
  ./bazel-bin/main $file tmp.qasm 12
  ./verify.py $file tmp.qasm
done

find benchmarks -type f -wholename "benchmarks/tket_bench/h2/*cmplt*sto3g.qasm" ! -wholename "**/original/*.qasm" -print0 | while read -d $'\0' file
do
  ./bazel-bin/main $file tmp.qasm 12
  ./verify.py $file tmp.qasm
done

find benchmarks -type f -wholename "benchmarks/tket_bench/h2/*cmplt*631g.qasm" ! -wholename "**/original/*.qasm" -print0 | while read -d $'\0' file
do
  ./bazel-bin/main $file tmp.qasm 12
  ./verify.py $file tmp.qasm
done