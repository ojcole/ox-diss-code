OPENQASM 2.0;
include "qelib1.inc";
qreg q[3];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[1];
u3(pi/2,0,pi) q[2];
cx q[0],q[2];
u3(pi,0,pi) q[2];
u3(0,0,-2.82721352577209) q[2];
u3(pi,0,pi) q[2];
u3(0,0,2.82721352577209) q[2];
cx q[0],q[2];
cx q[0],q[1];
cx q[1],q[2];
u3(pi,0,pi) q[2];
u3(0,0,5.65444278717041) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-5.65444278717041) q[2];
cx q[1],q[2];
cx q[0],q[1];
u3(1.71324872970581,-pi/2,pi/2) q[2];
u3(pi,0,pi) q[1];
u3(0,0,8.48165607452393) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-8.48165607452393) q[1];
u3(1.71324872970581,-pi/2,pi/2) q[0];
u3(1.71324872970581,-pi/2,pi/2) q[1];
