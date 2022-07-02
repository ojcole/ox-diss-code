OPENQASM 2.0;
include "qelib1.inc";
qreg q[2];
u3(pi,0,pi) q[1];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[1];
cx q[0],q[1];
u3(pi/2,0,pi) q[0];
