#include <iostream>
#include <vector>
#include <libff/algebra/curves/bls12_381/bls12_381_pp.hpp>
#include "upkzg/kzg.hpp"

using namespace upkzg;
using namespace std;

int main() {
    // Step 1: init & setup
    KZG::init();
    const size_t D = 8;
    CRS ck = KZG::kgen(D);
    cout << "[+] Generated CRS with D=" << D << "\n";

    // Polynomial f(x) = 2 + 3x + x^2
    vector<Fr> f = { Fr("2"), Fr("3"), Fr("1") };
    Fr z = Fr("5");

    // Step 2: commit, prove, verify
    auto com = KZG::commit(ck, f);
    auto pf = KZG::eval(ck, com, f, z);
    bool ok = KZG::check(ck, com, pf);

    cout << "Proof before update: " << (ok ? "PASS" : "FAIL") << "\n";

    // Step 3: update CRS
    Fr beta = Fr::random_element();
    auto [ck2, upd_pf] = KZG::update(ck, beta);
    cout << "Updated CRS with beta\n";

    bool update_ok = KZG::verify_update(ck, ck2, upd_pf);
    cout << "Update proof: " << (update_ok ? "PASS" : "FAIL") << "\n";

    // Step 4: recompute proof under new CRS
    auto com2 = KZG::commit(ck2, f);
    auto pf2  = KZG::eval(ck2, com2, f, z);
    bool ok2 = KZG::check(ck2, com2, pf2);

    cout << "Proof after update: " << (ok2 ? "PASS" : "FAIL") << "\n";

    // Cross-check: old proof under new CRS should fail
    bool old_ok2 = KZG::check(ck2, com, pf);
    cout << "Old proof under updated CRS: " << (old_ok2 ? "INCORRECT PASS" : "correctly FAIL") << "\n";

    return 0;
}
// This example demonstrates the KZG commitment scheme, polynomial evaluation, and update functionality.