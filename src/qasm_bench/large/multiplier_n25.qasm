OPENQASM 2.0;
include "qelib1.inc";
qreg q0[25];
u3(pi,0,pi) q0[21];
u3(pi,0,pi) q0[20];
u3(pi,0,pi) q0[16];
u3(pi/2,0,pi) q0[1];
cx q0[15],q0[1];
u3(0,0,-pi/4) q0[1];
cx q0[20],q0[1];
u3(0,0,pi/4) q0[1];
cx q0[15],q0[1];
u3(0,0,-pi/4) q0[1];
cx q0[20],q0[1];
u3(0,0,pi/4) q0[15];
u3(0,0,pi/4) q0[1];
u3(pi/2,0,pi) q0[1];
cx q0[20],q0[15];
u3(0,0,pi/4) q0[20];
u3(0,0,-pi/4) q0[15];
cx q0[20],q0[15];
u3(pi/2,0,pi) q0[4];
cx q0[16],q0[4];
u3(0,0,-pi/4) q0[4];
cx q0[20],q0[4];
u3(0,0,pi/4) q0[4];
cx q0[16],q0[4];
u3(0,0,-pi/4) q0[4];
cx q0[20],q0[4];
u3(0,0,pi/4) q0[16];
u3(0,0,pi/4) q0[4];
u3(pi/2,0,pi) q0[4];
cx q0[20],q0[16];
u3(0,0,pi/4) q0[20];
u3(0,0,-pi/4) q0[16];
cx q0[20],q0[16];
u3(pi/2,0,pi) q0[7];
cx q0[17],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[20],q0[7];
u3(0,0,pi/4) q0[7];
cx q0[17],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[20],q0[7];
u3(0,0,pi/4) q0[17];
u3(0,0,pi/4) q0[7];
u3(pi/2,0,pi) q0[7];
cx q0[20],q0[17];
u3(0,0,pi/4) q0[20];
u3(0,0,-pi/4) q0[17];
cx q0[20],q0[17];
u3(pi/2,0,pi) q0[10];
cx q0[18],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[20],q0[10];
u3(0,0,pi/4) q0[10];
cx q0[18],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[20],q0[10];
u3(0,0,pi/4) q0[18];
u3(0,0,pi/4) q0[10];
u3(pi/2,0,pi) q0[10];
cx q0[20],q0[18];
u3(0,0,pi/4) q0[20];
u3(0,0,-pi/4) q0[18];
cx q0[20],q0[18];
u3(pi/2,0,pi) q0[13];
cx q0[19],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[20],q0[13];
u3(0,0,pi/4) q0[13];
cx q0[19],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[20],q0[13];
u3(0,0,pi/4) q0[19];
u3(0,0,pi/4) q0[13];
u3(pi/2,0,pi) q0[13];
cx q0[20],q0[19];
u3(0,0,pi/4) q0[20];
u3(0,0,-pi/4) q0[19];
cx q0[20],q0[19];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[1],q0[2];
u3(0,0,pi/4) q0[1];
u3(0,0,-pi/4) q0[2];
cx q0[1],q0[2];
cx q0[1],q0[2];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[0],q0[2];
u3(0,0,pi/4) q0[0];
u3(0,0,-pi/4) q0[2];
cx q0[0],q0[2];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[4],q0[5];
u3(0,0,pi/4) q0[4];
u3(0,0,-pi/4) q0[5];
cx q0[4],q0[5];
cx q0[4],q0[5];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[3],q0[5];
u3(0,0,pi/4) q0[3];
u3(0,0,-pi/4) q0[5];
cx q0[3],q0[5];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[7],q0[8];
u3(0,0,pi/4) q0[7];
u3(0,0,-pi/4) q0[8];
cx q0[7],q0[8];
cx q0[7],q0[8];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[6],q0[8];
u3(0,0,pi/4) q0[6];
u3(0,0,-pi/4) q0[8];
cx q0[6],q0[8];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[10],q0[11];
u3(0,0,pi/4) q0[10];
u3(0,0,-pi/4) q0[11];
cx q0[10],q0[11];
cx q0[10],q0[11];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[9],q0[11];
u3(0,0,pi/4) q0[9];
u3(0,0,-pi/4) q0[11];
cx q0[9],q0[11];
cx q0[13],q0[14];
cx q0[12],q0[14];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[9],q0[11];
u3(0,0,pi/4) q0[9];
u3(0,0,-pi/4) q0[11];
cx q0[9],q0[11];
cx q0[10],q0[11];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[10],q0[11];
u3(0,0,pi/4) q0[10];
u3(0,0,-pi/4) q0[11];
cx q0[10],q0[11];
cx q0[10],q0[11];
cx q0[9],q0[11];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[6],q0[8];
u3(0,0,pi/4) q0[6];
u3(0,0,-pi/4) q0[8];
cx q0[6],q0[8];
cx q0[7],q0[8];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[7],q0[8];
u3(0,0,pi/4) q0[7];
u3(0,0,-pi/4) q0[8];
cx q0[7],q0[8];
cx q0[7],q0[8];
cx q0[6],q0[8];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[3],q0[5];
u3(0,0,pi/4) q0[3];
u3(0,0,-pi/4) q0[5];
cx q0[3],q0[5];
cx q0[4],q0[5];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[4],q0[5];
u3(0,0,pi/4) q0[4];
u3(0,0,-pi/4) q0[5];
cx q0[4],q0[5];
cx q0[4],q0[5];
cx q0[3],q0[5];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[0],q0[2];
u3(0,0,pi/4) q0[0];
u3(0,0,-pi/4) q0[2];
cx q0[0],q0[2];
cx q0[1],q0[2];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[1],q0[2];
u3(0,0,pi/4) q0[1];
u3(0,0,-pi/4) q0[2];
cx q0[1],q0[2];
cx q0[1],q0[2];
cx q0[0],q0[2];
u3(pi/2,0,pi) q0[1];
cx q0[15],q0[1];
u3(0,0,-pi/4) q0[1];
cx q0[20],q0[1];
u3(0,0,pi/4) q0[1];
cx q0[15],q0[1];
u3(0,0,-pi/4) q0[1];
cx q0[20],q0[1];
u3(0,0,pi/4) q0[15];
u3(0,0,pi/4) q0[1];
u3(pi/2,0,pi) q0[1];
cx q0[20],q0[15];
u3(0,0,pi/4) q0[20];
u3(0,0,-pi/4) q0[15];
cx q0[20],q0[15];
u3(pi/2,0,pi) q0[4];
cx q0[16],q0[4];
u3(0,0,-pi/4) q0[4];
cx q0[20],q0[4];
u3(0,0,pi/4) q0[4];
cx q0[16],q0[4];
u3(0,0,-pi/4) q0[4];
cx q0[20],q0[4];
u3(0,0,pi/4) q0[16];
u3(0,0,pi/4) q0[4];
u3(pi/2,0,pi) q0[4];
cx q0[20],q0[16];
u3(0,0,pi/4) q0[20];
u3(0,0,-pi/4) q0[16];
cx q0[20],q0[16];
u3(pi/2,0,pi) q0[7];
cx q0[17],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[20],q0[7];
u3(0,0,pi/4) q0[7];
cx q0[17],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[20],q0[7];
u3(0,0,pi/4) q0[17];
u3(0,0,pi/4) q0[7];
u3(pi/2,0,pi) q0[7];
cx q0[20],q0[17];
u3(0,0,pi/4) q0[20];
u3(0,0,-pi/4) q0[17];
cx q0[20],q0[17];
u3(pi/2,0,pi) q0[10];
cx q0[18],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[20],q0[10];
u3(0,0,pi/4) q0[10];
cx q0[18],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[20],q0[10];
u3(0,0,pi/4) q0[18];
u3(0,0,pi/4) q0[10];
u3(pi/2,0,pi) q0[10];
cx q0[20],q0[18];
u3(0,0,pi/4) q0[20];
u3(0,0,-pi/4) q0[18];
cx q0[20],q0[18];
u3(pi/2,0,pi) q0[13];
cx q0[19],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[20],q0[13];
u3(0,0,pi/4) q0[13];
cx q0[19],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[20],q0[13];
u3(0,0,pi/4) q0[19];
u3(0,0,pi/4) q0[13];
u3(pi/2,0,pi) q0[13];
cx q0[20],q0[19];
u3(0,0,pi/4) q0[20];
u3(0,0,-pi/4) q0[19];
cx q0[20],q0[19];
u3(pi/2,0,pi) q0[4];
cx q0[15],q0[4];
u3(0,0,-pi/4) q0[4];
cx q0[21],q0[4];
u3(0,0,pi/4) q0[4];
cx q0[15],q0[4];
u3(0,0,-pi/4) q0[4];
cx q0[21],q0[4];
u3(0,0,pi/4) q0[15];
u3(0,0,pi/4) q0[4];
u3(pi/2,0,pi) q0[4];
cx q0[21],q0[15];
u3(0,0,pi/4) q0[21];
u3(0,0,-pi/4) q0[15];
cx q0[21],q0[15];
u3(pi/2,0,pi) q0[7];
cx q0[16],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[21],q0[7];
u3(0,0,pi/4) q0[7];
cx q0[16],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[21],q0[7];
u3(0,0,pi/4) q0[16];
u3(0,0,pi/4) q0[7];
u3(pi/2,0,pi) q0[7];
cx q0[21],q0[16];
u3(0,0,pi/4) q0[21];
u3(0,0,-pi/4) q0[16];
cx q0[21],q0[16];
u3(pi/2,0,pi) q0[10];
cx q0[17],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[21],q0[10];
u3(0,0,pi/4) q0[10];
cx q0[17],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[21],q0[10];
u3(0,0,pi/4) q0[17];
u3(0,0,pi/4) q0[10];
u3(pi/2,0,pi) q0[10];
cx q0[21],q0[17];
u3(0,0,pi/4) q0[21];
u3(0,0,-pi/4) q0[17];
cx q0[21],q0[17];
u3(pi/2,0,pi) q0[13];
cx q0[18],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[21],q0[13];
u3(0,0,pi/4) q0[13];
cx q0[18],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[21],q0[13];
u3(0,0,pi/4) q0[18];
u3(0,0,pi/4) q0[13];
u3(pi/2,0,pi) q0[13];
cx q0[21],q0[18];
u3(0,0,pi/4) q0[21];
u3(0,0,-pi/4) q0[18];
cx q0[21],q0[18];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[1],q0[2];
u3(0,0,pi/4) q0[1];
u3(0,0,-pi/4) q0[2];
cx q0[1],q0[2];
cx q0[1],q0[2];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[0],q0[2];
u3(0,0,pi/4) q0[0];
u3(0,0,-pi/4) q0[2];
cx q0[0],q0[2];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[4],q0[5];
u3(0,0,pi/4) q0[4];
u3(0,0,-pi/4) q0[5];
cx q0[4],q0[5];
cx q0[4],q0[5];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[3],q0[5];
u3(0,0,pi/4) q0[3];
u3(0,0,-pi/4) q0[5];
cx q0[3],q0[5];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[7],q0[8];
u3(0,0,pi/4) q0[7];
u3(0,0,-pi/4) q0[8];
cx q0[7],q0[8];
cx q0[7],q0[8];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[6],q0[8];
u3(0,0,pi/4) q0[6];
u3(0,0,-pi/4) q0[8];
cx q0[6],q0[8];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[10],q0[11];
u3(0,0,pi/4) q0[10];
u3(0,0,-pi/4) q0[11];
cx q0[10],q0[11];
cx q0[10],q0[11];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[9],q0[11];
u3(0,0,pi/4) q0[9];
u3(0,0,-pi/4) q0[11];
cx q0[9],q0[11];
cx q0[13],q0[14];
cx q0[12],q0[14];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[9],q0[11];
u3(0,0,pi/4) q0[9];
u3(0,0,-pi/4) q0[11];
cx q0[9],q0[11];
cx q0[10],q0[11];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[10],q0[11];
u3(0,0,pi/4) q0[10];
u3(0,0,-pi/4) q0[11];
cx q0[10],q0[11];
cx q0[10],q0[11];
cx q0[9],q0[11];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[6],q0[8];
u3(0,0,pi/4) q0[6];
u3(0,0,-pi/4) q0[8];
cx q0[6],q0[8];
cx q0[7],q0[8];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[7],q0[8];
u3(0,0,pi/4) q0[7];
u3(0,0,-pi/4) q0[8];
cx q0[7],q0[8];
cx q0[7],q0[8];
cx q0[6],q0[8];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[3],q0[5];
u3(0,0,pi/4) q0[3];
u3(0,0,-pi/4) q0[5];
cx q0[3],q0[5];
cx q0[4],q0[5];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[4],q0[5];
u3(0,0,pi/4) q0[4];
u3(0,0,-pi/4) q0[5];
cx q0[4],q0[5];
cx q0[4],q0[5];
cx q0[3],q0[5];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[0],q0[2];
u3(0,0,pi/4) q0[0];
u3(0,0,-pi/4) q0[2];
cx q0[0],q0[2];
cx q0[1],q0[2];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[1],q0[2];
u3(0,0,pi/4) q0[1];
u3(0,0,-pi/4) q0[2];
cx q0[1],q0[2];
cx q0[1],q0[2];
cx q0[0],q0[2];
u3(pi/2,0,pi) q0[4];
cx q0[15],q0[4];
u3(0,0,-pi/4) q0[4];
cx q0[21],q0[4];
u3(0,0,pi/4) q0[4];
cx q0[15],q0[4];
u3(0,0,-pi/4) q0[4];
cx q0[21],q0[4];
u3(0,0,pi/4) q0[15];
u3(0,0,pi/4) q0[4];
u3(pi/2,0,pi) q0[4];
cx q0[21],q0[15];
u3(0,0,pi/4) q0[21];
u3(0,0,-pi/4) q0[15];
cx q0[21],q0[15];
u3(pi/2,0,pi) q0[7];
cx q0[16],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[21],q0[7];
u3(0,0,pi/4) q0[7];
cx q0[16],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[21],q0[7];
u3(0,0,pi/4) q0[16];
u3(0,0,pi/4) q0[7];
u3(pi/2,0,pi) q0[7];
cx q0[21],q0[16];
u3(0,0,pi/4) q0[21];
u3(0,0,-pi/4) q0[16];
cx q0[21],q0[16];
u3(pi/2,0,pi) q0[10];
cx q0[17],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[21],q0[10];
u3(0,0,pi/4) q0[10];
cx q0[17],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[21],q0[10];
u3(0,0,pi/4) q0[17];
u3(0,0,pi/4) q0[10];
u3(pi/2,0,pi) q0[10];
cx q0[21],q0[17];
u3(0,0,pi/4) q0[21];
u3(0,0,-pi/4) q0[17];
cx q0[21],q0[17];
u3(pi/2,0,pi) q0[13];
cx q0[18],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[21],q0[13];
u3(0,0,pi/4) q0[13];
cx q0[18],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[21],q0[13];
u3(0,0,pi/4) q0[18];
u3(0,0,pi/4) q0[13];
u3(pi/2,0,pi) q0[13];
cx q0[21],q0[18];
u3(0,0,pi/4) q0[21];
u3(0,0,-pi/4) q0[18];
cx q0[21],q0[18];
u3(pi/2,0,pi) q0[7];
cx q0[15],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[22],q0[7];
u3(0,0,pi/4) q0[7];
cx q0[15],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[22],q0[7];
u3(0,0,pi/4) q0[15];
u3(0,0,pi/4) q0[7];
u3(pi/2,0,pi) q0[7];
cx q0[22],q0[15];
u3(0,0,pi/4) q0[22];
u3(0,0,-pi/4) q0[15];
cx q0[22],q0[15];
u3(pi/2,0,pi) q0[10];
cx q0[16],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[22],q0[10];
u3(0,0,pi/4) q0[10];
cx q0[16],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[22],q0[10];
u3(0,0,pi/4) q0[16];
u3(0,0,pi/4) q0[10];
u3(pi/2,0,pi) q0[10];
cx q0[22],q0[16];
u3(0,0,pi/4) q0[22];
u3(0,0,-pi/4) q0[16];
cx q0[22],q0[16];
u3(pi/2,0,pi) q0[13];
cx q0[17],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[22],q0[13];
u3(0,0,pi/4) q0[13];
cx q0[17],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[22],q0[13];
u3(0,0,pi/4) q0[17];
u3(0,0,pi/4) q0[13];
u3(pi/2,0,pi) q0[13];
cx q0[22],q0[17];
u3(0,0,pi/4) q0[22];
u3(0,0,-pi/4) q0[17];
cx q0[22],q0[17];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[1],q0[2];
u3(0,0,pi/4) q0[1];
u3(0,0,-pi/4) q0[2];
cx q0[1],q0[2];
cx q0[1],q0[2];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[0],q0[2];
u3(0,0,pi/4) q0[0];
u3(0,0,-pi/4) q0[2];
cx q0[0],q0[2];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[4],q0[5];
u3(0,0,pi/4) q0[4];
u3(0,0,-pi/4) q0[5];
cx q0[4],q0[5];
cx q0[4],q0[5];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[3],q0[5];
u3(0,0,pi/4) q0[3];
u3(0,0,-pi/4) q0[5];
cx q0[3],q0[5];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[7],q0[8];
u3(0,0,pi/4) q0[7];
u3(0,0,-pi/4) q0[8];
cx q0[7],q0[8];
cx q0[7],q0[8];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[6],q0[8];
u3(0,0,pi/4) q0[6];
u3(0,0,-pi/4) q0[8];
cx q0[6],q0[8];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[10],q0[11];
u3(0,0,pi/4) q0[10];
u3(0,0,-pi/4) q0[11];
cx q0[10],q0[11];
cx q0[10],q0[11];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[9],q0[11];
u3(0,0,pi/4) q0[9];
u3(0,0,-pi/4) q0[11];
cx q0[9],q0[11];
cx q0[13],q0[14];
cx q0[12],q0[14];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[9],q0[11];
u3(0,0,pi/4) q0[9];
u3(0,0,-pi/4) q0[11];
cx q0[9],q0[11];
cx q0[10],q0[11];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[10],q0[11];
u3(0,0,pi/4) q0[10];
u3(0,0,-pi/4) q0[11];
cx q0[10],q0[11];
cx q0[10],q0[11];
cx q0[9],q0[11];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[6],q0[8];
u3(0,0,pi/4) q0[6];
u3(0,0,-pi/4) q0[8];
cx q0[6],q0[8];
cx q0[7],q0[8];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[7],q0[8];
u3(0,0,pi/4) q0[7];
u3(0,0,-pi/4) q0[8];
cx q0[7],q0[8];
cx q0[7],q0[8];
cx q0[6],q0[8];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[3],q0[5];
u3(0,0,pi/4) q0[3];
u3(0,0,-pi/4) q0[5];
cx q0[3],q0[5];
cx q0[4],q0[5];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[4],q0[5];
u3(0,0,pi/4) q0[4];
u3(0,0,-pi/4) q0[5];
cx q0[4],q0[5];
cx q0[4],q0[5];
cx q0[3],q0[5];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[0],q0[2];
u3(0,0,pi/4) q0[0];
u3(0,0,-pi/4) q0[2];
cx q0[0],q0[2];
cx q0[1],q0[2];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[1],q0[2];
u3(0,0,pi/4) q0[1];
u3(0,0,-pi/4) q0[2];
cx q0[1],q0[2];
cx q0[1],q0[2];
cx q0[0],q0[2];
u3(pi/2,0,pi) q0[7];
cx q0[15],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[22],q0[7];
u3(0,0,pi/4) q0[7];
cx q0[15],q0[7];
u3(0,0,-pi/4) q0[7];
cx q0[22],q0[7];
u3(0,0,pi/4) q0[15];
u3(0,0,pi/4) q0[7];
u3(pi/2,0,pi) q0[7];
cx q0[22],q0[15];
u3(0,0,pi/4) q0[22];
u3(0,0,-pi/4) q0[15];
cx q0[22],q0[15];
u3(pi/2,0,pi) q0[10];
cx q0[16],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[22],q0[10];
u3(0,0,pi/4) q0[10];
cx q0[16],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[22],q0[10];
u3(0,0,pi/4) q0[16];
u3(0,0,pi/4) q0[10];
u3(pi/2,0,pi) q0[10];
cx q0[22],q0[16];
u3(0,0,pi/4) q0[22];
u3(0,0,-pi/4) q0[16];
cx q0[22],q0[16];
u3(pi/2,0,pi) q0[13];
cx q0[17],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[22],q0[13];
u3(0,0,pi/4) q0[13];
cx q0[17],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[22],q0[13];
u3(0,0,pi/4) q0[17];
u3(0,0,pi/4) q0[13];
u3(pi/2,0,pi) q0[13];
cx q0[22],q0[17];
u3(0,0,pi/4) q0[22];
u3(0,0,-pi/4) q0[17];
cx q0[22],q0[17];
u3(pi/2,0,pi) q0[10];
cx q0[15],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[23],q0[10];
u3(0,0,pi/4) q0[10];
cx q0[15],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[23],q0[10];
u3(0,0,pi/4) q0[15];
u3(0,0,pi/4) q0[10];
u3(pi/2,0,pi) q0[10];
cx q0[23],q0[15];
u3(0,0,pi/4) q0[23];
u3(0,0,-pi/4) q0[15];
cx q0[23],q0[15];
u3(pi/2,0,pi) q0[13];
cx q0[16],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[23],q0[13];
u3(0,0,pi/4) q0[13];
cx q0[16],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[23],q0[13];
u3(0,0,pi/4) q0[16];
u3(0,0,pi/4) q0[13];
u3(pi/2,0,pi) q0[13];
cx q0[23],q0[16];
u3(0,0,pi/4) q0[23];
u3(0,0,-pi/4) q0[16];
cx q0[23],q0[16];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[1],q0[2];
u3(0,0,pi/4) q0[1];
u3(0,0,-pi/4) q0[2];
cx q0[1],q0[2];
cx q0[1],q0[2];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[0],q0[2];
u3(0,0,pi/4) q0[0];
u3(0,0,-pi/4) q0[2];
cx q0[0],q0[2];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[4],q0[5];
u3(0,0,pi/4) q0[4];
u3(0,0,-pi/4) q0[5];
cx q0[4],q0[5];
cx q0[4],q0[5];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[3],q0[5];
u3(0,0,pi/4) q0[3];
u3(0,0,-pi/4) q0[5];
cx q0[3],q0[5];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[7],q0[8];
u3(0,0,pi/4) q0[7];
u3(0,0,-pi/4) q0[8];
cx q0[7],q0[8];
cx q0[7],q0[8];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[6],q0[8];
u3(0,0,pi/4) q0[6];
u3(0,0,-pi/4) q0[8];
cx q0[6],q0[8];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[10],q0[11];
u3(0,0,pi/4) q0[10];
u3(0,0,-pi/4) q0[11];
cx q0[10],q0[11];
cx q0[10],q0[11];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[9],q0[11];
u3(0,0,pi/4) q0[9];
u3(0,0,-pi/4) q0[11];
cx q0[9],q0[11];
cx q0[13],q0[14];
cx q0[12],q0[14];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[9],q0[11];
u3(0,0,pi/4) q0[9];
u3(0,0,-pi/4) q0[11];
cx q0[9],q0[11];
cx q0[10],q0[11];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[10],q0[11];
u3(0,0,pi/4) q0[10];
u3(0,0,-pi/4) q0[11];
cx q0[10],q0[11];
cx q0[10],q0[11];
cx q0[9],q0[11];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[6],q0[8];
u3(0,0,pi/4) q0[6];
u3(0,0,-pi/4) q0[8];
cx q0[6],q0[8];
cx q0[7],q0[8];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[7],q0[8];
u3(0,0,pi/4) q0[7];
u3(0,0,-pi/4) q0[8];
cx q0[7],q0[8];
cx q0[7],q0[8];
cx q0[6],q0[8];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[3],q0[5];
u3(0,0,pi/4) q0[3];
u3(0,0,-pi/4) q0[5];
cx q0[3],q0[5];
cx q0[4],q0[5];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[4],q0[5];
u3(0,0,pi/4) q0[4];
u3(0,0,-pi/4) q0[5];
cx q0[4],q0[5];
cx q0[4],q0[5];
cx q0[3],q0[5];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[0],q0[2];
u3(0,0,pi/4) q0[0];
u3(0,0,-pi/4) q0[2];
cx q0[0],q0[2];
cx q0[1],q0[2];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[1],q0[2];
u3(0,0,pi/4) q0[1];
u3(0,0,-pi/4) q0[2];
cx q0[1],q0[2];
cx q0[1],q0[2];
cx q0[0],q0[2];
u3(pi/2,0,pi) q0[10];
cx q0[15],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[23],q0[10];
u3(0,0,pi/4) q0[10];
cx q0[15],q0[10];
u3(0,0,-pi/4) q0[10];
cx q0[23],q0[10];
u3(0,0,pi/4) q0[15];
u3(0,0,pi/4) q0[10];
u3(pi/2,0,pi) q0[10];
cx q0[23],q0[15];
u3(0,0,pi/4) q0[23];
u3(0,0,-pi/4) q0[15];
cx q0[23],q0[15];
u3(pi/2,0,pi) q0[13];
cx q0[16],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[23],q0[13];
u3(0,0,pi/4) q0[13];
cx q0[16],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[23],q0[13];
u3(0,0,pi/4) q0[16];
u3(0,0,pi/4) q0[13];
u3(pi/2,0,pi) q0[13];
cx q0[23],q0[16];
u3(0,0,pi/4) q0[23];
u3(0,0,-pi/4) q0[16];
cx q0[23],q0[16];
u3(pi/2,0,pi) q0[13];
cx q0[15],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[24],q0[13];
u3(0,0,pi/4) q0[13];
cx q0[15],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[24],q0[13];
u3(0,0,pi/4) q0[15];
u3(0,0,pi/4) q0[13];
u3(pi/2,0,pi) q0[13];
cx q0[24],q0[15];
u3(0,0,pi/4) q0[24];
u3(0,0,-pi/4) q0[15];
cx q0[24],q0[15];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[1],q0[2];
u3(0,0,pi/4) q0[1];
u3(0,0,-pi/4) q0[2];
cx q0[1],q0[2];
cx q0[1],q0[2];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[0],q0[2];
u3(0,0,pi/4) q0[0];
u3(0,0,-pi/4) q0[2];
cx q0[0],q0[2];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[4],q0[5];
u3(0,0,pi/4) q0[4];
u3(0,0,-pi/4) q0[5];
cx q0[4],q0[5];
cx q0[4],q0[5];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[3],q0[5];
u3(0,0,pi/4) q0[3];
u3(0,0,-pi/4) q0[5];
cx q0[3],q0[5];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[7],q0[8];
u3(0,0,pi/4) q0[7];
u3(0,0,-pi/4) q0[8];
cx q0[7],q0[8];
cx q0[7],q0[8];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[6],q0[8];
u3(0,0,pi/4) q0[6];
u3(0,0,-pi/4) q0[8];
cx q0[6],q0[8];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[10],q0[11];
u3(0,0,pi/4) q0[10];
u3(0,0,-pi/4) q0[11];
cx q0[10],q0[11];
cx q0[10],q0[11];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[9],q0[11];
u3(0,0,pi/4) q0[9];
u3(0,0,-pi/4) q0[11];
cx q0[9],q0[11];
cx q0[13],q0[14];
cx q0[12],q0[14];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[9],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[9],q0[11];
u3(0,0,pi/4) q0[9];
u3(0,0,-pi/4) q0[11];
cx q0[9],q0[11];
cx q0[10],q0[11];
u3(pi/2,0,pi) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[12];
cx q0[11],q0[12];
u3(0,0,-pi/4) q0[12];
cx q0[10],q0[12];
u3(0,0,pi/4) q0[11];
u3(0,0,pi/4) q0[12];
u3(pi/2,0,pi) q0[12];
cx q0[10],q0[11];
u3(0,0,pi/4) q0[10];
u3(0,0,-pi/4) q0[11];
cx q0[10],q0[11];
cx q0[10],q0[11];
cx q0[9],q0[11];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[6],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[6],q0[8];
u3(0,0,pi/4) q0[6];
u3(0,0,-pi/4) q0[8];
cx q0[6],q0[8];
cx q0[7],q0[8];
u3(pi/2,0,pi) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[9];
cx q0[8],q0[9];
u3(0,0,-pi/4) q0[9];
cx q0[7],q0[9];
u3(0,0,pi/4) q0[8];
u3(0,0,pi/4) q0[9];
u3(pi/2,0,pi) q0[9];
cx q0[7],q0[8];
u3(0,0,pi/4) q0[7];
u3(0,0,-pi/4) q0[8];
cx q0[7],q0[8];
cx q0[7],q0[8];
cx q0[6],q0[8];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[3],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[3],q0[5];
u3(0,0,pi/4) q0[3];
u3(0,0,-pi/4) q0[5];
cx q0[3],q0[5];
cx q0[4],q0[5];
u3(pi/2,0,pi) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[6];
cx q0[5],q0[6];
u3(0,0,-pi/4) q0[6];
cx q0[4],q0[6];
u3(0,0,pi/4) q0[5];
u3(0,0,pi/4) q0[6];
u3(pi/2,0,pi) q0[6];
cx q0[4],q0[5];
u3(0,0,pi/4) q0[4];
u3(0,0,-pi/4) q0[5];
cx q0[4],q0[5];
cx q0[4],q0[5];
cx q0[3],q0[5];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[0],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[0],q0[2];
u3(0,0,pi/4) q0[0];
u3(0,0,-pi/4) q0[2];
cx q0[0],q0[2];
cx q0[1],q0[2];
u3(pi/2,0,pi) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[3];
cx q0[2],q0[3];
u3(0,0,-pi/4) q0[3];
cx q0[1],q0[3];
u3(0,0,pi/4) q0[2];
u3(0,0,pi/4) q0[3];
u3(pi/2,0,pi) q0[3];
cx q0[1],q0[2];
u3(0,0,pi/4) q0[1];
u3(0,0,-pi/4) q0[2];
cx q0[1],q0[2];
cx q0[1],q0[2];
cx q0[0],q0[2];
u3(pi/2,0,pi) q0[13];
cx q0[15],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[24],q0[13];
u3(0,0,pi/4) q0[13];
cx q0[15],q0[13];
u3(0,0,-pi/4) q0[13];
cx q0[24],q0[13];
u3(0,0,pi/4) q0[15];
u3(0,0,pi/4) q0[13];
u3(pi/2,0,pi) q0[13];
cx q0[24],q0[15];
u3(0,0,pi/4) q0[24];
u3(0,0,-pi/4) q0[15];
cx q0[24],q0[15];
