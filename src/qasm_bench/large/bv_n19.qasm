OPENQASM 2.0;
include "qelib1.inc";
qreg qr[19];
u3(pi/2,0,pi) qr[0];
u3(pi/2,0,pi) qr[1];
u3(pi/2,0,pi) qr[2];
u3(pi/2,0,pi) qr[3];
u3(pi/2,0,pi) qr[4];
u3(pi/2,0,pi) qr[5];
u3(pi/2,0,pi) qr[6];
u3(pi/2,0,pi) qr[7];
u3(pi/2,0,pi) qr[8];
u3(pi/2,0,pi) qr[9];
u3(pi/2,0,pi) qr[10];
u3(pi/2,0,pi) qr[11];
u3(pi/2,0,pi) qr[12];
u3(pi/2,0,pi) qr[13];
u3(pi/2,0,pi) qr[14];
u3(pi/2,0,pi) qr[15];
u3(pi/2,0,pi) qr[16];
u3(pi/2,0,pi) qr[17];
u3(pi,0,pi) qr[18];
u3(pi/2,0,pi) qr[18];
cx qr[0],qr[18];
cx qr[1],qr[18];
cx qr[2],qr[18];
cx qr[3],qr[18];
cx qr[4],qr[18];
cx qr[5],qr[18];
cx qr[6],qr[18];
cx qr[7],qr[18];
cx qr[8],qr[18];
cx qr[9],qr[18];
cx qr[10],qr[18];
cx qr[11],qr[18];
cx qr[12],qr[18];
cx qr[13],qr[18];
cx qr[14],qr[18];
cx qr[15],qr[18];
cx qr[16],qr[18];
cx qr[17],qr[18];
u3(pi/2,0,pi) qr[0];
u3(pi/2,0,pi) qr[1];
u3(pi/2,0,pi) qr[2];
u3(pi/2,0,pi) qr[3];
u3(pi/2,0,pi) qr[4];
u3(pi/2,0,pi) qr[5];
u3(pi/2,0,pi) qr[6];
u3(pi/2,0,pi) qr[7];
u3(pi/2,0,pi) qr[8];
u3(pi/2,0,pi) qr[9];
u3(pi/2,0,pi) qr[10];
u3(pi/2,0,pi) qr[11];
u3(pi/2,0,pi) qr[12];
u3(pi/2,0,pi) qr[13];
u3(pi/2,0,pi) qr[14];
u3(pi/2,0,pi) qr[15];
u3(pi/2,0,pi) qr[16];
u3(pi/2,0,pi) qr[17];
