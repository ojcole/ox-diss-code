OPENQASM 2.0;
include "qelib1.inc";
qreg q1[2];
u3(1.57058537006378,-3.16672348976135,-1.58730872499291e-05) q1[0];
u3(0.786450207233429,1.49974524974823,0.0502195656299591) q1[1];
cx q1[0],q1[1];
u3(0.0502248033881187,0,pi) q1[0];
u3(1.64184737205505,-pi/2,pi) q1[1];
cx q1[0],q1[1];
u3(1.49567904372816e-05,pi/2,pi) q1[0];
u3(pi/2,pi/2,pi) q1[1];
cx q1[0],q1[1];
u3(1.57058537006378,-3.14160847663879,-0.0251309089362621) q1[0];
u3(2.35472130775452,3.0913941860199,-0.0710212215781212) q1[1];