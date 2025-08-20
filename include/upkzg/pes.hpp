#pragma once
#include <vector>
#include <libff/algebra/curves/bls12_381/bls12_381_pp.hpp>

namespace kupcom {

// Minimal PES (Polynomial Encoding Scheme) that appends ℓ random tail coefficients.
// Correctness + bounded independence (simple model for tests). See paper Def. 2. :contentReference[oaicite:6]{index=6}
struct PES {
  using pp = libff::bls12_381_pp;
  using Fr = libff::Fr<pp>;

  static std::vector<Fr> Enc(const std::vector<Fr>& w, size_t n, size_t ell, const std::vector<Fr>& rho) {
    if (w.size() != n || rho.size() != ell) throw std::runtime_error("bad PES input sizes");
    std::vector<Fr> f; f.reserve(n + ell);
    for (size_t i = 0; i < n; ++i) f.push_back(w[i]);
    for (size_t j = 0; j < ell; ++j) f.push_back(rho[j]);
    return f;
  }

  static std::vector<Fr> Dec(const std::vector<Fr>& f, size_t n, size_t ell) {
    if (f.size() != n + ell) throw std::runtime_error("bad PES sizes");
    return std::vector<Fr>(f.begin(), f.begin() + n);
  }
};

} // namespace kupcom
