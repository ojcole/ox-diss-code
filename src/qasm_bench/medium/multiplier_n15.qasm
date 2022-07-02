OPENQASM 2.0;
include "qelib1.inc";
qreg q[15];
u3(pi,0,pi) q[13];
u3(pi,0,pi) q[12];
u3(pi,0,pi) q[10];
u3(pi,0,pi) q[9];
u3(pi/2,0,pi) q[1];
cx q[9],q[1];
u3(0,0,-0.785398185253143) q[1];
cx q[12],q[1];
u3(0,0,0.785398185253143) q[1];
cx q[9],q[1];
u3(0,0,-0.785398185253143) q[1];
cx q[12],q[1];
u3(0,0,0.785398185253143) q[9];
u3(0,0,0.785398185253143) q[1];
u3(pi/2,0,pi) q[1];
cx q[12],q[9];
u3(0,0,0.785398185253143) q[12];
u3(0,0,-0.785398185253143) q[9];
cx q[12],q[9];
u3(pi/2,0,pi) q[4];
cx q[10],q[4];
u3(0,0,-0.785398185253143) q[4];
cx q[12],q[4];
u3(0,0,0.785398185253143) q[4];
cx q[10],q[4];
u3(0,0,-0.785398185253143) q[4];
cx q[12],q[4];
u3(0,0,0.785398185253143) q[10];
u3(0,0,0.785398185253143) q[4];
u3(pi/2,0,pi) q[4];
cx q[12],q[10];
u3(0,0,0.785398185253143) q[12];
u3(0,0,-0.785398185253143) q[10];
cx q[12],q[10];
u3(pi/2,0,pi) q[7];
cx q[11],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[12],q[7];
u3(0,0,0.785398185253143) q[7];
cx q[11],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[12],q[7];
u3(0,0,0.785398185253143) q[11];
u3(0,0,0.785398185253143) q[7];
u3(pi/2,0,pi) q[7];
cx q[12],q[11];
u3(0,0,0.785398185253143) q[12];
u3(0,0,-0.785398185253143) q[11];
cx q[12],q[11];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[1],q[2];
u3(0,0,0.785398185253143) q[1];
u3(0,0,-0.785398185253143) q[2];
cx q[1],q[2];
cx q[1],q[2];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[0],q[2];
u3(0,0,0.785398185253143) q[0];
u3(0,0,-0.785398185253143) q[2];
cx q[0],q[2];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[4],q[5];
u3(0,0,0.785398185253143) q[4];
u3(0,0,-0.785398185253143) q[5];
cx q[4],q[5];
cx q[4],q[5];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[3],q[5];
u3(0,0,0.785398185253143) q[3];
u3(0,0,-0.785398185253143) q[5];
cx q[3],q[5];
cx q[7],q[8];
cx q[6],q[8];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[3],q[5];
u3(0,0,0.785398185253143) q[3];
u3(0,0,-0.785398185253143) q[5];
cx q[3],q[5];
cx q[4],q[5];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[4],q[5];
u3(0,0,0.785398185253143) q[4];
u3(0,0,-0.785398185253143) q[5];
cx q[4],q[5];
cx q[4],q[5];
cx q[3],q[5];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[0],q[2];
u3(0,0,0.785398185253143) q[0];
u3(0,0,-0.785398185253143) q[2];
cx q[0],q[2];
cx q[1],q[2];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[1],q[2];
u3(0,0,0.785398185253143) q[1];
u3(0,0,-0.785398185253143) q[2];
cx q[1],q[2];
cx q[1],q[2];
cx q[0],q[2];
u3(pi/2,0,pi) q[1];
cx q[9],q[1];
u3(0,0,-0.785398185253143) q[1];
cx q[12],q[1];
u3(0,0,0.785398185253143) q[1];
cx q[9],q[1];
u3(0,0,-0.785398185253143) q[1];
cx q[12],q[1];
u3(0,0,0.785398185253143) q[9];
u3(0,0,0.785398185253143) q[1];
u3(pi/2,0,pi) q[1];
cx q[12],q[9];
u3(0,0,0.785398185253143) q[12];
u3(0,0,-0.785398185253143) q[9];
cx q[12],q[9];
u3(pi/2,0,pi) q[4];
cx q[10],q[4];
u3(0,0,-0.785398185253143) q[4];
cx q[12],q[4];
u3(0,0,0.785398185253143) q[4];
cx q[10],q[4];
u3(0,0,-0.785398185253143) q[4];
cx q[12],q[4];
u3(0,0,0.785398185253143) q[10];
u3(0,0,0.785398185253143) q[4];
u3(pi/2,0,pi) q[4];
cx q[12],q[10];
u3(0,0,0.785398185253143) q[12];
u3(0,0,-0.785398185253143) q[10];
cx q[12],q[10];
u3(pi/2,0,pi) q[7];
cx q[11],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[12],q[7];
u3(0,0,0.785398185253143) q[7];
cx q[11],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[12],q[7];
u3(0,0,0.785398185253143) q[11];
u3(0,0,0.785398185253143) q[7];
u3(pi/2,0,pi) q[7];
cx q[12],q[11];
u3(0,0,0.785398185253143) q[12];
u3(0,0,-0.785398185253143) q[11];
cx q[12],q[11];
u3(pi/2,0,pi) q[4];
cx q[9],q[4];
u3(0,0,-0.785398185253143) q[4];
cx q[13],q[4];
u3(0,0,0.785398185253143) q[4];
cx q[9],q[4];
u3(0,0,-0.785398185253143) q[4];
cx q[13],q[4];
u3(0,0,0.785398185253143) q[9];
u3(0,0,0.785398185253143) q[4];
u3(pi/2,0,pi) q[4];
cx q[13],q[9];
u3(0,0,0.785398185253143) q[13];
u3(0,0,-0.785398185253143) q[9];
cx q[13],q[9];
u3(pi/2,0,pi) q[7];
cx q[10],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[13],q[7];
u3(0,0,0.785398185253143) q[7];
cx q[10],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[13],q[7];
u3(0,0,0.785398185253143) q[10];
u3(0,0,0.785398185253143) q[7];
u3(pi/2,0,pi) q[7];
cx q[13],q[10];
u3(0,0,0.785398185253143) q[13];
u3(0,0,-0.785398185253143) q[10];
cx q[13],q[10];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[1],q[2];
u3(0,0,0.785398185253143) q[1];
u3(0,0,-0.785398185253143) q[2];
cx q[1],q[2];
cx q[1],q[2];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[0],q[2];
u3(0,0,0.785398185253143) q[0];
u3(0,0,-0.785398185253143) q[2];
cx q[0],q[2];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[4],q[5];
u3(0,0,0.785398185253143) q[4];
u3(0,0,-0.785398185253143) q[5];
cx q[4],q[5];
cx q[4],q[5];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[3],q[5];
u3(0,0,0.785398185253143) q[3];
u3(0,0,-0.785398185253143) q[5];
cx q[3],q[5];
cx q[7],q[8];
cx q[6],q[8];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[3],q[5];
u3(0,0,0.785398185253143) q[3];
u3(0,0,-0.785398185253143) q[5];
cx q[3],q[5];
cx q[4],q[5];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[4],q[5];
u3(0,0,0.785398185253143) q[4];
u3(0,0,-0.785398185253143) q[5];
cx q[4],q[5];
cx q[4],q[5];
cx q[3],q[5];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[0],q[2];
u3(0,0,0.785398185253143) q[0];
u3(0,0,-0.785398185253143) q[2];
cx q[0],q[2];
cx q[1],q[2];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[1],q[2];
u3(0,0,0.785398185253143) q[1];
u3(0,0,-0.785398185253143) q[2];
cx q[1],q[2];
cx q[1],q[2];
cx q[0],q[2];
u3(pi/2,0,pi) q[4];
cx q[9],q[4];
u3(0,0,-0.785398185253143) q[4];
cx q[13],q[4];
u3(0,0,0.785398185253143) q[4];
cx q[9],q[4];
u3(0,0,-0.785398185253143) q[4];
cx q[13],q[4];
u3(0,0,0.785398185253143) q[9];
u3(0,0,0.785398185253143) q[4];
u3(pi/2,0,pi) q[4];
cx q[13],q[9];
u3(0,0,0.785398185253143) q[13];
u3(0,0,-0.785398185253143) q[9];
cx q[13],q[9];
u3(pi/2,0,pi) q[7];
cx q[10],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[13],q[7];
u3(0,0,0.785398185253143) q[7];
cx q[10],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[13],q[7];
u3(0,0,0.785398185253143) q[10];
u3(0,0,0.785398185253143) q[7];
u3(pi/2,0,pi) q[7];
cx q[13],q[10];
u3(0,0,0.785398185253143) q[13];
u3(0,0,-0.785398185253143) q[10];
cx q[13],q[10];
u3(pi/2,0,pi) q[7];
cx q[9],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[14],q[7];
u3(0,0,0.785398185253143) q[7];
cx q[9],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[14],q[7];
u3(0,0,0.785398185253143) q[9];
u3(0,0,0.785398185253143) q[7];
u3(pi/2,0,pi) q[7];
cx q[14],q[9];
u3(0,0,0.785398185253143) q[14];
u3(0,0,-0.785398185253143) q[9];
cx q[14],q[9];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[1],q[2];
u3(0,0,0.785398185253143) q[1];
u3(0,0,-0.785398185253143) q[2];
cx q[1],q[2];
cx q[1],q[2];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[0],q[2];
u3(0,0,0.785398185253143) q[0];
u3(0,0,-0.785398185253143) q[2];
cx q[0],q[2];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[4],q[5];
u3(0,0,0.785398185253143) q[4];
u3(0,0,-0.785398185253143) q[5];
cx q[4],q[5];
cx q[4],q[5];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[3],q[5];
u3(0,0,0.785398185253143) q[3];
u3(0,0,-0.785398185253143) q[5];
cx q[3],q[5];
cx q[7],q[8];
cx q[6],q[8];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[3],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[3],q[5];
u3(0,0,0.785398185253143) q[3];
u3(0,0,-0.785398185253143) q[5];
cx q[3],q[5];
cx q[4],q[5];
u3(pi/2,0,pi) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.785398185253143) q[6];
cx q[4],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,0.785398185253143) q[6];
u3(pi/2,0,pi) q[6];
cx q[4],q[5];
u3(0,0,0.785398185253143) q[4];
u3(0,0,-0.785398185253143) q[5];
cx q[4],q[5];
cx q[4],q[5];
cx q[3],q[5];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[0],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[0],q[2];
u3(0,0,0.785398185253143) q[0];
u3(0,0,-0.785398185253143) q[2];
cx q[0],q[2];
cx q[1],q[2];
u3(pi/2,0,pi) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[2],q[3];
u3(0,0,-0.785398185253143) q[3];
cx q[1],q[3];
u3(0,0,0.785398185253143) q[2];
u3(0,0,0.785398185253143) q[3];
u3(pi/2,0,pi) q[3];
cx q[1],q[2];
u3(0,0,0.785398185253143) q[1];
u3(0,0,-0.785398185253143) q[2];
cx q[1],q[2];
cx q[1],q[2];
cx q[0],q[2];
u3(pi/2,0,pi) q[7];
cx q[9],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[14],q[7];
u3(0,0,0.785398185253143) q[7];
cx q[9],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[14],q[7];
u3(0,0,0.785398185253143) q[9];
u3(0,0,0.785398185253143) q[7];
u3(pi/2,0,pi) q[7];
cx q[14],q[9];
u3(0,0,0.785398185253143) q[14];
u3(0,0,-0.785398185253143) q[9];
cx q[14],q[9];
