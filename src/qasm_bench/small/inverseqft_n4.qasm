OPENQASM 2.0;
include "qelib1.inc";
qreg q[4];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[1];
u3(pi/2,0,pi) q[2];
u3(pi/2,0,pi) q[3];
u3(pi/2,0,pi) q[0];
u3(0,0,pi/2) q[1];
u3(pi/2,0,pi) q[1];
u3(0,0,0.785398185253143) q[2];
u3(0,0,pi/2) q[2];
u3(pi/2,0,pi) q[2];
u3(0,0,0.392699092626572) q[3];
u3(0,0,0.785398185253143) q[3];
u3(0,0,pi/2) q[3];
u3(pi/2,0,pi) q[3];
