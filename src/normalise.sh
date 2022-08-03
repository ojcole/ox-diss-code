#!/usr/bin/env bash

mkdir original

find . -type f -wholename "*/*/*.qasm" -print0 | while read -d $'\0' file
do
  base=$(basename $file)
  cp $file original/$base
  ../../../../bazel-bin/normalise $file > $base
done