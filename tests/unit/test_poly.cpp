TEST(PolyTest, EvalAndQuotient) {
    Polynomial p({2,3,1}); // 2 + 3x + 1x^2
    Fr z = Fr::from_uint64(1);
    Fr y = p.eval(z);
    EXPECT_EQ(y, Fr::from_uint64(6));
    Polynomial q = p.quotient_div_x_minus_z(z, y);
    // q should be 1x + 2
    ASSERT_EQ(q.coeffs()[0], Fr::from_uint64(2));
    ASSERT_EQ(q.coeffs()[1], Fr::from_uint64(1));
}
