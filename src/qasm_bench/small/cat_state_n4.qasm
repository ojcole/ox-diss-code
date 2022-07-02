OPENQASM 2.0;
include "qelib1.inc";
qreg bits[4];
u3(pi/2,0,pi) bits[0];
cx bits[0],bits[1];
cx bits[1],bits[2];
cx bits[2],bits[3];
