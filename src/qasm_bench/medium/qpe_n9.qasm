OPENQASM 2.0;
include "qelib1.inc";
qreg q[9];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[1];
u3(pi/2,0,pi) q[2];
u3(pi/2,0,pi) q[3];
u3(pi/2,0,pi) q[4];
u3(pi/2,0,pi) q[5];
u3(pi,0,pi) q[6];
u3(pi,0,pi) q[7];
u3(pi,0,pi) q[8];
u3(pi/2,0,pi) q[7];
cx q[6],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[5],q[7];
u3(0,0,0.785398185253143) q[7];
cx q[6],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[5],q[7];
u3(0,0,0.785398185253143) q[6];
u3(0,0,0.785398185253143) q[7];
u3(pi/2,0,pi) q[7];
cx q[5],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,-0.785398185253143) q[6];
cx q[5],q[6];
u3(pi/2,0,pi) q[8];
cx q[7],q[8];
u3(pi/2,0,pi) q[8];
u3(pi/2,0,pi) q[7];
cx q[6],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[5],q[7];
u3(0,0,0.785398185253143) q[7];
cx q[6],q[7];
u3(0,0,-0.785398185253143) q[7];
cx q[5],q[7];
u3(0,0,0.785398185253143) q[6];
u3(0,0,0.785398185253143) q[7];
u3(pi/2,0,pi) q[7];
cx q[5],q[6];
u3(0,0,0.785398185253143) q[5];
u3(0,0,-0.785398185253143) q[6];
cx q[5],q[6];
u3(0,0,-0.0490873865783215) q[5];
cx q[5],q[0];
u3(0,0,0.0490873865783215) q[0];
cx q[5],q[0];
u3(0,0,-0.0490873865783215) q[0];
u3(0,0,-0.0981747731566429) q[5];
cx q[5],q[1];
u3(0,0,0.0981747731566429) q[1];
cx q[5],q[1];
u3(0,0,-0.0981747731566429) q[1];
u3(0,0,-0.196349546313286) q[5];
cx q[5],q[2];
u3(0,0,0.196349546313286) q[2];
cx q[5],q[2];
u3(0,0,-0.196349546313286) q[2];
u3(0,0,-0.392699092626572) q[5];
cx q[5],q[3];
u3(0,0,0.392699092626572) q[3];
cx q[5],q[3];
u3(0,0,-0.392699092626572) q[3];
u3(0,0,-0.785398185253143) q[5];
cx q[5],q[4];
u3(0,0,0.785398185253143) q[4];
cx q[5],q[4];
u3(0,0,-0.785398185253143) q[4];
u3(0,0,-0.0981747731566429) q[4];
cx q[4],q[0];
u3(0,0,0.0981747731566429) q[0];
cx q[4],q[0];
u3(0,0,-0.0981747731566429) q[0];
u3(0,0,-0.196349546313286) q[4];
cx q[4],q[1];
u3(0,0,0.196349546313286) q[1];
cx q[4],q[1];
u3(0,0,-0.196349546313286) q[1];
u3(0,0,-0.392699092626572) q[4];
cx q[4],q[2];
u3(0,0,0.392699092626572) q[2];
cx q[4],q[2];
u3(0,0,-0.392699092626572) q[2];
u3(0,0,-0.785398185253143) q[4];
cx q[4],q[3];
u3(0,0,0.785398185253143) q[3];
cx q[4],q[3];
u3(0,0,-0.785398185253143) q[3];
u3(0,0,-0.196349546313286) q[3];
cx q[3],q[0];
u3(0,0,0.196349546313286) q[0];
cx q[3],q[0];
u3(0,0,-0.196349546313286) q[0];
u3(0,0,-0.392699092626572) q[3];
cx q[3],q[1];
u3(0,0,0.392699092626572) q[1];
cx q[3],q[1];
u3(0,0,-0.392699092626572) q[1];
u3(0,0,-0.785398185253143) q[3];
cx q[3],q[2];
u3(0,0,0.785398185253143) q[2];
cx q[3],q[2];
u3(0,0,-0.785398185253143) q[2];
u3(0,0,-0.392699092626572) q[2];
cx q[2],q[0];
u3(0,0,0.392699092626572) q[0];
cx q[2],q[0];
u3(0,0,-0.392699092626572) q[0];
u3(0,0,-0.785398185253143) q[2];
cx q[2],q[1];
u3(0,0,0.785398185253143) q[1];
cx q[2],q[1];
u3(0,0,-0.785398185253143) q[1];
u3(0,0,-0.785398185253143) q[1];
cx q[1],q[0];
u3(0,0,0.785398185253143) q[0];
cx q[1],q[0];
u3(0,0,-0.785398185253143) q[0];
u3(pi/2,0,pi) q[0];
u3(pi/2,0,pi) q[1];
u3(pi/2,0,pi) q[2];
u3(pi/2,0,pi) q[3];
u3(pi/2,0,pi) q[4];
u3(pi/2,0,pi) q[5];
