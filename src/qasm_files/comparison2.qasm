OPENQASM 2.0;
include "qelib1.inc";
qreg q[3];
qreg a[2];
u3(-pi/2,pi,pi/2) q[0];
u3(-pi/2,0,pi/2) q[1];
u3(pi/2,pi,pi/2) q[2];
u3(pi/2,pi/2,pi/2) a[0];
u3(pi/2,pi/2,pi/2) a[1];
cx a[1],q[2];
cx a[1],q[1];
cx a[0],q[1];
cx a[0],q[0];
u3(pi/2,0,pi/2) a[1];
u3(pi/2,0,pi/2) a[0];
u3(pi/2,0,pi) q[2];
u3(pi/2,0,pi) q[1];
u3(pi/2,0,pi) q[0];
