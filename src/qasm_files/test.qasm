OPENQASM 2.0;
include "qelib1.inc";
qreg q[1];
u3(pi/2,-pi/2,pi/2) q[0];
u3(0,0,pi/2) q[0];
tdg q[0];
u3(0,0,pi/2) q[0];