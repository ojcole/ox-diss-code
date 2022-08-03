OPENQASM 2.0;
include "qelib1.inc";
qreg q[15];
u3(pi/2,0,pi) q[0];
u3(0,0,pi/4) q[1];
cx q[1],q[0];
u3(0,0,-pi/4) q[0];
cx q[1],q[0];
u3(0,0,pi/4) q[0];
u3(pi/2,0,pi) q[1];
u3(0,0,pi/8) q[2];
cx q[2],q[0];
u3(0,0,-pi/8) q[0];
cx q[2],q[0];
u3(0,0,pi/8) q[0];
u3(0,0,pi/4) q[2];
cx q[2],q[1];
u3(0,0,-pi/4) q[1];
cx q[2],q[1];
u3(0,0,pi/4) q[1];
u3(pi/2,0,pi) q[2];
u3(0,0,0.196349546313286) q[3];
cx q[3],q[0];
u3(0,0,-0.196349546313286) q[0];
cx q[3],q[0];
u3(0,0,0.196349546313286) q[0];
u3(0,0,pi/8) q[3];
cx q[3],q[1];
u3(0,0,-pi/8) q[1];
cx q[3],q[1];
u3(0,0,pi/8) q[1];
u3(0,0,pi/4) q[3];
cx q[3],q[2];
u3(0,0,-pi/4) q[2];
cx q[3],q[2];
u3(0,0,pi/4) q[2];
u3(pi/2,0,pi) q[3];
u3(0,0,0.0981747731566429) q[4];
cx q[4],q[0];
u3(0,0,-0.0981747731566429) q[0];
cx q[4],q[0];
u3(0,0,0.0981747731566429) q[0];
u3(0,0,0.196349546313286) q[4];
cx q[4],q[1];
u3(0,0,-0.196349546313286) q[1];
cx q[4],q[1];
u3(0,0,0.196349546313286) q[1];
u3(0,0,pi/8) q[4];
cx q[4],q[2];
u3(0,0,-pi/8) q[2];
cx q[4],q[2];
u3(0,0,pi/8) q[2];
u3(0,0,pi/4) q[4];
cx q[4],q[3];
u3(0,0,-pi/4) q[3];
cx q[4],q[3];
u3(0,0,pi/4) q[3];
u3(pi/2,0,pi) q[4];
u3(0,0,0.0490873865783215) q[5];
cx q[5],q[0];
u3(0,0,-0.0490873865783215) q[0];
cx q[5],q[0];
u3(0,0,0.0490873865783215) q[0];
u3(0,0,0.0981747731566429) q[5];
cx q[5],q[1];
u3(0,0,-0.0981747731566429) q[1];
cx q[5],q[1];
u3(0,0,0.0981747731566429) q[1];
u3(0,0,0.196349546313286) q[5];
cx q[5],q[2];
u3(0,0,-0.196349546313286) q[2];
cx q[5],q[2];
u3(0,0,0.196349546313286) q[2];
u3(0,0,pi/8) q[5];
cx q[5],q[3];
u3(0,0,-pi/8) q[3];
cx q[5],q[3];
u3(0,0,pi/8) q[3];
u3(0,0,pi/4) q[5];
cx q[5],q[4];
u3(0,0,-pi/4) q[4];
cx q[5],q[4];
u3(0,0,pi/4) q[4];
u3(pi/2,0,pi) q[5];
u3(0,0,0.0245436932891607) q[6];
cx q[6],q[0];
u3(0,0,-0.0245436932891607) q[0];
cx q[6],q[0];
u3(0,0,0.0245436932891607) q[0];
u3(0,0,0.0490873865783215) q[6];
cx q[6],q[1];
u3(0,0,-0.0490873865783215) q[1];
cx q[6],q[1];
u3(0,0,0.0490873865783215) q[1];
u3(0,0,0.0981747731566429) q[6];
cx q[6],q[2];
u3(0,0,-0.0981747731566429) q[2];
cx q[6],q[2];
u3(0,0,0.0981747731566429) q[2];
u3(0,0,0.196349546313286) q[6];
cx q[6],q[3];
u3(0,0,-0.196349546313286) q[3];
cx q[6],q[3];
u3(0,0,0.196349546313286) q[3];
u3(0,0,pi/8) q[6];
cx q[6],q[4];
u3(0,0,-pi/8) q[4];
cx q[6],q[4];
u3(0,0,pi/8) q[4];
u3(0,0,pi/4) q[6];
cx q[6],q[5];
u3(0,0,-pi/4) q[5];
cx q[6],q[5];
u3(0,0,pi/4) q[5];
u3(pi/2,0,pi) q[6];
u3(0,0,0.0122718466445804) q[7];
cx q[7],q[0];
u3(0,0,-0.0122718466445804) q[0];
cx q[7],q[0];
u3(0,0,0.0122718466445804) q[0];
u3(0,0,0.0245436932891607) q[7];
cx q[7],q[1];
u3(0,0,-0.0245436932891607) q[1];
cx q[7],q[1];
u3(0,0,0.0245436932891607) q[1];
u3(0,0,0.0490873865783215) q[7];
cx q[7],q[2];
u3(0,0,-0.0490873865783215) q[2];
cx q[7],q[2];
u3(0,0,0.0490873865783215) q[2];
u3(0,0,0.0981747731566429) q[7];
cx q[7],q[3];
u3(0,0,-0.0981747731566429) q[3];
cx q[7],q[3];
u3(0,0,0.0981747731566429) q[3];
u3(0,0,0.196349546313286) q[7];
cx q[7],q[4];
u3(0,0,-0.196349546313286) q[4];
cx q[7],q[4];
u3(0,0,0.196349546313286) q[4];
u3(0,0,pi/8) q[7];
cx q[7],q[5];
u3(0,0,-pi/8) q[5];
cx q[7],q[5];
u3(0,0,pi/8) q[5];
u3(0,0,pi/4) q[7];
cx q[7],q[6];
u3(0,0,-pi/4) q[6];
cx q[7],q[6];
u3(0,0,pi/4) q[6];
u3(pi/2,0,pi) q[7];
u3(0,0,0.00613592332229018) q[8];
cx q[8],q[0];
u3(0,0,-0.00613592332229018) q[0];
cx q[8],q[0];
u3(0,0,0.00613592332229018) q[0];
u3(0,0,0.0122718466445804) q[8];
cx q[8],q[1];
u3(0,0,-0.0122718466445804) q[1];
cx q[8],q[1];
u3(0,0,0.0122718466445804) q[1];
u3(0,0,0.0245436932891607) q[8];
cx q[8],q[2];
u3(0,0,-0.0245436932891607) q[2];
cx q[8],q[2];
u3(0,0,0.0245436932891607) q[2];
u3(0,0,0.0490873865783215) q[8];
cx q[8],q[3];
u3(0,0,-0.0490873865783215) q[3];
cx q[8],q[3];
u3(0,0,0.0490873865783215) q[3];
u3(0,0,0.0981747731566429) q[8];
cx q[8],q[4];
u3(0,0,-0.0981747731566429) q[4];
cx q[8],q[4];
u3(0,0,0.0981747731566429) q[4];
u3(0,0,0.196349546313286) q[8];
cx q[8],q[5];
u3(0,0,-0.196349546313286) q[5];
cx q[8],q[5];
u3(0,0,0.196349546313286) q[5];
u3(0,0,pi/8) q[8];
cx q[8],q[6];
u3(0,0,-pi/8) q[6];
cx q[8],q[6];
u3(0,0,pi/8) q[6];
u3(0,0,pi/4) q[8];
cx q[8],q[7];
u3(0,0,-pi/4) q[7];
cx q[8],q[7];
u3(0,0,pi/4) q[7];
u3(pi/2,0,pi) q[8];
u3(0,0,0.00306796166114509) q[9];
cx q[9],q[0];
u3(0,0,-0.00306796166114509) q[0];
cx q[9],q[0];
u3(0,0,0.00306796166114509) q[0];
u3(0,0,0.00613592332229018) q[9];
cx q[9],q[1];
u3(0,0,-0.00613592332229018) q[1];
cx q[9],q[1];
u3(0,0,0.00613592332229018) q[1];
u3(0,0,0.0122718466445804) q[9];
cx q[9],q[2];
u3(0,0,-0.0122718466445804) q[2];
cx q[9],q[2];
u3(0,0,0.0122718466445804) q[2];
u3(0,0,0.0245436932891607) q[9];
cx q[9],q[3];
u3(0,0,-0.0245436932891607) q[3];
cx q[9],q[3];
u3(0,0,0.0245436932891607) q[3];
u3(0,0,0.0490873865783215) q[9];
cx q[9],q[4];
u3(0,0,-0.0490873865783215) q[4];
cx q[9],q[4];
u3(0,0,0.0490873865783215) q[4];
u3(0,0,0.0981747731566429) q[9];
cx q[9],q[5];
u3(0,0,-0.0981747731566429) q[5];
cx q[9],q[5];
u3(0,0,0.0981747731566429) q[5];
u3(0,0,0.196349546313286) q[9];
cx q[9],q[6];
u3(0,0,-0.196349546313286) q[6];
cx q[9],q[6];
u3(0,0,0.196349546313286) q[6];
u3(0,0,pi/8) q[9];
cx q[9],q[7];
u3(0,0,-pi/8) q[7];
cx q[9],q[7];
u3(0,0,pi/8) q[7];
u3(0,0,pi/4) q[9];
cx q[9],q[8];
u3(0,0,-pi/4) q[8];
cx q[9],q[8];
u3(0,0,pi/4) q[8];
u3(pi/2,0,pi) q[9];
u3(0,0,0.00153398083057255) q[10];
cx q[10],q[0];
u3(0,0,-0.00153398083057255) q[0];
cx q[10],q[0];
u3(0,0,0.00153398083057255) q[0];
u3(0,0,0.00306796166114509) q[10];
cx q[10],q[1];
u3(0,0,-0.00306796166114509) q[1];
cx q[10],q[1];
u3(0,0,0.00306796166114509) q[1];
u3(0,0,0.00613592332229018) q[10];
cx q[10],q[2];
u3(0,0,-0.00613592332229018) q[2];
cx q[10],q[2];
u3(0,0,0.00613592332229018) q[2];
u3(0,0,0.0122718466445804) q[10];
cx q[10],q[3];
u3(0,0,-0.0122718466445804) q[3];
cx q[10],q[3];
u3(0,0,0.0122718466445804) q[3];
u3(0,0,0.0245436932891607) q[10];
cx q[10],q[4];
u3(0,0,-0.0245436932891607) q[4];
cx q[10],q[4];
u3(0,0,0.0245436932891607) q[4];
u3(0,0,0.0490873865783215) q[10];
cx q[10],q[5];
u3(0,0,-0.0490873865783215) q[5];
cx q[10],q[5];
u3(0,0,0.0490873865783215) q[5];
u3(0,0,0.0981747731566429) q[10];
cx q[10],q[6];
u3(0,0,-0.0981747731566429) q[6];
cx q[10],q[6];
u3(0,0,0.0981747731566429) q[6];
u3(0,0,0.196349546313286) q[10];
cx q[10],q[7];
u3(0,0,-0.196349546313286) q[7];
cx q[10],q[7];
u3(0,0,0.196349546313286) q[7];
u3(0,0,pi/8) q[10];
cx q[10],q[8];
u3(0,0,-pi/8) q[8];
cx q[10],q[8];
u3(0,0,pi/8) q[8];
u3(0,0,pi/4) q[10];
cx q[10],q[9];
u3(0,0,-pi/4) q[9];
cx q[10],q[9];
u3(0,0,pi/4) q[9];
u3(pi/2,0,pi) q[10];
u3(0,0,0.000766990415286273) q[11];
cx q[11],q[0];
u3(0,0,-0.000766990415286273) q[0];
cx q[11],q[0];
u3(0,0,0.000766990415286273) q[0];
u3(0,0,0.00153398083057255) q[11];
cx q[11],q[1];
u3(0,0,-0.00153398083057255) q[1];
cx q[11],q[1];
u3(0,0,0.00153398083057255) q[1];
u3(0,0,0.00306796166114509) q[11];
cx q[11],q[2];
u3(0,0,-0.00306796166114509) q[2];
cx q[11],q[2];
u3(0,0,0.00306796166114509) q[2];
u3(0,0,0.00613592332229018) q[11];
cx q[11],q[3];
u3(0,0,-0.00613592332229018) q[3];
cx q[11],q[3];
u3(0,0,0.00613592332229018) q[3];
u3(0,0,0.0122718466445804) q[11];
cx q[11],q[4];
u3(0,0,-0.0122718466445804) q[4];
cx q[11],q[4];
u3(0,0,0.0122718466445804) q[4];
u3(0,0,0.0245436932891607) q[11];
cx q[11],q[5];
u3(0,0,-0.0245436932891607) q[5];
cx q[11],q[5];
u3(0,0,0.0245436932891607) q[5];
u3(0,0,0.0490873865783215) q[11];
cx q[11],q[6];
u3(0,0,-0.0490873865783215) q[6];
cx q[11],q[6];
u3(0,0,0.0490873865783215) q[6];
u3(0,0,0.0981747731566429) q[11];
cx q[11],q[7];
u3(0,0,-0.0981747731566429) q[7];
cx q[11],q[7];
u3(0,0,0.0981747731566429) q[7];
u3(0,0,0.196349546313286) q[11];
cx q[11],q[8];
u3(0,0,-0.196349546313286) q[8];
cx q[11],q[8];
u3(0,0,0.196349546313286) q[8];
u3(0,0,pi/8) q[11];
cx q[11],q[9];
u3(0,0,-pi/8) q[9];
cx q[11],q[9];
u3(0,0,pi/8) q[9];
u3(0,0,pi/4) q[11];
cx q[11],q[10];
u3(0,0,-pi/4) q[10];
cx q[11],q[10];
u3(0,0,pi/4) q[10];
u3(pi/2,0,pi) q[11];
u3(0,0,0.000383495207643136) q[12];
cx q[12],q[0];
u3(0,0,-0.000383495207643136) q[0];
cx q[12],q[0];
u3(0,0,0.000383495207643136) q[0];
u3(0,0,0.000766990415286273) q[12];
cx q[12],q[1];
u3(0,0,-0.000766990415286273) q[1];
cx q[12],q[1];
u3(0,0,0.000766990415286273) q[1];
u3(0,0,0.00153398083057255) q[12];
cx q[12],q[2];
u3(0,0,-0.00153398083057255) q[2];
cx q[12],q[2];
u3(0,0,0.00153398083057255) q[2];
u3(0,0,0.00306796166114509) q[12];
cx q[12],q[3];
u3(0,0,-0.00306796166114509) q[3];
cx q[12],q[3];
u3(0,0,0.00306796166114509) q[3];
u3(0,0,0.00613592332229018) q[12];
cx q[12],q[4];
u3(0,0,-0.00613592332229018) q[4];
cx q[12],q[4];
u3(0,0,0.00613592332229018) q[4];
u3(0,0,0.0122718466445804) q[12];
cx q[12],q[5];
u3(0,0,-0.0122718466445804) q[5];
cx q[12],q[5];
u3(0,0,0.0122718466445804) q[5];
u3(0,0,0.0245436932891607) q[12];
cx q[12],q[6];
u3(0,0,-0.0245436932891607) q[6];
cx q[12],q[6];
u3(0,0,0.0245436932891607) q[6];
u3(0,0,0.0490873865783215) q[12];
cx q[12],q[7];
u3(0,0,-0.0490873865783215) q[7];
cx q[12],q[7];
u3(0,0,0.0490873865783215) q[7];
u3(0,0,0.0981747731566429) q[12];
cx q[12],q[8];
u3(0,0,-0.0981747731566429) q[8];
cx q[12],q[8];
u3(0,0,0.0981747731566429) q[8];
u3(0,0,0.196349546313286) q[12];
cx q[12],q[9];
u3(0,0,-0.196349546313286) q[9];
cx q[12],q[9];
u3(0,0,0.196349546313286) q[9];
u3(0,0,pi/8) q[12];
cx q[12],q[10];
u3(0,0,-pi/8) q[10];
cx q[12],q[10];
u3(0,0,pi/8) q[10];
u3(0,0,pi/4) q[12];
cx q[12],q[11];
u3(0,0,-pi/4) q[11];
cx q[12],q[11];
u3(0,0,pi/4) q[11];
u3(pi/2,0,pi) q[12];
u3(0,0,0.000191747603821568) q[13];
cx q[13],q[0];
u3(0,0,-0.000191747603821568) q[0];
cx q[13],q[0];
u3(0,0,0.000191747603821568) q[0];
u3(0,0,0.000383495207643136) q[13];
cx q[13],q[1];
u3(0,0,-0.000383495207643136) q[1];
cx q[13],q[1];
u3(0,0,0.000383495207643136) q[1];
u3(0,0,0.000766990415286273) q[13];
cx q[13],q[2];
u3(0,0,-0.000766990415286273) q[2];
cx q[13],q[2];
u3(0,0,0.000766990415286273) q[2];
u3(0,0,0.00153398083057255) q[13];
cx q[13],q[3];
u3(0,0,-0.00153398083057255) q[3];
cx q[13],q[3];
u3(0,0,0.00153398083057255) q[3];
u3(0,0,0.00306796166114509) q[13];
cx q[13],q[4];
u3(0,0,-0.00306796166114509) q[4];
cx q[13],q[4];
u3(0,0,0.00306796166114509) q[4];
u3(0,0,0.00613592332229018) q[13];
cx q[13],q[5];
u3(0,0,-0.00613592332229018) q[5];
cx q[13],q[5];
u3(0,0,0.00613592332229018) q[5];
u3(0,0,0.0122718466445804) q[13];
cx q[13],q[6];
u3(0,0,-0.0122718466445804) q[6];
cx q[13],q[6];
u3(0,0,0.0122718466445804) q[6];
u3(0,0,0.0245436932891607) q[13];
cx q[13],q[7];
u3(0,0,-0.0245436932891607) q[7];
cx q[13],q[7];
u3(0,0,0.0245436932891607) q[7];
u3(0,0,0.0490873865783215) q[13];
cx q[13],q[8];
u3(0,0,-0.0490873865783215) q[8];
cx q[13],q[8];
u3(0,0,0.0490873865783215) q[8];
u3(0,0,0.0981747731566429) q[13];
cx q[13],q[9];
u3(0,0,-0.0981747731566429) q[9];
cx q[13],q[9];
u3(0,0,0.0981747731566429) q[9];
u3(0,0,0.196349546313286) q[13];
cx q[13],q[10];
u3(0,0,-0.196349546313286) q[10];
cx q[13],q[10];
u3(0,0,0.196349546313286) q[10];
u3(0,0,pi/8) q[13];
cx q[13],q[11];
u3(0,0,-pi/8) q[11];
cx q[13],q[11];
u3(0,0,pi/8) q[11];
u3(0,0,pi/4) q[13];
cx q[13],q[12];
u3(0,0,-pi/4) q[12];
cx q[13],q[12];
u3(0,0,pi/4) q[12];
u3(pi/2,0,pi) q[13];
u3(0,0,9.58738019107841e-05) q[14];
cx q[14],q[0];
u3(0,0,-9.58738019107841e-05) q[0];
cx q[14],q[0];
u3(0,0,9.58738019107841e-05) q[0];
u3(0,0,0.000191747603821568) q[14];
cx q[14],q[1];
u3(0,0,-0.000191747603821568) q[1];
cx q[14],q[1];
u3(0,0,0.000191747603821568) q[1];
u3(0,0,0.000383495207643136) q[14];
cx q[14],q[2];
u3(0,0,-0.000383495207643136) q[2];
cx q[14],q[2];
u3(0,0,0.000383495207643136) q[2];
u3(0,0,0.000766990415286273) q[14];
cx q[14],q[3];
u3(0,0,-0.000766990415286273) q[3];
cx q[14],q[3];
u3(0,0,0.000766990415286273) q[3];
u3(0,0,0.00153398083057255) q[14];
cx q[14],q[4];
u3(0,0,-0.00153398083057255) q[4];
cx q[14],q[4];
u3(0,0,0.00153398083057255) q[4];
u3(0,0,0.00306796166114509) q[14];
cx q[14],q[5];
u3(0,0,-0.00306796166114509) q[5];
cx q[14],q[5];
u3(0,0,0.00306796166114509) q[5];
u3(0,0,0.00613592332229018) q[14];
cx q[14],q[6];
u3(0,0,-0.00613592332229018) q[6];
cx q[14],q[6];
u3(0,0,0.00613592332229018) q[6];
u3(0,0,0.0122718466445804) q[14];
cx q[14],q[7];
u3(0,0,-0.0122718466445804) q[7];
cx q[14],q[7];
u3(0,0,0.0122718466445804) q[7];
u3(0,0,0.0245436932891607) q[14];
cx q[14],q[8];
u3(0,0,-0.0245436932891607) q[8];
cx q[14],q[8];
u3(0,0,0.0245436932891607) q[8];
u3(0,0,0.0490873865783215) q[14];
cx q[14],q[9];
u3(0,0,-0.0490873865783215) q[9];
cx q[14],q[9];
u3(0,0,0.0490873865783215) q[9];
u3(0,0,0.0981747731566429) q[14];
cx q[14],q[10];
u3(0,0,-0.0981747731566429) q[10];
cx q[14],q[10];
u3(0,0,0.0981747731566429) q[10];
u3(0,0,0.196349546313286) q[14];
cx q[14],q[11];
u3(0,0,-0.196349546313286) q[11];
cx q[14],q[11];
u3(0,0,0.196349546313286) q[11];
u3(0,0,pi/8) q[14];
cx q[14],q[12];
u3(0,0,-pi/8) q[12];
cx q[14],q[12];
u3(0,0,pi/8) q[12];
u3(0,0,pi/4) q[14];
cx q[14],q[13];
u3(0,0,-pi/4) q[13];
cx q[14],q[13];
u3(0,0,pi/4) q[13];
u3(pi/2,0,pi) q[14];