OPENQASM 2.0;
include "qelib1.inc";

qreg q[2];
cx q[0], q[1];
h q[0];