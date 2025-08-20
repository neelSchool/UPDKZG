#pragma once
#include "types.hpp"
#include "srs.hpp"
#include "poly.hpp"

namespace upkzg {

// Commit to polynomial using multi-exponentiation on SRS
Commit Commit(const SRS &srs, const Polynomial &f);

// Prover: compute evaluation proof at z
EvalProof EvalProve(const SRS &srs, const Polynomial &f, const Fr &z);

// Verifier: check evaluation proof
bool EvalVerify(const SRS &srs, const Commit &c, const EvalProof &proof);

// Update SRS (performed by an updater who knows β)
SRS UpdateSRS(const SRS &old_srs, const Fr &beta, UpdateProof &out_proof);

// Verify update correctness
bool VerifyUpdate(const SRS &old_srs, const SRS &new_srs, const UpdateProof &proof);

}
