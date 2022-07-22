OPENQASM 2.0;
include "qelib1.inc";

// sqrt(X)
gate sx a { sdg a; h a; sdg a; }
// inverse sqrt(X)
gate sxdg a { s a; h a; s a; }

gate pauli_t_two a,b { cx a, b; t b; cx a, b; }
gate pauli_t_three a,b,c { cx a, b; cx b, c; t c; cx b, c; cx a, b; }
gate pauli_t_four a,b,c,d { cx a, b; cx b, c; cx c, d; t d; cx c, d; cx b, c; cx a, b; }

qreg q[5];

// IXZIZ
h q[1];
pauli_t_three q[1],q[2],q[4];
h q[1];

// IYIZY
sx q[1];
sx q[4];
pauli_t_three q[1],q[3],q[4];
sxdg q[1];
sxdg q[4];

// XXIYI
h q[0];
h q[1];
sx q[3];
pauli_t_three q[0],q[1],q[3];
h q[0];
h q[1];
sxdg q[3];

// YYXII
sx q[0];
sx q[1];
h q[2];
pauli_t_three q[0],q[1],q[2];
sxdg q[0];
sxdg q[1];
h q[2];

// ZIYXX
sx q[2];
h q[3];
h q[4];
pauli_t_four q[0],q[2],q[3],q[4];
sxdg q[2];
h q[3];
h q[4];

// ZXIZZ
h q[1];
pauli_t_four q[0],q[1],q[3],q[4];
h q[1];

// ZYZIZ
sx q[1];
sx q[4];
pauli_t_four q[0],q[1],q[2],q[4];
sxdg q[1];
sxdg q[4];