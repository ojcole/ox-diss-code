OPENQASM 2.0;
include "qelib1.inc";
qreg q[4];
rz(pi/4) q[0];
rx(pi/4) q[1];
ry(pi/4) q[2];
u1(pi/8) q[3];