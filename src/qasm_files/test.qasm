OPENQASM 2.0;
include "qelib1.inc";

qreg q[8];
u3(1.1,-pi/2,pi/2) q[0];
u3(1.1,0,0) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.55) q[0];
u3(1.1,-pi/2,pi/2) q[1];
u3(1.1,0,0) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.55) q[1];
u3(pi,0,pi) q[0];
u3(0,0,-pi*0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi*0.55) q[0];
u3(pi,0,pi) q[1];
u3(0,0,-pi*0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi*0.55) q[1];
u3(pi/2,0,pi/4) q[0];
u3(pi/2,pi,3*pi/4) q[1];
u3(pi/2,-pi/2,pi/2) q[0];
CX q[0],q[1];
u3(pi*0.4,-pi/2,pi/2) q[0];
u3(pi/2,0,0) q[1];
CX q[1],q[0];
u3(-pi/2,-pi/2,pi/2) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-pi/4) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi/4) q[1];
CX q[0],q[1];
u3(pi/2,pi*0.65,pi) q[0];
u3(pi/2,pi*0.15,0) q[1];
u3(0,pi,pi/2) q[0];
u3(0,0,pi/2) q[1];
u3(pi/2,-pi/2,pi/2) q[0];
CX q[0],q[1];
u3(pi*0.4,-pi/2,pi/2) q[0];
u3(pi/2,0,0) q[1];
CX q[1],q[0];
u3(-pi/2,-pi/2,pi/2) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-pi/4) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi/4) q[1];
CX q[0],q[1];
u3(pi,0,pi/2) q[0];
u3(pi,0,3*pi/2) q[1];
u3(pi/2,3*pi/2,3*pi/2) q[0];
u3(pi/2,pi/2,3*pi/2) q[1];
u3(pi/2,-pi/2,pi/2) q[0];
CX q[0],q[1];
u3(pi*0.4,-pi/2,pi/2) q[0];
u3(pi/2,0,0) q[1];
CX q[1],q[0];
u3(-pi/2,-pi/2,pi/2) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-pi/4) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi/4) q[1];
CX q[0],q[1];
u3(pi/2,pi/2,pi/2) q[0];
u3(pi/2,pi/2,3*pi/2) q[1];
u3(1.1,-pi/2,pi/2) q[0];
u3(1.1,0,0) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.55) q[0];
u3(1.1,-pi/2,pi/2) q[1];
u3(1.1,0,0) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.55) q[1];
u3(1.1,-pi/2,pi/2) q[2];
u3(1.1,0,0) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.55) q[2];
u3(1.1,-pi/2,pi/2) q[3];
u3(1.1,0,0) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.55) q[3];
u3(pi,0,pi) q[2];
u3(0,0,-pi*0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi*0.55) q[2];
u3(pi,0,pi) q[3];
u3(0,0,-pi*0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi*0.55) q[3];
u3(pi/2,0,pi/4) q[2];
u3(pi/2,pi,3*pi/4) q[3];
u3(pi/2,-pi/2,pi/2) q[2];
CX q[2],q[3];
u3(pi*0.4,-pi/2,pi/2) q[2];
u3(pi/2,0,0) q[3];
CX q[3],q[2];
u3(-pi/2,-pi/2,pi/2) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-pi/4) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi/4) q[3];
CX q[2],q[3];
u3(pi/2,pi*0.65,pi) q[2];
u3(pi/2,pi*0.15,0) q[3];
u3(0,pi,pi/2) q[2];
u3(0,0,pi/2) q[3];
u3(pi/2,-pi/2,pi/2) q[2];
CX q[2],q[3];
u3(pi*0.4,-pi/2,pi/2) q[2];
u3(pi/2,0,0) q[3];
CX q[3],q[2];
u3(-pi/2,-pi/2,pi/2) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-pi/4) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi/4) q[3];
CX q[2],q[3];
u3(pi,0,pi/2) q[2];
u3(pi,0,3*pi/2) q[3];
u3(pi/2,3*pi/2,3*pi/2) q[2];
u3(pi/2,pi/2,3*pi/2) q[3];
u3(pi/2,-pi/2,pi/2) q[2];
CX q[2],q[3];
u3(pi*0.4,-pi/2,pi/2) q[2];
u3(pi/2,0,0) q[3];
CX q[3],q[2];
u3(-pi/2,-pi/2,pi/2) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-pi/4) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi/4) q[3];
CX q[2],q[3];
u3(pi/2,pi/2,pi/2) q[2];
u3(pi/2,pi/2,3*pi/2) q[3];
u3(1.1,-pi/2,pi/2) q[2];
u3(1.1,0,0) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.55) q[2];
u3(1.1,-pi/2,pi/2) q[3];
u3(1.1,0,0) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.55) q[3];
u3(1.1,-pi/2,pi/2) q[4];
u3(1.1,0,0) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,0.55) q[4];
u3(1.1,-pi/2,pi/2) q[5];
u3(1.1,0,0) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,0.55) q[5];
u3(pi,0,pi) q[4];
u3(0,0,-pi*0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi*0.55) q[4];
u3(pi,0,pi) q[5];
u3(0,0,-pi*0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi*0.55) q[5];
u3(pi/2,0,pi/4) q[4];
u3(pi/2,pi,3*pi/4) q[5];
u3(pi/2,-pi/2,pi/2) q[4];
CX q[4],q[5];
u3(pi*0.4,-pi/2,pi/2) q[4];
u3(pi/2,0,0) q[5];
CX q[5],q[4];
u3(-pi/2,-pi/2,pi/2) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-pi/4) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi/4) q[5];
CX q[4],q[5];
u3(pi/2,pi*0.65,pi) q[4];
u3(pi/2,pi*0.15,0) q[5];
u3(0,pi,pi/2) q[4];
u3(0,0,pi/2) q[5];
u3(pi/2,-pi/2,pi/2) q[4];
CX q[4],q[5];
u3(pi*0.4,-pi/2,pi/2) q[4];
u3(pi/2,0,0) q[5];
CX q[5],q[4];
u3(-pi/2,-pi/2,pi/2) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-pi/4) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi/4) q[5];
CX q[4],q[5];
u3(pi,0,pi/2) q[4];
u3(pi,0,3*pi/2) q[5];
u3(pi/2,3*pi/2,3*pi/2) q[4];
u3(pi/2,pi/2,3*pi/2) q[5];
u3(pi/2,-pi/2,pi/2) q[4];
CX q[4],q[5];
u3(pi*0.4,-pi/2,pi/2) q[4];
u3(pi/2,0,0) q[5];
CX q[5],q[4];
u3(-pi/2,-pi/2,pi/2) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-pi/4) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi/4) q[5];
CX q[4],q[5];
u3(pi/2,pi/2,pi/2) q[4];
u3(pi/2,pi/2,3*pi/2) q[5];
u3(1.1,-pi/2,pi/2) q[4];
u3(1.1,0,0) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,0.55) q[4];
u3(1.1,-pi/2,pi/2) q[5];
u3(1.1,0,0) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,0.55) q[5];
u3(1.1,-pi/2,pi/2) q[6];
u3(1.1,0,0) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,0.55) q[6];
u3(1.1,-pi/2,pi/2) q[7];
u3(1.1,0,0) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,0.55) q[7];
u3(pi,0,pi) q[6];
u3(0,0,-pi*0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi*0.55) q[6];
u3(pi,0,pi) q[7];
u3(0,0,-pi*0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi*0.55) q[7];
u3(pi/2,0,pi/4) q[6];
u3(pi/2,pi,3*pi/4) q[7];
u3(pi/2,-pi/2,pi/2) q[6];
CX q[6],q[7];
u3(pi*0.4,-pi/2,pi/2) q[6];
u3(pi/2,0,0) q[7];
CX q[7],q[6];
u3(-pi/2,-pi/2,pi/2) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-pi/4) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi/4) q[7];
CX q[6],q[7];
u3(pi/2,pi*0.65,pi) q[6];
u3(pi/2,pi*0.15,0) q[7];
u3(0,pi,pi/2) q[6];
u3(0,0,pi/2) q[7];
u3(pi/2,-pi/2,pi/2) q[6];
CX q[6],q[7];
u3(pi*0.4,-pi/2,pi/2) q[6];
u3(pi/2,0,0) q[7];
CX q[7],q[6];
u3(-pi/2,-pi/2,pi/2) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-pi/4) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi/4) q[7];
CX q[6],q[7];
u3(pi,0,pi/2) q[6];
u3(pi,0,3*pi/2) q[7];
u3(pi/2,3*pi/2,3*pi/2) q[6];
u3(pi/2,pi/2,3*pi/2) q[7];
u3(pi/2,-pi/2,pi/2) q[6];
CX q[6],q[7];
u3(pi*0.4,-pi/2,pi/2) q[6];
u3(pi/2,0,0) q[7];
CX q[7],q[6];
u3(-pi/2,-pi/2,pi/2) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-pi/4) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi/4) q[7];
CX q[6],q[7];
u3(pi/2,pi/2,pi/2) q[6];
u3(pi/2,pi/2,3*pi/2) q[7];
u3(1.1,-pi/2,pi/2) q[6];
u3(1.1,0,0) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,0.55) q[6];
u3(1.1,-pi/2,pi/2) q[7];
u3(1.1,0,0) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,0.55) q[7];
u3(1.1,-pi/2,pi/2) q[1];
u3(1.1,0,0) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.55) q[1];
u3(1.1,-pi/2,pi/2) q[2];
u3(1.1,0,0) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.55) q[2];
u3(pi,0,pi) q[1];
u3(0,0,-pi*0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi*0.55) q[1];
u3(pi,0,pi) q[2];
u3(0,0,-pi*0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi*0.55) q[2];
u3(pi/2,0,pi/4) q[1];
u3(pi/2,pi,3*pi/4) q[2];
u3(pi/2,-pi/2,pi/2) q[1];
CX q[1],q[2];
u3(pi*0.4,-pi/2,pi/2) q[1];
u3(pi/2,0,0) q[2];
CX q[2],q[1];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-pi/4) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi/4) q[2];
CX q[1],q[2];
u3(pi/2,pi*0.65,pi) q[1];
u3(pi/2,pi*0.15,0) q[2];
u3(0,pi,pi/2) q[1];
u3(0,0,pi/2) q[2];
u3(pi/2,-pi/2,pi/2) q[1];
CX q[1],q[2];
u3(pi*0.4,-pi/2,pi/2) q[1];
u3(pi/2,0,0) q[2];
CX q[2],q[1];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-pi/4) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi/4) q[2];
CX q[1],q[2];
u3(pi,0,pi/2) q[1];
u3(pi,0,3*pi/2) q[2];
u3(pi/2,3*pi/2,3*pi/2) q[1];
u3(pi/2,pi/2,3*pi/2) q[2];
u3(pi/2,-pi/2,pi/2) q[1];
CX q[1],q[2];
u3(pi*0.4,-pi/2,pi/2) q[1];
u3(pi/2,0,0) q[2];
CX q[2],q[1];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-pi/4) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi/4) q[2];
CX q[1],q[2];
u3(pi/2,pi/2,pi/2) q[1];
u3(pi/2,pi/2,3*pi/2) q[2];
u3(1.1,-pi/2,pi/2) q[1];
u3(1.1,0,0) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.55) q[1];
u3(1.1,-pi/2,pi/2) q[2];
u3(1.1,0,0) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.55) q[2];
u3(1.1,-pi/2,pi/2) q[3];
u3(1.1,0,0) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.55) q[3];
u3(1.1,-pi/2,pi/2) q[4];
u3(1.1,0,0) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,0.55) q[4];
u3(pi,0,pi) q[3];
u3(0,0,-pi*0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi*0.55) q[3];
u3(pi,0,pi) q[4];
u3(0,0,-pi*0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi*0.55) q[4];
u3(pi/2,0,pi/4) q[3];
u3(pi/2,pi,3*pi/4) q[4];
u3(pi/2,-pi/2,pi/2) q[3];
CX q[3],q[4];
u3(pi*0.4,-pi/2,pi/2) q[3];
u3(pi/2,0,0) q[4];
CX q[4],q[3];
u3(-pi/2,-pi/2,pi/2) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-pi/4) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi/4) q[4];
CX q[3],q[4];
u3(pi/2,pi*0.65,pi) q[3];
u3(pi/2,pi*0.15,0) q[4];
u3(0,pi,pi/2) q[3];
u3(0,0,pi/2) q[4];
u3(pi/2,-pi/2,pi/2) q[3];
CX q[3],q[4];
u3(pi*0.4,-pi/2,pi/2) q[3];
u3(pi/2,0,0) q[4];
CX q[4],q[3];
u3(-pi/2,-pi/2,pi/2) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-pi/4) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi/4) q[4];
CX q[3],q[4];
u3(pi,0,pi/2) q[3];
u3(pi,0,3*pi/2) q[4];
u3(pi/2,3*pi/2,3*pi/2) q[3];
u3(pi/2,pi/2,3*pi/2) q[4];
u3(pi/2,-pi/2,pi/2) q[3];
CX q[3],q[4];
u3(pi*0.4,-pi/2,pi/2) q[3];
u3(pi/2,0,0) q[4];
CX q[4],q[3];
u3(-pi/2,-pi/2,pi/2) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-pi/4) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi/4) q[4];
CX q[3],q[4];
u3(pi/2,pi/2,pi/2) q[3];
u3(pi/2,pi/2,3*pi/2) q[4];
u3(1.1,-pi/2,pi/2) q[3];
u3(1.1,0,0) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.55) q[3];
u3(1.1,-pi/2,pi/2) q[4];
u3(1.1,0,0) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,0.55) q[4];
u3(1.1,-pi/2,pi/2) q[5];
u3(1.1,0,0) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,0.55) q[5];
u3(1.1,-pi/2,pi/2) q[6];
u3(1.1,0,0) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,0.55) q[6];
u3(pi,0,pi) q[5];
u3(0,0,-pi*0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi*0.55) q[5];
u3(pi,0,pi) q[6];
u3(0,0,-pi*0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi*0.55) q[6];
u3(pi/2,0,pi/4) q[5];
u3(pi/2,pi,3*pi/4) q[6];
u3(pi/2,-pi/2,pi/2) q[5];
CX q[5],q[6];
u3(pi*0.4,-pi/2,pi/2) q[5];
u3(pi/2,0,0) q[6];
CX q[6],q[5];
u3(-pi/2,-pi/2,pi/2) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-pi/4) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi/4) q[6];
CX q[5],q[6];
u3(pi/2,pi*0.65,pi) q[5];
u3(pi/2,pi*0.15,0) q[6];
u3(0,pi,pi/2) q[5];
u3(0,0,pi/2) q[6];
u3(pi/2,-pi/2,pi/2) q[5];
CX q[5],q[6];
u3(pi*0.4,-pi/2,pi/2) q[5];
u3(pi/2,0,0) q[6];
CX q[6],q[5];
u3(-pi/2,-pi/2,pi/2) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-pi/4) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi/4) q[6];
CX q[5],q[6];
u3(pi,0,pi/2) q[5];
u3(pi,0,3*pi/2) q[6];
u3(pi/2,3*pi/2,3*pi/2) q[5];
u3(pi/2,pi/2,3*pi/2) q[6];
u3(pi/2,-pi/2,pi/2) q[5];
CX q[5],q[6];
u3(pi*0.4,-pi/2,pi/2) q[5];
u3(pi/2,0,0) q[6];
CX q[6],q[5];
u3(-pi/2,-pi/2,pi/2) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-pi/4) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi/4) q[6];
CX q[5],q[6];
u3(pi/2,pi/2,pi/2) q[5];
u3(pi/2,pi/2,3*pi/2) q[6];
u3(1.1,-pi/2,pi/2) q[5];
u3(1.1,0,0) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,0.55) q[5];
u3(1.1,-pi/2,pi/2) q[6];
u3(1.1,0,0) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,0.55) q[6];
u3(1.1,-pi/2,pi/2) q[7];
u3(1.1,0,0) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,0.55) q[7];
u3(1.1,-pi/2,pi/2) q[0];
u3(1.1,0,0) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.55) q[0];
u3(pi,0,pi) q[7];
u3(0,0,-pi*0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi*0.55) q[7];
u3(pi,0,pi) q[0];
u3(0,0,-pi*0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi*0.55) q[0];
u3(pi/2,0,pi/4) q[7];
u3(pi/2,pi,3*pi/4) q[0];
u3(pi/2,-pi/2,pi/2) q[7];
CX q[7],q[0];
u3(pi*0.4,-pi/2,pi/2) q[7];
u3(pi/2,0,0) q[0];
CX q[0],q[7];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-pi/4) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi/4) q[0];
CX q[7],q[0];
u3(pi/2,pi*0.65,pi) q[7];
u3(pi/2,pi*0.15,0) q[0];
u3(0,pi,pi/2) q[7];
u3(0,0,pi/2) q[0];
u3(pi/2,-pi/2,pi/2) q[7];
CX q[7],q[0];
u3(pi*0.4,-pi/2,pi/2) q[7];
u3(pi/2,0,0) q[0];
CX q[0],q[7];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-pi/4) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi/4) q[0];
CX q[7],q[0];
u3(pi,0,pi/2) q[7];
u3(pi,0,3*pi/2) q[0];
u3(pi/2,3*pi/2,3*pi/2) q[7];
u3(pi/2,pi/2,3*pi/2) q[0];
u3(pi/2,-pi/2,pi/2) q[7];
CX q[7],q[0];
u3(pi*0.4,-pi/2,pi/2) q[7];
u3(pi/2,0,0) q[0];
CX q[0],q[7];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-pi/4) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi/4) q[0];
CX q[7],q[0];
u3(pi/2,pi/2,pi/2) q[7];
u3(pi/2,pi/2,3*pi/2) q[0];
u3(1.1,-pi/2,pi/2) q[7];
u3(1.1,0,0) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,0.55) q[7];
u3(1.1,-pi/2,pi/2) q[0];
u3(1.1,0,0) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.55) q[0];
u3(-pi/2,0,0) q[1];
u3(pi/2,0,pi/4) q[0];
u3(pi/2,pi,3*pi/4) q[1];
u3(pi/2,-pi/2,pi/2) q[0];
CX q[0],q[1];
u3(pi*0.05,-pi/2,pi/2) q[0];
u3(pi/2,0,0) q[1];
CX q[1],q[0];
u3(-pi/2,-pi/2,pi/2) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-pi/4) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi/4) q[1];
CX q[0],q[1];
u3(pi/2,pi*0.3,pi) q[0];
u3(pi/2,pi*1.8,0) q[1];
u3(pi/2,0,0) q[1];
u3(-pi/2,0,0) q[3];
u3(pi/2,0,pi/4) q[2];
u3(pi/2,pi,3*pi/4) q[3];
u3(pi/2,-pi/2,pi/2) q[2];
CX q[2],q[3];
u3(pi*0.05,-pi/2,pi/2) q[2];
u3(pi/2,0,0) q[3];
CX q[3],q[2];
u3(-pi/2,-pi/2,pi/2) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-pi/4) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi/4) q[3];
CX q[2],q[3];
u3(pi/2,pi*0.3,pi) q[2];
u3(pi/2,pi*1.8,0) q[3];
u3(pi/2,0,0) q[3];
u3(-pi/2,0,0) q[5];
u3(pi/2,0,pi/4) q[4];
u3(pi/2,pi,3*pi/4) q[5];
u3(pi/2,-pi/2,pi/2) q[4];
CX q[4],q[5];
u3(pi*0.05,-pi/2,pi/2) q[4];
u3(pi/2,0,0) q[5];
CX q[5],q[4];
u3(-pi/2,-pi/2,pi/2) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-pi/4) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi/4) q[5];
CX q[4],q[5];
u3(pi/2,pi*0.3,pi) q[4];
u3(pi/2,pi*1.8,0) q[5];
u3(pi/2,0,0) q[5];
u3(-pi/2,0,0) q[7];
u3(pi/2,0,pi/4) q[6];
u3(pi/2,pi,3*pi/4) q[7];
u3(pi/2,-pi/2,pi/2) q[6];
CX q[6],q[7];
u3(pi*0.05,-pi/2,pi/2) q[6];
u3(pi/2,0,0) q[7];
CX q[7],q[6];
u3(-pi/2,-pi/2,pi/2) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-pi/4) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi/4) q[7];
CX q[6],q[7];
u3(pi/2,pi*0.3,pi) q[6];
u3(pi/2,pi*1.8,0) q[7];
u3(pi/2,0,0) q[7];
u3(pi/2,0,pi/4) q[0];
u3(pi/2,pi,3*pi/4) q[1];
u3(pi/2,-pi/2,pi/2) q[0];
CX q[0],q[1];
u3(pi*0.05,-pi/2,pi/2) q[0];
u3(pi/2,0,0) q[1];
CX q[1],q[0];
u3(-pi/2,-pi/2,pi/2) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-pi/4) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi/4) q[1];
CX q[0],q[1];
u3(pi/2,pi*0.3,pi) q[0];
u3(pi/2,pi*1.8,0) q[1];
u3(pi/2,0,pi/4) q[2];
u3(pi/2,pi,3*pi/4) q[3];
u3(pi/2,-pi/2,pi/2) q[2];
CX q[2],q[3];
u3(pi*0.05,-pi/2,pi/2) q[2];
u3(pi/2,0,0) q[3];
CX q[3],q[2];
u3(-pi/2,-pi/2,pi/2) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-pi/4) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi/4) q[3];
CX q[2],q[3];
u3(pi/2,pi*0.3,pi) q[2];
u3(pi/2,pi*1.8,0) q[3];
u3(pi/2,0,pi/4) q[4];
u3(pi/2,pi,3*pi/4) q[5];
u3(pi/2,-pi/2,pi/2) q[4];
CX q[4],q[5];
u3(pi*0.05,-pi/2,pi/2) q[4];
u3(pi/2,0,0) q[5];
CX q[5],q[4];
u3(-pi/2,-pi/2,pi/2) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-pi/4) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi/4) q[5];
CX q[4],q[5];
u3(pi/2,pi*0.3,pi) q[4];
u3(pi/2,pi*1.8,0) q[5];
u3(pi/2,0,pi/4) q[6];
u3(pi/2,pi,3*pi/4) q[7];
u3(pi/2,-pi/2,pi/2) q[6];
CX q[6],q[7];
u3(pi*0.05,-pi/2,pi/2) q[6];
u3(pi/2,0,0) q[7];
CX q[7],q[6];
u3(-pi/2,-pi/2,pi/2) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-pi/4) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi/4) q[7];
CX q[6],q[7];
u3(pi/2,pi*0.3,pi) q[6];
u3(pi/2,pi*1.8,0) q[7];
u3(-pi/2,0,0) q[2];
u3(pi/2,0,pi/4) q[1];
u3(pi/2,pi,3*pi/4) q[2];
u3(pi/2,-pi/2,pi/2) q[1];
CX q[1],q[2];
u3(pi*0.05,-pi/2,pi/2) q[1];
u3(pi/2,0,0) q[2];
CX q[2],q[1];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-pi/4) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi/4) q[2];
CX q[1],q[2];
u3(pi/2,pi*0.3,pi) q[1];
u3(pi/2,pi*1.8,0) q[2];
u3(pi/2,0,0) q[2];
u3(-pi/2,0,0) q[4];
u3(pi/2,0,pi/4) q[3];
u3(pi/2,pi,3*pi/4) q[4];
u3(pi/2,-pi/2,pi/2) q[3];
CX q[3],q[4];
u3(pi*0.05,-pi/2,pi/2) q[3];
u3(pi/2,0,0) q[4];
CX q[4],q[3];
u3(-pi/2,-pi/2,pi/2) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-pi/4) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi/4) q[4];
CX q[3],q[4];
u3(pi/2,pi*0.3,pi) q[3];
u3(pi/2,pi*1.8,0) q[4];
u3(pi/2,0,0) q[4];
u3(-pi/2,0,0) q[6];
u3(pi/2,0,pi/4) q[5];
u3(pi/2,pi,3*pi/4) q[6];
u3(pi/2,-pi/2,pi/2) q[5];
CX q[5],q[6];
u3(pi*0.05,-pi/2,pi/2) q[5];
u3(pi/2,0,0) q[6];
CX q[6],q[5];
u3(-pi/2,-pi/2,pi/2) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-pi/4) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi/4) q[6];
CX q[5],q[6];
u3(pi/2,pi*0.3,pi) q[5];
u3(pi/2,pi*1.8,0) q[6];
u3(pi/2,0,0) q[6];
u3(-pi/2,0,0) q[0];
u3(pi/2,0,pi/4) q[7];
u3(pi/2,pi,3*pi/4) q[0];
u3(pi/2,-pi/2,pi/2) q[7];
CX q[7],q[0];
u3(pi*0.05,-pi/2,pi/2) q[7];
u3(pi/2,0,0) q[0];
CX q[0],q[7];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-pi/4) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi/4) q[0];
CX q[7],q[0];
u3(pi/2,pi*0.3,pi) q[7];
u3(pi/2,pi*1.8,0) q[0];
u3(pi/2,0,0) q[0];
u3(pi/2,0,pi/4) q[1];
u3(pi/2,pi,3*pi/4) q[2];
u3(pi/2,-pi/2,pi/2) q[1];
CX q[1],q[2];
u3(pi*0.05,-pi/2,pi/2) q[1];
u3(pi/2,0,0) q[2];
CX q[2],q[1];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-pi/4) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi/4) q[2];
CX q[1],q[2];
u3(pi/2,pi*0.3,pi) q[1];
u3(pi/2,pi*1.8,0) q[2];
u3(pi/2,0,pi/4) q[3];
u3(pi/2,pi,3*pi/4) q[4];
u3(pi/2,-pi/2,pi/2) q[3];
CX q[3],q[4];
u3(pi*0.05,-pi/2,pi/2) q[3];
u3(pi/2,0,0) q[4];
CX q[4],q[3];
u3(-pi/2,-pi/2,pi/2) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-pi/4) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi/4) q[4];
CX q[3],q[4];
u3(pi/2,pi*0.3,pi) q[3];
u3(pi/2,pi*1.8,0) q[4];
u3(pi/2,0,pi/4) q[5];
u3(pi/2,pi,3*pi/4) q[6];
u3(pi/2,-pi/2,pi/2) q[5];
CX q[5],q[6];
u3(pi*0.05,-pi/2,pi/2) q[5];
u3(pi/2,0,0) q[6];
CX q[6],q[5];
u3(-pi/2,-pi/2,pi/2) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-pi/4) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi/4) q[6];
CX q[5],q[6];
u3(pi/2,pi*0.3,pi) q[5];
u3(pi/2,pi*1.8,0) q[6];
u3(pi/2,0,pi/4) q[7];
u3(pi/2,pi,3*pi/4) q[0];
u3(pi/2,-pi/2,pi/2) q[7];
CX q[7],q[0];
u3(pi*0.05,-pi/2,pi/2) q[7];
u3(pi/2,0,0) q[0];
CX q[0],q[7];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-pi/4) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi/4) q[0];
CX q[7],q[0];
u3(pi/2,pi*0.3,pi) q[7];
u3(pi/2,pi*1.8,0) q[0];
u3(1.1,-pi/2,pi/2) q[0];
u3(1.1,0,0) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.55) q[0];
u3(1.1,-pi/2,pi/2) q[1];
u3(1.1,0,0) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.55) q[1];
u3(pi,0,pi) q[0];
u3(0,0,-pi*0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi*0.55) q[0];
u3(pi,0,pi) q[1];
u3(0,0,-pi*0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi*0.55) q[1];
u3(pi/2,0,pi/4) q[0];
u3(pi/2,pi,3*pi/4) q[1];
u3(pi/2,-pi/2,pi/2) q[0];
CX q[0],q[1];
u3(pi*0.4,-pi/2,pi/2) q[0];
u3(pi/2,0,0) q[1];
CX q[1],q[0];
u3(-pi/2,-pi/2,pi/2) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-pi/4) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi/4) q[1];
CX q[0],q[1];
u3(pi/2,pi*0.65,pi) q[0];
u3(pi/2,pi*0.15,0) q[1];
u3(0,pi,pi/2) q[0];
u3(0,0,pi/2) q[1];
u3(pi/2,-pi/2,pi/2) q[0];
CX q[0],q[1];
u3(pi*0.4,-pi/2,pi/2) q[0];
u3(pi/2,0,0) q[1];
CX q[1],q[0];
u3(-pi/2,-pi/2,pi/2) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-pi/4) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi/4) q[1];
CX q[0],q[1];
u3(pi,0,pi/2) q[0];
u3(pi,0,3*pi/2) q[1];
u3(pi/2,3*pi/2,3*pi/2) q[0];
u3(pi/2,pi/2,3*pi/2) q[1];
u3(pi/2,-pi/2,pi/2) q[0];
CX q[0],q[1];
u3(pi*0.4,-pi/2,pi/2) q[0];
u3(pi/2,0,0) q[1];
CX q[1],q[0];
u3(-pi/2,-pi/2,pi/2) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-pi/4) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi/4) q[1];
CX q[0],q[1];
u3(pi/2,pi/2,pi/2) q[0];
u3(pi/2,pi/2,3*pi/2) q[1];
u3(1.1,-pi/2,pi/2) q[0];
u3(1.1,0,0) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.55) q[0];
u3(1.1,-pi/2,pi/2) q[1];
u3(1.1,0,0) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.55) q[1];
u3(1.1,-pi/2,pi/2) q[2];
u3(1.1,0,0) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.55) q[2];
u3(1.1,-pi/2,pi/2) q[3];
u3(1.1,0,0) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.55) q[3];
u3(pi,0,pi) q[2];
u3(0,0,-pi*0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi*0.55) q[2];
u3(pi,0,pi) q[3];
u3(0,0,-pi*0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi*0.55) q[3];
u3(pi/2,0,pi/4) q[2];
u3(pi/2,pi,3*pi/4) q[3];
u3(pi/2,-pi/2,pi/2) q[2];
CX q[2],q[3];
u3(pi*0.4,-pi/2,pi/2) q[2];
u3(pi/2,0,0) q[3];
CX q[3],q[2];
u3(-pi/2,-pi/2,pi/2) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-pi/4) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi/4) q[3];
CX q[2],q[3];
u3(pi/2,pi*0.65,pi) q[2];
u3(pi/2,pi*0.15,0) q[3];
u3(0,pi,pi/2) q[2];
u3(0,0,pi/2) q[3];
u3(pi/2,-pi/2,pi/2) q[2];
CX q[2],q[3];
u3(pi*0.4,-pi/2,pi/2) q[2];
u3(pi/2,0,0) q[3];
CX q[3],q[2];
u3(-pi/2,-pi/2,pi/2) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-pi/4) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi/4) q[3];
CX q[2],q[3];
u3(pi,0,pi/2) q[2];
u3(pi,0,3*pi/2) q[3];
u3(pi/2,3*pi/2,3*pi/2) q[2];
u3(pi/2,pi/2,3*pi/2) q[3];
u3(pi/2,-pi/2,pi/2) q[2];
CX q[2],q[3];
u3(pi*0.4,-pi/2,pi/2) q[2];
u3(pi/2,0,0) q[3];
CX q[3],q[2];
u3(-pi/2,-pi/2,pi/2) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-pi/4) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi/4) q[3];
CX q[2],q[3];
u3(pi/2,pi/2,pi/2) q[2];
u3(pi/2,pi/2,3*pi/2) q[3];
u3(1.1,-pi/2,pi/2) q[2];
u3(1.1,0,0) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.55) q[2];
u3(1.1,-pi/2,pi/2) q[3];
u3(1.1,0,0) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.55) q[3];
u3(1.1,-pi/2,pi/2) q[4];
u3(1.1,0,0) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,0.55) q[4];
u3(1.1,-pi/2,pi/2) q[5];
u3(1.1,0,0) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,0.55) q[5];
u3(pi,0,pi) q[4];
u3(0,0,-pi*0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi*0.55) q[4];
u3(pi,0,pi) q[5];
u3(0,0,-pi*0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi*0.55) q[5];
u3(pi/2,0,pi/4) q[4];
u3(pi/2,pi,3*pi/4) q[5];
u3(pi/2,-pi/2,pi/2) q[4];
CX q[4],q[5];
u3(pi*0.4,-pi/2,pi/2) q[4];
u3(pi/2,0,0) q[5];
CX q[5],q[4];
u3(-pi/2,-pi/2,pi/2) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-pi/4) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi/4) q[5];
CX q[4],q[5];
u3(pi/2,pi*0.65,pi) q[4];
u3(pi/2,pi*0.15,0) q[5];
u3(0,pi,pi/2) q[4];
u3(0,0,pi/2) q[5];
u3(pi/2,-pi/2,pi/2) q[4];
CX q[4],q[5];
u3(pi*0.4,-pi/2,pi/2) q[4];
u3(pi/2,0,0) q[5];
CX q[5],q[4];
u3(-pi/2,-pi/2,pi/2) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-pi/4) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi/4) q[5];
CX q[4],q[5];
u3(pi,0,pi/2) q[4];
u3(pi,0,3*pi/2) q[5];
u3(pi/2,3*pi/2,3*pi/2) q[4];
u3(pi/2,pi/2,3*pi/2) q[5];
u3(pi/2,-pi/2,pi/2) q[4];
CX q[4],q[5];
u3(pi*0.4,-pi/2,pi/2) q[4];
u3(pi/2,0,0) q[5];
CX q[5],q[4];
u3(-pi/2,-pi/2,pi/2) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-pi/4) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi/4) q[5];
CX q[4],q[5];
u3(pi/2,pi/2,pi/2) q[4];
u3(pi/2,pi/2,3*pi/2) q[5];
u3(1.1,-pi/2,pi/2) q[4];
u3(1.1,0,0) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,0.55) q[4];
u3(1.1,-pi/2,pi/2) q[5];
u3(1.1,0,0) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,0.55) q[5];
u3(1.1,-pi/2,pi/2) q[6];
u3(1.1,0,0) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,0.55) q[6];
u3(1.1,-pi/2,pi/2) q[7];
u3(1.1,0,0) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,0.55) q[7];
u3(pi,0,pi) q[6];
u3(0,0,-pi*0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi*0.55) q[6];
u3(pi,0,pi) q[7];
u3(0,0,-pi*0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi*0.55) q[7];
u3(pi/2,0,pi/4) q[6];
u3(pi/2,pi,3*pi/4) q[7];
u3(pi/2,-pi/2,pi/2) q[6];
CX q[6],q[7];
u3(pi*0.4,-pi/2,pi/2) q[6];
u3(pi/2,0,0) q[7];
CX q[7],q[6];
u3(-pi/2,-pi/2,pi/2) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-pi/4) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi/4) q[7];
CX q[6],q[7];
u3(pi/2,pi*0.65,pi) q[6];
u3(pi/2,pi*0.15,0) q[7];
u3(0,pi,pi/2) q[6];
u3(0,0,pi/2) q[7];
u3(pi/2,-pi/2,pi/2) q[6];
CX q[6],q[7];
u3(pi*0.4,-pi/2,pi/2) q[6];
u3(pi/2,0,0) q[7];
CX q[7],q[6];
u3(-pi/2,-pi/2,pi/2) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-pi/4) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi/4) q[7];
CX q[6],q[7];
u3(pi,0,pi/2) q[6];
u3(pi,0,3*pi/2) q[7];
u3(pi/2,3*pi/2,3*pi/2) q[6];
u3(pi/2,pi/2,3*pi/2) q[7];
u3(pi/2,-pi/2,pi/2) q[6];
CX q[6],q[7];
u3(pi*0.4,-pi/2,pi/2) q[6];
u3(pi/2,0,0) q[7];
CX q[7],q[6];
u3(-pi/2,-pi/2,pi/2) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-pi/4) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi/4) q[7];
CX q[6],q[7];
u3(pi/2,pi/2,pi/2) q[6];
u3(pi/2,pi/2,3*pi/2) q[7];
u3(1.1,-pi/2,pi/2) q[6];
u3(1.1,0,0) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,0.55) q[6];
u3(1.1,-pi/2,pi/2) q[7];
u3(1.1,0,0) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,0.55) q[7];
u3(1.1,-pi/2,pi/2) q[1];
u3(1.1,0,0) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.55) q[1];
u3(1.1,-pi/2,pi/2) q[2];
u3(1.1,0,0) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.55) q[2];
u3(pi,0,pi) q[1];
u3(0,0,-pi*0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,pi*0.55) q[1];
u3(pi,0,pi) q[2];
u3(0,0,-pi*0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi*0.55) q[2];
u3(pi/2,0,pi/4) q[1];
u3(pi/2,pi,3*pi/4) q[2];
u3(pi/2,-pi/2,pi/2) q[1];
CX q[1],q[2];
u3(pi*0.4,-pi/2,pi/2) q[1];
u3(pi/2,0,0) q[2];
CX q[2],q[1];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-pi/4) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi/4) q[2];
CX q[1],q[2];
u3(pi/2,pi*0.65,pi) q[1];
u3(pi/2,pi*0.15,0) q[2];
u3(0,pi,pi/2) q[1];
u3(0,0,pi/2) q[2];
u3(pi/2,-pi/2,pi/2) q[1];
CX q[1],q[2];
u3(pi*0.4,-pi/2,pi/2) q[1];
u3(pi/2,0,0) q[2];
CX q[2],q[1];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-pi/4) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi/4) q[2];
CX q[1],q[2];
u3(pi,0,pi/2) q[1];
u3(pi,0,3*pi/2) q[2];
u3(pi/2,3*pi/2,3*pi/2) q[1];
u3(pi/2,pi/2,3*pi/2) q[2];
u3(pi/2,-pi/2,pi/2) q[1];
CX q[1],q[2];
u3(pi*0.4,-pi/2,pi/2) q[1];
u3(pi/2,0,0) q[2];
CX q[2],q[1];
u3(-pi/2,-pi/2,pi/2) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-pi/4) q[2];
u3(pi,0,pi) q[2];
u3(0,0,pi/4) q[2];
CX q[1],q[2];
u3(pi/2,pi/2,pi/2) q[1];
u3(pi/2,pi/2,3*pi/2) q[2];
u3(1.1,-pi/2,pi/2) q[1];
u3(1.1,0,0) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.55) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.55) q[1];
u3(1.1,-pi/2,pi/2) q[2];
u3(1.1,0,0) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.55) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.55) q[2];
u3(1.1,-pi/2,pi/2) q[3];
u3(1.1,0,0) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.55) q[3];
u3(1.1,-pi/2,pi/2) q[4];
u3(1.1,0,0) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,0.55) q[4];
u3(pi,0,pi) q[3];
u3(0,0,-pi*0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,pi*0.55) q[3];
u3(pi,0,pi) q[4];
u3(0,0,-pi*0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi*0.55) q[4];
u3(pi/2,0,pi/4) q[3];
u3(pi/2,pi,3*pi/4) q[4];
u3(pi/2,-pi/2,pi/2) q[3];
CX q[3],q[4];
u3(pi*0.4,-pi/2,pi/2) q[3];
u3(pi/2,0,0) q[4];
CX q[4],q[3];
u3(-pi/2,-pi/2,pi/2) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-pi/4) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi/4) q[4];
CX q[3],q[4];
u3(pi/2,pi*0.65,pi) q[3];
u3(pi/2,pi*0.15,0) q[4];
u3(0,pi,pi/2) q[3];
u3(0,0,pi/2) q[4];
u3(pi/2,-pi/2,pi/2) q[3];
CX q[3],q[4];
u3(pi*0.4,-pi/2,pi/2) q[3];
u3(pi/2,0,0) q[4];
CX q[4],q[3];
u3(-pi/2,-pi/2,pi/2) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-pi/4) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi/4) q[4];
CX q[3],q[4];
u3(pi,0,pi/2) q[3];
u3(pi,0,3*pi/2) q[4];
u3(pi/2,3*pi/2,3*pi/2) q[3];
u3(pi/2,pi/2,3*pi/2) q[4];
u3(pi/2,-pi/2,pi/2) q[3];
CX q[3],q[4];
u3(pi*0.4,-pi/2,pi/2) q[3];
u3(pi/2,0,0) q[4];
CX q[4],q[3];
u3(-pi/2,-pi/2,pi/2) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-pi/4) q[4];
u3(pi,0,pi) q[4];
u3(0,0,pi/4) q[4];
CX q[3],q[4];
u3(pi/2,pi/2,pi/2) q[3];
u3(pi/2,pi/2,3*pi/2) q[4];
u3(1.1,-pi/2,pi/2) q[3];
u3(1.1,0,0) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-0.55) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.55) q[3];
u3(1.1,-pi/2,pi/2) q[4];
u3(1.1,0,0) q[4];
u3(pi,0,pi) q[4];
u3(0,0,-0.55) q[4];
u3(pi,0,pi) q[4];
u3(0,0,0.55) q[4];
u3(1.1,-pi/2,pi/2) q[5];
u3(1.1,0,0) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,0.55) q[5];
u3(1.1,-pi/2,pi/2) q[6];
u3(1.1,0,0) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,0.55) q[6];
u3(pi,0,pi) q[5];
u3(0,0,-pi*0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,pi*0.55) q[5];
u3(pi,0,pi) q[6];
u3(0,0,-pi*0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi*0.55) q[6];
u3(pi/2,0,pi/4) q[5];
u3(pi/2,pi,3*pi/4) q[6];
u3(pi/2,-pi/2,pi/2) q[5];
CX q[5],q[6];
u3(pi*0.4,-pi/2,pi/2) q[5];
u3(pi/2,0,0) q[6];
CX q[6],q[5];
u3(-pi/2,-pi/2,pi/2) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-pi/4) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi/4) q[6];
CX q[5],q[6];
u3(pi/2,pi*0.65,pi) q[5];
u3(pi/2,pi*0.15,0) q[6];
u3(0,pi,pi/2) q[5];
u3(0,0,pi/2) q[6];
u3(pi/2,-pi/2,pi/2) q[5];
CX q[5],q[6];
u3(pi*0.4,-pi/2,pi/2) q[5];
u3(pi/2,0,0) q[6];
CX q[6],q[5];
u3(-pi/2,-pi/2,pi/2) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-pi/4) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi/4) q[6];
CX q[5],q[6];
u3(pi,0,pi/2) q[5];
u3(pi,0,3*pi/2) q[6];
u3(pi/2,3*pi/2,3*pi/2) q[5];
u3(pi/2,pi/2,3*pi/2) q[6];
u3(pi/2,-pi/2,pi/2) q[5];
CX q[5],q[6];
u3(pi*0.4,-pi/2,pi/2) q[5];
u3(pi/2,0,0) q[6];
CX q[6],q[5];
u3(-pi/2,-pi/2,pi/2) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-pi/4) q[6];
u3(pi,0,pi) q[6];
u3(0,0,pi/4) q[6];
CX q[5],q[6];
u3(pi/2,pi/2,pi/2) q[5];
u3(pi/2,pi/2,3*pi/2) q[6];
u3(1.1,-pi/2,pi/2) q[5];
u3(1.1,0,0) q[5];
u3(pi,0,pi) q[5];
u3(0,0,-0.55) q[5];
u3(pi,0,pi) q[5];
u3(0,0,0.55) q[5];
u3(1.1,-pi/2,pi/2) q[6];
u3(1.1,0,0) q[6];
u3(pi,0,pi) q[6];
u3(0,0,-0.55) q[6];
u3(pi,0,pi) q[6];
u3(0,0,0.55) q[6];
u3(1.1,-pi/2,pi/2) q[7];
u3(1.1,0,0) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,0.55) q[7];
u3(1.1,-pi/2,pi/2) q[0];
u3(1.1,0,0) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.55) q[0];
u3(pi,0,pi) q[7];
u3(0,0,-pi*0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,pi*0.55) q[7];
u3(pi,0,pi) q[0];
u3(0,0,-pi*0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi*0.55) q[0];
u3(pi/2,0,pi/4) q[7];
u3(pi/2,pi,3*pi/4) q[0];
u3(pi/2,-pi/2,pi/2) q[7];
CX q[7],q[0];
u3(pi*0.4,-pi/2,pi/2) q[7];
u3(pi/2,0,0) q[0];
CX q[0],q[7];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-pi/4) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi/4) q[0];
CX q[7],q[0];
u3(pi/2,pi*0.65,pi) q[7];
u3(pi/2,pi*0.15,0) q[0];
u3(0,pi,pi/2) q[7];
u3(0,0,pi/2) q[0];
u3(pi/2,-pi/2,pi/2) q[7];
CX q[7],q[0];
u3(pi*0.4,-pi/2,pi/2) q[7];
u3(pi/2,0,0) q[0];
CX q[0],q[7];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-pi/4) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi/4) q[0];
CX q[7],q[0];
u3(pi,0,pi/2) q[7];
u3(pi,0,3*pi/2) q[0];
u3(pi/2,3*pi/2,3*pi/2) q[7];
u3(pi/2,pi/2,3*pi/2) q[0];
u3(pi/2,-pi/2,pi/2) q[7];
CX q[7],q[0];
u3(pi*0.4,-pi/2,pi/2) q[7];
u3(pi/2,0,0) q[0];
CX q[0],q[7];
u3(-pi/2,-pi/2,pi/2) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-pi/4) q[0];
u3(pi,0,pi) q[0];
u3(0,0,pi/4) q[0];
CX q[7],q[0];
u3(pi/2,pi/2,pi/2) q[7];
u3(pi/2,pi/2,3*pi/2) q[0];
u3(1.1,-pi/2,pi/2) q[7];
u3(1.1,0,0) q[7];
u3(pi,0,pi) q[7];
u3(0,0,-0.55) q[7];
u3(pi,0,pi) q[7];
u3(0,0,0.55) q[7];
u3(1.1,-pi/2,pi/2) q[0];
u3(1.1,0,0) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.55) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.55) q[0];
