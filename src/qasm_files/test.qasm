OPENQASM 2.0;
include "qelib1.inc";

qreg q[4];

x q[0];
s q[1];
cx q[2], q[3];
h q[3];
s q[2];
y q[1];
cx q[0], q[1];
s q[3];
h q[1];
h q[0];
s q[0];
cx q[0], q[2];

// h q[0];
// z q[0];
// h q[0];