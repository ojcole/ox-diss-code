OPENQASM 2.0;
include "qelib1.inc";
qreg q[2];
u3(pi/2,0,pi) q[0];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[0];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-pi/2) q[0];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[0];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-pi/4) q[0];
u3(0,0,-pi/2) q[0];
u3(0,0,-2.35619449615479) q[0];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[0];
u3(0,0,-1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,1.17809724807739) q[1];
cx q[0],q[1];
u3(0,0,-0.392699092626572) q[0];
u3(0,0,-pi/4) q[0];
u3(0,0,-1.17809724807739) q[0];
u3(0,0,-pi/2) q[0];
u3(0,0,-1.96349537372589) q[0];
u3(0,0,-2.35619449615479) q[0];
u3(0,0,-2.74889349937439) q[0];
u3(pi/2,0,pi) q[0];
