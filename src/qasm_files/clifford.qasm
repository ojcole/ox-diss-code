OPENQASM 2.0;
include "qelib1.inc";

qreg q[1];
u1(1.1) q[0];
x q[0];