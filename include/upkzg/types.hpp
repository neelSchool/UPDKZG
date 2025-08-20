#pragma once
#include <vector>
#include <cstdint>

namespace upkzg {

using Fr = /* alias for scalar type from blst/libff */;
using G1 = /* group element type (G1) */;
using G2 = /* group element type (G2) */;

struct SRS {
    std::vector<G1> g1_powers;  // g^{α^0...α^d}
    std::vector<G2> g2_powers;  // h^{α^0...α^d}  (depending on layout)
    G1 g; G2 h;                 // base generators
    // Optional metadata: max_degree, version, etc.
};

struct Commit {
    G1 c;
};

struct EvalProof {
    Fr z;
    Fr y;
    G1 pi;
};

struct UpdateProof {
    G1 g_beta;   // g^beta or similar
    G2 h_beta;   // h^beta (if needed)
    G1 relation; // optional small relation element
    // struct content matches the pairing checks you choose
};
}
