OPENQASM 2.0;
include "qelib1.inc";
qreg q[4];
u3(0,0,pi) q[0];
u3(0,0,pi) q[1];
u3(0,0,pi) q[2];
u3(0,0,pi) q[3];
u3(pi,0,pi) q[1];
u3(0,0,-0.392699092626572) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.392699092626572) q[1];
u3(pi,0,pi) q[2];
u3(0,0,0.392699092626572) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.392699092626572) q[2];
cx q[1],q[2];
u3(pi/2,0,pi) q[1];
cx q[2],q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.785398185253143) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.785398185253143) q[1];
cx q[2],q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.785398185253143) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.785398185253143) q[1];
u3(pi/2,0,pi) q[1];
cx q[1],q[2];
u3(pi,0,pi) q[1];
u3(0,0,0.392699092626572) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.392699092626572) q[1];
u3(pi,0,pi) q[2];
u3(0,0,-0.392699092626572) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.392699092626572) q[2];
u3(pi,0,pi) q[0];
u3(0,0,-0.392699092626572) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.392699092626572) q[0];
u3(pi,0,pi) q[1];
u3(0,0,0.392699092626572) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.392699092626572) q[1];
cx q[0],q[1];
u3(pi/2,0,pi) q[0];
cx q[1],q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.0638576969504356) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.0638576969504356) q[0];
cx q[1],q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.0638576969504356) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.0638576969504356) q[0];
u3(pi/2,0,pi) q[0];
cx q[0],q[1];
u3(pi,0,pi) q[0];
u3(0,0,0.392699092626572) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.392699092626572) q[0];
u3(pi,0,pi) q[1];
u3(0,0,-0.392699092626572) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.392699092626572) q[1];
u3(pi,0,pi) q[2];
u3(0,0,-0.392699092626572) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.392699092626572) q[2];
u3(pi,0,pi) q[3];
u3(0,0,0.392699092626572) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-0.392699092626572) q[3];
cx q[2],q[3];
u3(pi/2,0,pi) q[2];
cx q[3],q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.0638576969504356) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.0638576969504356) q[2];
cx q[3],q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.0638576969504356) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.0638576969504356) q[2];
u3(pi/2,0,pi) q[2];
cx q[2],q[3];
u3(pi,0,pi) q[2];
u3(0,0,0.392699092626572) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.392699092626572) q[2];
u3(pi,0,pi) q[3];
u3(0,0,-0.392699092626572) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.392699092626572) q[3];
u3(pi,0,pi) q[0];
u3(0,0,-0.176428288221359) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.176428288221359) q[0];
u3(pi,0,pi) q[1];
u3(0,0,-0.392699092626572) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.392699092626572) q[1];
u3(pi,0,pi) q[2];
u3(0,0,0.392699092626572) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.392699092626572) q[2];
cx q[1],q[2];
u3(pi/2,0,pi) q[1];
cx q[2],q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.785398185253143) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.785398185253143) q[1];
cx q[2],q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.785398185253143) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.785398185253143) q[1];
u3(pi/2,0,pi) q[1];
cx q[1],q[2];
u3(pi,0,pi) q[1];
u3(0,0,0.392699092626572) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.392699092626572) q[1];
u3(pi,0,pi) q[2];
u3(0,0,-0.392699092626572) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.392699092626572) q[2];
u3(pi,0,pi) q[1];
u3(0,0,-0.176428288221359) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.176428288221359) q[1];
u3(pi,0,pi) q[3];
u3(0,0,-0.0887358486652374) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.0887358486652374) q[3];
u3(pi,0,pi) q[2];
u3(0,0,-0.0887358486652374) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.0887358486652374) q[2];
u3(pi,0,pi) q[1];
u3(0,0,-0.392699092626572) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.392699092626572) q[1];
u3(pi,0,pi) q[2];
u3(0,0,0.392699092626572) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.392699092626572) q[2];
cx q[1],q[2];
u3(pi/2,0,pi) q[1];
cx q[2],q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.785398185253143) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.785398185253143) q[1];
cx q[2],q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.785398185253143) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.785398185253143) q[1];
u3(pi/2,0,pi) q[1];
cx q[1],q[2];
u3(pi,0,pi) q[1];
u3(0,0,0.392699092626572) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.392699092626572) q[1];
u3(pi,0,pi) q[2];
u3(0,0,-0.392699092626572) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.392699092626572) q[2];
u3(pi,0,pi) q[0];
u3(0,0,-0.392699092626572) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.392699092626572) q[0];
u3(pi,0,pi) q[1];
u3(0,0,0.392699092626572) q[1];
u3(pi,0,pi) q[1];
u3(0,0,-0.392699092626572) q[1];
cx q[0],q[1];
u3(pi/2,0,pi) q[0];
cx q[1],q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.040078479796648) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.040078479796648) q[0];
cx q[1],q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.040078479796648) q[0];
u3(pi,0,pi) q[0];
u3(0,0,0.040078479796648) q[0];
u3(pi/2,0,pi) q[0];
cx q[0],q[1];
u3(pi,0,pi) q[0];
u3(0,0,0.392699092626572) q[0];
u3(pi,0,pi) q[0];
u3(0,0,-0.392699092626572) q[0];
u3(pi,0,pi) q[1];
u3(0,0,-0.392699092626572) q[1];
u3(pi,0,pi) q[1];
u3(0,0,0.392699092626572) q[1];
u3(pi,0,pi) q[2];
u3(0,0,-0.392699092626572) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.392699092626572) q[2];
u3(pi,0,pi) q[3];
u3(0,0,0.392699092626572) q[3];
u3(pi,0,pi) q[3];
u3(0,0,-0.392699092626572) q[3];
cx q[2],q[3];
u3(pi/2,0,pi) q[2];
cx q[3],q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.040078479796648) q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.040078479796648) q[2];
cx q[3],q[2];
u3(pi,0,pi) q[2];
u3(0,0,0.040078479796648) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.040078479796648) q[2];
u3(pi/2,0,pi) q[2];
cx q[2],q[3];
u3(pi,0,pi) q[2];
u3(0,0,0.392699092626572) q[2];
u3(pi,0,pi) q[2];
u3(0,0,-0.392699092626572) q[2];
u3(pi,0,pi) q[3];
u3(0,0,-0.392699092626572) q[3];
u3(pi,0,pi) q[3];
u3(0,0,0.392699092626572) q[3];
cx q[3],q[2];
cx q[2],q[3];
cx q[3],q[2];
cx q[1],q[0];
cx q[0],q[1];
cx q[1],q[0];
cx q[2],q[1];
cx q[1],q[2];
cx q[2],q[1];
cx q[3],q[2];
cx q[2],q[3];
cx q[3],q[2];
cx q[1],q[0];
cx q[0],q[1];
cx q[1],q[0];
cx q[2],q[1];
cx q[1],q[2];
cx q[2],q[1];
