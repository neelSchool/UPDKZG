#pragma once
#include <vector>
#include <stdexcept>
#include <libff/algebra/curves/bls12_381/bls12_381_pp.hpp>

namespace kupcom {

using pp = libff::bls12_381_pp;
using Fr = libff::Fr<pp>;
using G1 = libff::G1<pp>;
using G2 = libff::G2<pp>;
using GT = libff::GT<pp>;

struct CRS {
  std::vector<G1> g1_pows; // [0..D], g^{α^i}
  G2 h_tau;                // h^{α}
  G1 g1_gen;               // g
  G2 h_gen;                // h
  size_t D = 0;
};

struct UpdateProof {
  G1 g_beta; // g^β
  G2 h_beta; // h^β
};

struct Commitment {
  G1 C;         // commitment in G1
  size_t deg;   // degree used
};

struct EvalProof {
  G1 pi;  // g^{q(αβ)}
  Fr z;   // evaluation point
  Fr y;   // claimed value f(z)
};

class KZG {
public:
  static void init();
  static CRS kgen(size_t D);

  static std::pair<CRS, UpdateProof> update(const CRS& ck, const Fr& beta);

  static bool verify_update(const CRS& prev, const CRS& next, const UpdateProof& pi);

  static Commitment commit(const CRS& ck, const std::vector<Fr>& coeffs);

  static EvalProof eval(const CRS& ck,
                        const Commitment& com,
                        const std::vector<Fr>& coeffs,
                        const Fr& z);

  static bool check(const CRS& ck, const Commitment& com, const EvalProof& pf);

  // utilities
  static Fr eval_poly(const std::vector<Fr>& f, const Fr& z);
  static std::vector<Fr> quotient(const std::vector<Fr>& f, const Fr& z, const Fr& y);
};

} // namespace kupcom
