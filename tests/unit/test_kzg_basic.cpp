#include <gtest/gtest.h>
#include "upkzg/srs.hpp"
#include "upkzg/kzg.hpp"
#include "upkzg/poly.hpp"

using namespace upkzg;

static std::mt19937_64 test_rng(123456);

TEST(KZGBasic, CommitEvalVerify) {
    // Arrange
    SRS srs = KGen(16, [](){ return Fr::random(test_rng); });
    Polynomial f({Fr::from_uint64(1), Fr::from_uint64(2), Fr::from_uint64(3)});

    // Act
    Commit c = Commit(srs, f);
    Fr z = Fr::from_uint64(7);
    EvalProof proof = EvalProve(srs, f, z);

    // Assert
    EXPECT_TRUE(EvalVerify(srs, c, proof));
}

TEST(KZGBasic, EvalTamperFails) {
    SRS srs = KGen(8, [](){ return Fr::random(test_rng); });
    Polynomial f({Fr::from_uint64(2), Fr::from_uint64(1)});

    Commit c = Commit(srs, f);
    Fr z = Fr::from_uint64(3);
    EvalProof proof = EvalProve(srs, f, z);

    // Tamper y
    proof.y = Fr::from_uint64(999);
    EXPECT_FALSE(EvalVerify(srs, c, proof));
}
