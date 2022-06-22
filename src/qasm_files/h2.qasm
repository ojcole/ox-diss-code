OPENQASM 2.0;
include "qelib1.inc";

// sqrt(X)
gate sx a { sdg a; h a; sdg a; }
// inverse sqrt(X)
gate sxdg a { s a; h a; s a; }

gate pauli_t_two a,b { cx a, b; t b; cx a, b; }
gate pauli_t_four a,b,c,d { cx a, b; cx b, c; cx c, d; t d; cx c, d; cx b, c; cx a, b; }

qreg q[4];

x q[0];
x q[2];

// XYII
h q[0];
sxdg q[1];
pauli_t_two q[0], q[1];
sx q[1];
h q[0];

// YXII
h q[1];
sxdg q[0];
pauli_t_two q[0], q[1];
sx q[0];
h q[1];


// IIXY
h q[2];
sxdg q[3];
pauli_t_two q[2], q[3];
sx q[3];
h q[2];

// IIYX
h q[3];
sxdg q[2];
pauli_t_two q[2], q[3];
sx q[2];
h q[3];

// XYYY
h q[0];
sxdg q[1];
sxdg q[2];
sxdg q[3];
pauli_t_four q[0], q[1], q[2], q[3];
h q[0];
sx q[1];
sx q[2];
sx q[3];

// YXYY
sxdg q[0];
h q[1];
sxdg q[2];
sxdg q[3];
pauli_t_four q[0], q[1], q[2], q[3];
sx q[0];
h q[1];
sx q[2];
sx q[3];

// YYXY
sxdg q[0];
sxdg q[1];
h q[2];
sxdg q[3];
pauli_t_four q[0], q[1], q[2], q[3];
sx q[0];
sx q[1];
h q[2];
sx q[3];

// YYYX
sxdg q[0];
sxdg q[1];
sxdg q[2];
h q[3];
pauli_t_four q[0], q[1], q[2], q[3];
sx q[0];
sx q[1];
sx q[2];
h q[3];

// YXXX
sxdg q[0];
h q[1];
h q[2];
h q[3];
pauli_t_four q[0], q[1], q[2], q[3];
sx q[0];
h q[1];
h q[2];
h q[3];

// XYXX
h q[0];
sxdg q[1];
h q[2];
h q[3];
pauli_t_four q[0], q[1], q[2], q[3];
h q[0];
sx q[1];
h q[2];
h q[3];

// XXYX
h q[0];
h q[1];
sxdg q[2];
h q[3];
pauli_t_four q[0], q[1], q[2], q[3];
h q[0];
h q[1];
sx q[2];
h q[3];

// XXXY
h q[0];
h q[1];
h q[2];
sxdg q[3];
pauli_t_four q[0], q[1], q[2], q[3];
h q[0];
h q[1];
h q[2];
sx q[3];