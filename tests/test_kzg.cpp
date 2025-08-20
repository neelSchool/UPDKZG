#include <gtest/gtest.h>
#include "kupcom/kzg.hpp"
#include "kupcom/pes.hpp"

using namespace kupcom;

TEST(KZG, KGenCommitEvalCheck) {
  KZG::init();
  const size_t D = 16;
  CRS ck = KZG::kgen(D);

  // Simple polynomial f(X) = 3 + 2X + X^2
  std::vector<Fr> f(3);
  f[0] = Fr("3"); f[1] = Fr("2"); f[2] = Fr("1");

  auto com = KZG::commit(ck, f);
  Fr z = Fr("5");
  auto pf = KZG::eval(ck, com, f, z);
  ASSERT_TRUE(KZG::check(ck, com, pf));

  // Wrong y should fail
  auto bad = pf; bad.y = bad.y + Fr::one();
  ASSERT_FALSE(KZG::check(ck, com, bad));
}

TEST(KZG, UpdateAndVerify) {
  KZG::init();
  const size_t D = 32;
  CRS ck = KZG::kgen(D);

  // Update SRS with random β
  Fr beta = Fr::random_element();
  auto [ck2, pi] = KZG::update(ck, beta);
  ASSERT_TRUE(KZG::verify_update(ck, ck2, pi));

  // Commit before and after update; same polynomial still verifies against the updated key w/ fresh proof
  std::vector<Fr> f = {Fr("7"), Fr("0"), Fr("4")}; // 7 + 4 X^2
  auto c1 = KZG::commit(ck, f);
  auto c2 = KZG::commit(ck2, f);
  Fr z = Fr("9");

  auto p1 = KZG::eval(ck, c1, f, z);
  auto p2 = KZG::eval(ck2, c2, f, z);

  ASSERT_TRUE(KZG::check(ck, c1, p1));
  ASSERT_TRUE(KZG::check(ck2, c2, p2));

  // Cross-check should fail: proof under ck shouldn't verify under ck2
  ASSERT_FALSE(KZG::check(ck2, c1, p1));
  ASSERT_FALSE(KZG::check(ck,  c2, p2));
}

TEST(PES, EncodeDecode) {
  KZG::init();
  std::vector<Fr> w = {Fr("1"), Fr("2"), Fr("3")};
  std::vector<Fr> rho = {Fr::random_element(), Fr::random_element()};
  auto f = PES::Enc(w, 3, 2, rho);
  auto w2 = PES::Dec(f, 3, 2);
  ASSERT_EQ(w2.size(), w.size());
  for (size_t i = 0; i < w.size(); ++i) ASSERT_EQ(w2[i], w[i]);
}
