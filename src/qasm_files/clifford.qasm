z OPENQASM 2.0;
include "qelib1.inc";

qreg qubits[2];

h qubits[0];
cx qubits[0], qubits[1];
s qubits[0];

// qreg anc[2];

// cx qubits, anc;
// h anc;
// s anc[1];
// cx anc[0], anc[1];
// cx anc[1], anc[0];