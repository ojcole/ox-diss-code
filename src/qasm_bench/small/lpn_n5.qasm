OPENQASM 2.0;
include "qelib1.inc";
qreg q[5];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[1];
u3(pi/2,0,pi) q[3];
u3(pi/2,0,pi) q[4];
cx q[3],q[2];
cx q[0],q[2];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[1];
u3(pi/2,0,pi) q[2];
u3(pi/2,0,pi) q[3];
u3(pi/2,0,pi) q[4];
