#!/usr/bin/env bash

find . -type f -wholename "./qasm_bench/small/*.qasm" -print0 | while read -d $'\0' file
do
  ./bazel-bin/main $file tmp.qasm 12
  ./verify.py $file tmp.qasm
done

find . -type f -wholename "./qasm_bench/medium/*.qasm" -print0 | while read -d $'\0' file
do
  ./bazel-bin/main $file tmp.qasm 12
  ./verify.py $file tmp.qasm
done

find . -type f -wholename "./tket_bench/h2/*cmplt*sto3g.qasm" -print0 | while read -d $'\0' file
do
  ./bazel-bin/main $file tmp.qasm 12
  ./verify.py $file tmp.qasm
done

find . -type f -wholename "./tket_bench/h2/*cmplt*631g.qasm" -print0 | while read -d $'\0' file
do
  ./bazel-bin/main $file tmp.qasm 12
  ./verify.py $file tmp.qasm
done

find . -type f -wholename "./tket_bench/h2/*cmplt*ccpvdz.qasm" -print0 | while read -d $'\0' file
do
  ./bazel-bin/main $file tmp.qasm 12
  ./verify.py $file tmp.qasm
done
