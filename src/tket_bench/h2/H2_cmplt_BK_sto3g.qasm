OPENQASM 2.0;
include "qelib1.inc";
qreg q[4];
u3(pi,0,pi) q[0];
u3(pi/2,-pi/2,pi/2) q[0];
u3(pi,0,pi) q[1];
cx q[0],q[1];
u1(0.0001) q[1];
cx q[0],q[1];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi/2,-pi/2,pi/2) q[0];
u1(-0.0001) q[0];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi/2,0,pi) q[0];
u3(pi,0,pi) q[2];
u3(pi/2,-pi/2,pi/2) q[2];
cx q[1],q[2];
cx q[2],q[3];
u1(0.0001) q[3];
cx q[2],q[3];
cx q[1],q[2];
cx q[0],q[1];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi/2,-pi/2,pi/2) q[2];
u1(-0.0001) q[2];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi/2,-pi/2,pi/2) q[2];
cx q[1],q[2];
cx q[2],q[3];
u1(2.5e-05) q[3];
cx q[2],q[3];
cx q[1],q[2];
cx q[0],q[1];
u3(pi/2,0,pi) q[0];
u3(pi/2,-pi/2,pi/2) q[0];
cx q[0],q[1];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi/2,0,pi) q[2];
cx q[1],q[2];
u1(2.5e-05) q[2];
cx q[1],q[2];
cx q[0],q[1];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi/2,-pi/2,pi/2) q[0];
u3(pi/2,0,pi) q[2];
u3(pi/2,0,pi) q[2];
cx q[0],q[2];
cx q[2],q[3];
u1(-2.5e-05) q[3];
cx q[2],q[3];
cx q[0],q[2];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[2];
u3(pi/2,-pi/2,pi/2) q[2];
cx q[0],q[2];
u1(-2.5e-05) q[2];
cx q[0],q[2];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[0];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi/2,-pi/2,pi/2) q[2];
cx q[0],q[2];
cx q[2],q[3];
u1(-2.5e-05) q[3];
cx q[2],q[3];
cx q[0],q[2];
u3(pi/2,0,pi) q[0];
u3(pi/2,-pi/2,pi/2) q[0];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi/2,0,pi) q[2];
cx q[0],q[2];
u1(-2.5e-05) q[2];
cx q[0],q[2];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi/2,-pi/2,pi/2) q[0];
cx q[0],q[1];
u3(pi/2,0,pi) q[2];
u3(pi/2,0,pi) q[2];
cx q[1],q[2];
cx q[2],q[3];
u1(2.5e-05) q[3];
cx q[2],q[3];
cx q[1],q[2];
cx q[0],q[1];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi/2,0,pi) q[0];
cx q[0],q[1];
u3(pi/2,0,pi) q[2];
u3(pi/2,-pi/2,pi/2) q[2];
cx q[1],q[2];
u1(2.5e-05) q[2];
cx q[1],q[2];
cx q[0],q[1];
u3(pi/2,0,pi) q[0];
u3(-pi/2,-pi/2,pi/2) q[2];
