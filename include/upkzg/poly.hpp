#pragma once
#include "types.hpp"

namespace upkzg {
class Polynomial {
public:
    Polynomial() = default;
    explicit Polynomial(std::vector<Fr> coeffs);
    size_t degree() const;
    Fr eval(const Fr &x) const;
    Polynomial add(const Polynomial &other) const;
    Polynomial sub(const Polynomial &other) const;
    Polynomial mul(const Polynomial &other) const;
    // (X - z) division: quotient = (f - y) / (X - z)
    Polynomial quotient_div_x_minus_z(const Fr &z, const Fr &y) const;
    const std::vector<Fr>& coeffs() const;
};
}
